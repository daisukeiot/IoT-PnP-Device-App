/************************************************************************************************
 * This code was automatically generated by Digital Twin Code Generator tool 0.6.8.
 * Changes to this file may cause incorrect behavior and will be lost if the code is regenerated.
 *
 * Generated Date: 6/2/2020
 ***********************************************************************************************/

#ifndef DEVICEINFORMATION_INTERFACE_H
#define DEVICEINFORMATION_INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "digitaltwin_interface_client.h"
#include "azure_c_shared_utility/xlogging.h"
#include "azure_c_shared_utility/threadapi.h"

#include "digitaltwin_client_helper.h"
#include "digitaltwin_serializer.h"
#include "parson.h"
#include "../SensorTileBox_pnp_impl.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum DEVICEINFORMATION_READONLY_PROPERTY_TAG
{
    DeviceInformation_MANUFACTURER_PROPERTY,
    DeviceInformation_MODEL_PROPERTY,
    DeviceInformation_SWVERSION_PROPERTY,
    DeviceInformation_OSNAME_PROPERTY,
    DeviceInformation_PROCESSORARCHITECTURE_PROPERTY,
    DeviceInformation_PROCESSORMANUFACTURER_PROPERTY,
    DeviceInformation_TOTALSTORAGE_PROPERTY,
    DeviceInformation_TOTALMEMORY_PROPERTY
} DEVICEINFORMATION_PROPERTY;

// DigitalTwin interface name from service perspective.
static const char DeviceInformationInterfaceId[] = "urn:azureiot:DeviceManagement:DeviceInformation:1";
static const char DeviceInformationInterfaceInstanceName[] = "DeviceInformation";

// Telemetry names for this interface.

// Property names for this interface.

#define DeviceInformationInterface_ManufacturerProperty "manufacturer"

#define DeviceInformationInterface_ModelProperty "model"

#define DeviceInformationInterface_SwVersionProperty "swVersion"

#define DeviceInformationInterface_OsNameProperty "osName"

#define DeviceInformationInterface_ProcessorArchitectureProperty "processorArchitecture"

#define DeviceInformationInterface_ProcessorManufacturerProperty "processorManufacturer"

#define DeviceInformationInterface_TotalStorageProperty "totalStorage"

#define DeviceInformationInterface_TotalMemoryProperty "totalMemory"

// Command names for this interface

// Methods
DIGITALTWIN_INTERFACE_CLIENT_HANDLE DeviceInformationInterface_Create();

void DeviceInformationInterface_Close(DIGITALTWIN_INTERFACE_CLIENT_HANDLE digitalTwinInterfaceClientHandle);

DIGITALTWIN_CLIENT_RESULT DeviceInformationInterface_Property_ReportAll();

DIGITALTWIN_CLIENT_RESULT DeviceInformationInterface_Property_ReportManufacturer();

DIGITALTWIN_CLIENT_RESULT DeviceInformationInterface_Property_ReportModel();

DIGITALTWIN_CLIENT_RESULT DeviceInformationInterface_Property_ReportSwVersion();

DIGITALTWIN_CLIENT_RESULT DeviceInformationInterface_Property_ReportOsName();

DIGITALTWIN_CLIENT_RESULT DeviceInformationInterface_Property_ReportProcessorArchitecture();

DIGITALTWIN_CLIENT_RESULT DeviceInformationInterface_Property_ReportProcessorManufacturer();

DIGITALTWIN_CLIENT_RESULT DeviceInformationInterface_Property_ReportTotalStorage();

DIGITALTWIN_CLIENT_RESULT DeviceInformationInterface_Property_ReportTotalMemory();

#ifdef __cplusplus
}
#endif

#endif  // DEVICEINFORMATION_INTERFACE_H
