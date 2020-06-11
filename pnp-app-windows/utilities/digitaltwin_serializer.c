/************************************************************************************************
 * This code was automatically generated by Digital Twin Code Generator tool 0.6.8.
 * Changes to this file may cause incorrect behavior and will be lost if the code is regenerated.
 *
 * Generated Date: 6/2/2020
 ***********************************************************************************************/

#include "digitaltwin_serializer.h"

//
// Serialize telemetry data
//

bool SensorTile_Box_SerializeTemperatureTelemetry(char * payloadBuffer, int size)
{
    if (payloadBuffer == NULL)
    {
        return false;
    }

    memset(payloadBuffer, 0, size);

    float temperature = SensorTile_Box_Telemetry_ReadTemperature();

    int neededSize = snprintf(NULL, 0, "%f", temperature);

    if (neededSize > size - 1)
    {
        LogError("Failed to build temperature payload string");
        return false;
    }
    else
    {
        snprintf(payloadBuffer, size, "%f", temperature);
    }

    return true;
}

bool SensorTile_Box_SerializePressureTelemetry(char * payloadBuffer, int size)
{
    if (payloadBuffer == NULL)
    {
        return false;
    }

    memset(payloadBuffer, 0, size);

    float pressure = SensorTile_Box_Telemetry_ReadPressure();

    int neededSize = snprintf(NULL, 0, "%f", pressure);

    if (neededSize > size - 1)
    {
        LogError("Failed to build pressure payload string");
        return false;
    }
    else
    {
        snprintf(payloadBuffer, size, "%f", pressure);
    }

    return true;
}

bool SensorTile_Box_SerializeHumidityTelemetry(char * payloadBuffer, int size)
{
    if (payloadBuffer == NULL)
    {
        return false;
    }

    memset(payloadBuffer, 0, size);

    float humidity = SensorTile_Box_Telemetry_ReadHumidity();

    int neededSize = snprintf(NULL, 0, "%f", humidity);

    if (neededSize > size - 1)
    {
        LogError("Failed to build humidity payload string");
        return false;
    }
    else
    {
        snprintf(payloadBuffer, size, "%f", humidity);
    }

    return true;
}

bool SensorTile_Box_SerializeAcceleroTelemetry(char * payloadBuffer, int size)
{
    if (payloadBuffer == NULL)
    {
        return false;
    }

    memset(payloadBuffer, 0, size);

    SensorTile_Box_ACCELERO accelero;
    SensorTile_Box_Telemetry_ReadAccelero(&accelero);

    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);

    json_object_set_number(root_object, "X", accelero.X);

    json_object_set_number(root_object, "Y", accelero.Y);

    json_object_set_number(root_object, "Z", accelero.Z);

    char * serializedString = json_serialize_to_string(root_value);

    int neededSize = (int)strlen(serializedString);
    if (serializedString == NULL || neededSize > size - 1)
    {
        LogError("Failed to build accelero payload string");
        return false;
    }
    else
    {
        memcpy(payloadBuffer, serializedString, neededSize);
        free(serializedString);
    }

    json_value_free(root_value);

    return true;
}

bool SensorTile_Box_SerializeGyroTelemetry(char * payloadBuffer, int size)
{
    if (payloadBuffer == NULL)
    {
        return false;
    }

    memset(payloadBuffer, 0, size);

    SensorTile_Box_GYRO gyro;
    SensorTile_Box_Telemetry_ReadGyro(&gyro);

    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);

    json_object_set_number(root_object, "X", gyro.X);

    json_object_set_number(root_object, "Y", gyro.Y);

    json_object_set_number(root_object, "Z", gyro.Z);

    char * serializedString = json_serialize_to_string(root_value);

    int neededSize = (int)strlen(serializedString);
    if (serializedString == NULL || neededSize > size - 1)
    {
        LogError("Failed to build gyro payload string");
        return false;
    }
    else
    {
        memcpy(payloadBuffer, serializedString, neededSize);
        free(serializedString);
    }

    json_value_free(root_value);

    return true;
}

bool SensorTile_Box_SerializeMegnetoTelemetry(char * payloadBuffer, int size)
{
    if (payloadBuffer == NULL)
    {
        return false;
    }

    memset(payloadBuffer, 0, size);

    SensorTile_Box_MEGNETO megneto;
    SensorTile_Box_Telemetry_ReadMegneto(&megneto);

    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);

    json_object_set_number(root_object, "X", megneto.X);

    json_object_set_number(root_object, "Y", megneto.Y);

    json_object_set_number(root_object, "Z", megneto.Z);

    char * serializedString = json_serialize_to_string(root_value);

    int neededSize = (int)strlen(serializedString);
    if (serializedString == NULL || neededSize > size - 1)
    {
        LogError("Failed to build megneto payload string");
        return false;
    }
    else
    {
        memcpy(payloadBuffer, serializedString, neededSize);
        free(serializedString);
    }

    json_value_free(root_value);

    return true;
}

