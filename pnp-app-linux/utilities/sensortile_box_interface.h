/************************************************************************************************
 * This code was automatically generated by Digital Twin Code Generator tool 0.6.8.
 * Changes to this file may cause incorrect behavior and will be lost if the code is regenerated.
 *
 * Generated Date: 6/2/2020
 ***********************************************************************************************/

#ifndef SensorTile_Box_INTERFACE_H
#define SensorTile_Box_INTERFACE_H

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

typedef enum SensorTile_Box_TELEMETRY_TAG
{
    SensorTile_Box_TEMPERATURE_TELEMETRY,
    SensorTile_Box_PRESSURE_TELEMETRY,
    SensorTile_Box_HUMIDITY_TELEMETRY,
    SensorTile_Box_ACCELERO_TELEMETRY,
    SensorTile_Box_GYRO_TELEMETRY,
    SensorTile_Box_MEGNETO_TELEMETRY
} SensorTile_Box_TELEMETRY;

// DigitalTwin interface name from service perspective.
static const char SensorTile_BoxInterfaceId[] = "urn:iotPnpPublicPreviewStSensor:SensorTileBox:1";
static const char SensorTile_BoxInterfaceInstanceName[] = "SensorTile_Box";

// Telemetry names for this interface.

static const char SensorTile_BoxInterface_TemperatureTelemetry[] = "temperature";

static const char SensorTile_BoxInterface_PressureTelemetry[] = "pressure";

static const char SensorTile_BoxInterface_HumidityTelemetry[] = "humidity";

static const char SensorTile_BoxInterface_AcceleroTelemetry[] = "accelero";

static const char SensorTile_BoxInterface_GyroTelemetry[] = "gyro";

static const char SensorTile_BoxInterface_MegnetoTelemetry[] = "megneto";

// Property names for this interface.

// Command names for this interface

// Methods
DIGITALTWIN_INTERFACE_CLIENT_HANDLE SensorTile_BoxInterface_Create();

void SensorTile_BoxInterface_Close(DIGITALTWIN_INTERFACE_CLIENT_HANDLE digitalTwinInterfaceClientHandle);

DIGITALTWIN_CLIENT_RESULT SensorTile_BoxInterface_Telemetry_SendAll();

#ifdef __cplusplus
}
#endif

#endif  // SensorTile_Box_INTERFACE_H
