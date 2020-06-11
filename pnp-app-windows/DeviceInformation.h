#pragma once

#ifndef DEVICE_INFO
#define DEVICE_INFO

#include <stdio.h>

#ifdef _WIN32

#include <windows.h>

#else
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h> 
#include <ctype.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/statvfs.h>

typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef int32_t LONG;
typedef uint16_t UINT16;
typedef unsigned char UCHAR;
typedef uint64_t ULONG64;
typedef int64_t LONGLONG;
typedef unsigned char BYTE;
typedef BYTE *LPBYTE;
typedef int BOOL;
#define FALSE 0
#define TRUE 1
typedef unsigned int UINT;

typedef union _LARGE_INTEGER {
  struct {
    DWORD LowPart;
    LONG  HighPart;
  };
  struct {
    DWORD LowPart;
    LONG  HighPart;
  } u;
  LONGLONG QuadPart;
} LARGE_INTEGER;

#endif

#pragma pack(push) 
#pragma pack(1)

typedef struct _SMBIOSHEADER_
{
	BYTE Type;
	BYTE Length;
	WORD Handle;
} SMBIOSHEADER, * PSMBIOSHEADER;

typedef struct _RawSMBIOSData
{
	BYTE	Used20CallingMethod;
	BYTE	SMBIOSMajorVersion;
	BYTE	SMBIOSMinorVersion;
	BYTE	DmiRevision;
	DWORD	Length;
	LPBYTE	SMBIOSTableData;
} RawSMBIOSData, * PRawSMBIOSData;

typedef struct _TYPE_0_ {
	SMBIOSHEADER	Header;
	UCHAR	Vendor;
	UCHAR	Version;
	UINT16	StartingAddrSeg;
	UCHAR	ReleaseDate;
	UCHAR	ROMSize;
	ULONG64 Characteristics;
	UCHAR	Extension[2]; // spec. 2.3
	UCHAR	MajorRelease;
	UCHAR	MinorRelease;
	UCHAR	ECFirmwareMajor;
	UCHAR	ECFirmwareMinor;
} BIOSInfo, * PBIOSInfo;

typedef struct _TYPE_1_ {
	SMBIOSHEADER	Header;
	UCHAR	Manufacturer;
	UCHAR	ProductName;
	UCHAR	Version;
	UCHAR	SN;
	UCHAR	UUID[16];
	UCHAR	WakeUpType;
	UCHAR	SKUNumber;
	UCHAR	Family;
} SystemInfo, * PSystemInfo;

typedef struct _TYPE_4_ {
	SMBIOSHEADER	Header;
	UCHAR	SocketDesignation;
	UCHAR	ProcessorType;
	UCHAR	ProcessorFamily;
	UCHAR	ProcessorManufacturer;
	ULONG64	ProcessorID;
	UCHAR	ProcessorRevision;
	UCHAR	Voltage;
	WORD	ExternalClock;
	WORD    MaxSpeed;
	WORD    CurrentSpeed;
	UCHAR   Status;
	UCHAR   ProcessorUpgrade;
	WORD    L1CacheHandle;
	WORD    L2CacheHandle;
	WORD    L3CacheHandle;
	UCHAR   SerialNumber;
	UCHAR   AssetTag;
	UCHAR   PartNumber;
	UCHAR   CoreCount;
	UCHAR   CoreEnabled;
	UCHAR   ThreadCOunt;
	WORD    ProcessorCharacteristics;
	WORD    ProcessorFamily2;
	WORD    CoreCount2;
	WORD    CoreEnabled2;
	WORD    ThreadCount2;
} ProcessorInfo, * PProcessorInfo;

typedef struct _TYPE_17_ {
	SMBIOSHEADER	Header;
	WORD  	PhysicalMemoryArrayHandle;
	WORD	MemoryErrorInformationHandle;
	WORD	TotalWidth;
	WORD	DataWidth;
	WORD	Size;
	UCHAR	FormFactor;
	UCHAR	DeviceSet;
	UCHAR	DeviceLocator;
	UCHAR	BankLocator;
	UCHAR	MemoryType;
	WORD	TypeDetail;
	WORD	Speed;
	UCHAR	Manufacturer;
	UCHAR	SerialNumber;
	UCHAR	AssetTag;
	UCHAR	PartNumber;
	UCHAR	Attributes;
	DWORD	ExtendedSize;
	WORD	ConfiguredMemorySpeed;
	WORD	MinimumVoltage;
	WORD	MaximumVoltage;
	WORD	ConfiguredVoltage;
	UCHAR	MemoryTechnology;
	WORD	MemoryOperatingModeCapacity;
	UCHAR	FirmwareVersion;
	WORD	ModuleManufacturerID;
	WORD	ModuleProductID;
	WORD	MemorySubsystemControllerManufacturerID;
	WORD	MemorySubsystemControllerProductsID;
	ULONG64 NonVolatileSize;
	ULONG64 VolatileSize;
	ULONG64 CacheSize;
	ULONG64 LogicalSize;
	DWORD   ExtendedSpeed;
	DWORD   ExtendedConfiguredMemorySpeed;
} MemoryDevice, * PMemoryDevice;

typedef struct _TYPE_19_ {
	SMBIOSHEADER	Header;
	WORD  	StartingAddress;
	DWORD	EndingAddress;
	WORD	MemoryArrayHandle;
	UCHAR	PartitionWidth;
	ULONG64 ExtendedStartingAddress;
	ULONG64	ExtendedEndingAddress;
} MemoryArrayMappedAddress, * PMemoryArrayMappedAddress;

BOOL GetManufacturer(char* bufffer, size_t buffer_size);
BOOL GetModel(char* bufffer, size_t buffer_size);
BOOL GetSwVersion(char* bufffer, size_t buffer_size);
BOOL GetOsName(char* bufffer, size_t buffer_size);
BOOL GetProcessorArchitecture(char* bufffer, size_t buffer_size);
BOOL GetProcessorManufacturer(char* bufffer, size_t buffer_size);
long GetTotalStorage();
ULONG64 GetTotalMemory();

#endif