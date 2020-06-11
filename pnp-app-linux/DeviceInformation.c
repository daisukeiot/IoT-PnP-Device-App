#include "DeviceInformation.h"

PRawSMBIOSData g_smbios = NULL;

const char Version_String[] = "1.0";

#ifdef _WIN32
static const char* FindString(const char* table_string, UINT string_id)
{

    if (0 == string_id || 0 == *table_string)
        return '\0';

    while (--string_id)
    {
        table_string += strlen((char*)table_string) + 1;
    }
    return table_string;
}

LPBYTE GetSMBIOS(int table_id)
{
//    /sys/devices/virtual/dmi/id
    DWORD table_size;
    LPBYTE pSMBOIS = NULL;
    LPBYTE pTable = NULL;
    const BYTE byteSignature[] = { 'B', 'M', 'S', 'R' };
    const DWORD Signature = *((DWORD*)byteSignature);

    if (g_smbios == NULL)
    {
        table_size = GetSystemFirmwareTable(Signature, 0, NULL, 0);

        pSMBOIS = malloc(table_size);

        if (GetSystemFirmwareTable(Signature, 0, pSMBOIS, table_size) == table_size)
        {
            PRawSMBIOSData pDMIData = (PRawSMBIOSData)pSMBOIS;
            printf("SMBIOS version : %d.%d\r\n", pDMIData->SMBIOSMajorVersion, pDMIData->SMBIOSMinorVersion);
            printf("DMI Revision   : %x\r\n", pDMIData->DmiRevision);
            printf("Total length   : %d\r\n", pDMIData->Length);

            g_smbios = (PRawSMBIOSData)pSMBOIS;
        }
        else
        {
            free(pSMBOIS);
            pSMBOIS = NULL;
        }
    }

    if (g_smbios)
    {
        size_t offset = 0;
        size_t table_size = 0;
        LPBYTE p_current = (LPBYTE)&g_smbios->SMBIOSTableData;
        LPBYTE p_TableStart = p_current;
        PSMBIOSHEADER pHeader;

        while (offset < g_smbios->Length)
        {
            pHeader = (PSMBIOSHEADER)p_current;
            int i;

            if (pHeader->Type == 127 && pHeader->Length == 4)
            {
                break;
            }

            offset += pHeader->Length;
            p_current = p_TableStart + offset;

            for (i = 0; ; i++)
            {
                if (*(p_current + i) == 0 && *(p_current + i + 1) == 0)
                {
                    table_size = i + 2;
                    offset += table_size;
                    break;
                }
            }

            if (pHeader->Type == table_id)
            {
                size_t size = table_size + pHeader->Length;
                pTable = malloc(size);
                if (pTable)
                {
                    memcpy(pTable, pHeader, size);
                    break;
                }
            }
            p_current = p_TableStart + offset;

        }
    }
    return pTable;
}
#else

BOOL IsFileExist(const char *fileName)
{
    if( access(fileName, F_OK ) == 0)
    {
        return TRUE;
    } 
    return FALSE;
}

void TrimString(char* Buffer)
{
    char *ptr;
    char szBuffer[512];
    size_t length = strlen(Buffer);

    strcpy(szBuffer, Buffer);

    ptr = szBuffer;

    while(*ptr && ((*ptr == '"') || (isspace(*ptr) || (*ptr == ':'))))
    {
        ptr++;
    }

    length = strlen(ptr);

    while((length > 0) && ((ptr[length-1] == '\n') || (ptr[length-1] == '\r') || (ptr[length-1] == '"') || isspace(ptr[length-1]) || ptr[length-1] == '.'))
    {
        ptr[length - 1] ='\0';
        length--;
    }

    if (length != strlen(Buffer))
    {
        strcpy(Buffer, ptr);
    }
}

/*
 Read BIOS data from files in /sys/devices/virtual/dmi/id
*/
BOOL FindString(char* Buffer, int Buffer_size, const char* fileName)
{
    FILE *file;
    char *line = NULL;
    char *ptr;

    memset(Buffer, 0, Buffer_size);

    if (!IsFileExist(fileName))
    {
        return FALSE;
    }

    file = fopen(fileName, "r");

    if (file)
    {
        if(fgets(Buffer, Buffer_size, file) != NULL) {
            TrimString(Buffer);
            printf("FindString %lu %s\r\n", strlen(Buffer), Buffer);
        }
        fclose(file);
    }
    return TRUE;
}
#endif