//
// Serialize read-only property
//

bool DeviceInformation_SerializeManufacturerProperty(char * payloadBuffer, int size)
{
    if (payloadBuffer == NULL)
    {
        return false;
    }

    memset(payloadBuffer, 0, size);

    char* manufacturer = DeviceInformation_Property_GetManufacturer();

    int neededSize = snprintf(NULL, 0, "\"%s\"", manufacturer);

    if (neededSize > size - 1)
    {
        LogError("Failed to build manufacturer payload string");
        return false;
    }
    else
    {
        snprintf(payloadBuffer, size, "\"%s\"", manufacturer);
    }

    return true;
}

bool DeviceInformation_SerializeModelProperty(char * payloadBuffer, int size)
{
    if (payloadBuffer == NULL)
    {
        return false;
    }

    memset(payloadBuffer, 0, size);

    char* model = DeviceInformation_Property_GetModel();

    int neededSize = snprintf(NULL, 0, "\"%s\"", model);

    if (neededSize > size - 1)
    {
        LogError("Failed to build model payload string");
        return false;
    }
    else
    {
        snprintf(payloadBuffer, size, "\"%s\"", model);
    }

    return true;
}

bool DeviceInformation_SerializeSwVersionProperty(char * payloadBuffer, int size)
{
    if (payloadBuffer == NULL)
    {
        return false;
    }

    memset(payloadBuffer, 0, size);

    char* swVersion = DeviceInformation_Property_GetSwVersion();

    int neededSize = snprintf(NULL, 0, "\"%s\"", swVersion);

    if (neededSize > size - 1)
    {
        LogError("Failed to build swVersion payload string");
        return false;
    }
    else
    {
        snprintf(payloadBuffer, size, "\"%s\"", swVersion);
    }

    return true;
}

bool DeviceInformation_SerializeOsNameProperty(char * payloadBuffer, int size)
{
    if (payloadBuffer == NULL)
    {
        return false;
    }

    memset(payloadBuffer, 0, size);

    char* osName = DeviceInformation_Property_GetOsName();

    int neededSize = snprintf(NULL, 0, "\"%s\"", osName);

    if (neededSize > size - 1)
    {
        LogError("Failed to build osName payload string");
        return false;
    }
    else
    {
        snprintf(payloadBuffer, size, "\"%s\"", osName);
    }

    return true;
}

bool DeviceInformation_SerializeProcessorArchitectureProperty(char * payloadBuffer, int size)
{
    if (payloadBuffer == NULL)
    {
        return false;
    }

    memset(payloadBuffer, 0, size);

    char* processorArchitecture = DeviceInformation_Property_GetProcessorArchitecture();

    int neededSize = snprintf(NULL, 0, "\"%s\"", processorArchitecture);

    if (neededSize > size - 1)
    {
        LogError("Failed to build processorArchitecture payload string");
        return false;
    }
    else
    {
        snprintf(payloadBuffer, size, "\"%s\"", processorArchitecture);
    }

    return true;
}

bool DeviceInformation_SerializeProcessorManufacturerProperty(char * payloadBuffer, int size)
{
    if (payloadBuffer == NULL)
    {
        return false;
    }

    memset(payloadBuffer, 0, size);

    char* processorManufacturer = DeviceInformation_Property_GetProcessorManufacturer();

    int neededSize = snprintf(NULL, 0, "\"%s\"", processorManufacturer);

    if (neededSize > size - 1)
    {
        LogError("Failed to build processorManufacturer payload string");
        return false;
    }
    else
    {
        snprintf(payloadBuffer, size, "\"%s\"", processorManufacturer);
    }

    return true;
}

bool DeviceInformation_SerializeTotalStorageProperty(char * payloadBuffer, int size)
{
    if (payloadBuffer == NULL)
    {
        return false;
    }

    memset(payloadBuffer, 0, size);

    long totalStorage = DeviceInformation_Property_GetTotalStorage();

    int neededSize = snprintf(NULL, 0, "%ld", totalStorage);

    if (neededSize > size - 1)
    {
        LogError("Failed to build totalStorage payload string");
        return false;
    }
    else
    {
        snprintf(payloadBuffer, size, "%ld", totalStorage);
    }

    return true;
}

bool DeviceInformation_SerializeTotalMemoryProperty(char * payloadBuffer, int size)
{
    if (payloadBuffer == NULL)
    {
        return false;
    }

    memset(payloadBuffer, 0, size);

    long totalMemory = DeviceInformation_Property_GetTotalMemory();

    int neededSize = snprintf(NULL, 0, "%ld", totalMemory);

    if (neededSize > size - 1)
    {
        LogError("Failed to build totalMemory payload string");
        return false;
    }
    else
    {
        snprintf(payloadBuffer, size, "%ld", totalMemory);
    }

    return true;
}

