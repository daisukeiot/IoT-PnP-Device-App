#pragma once

#ifndef SENSORTILE_BOX_H
#define SENSORTILE_BOX_H
#include <stdio.h>
#include <stdint.h>
#include <time.h>

#ifdef _WIN32

#include <tchar.h>
#include <windows.h>

#else
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#include <sys/time.h>

typedef int HANDLE;
#define INVALID_HANDLE_VALUE -1

typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef int32_t LONG;
typedef uint16_t UINT16;
typedef unsigned char UCHAR;
typedef uint64_t ULONG64;
typedef uint64_t ULONGLONG;
typedef int64_t LONGLONG;
typedef unsigned char BYTE;
typedef BYTE *LPBYTE;
typedef int BOOL;
#define FALSE 0
#define TRUE 1

#define GetLastError() \
	errno
#endif

#define FDevAddr                     1U
#define STEVAL_IDI001V1_ADDR	     50U

#define TMsg_EOF                     0xF0
#define TMsg_BS                      0xF1
#define TMsg_BS_EOF                  0xF2
#define TMsg_MaxLen                  1024

#define CMD_Ping                     0x01U
#define CMD_Read_PresString          0x02U
#define CMD_NACK                     0x03U
#define CMD_CheckModeSupport         0x04U
#define CMD_UploadAR                 0x05U
#define CMD_UploadCP                 0x06U
#define CMD_Start_Data_Streaming     0x08U
#define CMD_Stop_Data_Streaming      0x09U
#define CMD_StartDemo                0x0AU
#define CMD_Sleep_Sec                0x0BU
#define CMD_Set_DateTime             0x0CU
#define CMD_Get_DateTime             0x0DU
#define CMD_Enter_DFU_Mode           0x0EU
#define CMD_Reset                    0x0FU
#define CMD_Enable_Disable_Sensor    0x10U
#define CMD_Initialize_Sensor        0x11U
#define CMD_Read_Sensor_Data         0x12U
#define CMD_Sensor2                  0x13U
#define CMD_Sensor                   0x50U
#define CMD_Reply_Add                0x80U

#define SENSOR_FLAG_PRESSURE         0x01U
#define SENSOR_FLAG_TEMPERATURE      0x02U
#define SENSOR_FLAG_HUMIDITY         0x04U
#define SENSOR_FLAG_ACCELEROMETER    0x08U
#define SENSOR_FLAG_GYRO             0x10U
#define SENSOR_FLAG_MEGNETOMETER     0x20U

/* Enable sensor masks */
#define PRESSURE_SENSOR_ENABLED      0x00000001U
#define TEMPERATURE_SENSOR_ENABLED   0x00000002U
#define HUMIDITY_SENSOR_ENABLED      0x00000004U
#define UV_SENSOR_ENABLED            0x00000008U /* for future use */
#define ACCELEROMETER_SENSOR_ENABLED 0x00000010U
#define GYROSCOPE_SENSOR_ENABLED     0x00000020U
#define MAGNETIC_SENSOR_ENABLED      0x00000040U
#define INTERRUPTS_ENABLED           0x00000100U
#define FSM_ENABLED                  0x00000200U
#define MLC_ENABLED                  0x00000400U

#define SC_ACCELEROMETER             0x01U
#define SC_GYROSCOPE                 0x02U
#define SC_MAGNETOMETER              0x03U
#define SC_TEMPERATURE               0x04U
#define SC_HUMIDITY                  0x05U
#define SC_PRESSURE                  0x06U
#define SC_UV                        0x07U

#define SC_GET_SENSOR_NAME           0x01U
#define SC_READ_REGISTER             0x02U
#define SC_WRITE_REGISTER            0x03U
#define SC_GET_FULL_SCALE_LIST       0x04U
#define SC_SET_FULL_SCALE            0x05U
#define SC_GET_ODR_LIST              0x06U
#define SC_SET_ODR                   0x07U
#define SC_GET_FULL_SCALE            0x1EU
#define SC_GET_ODR                   0x1FU
#define SC_GET_SENSOR_LIST           0x14U
#define SC_SET_SENSOR_INDEX          0x15U

#define RTC_WEEKDAY_MONDAY          ((uint8_t)0x01U)
#define RTC_WEEKDAY_TUESDAY         ((uint8_t)0x02U)
#define RTC_WEEKDAY_WEDNESDAY       ((uint8_t)0x03U)
#define RTC_WEEKDAY_THURSDAY        ((uint8_t)0x04U)
#define RTC_WEEKDAY_FRIDAY          ((uint8_t)0x05U)
#define RTC_WEEKDAY_SATURDAY        ((uint8_t)0x06U)
#define RTC_WEEKDAY_SUNDAY          ((uint8_t)0x07U)

typedef struct {
	unsigned int Len;
	unsigned char Data[TMsg_MaxLen];
} TMsg;

// 3 : Header
// 4 : TimeStamp
// 1 : Flag
// 4 : Pressure
// 4 : Temperature
// 4 : Humidity
// 12 : Accelerometer
// 12 : Gyro
// 12 : Magneto
// 1  : Checksum

// = 57
typedef struct {
	unsigned char data[64];
}SensorData1;

typedef struct {
	unsigned char year;
	unsigned char month;
	unsigned char day;
	unsigned char hours;
	unsigned char minutes;
	unsigned char seconds;
	unsigned char sub_seconds;
} TimeStamp_Data;

typedef struct {
	TimeStamp_Data timeStamp;
	unsigned char flag;
	unsigned char data[64];
}SensorData;

typedef struct {
	unsigned char sensorCmd;
	unsigned char sensorid;
	unsigned char name[48];
}SensorName;

typedef struct THREE_AXIS_DATA_TAG
{
    int X;
    int Y;
    int Z;
} THREE_AXIS_DATA, *PTHREE_AXIS_DATA;

extern HANDLE hSensorTag;

HANDLE InitializeSensorTile(int ComPortNumber);
int Get_Sensor_Data(HANDLE hComm, int BufferLength, SensorData* Buffer);
float GetPressure();
float GetTemperature();
float GetHumidity();
void GetAccelerometer(PTHREE_AXIS_DATA AxisData);
void GetGyrometer(PTHREE_AXIS_DATA AxisData);
void GetMagnetometer(PTHREE_AXIS_DATA AxisData);

#endif