BOOL GetManufacturer(char* Buffer, size_t Buffer_size)
{
#ifdef _WIN32
    PBIOSInfo pTable = NULL;
    const char* p_str;
    pTable = (PBIOSInfo)GetSMBIOS(0);

    if (pTable)
    {
        p_str = FindString((LPBYTE)pTable + pTable->Header.Length, pTable->Vendor);
        snprintf(Buffer, Buffer_size, "%s", p_str);
        free(pTable);
        return TRUE;
    }
    else {
        snprintf(Buffer, Buffer_size, "%s", "Unknown");
        return FALSE;
    }
#else
    char szFile[] = "/sys/devices/virtual/dmi/id/bios_vendor";
    return FindString(Buffer, Buffer_size, szFile);
#endif

}

BOOL GetModel(char* Buffer, size_t Buffer_size)
{
#ifdef _WIN32
    PSystemInfo pTable = NULL;
    const char* p_str;
    pTable = (PSystemInfo)GetSMBIOS(1);

    if (pTable)
    {
        p_str =  FindString((LPBYTE)pTable + pTable->Header.Length, pTable->Family);
        snprintf(Buffer, Buffer_size, "%s", p_str);
        free(pTable);
        return TRUE;

    }
    else {
        snprintf(Buffer, Buffer_size, "%s", "Unknown");
        return FALSE;
    }
#else
    const char szFile[] = "/sys/devices/virtual/dmi/id/product_name";
    return FindString(Buffer, Buffer_size, szFile);
#endif

}

BOOL GetSwVersion(char* Buffer, size_t Buffer_size)
{
    snprintf(Buffer, Buffer_size, "%s", Version_String);
    return TRUE;
}

BOOL GetOsName(char* Buffer, size_t Buffer_size)
{

#ifdef _WIN32
    HKEY hKey;
    DWORD dwBufferSize = (DWORD)Buffer_size;
    DWORD dwType = 0;
    DWORD dwRet;

    dwRet = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows NT\\CurrentVersion", 0, KEY_QUERY_VALUE, &hKey);
    if (dwRet == ERROR_SUCCESS)
    {
        dwRet = RegQueryValueExA(hKey, "ProductName", 0, &dwType, (LPBYTE)Buffer, &dwBufferSize);
        if (dwRet != ERROR_SUCCESS)
        {
            printf("Cannot Access Registry %d\r\n", HRESULT_FROM_WIN32(dwRet));
        }

        RegCloseKey(hKey);
        return TRUE;
    }
    else {
        printf("Cannot Access Registry %d\r\n", GetLastError());
    }
    snprintf(Buffer, Buffer_size, "%s", "Unknown");
    return FALSE;

#else
    FILE *file;
    char* ptr;
    char szTemp[256];
    const char fileName[] = "/etc/lsb-release"; 

    memset(Buffer, 0, Buffer_size);

    if (!IsFileExist(fileName))
    {
        return FALSE;
    }

    file = fopen(fileName, "r");

    if (file)
    {
        while (fgets(szTemp, sizeof(szTemp), file) != NULL) {
            if (!(strncmp(szTemp, "DISTRIB_DESCRIPTION=", strlen("DISTRIB_DESCRIPTION="))))
            {
                ptr = szTemp + strlen("DISTRIB_DESCRIPTION=");
                TrimString(ptr);
                strcpy(Buffer, ptr);
                break;
            }
        }
        fclose(file);
    }
    return TRUE;
#endif

}

BOOL GetProcessorArchitecture(char* Buffer, size_t Buffer_size)
{
#ifdef _WIN32
    SYSTEM_INFO si;

    GetSystemInfo(&si);

    switch (si.wProcessorArchitecture)
    {
    case PROCESSOR_ARCHITECTURE_AMD64:
        snprintf(Buffer, Buffer_size, "%s", "x64");
        break;
    case PROCESSOR_ARCHITECTURE_ARM:
        snprintf(Buffer, Buffer_size, "%s", "ARM");
        break;
    case PROCESSOR_ARCHITECTURE_ARM64:
        snprintf(Buffer, Buffer_size, "%s", "ARM64");
        break;
    case PROCESSOR_ARCHITECTURE_INTEL:
        snprintf(Buffer, Buffer_size, "%s", "x86");
        break;
    case PROCESSOR_ARCHITECTURE_UNKNOWN:
        snprintf(Buffer, Buffer_size, "%s", "Unknown");
        break;
    }

    return TRUE;
#else
    struct utsname unameData;
    uname(&unameData);
    strcpy(Buffer, unameData.machine);
    return TRUE;
#endif
}

BOOL GetProcessorManufacturer(char* Buffer, size_t Buffer_size)
{
#ifdef _WIN32
    PProcessorInfo pTable = NULL;
    const char* p_str;
    pTable = (PProcessorInfo)GetSMBIOS(4);

    if (pTable)
    {
        p_str = FindString((LPBYTE)pTable + pTable->Header.Length, pTable->ProcessorManufacturer);

        snprintf(Buffer, Buffer_size, "%s", p_str);
        free(pTable);
        return TRUE;
    }
    else {
        snprintf(Buffer, Buffer_size, "%s", "Unknown");
        return FALSE;
    }
#else
    FILE *file;
    char szTemp[256];
    const char fileName[] = "/proc/cpuinfo"; 

    memset(Buffer, 0, Buffer_size);

    if (!IsFileExist(fileName))
    {
        return FALSE;
    }

    file = fopen(fileName, "r");
    if (file)
    {
        while (fgets(szTemp, sizeof(szTemp), file) != NULL) {

            if (!(strncmp(szTemp, "vendor_id", strlen("vendor_id"))))
            {
                char *ptr = szTemp + strlen("vendor_id");
                TrimString(ptr);
                strcpy(Buffer, ptr);
                break;
            }
        }
        fclose(file);
    }
    return TRUE;
#endif
}

long GetTotalStorage()
{
    LARGE_INTEGER size;

    size.QuadPart = -1;
#ifdef _WIN32
    
    size.QuadPart = -1;

    HANDLE hDisk;

    hDisk = CreateFile("\\\\.\\PhysicalDrive0",
                        0,
                        FILE_SHARE_READ | FILE_SHARE_WRITE,
                        NULL,
                        OPEN_EXISTING,
                        0,
                        NULL);

    if (hDisk != INVALID_HANDLE_VALUE)
    {
        DISK_GEOMETRY_EX geo;

        DWORD dwSize;
        if (DeviceIoControl(hDisk,
            IOCTL_DISK_GET_DRIVE_GEOMETRY_EX,
            NULL,
            0,
            &geo,
            sizeof(geo),
            &dwSize,
            NULL))
        {
            size = geo.DiskSize;
            size.QuadPart = size.QuadPart / 1024;
        }
    } else {
        printf("Err : Failed to open handle to Disk 0.  Err %d\r\n", GetLastError());
    }

    return (long)size.QuadPart;
#else
    struct statvfs buffer;
    int ret = statvfs(".", &buffer);

    if (ret == 0)
    {
        size.QuadPart = (double)(buffer.f_blocks * buffer.f_frsize);
    } else {
        printf("Err : statvfs failed.  Err %d\r\n", errno);
    }
    printf(" Total : %lu\r\n", size.QuadPart);
    return (long)(size.QuadPart / 1024);
#endif
}

ULONG64 GetTotalMemory()
{
    ULONG64 size = -1;
#ifdef _WIN32
    if (!GetPhysicallyInstalledSystemMemory(&size))
    {
        printf("Failed to get memory info.  %d\r\n", GetLastError());
    }

    return size;
#else
    FILE *file;
    char szTemp[256];
    const char fileName[] = "/proc/meminfo"; 

    if (!IsFileExist(fileName))
    {
        return FALSE;
    }

    file = fopen(fileName, "r");
    if (file)
    {
        while (fgets(szTemp, sizeof(szTemp), file) != NULL) {

            if (!(strncmp(szTemp, "MemTotal:", strlen("MemTotal:"))))
            {
                char *ptr = szTemp + strlen("MemTotal:");
                char *ptrTemp;

                TrimString(ptr);

                ptrTemp = ptr;

                while(*ptrTemp)
                {
                    if (isdigit(*ptrTemp))
                    {
                        ptrTemp++;
                    } else {
                        *ptrTemp = '\0';
                        size = atoi(ptr);
                        break;
                    }
                }
                break;
            }
        }
        fclose(file);
    }
    return size;

#endif
}
