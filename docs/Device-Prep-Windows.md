# Windows Application

A sample IoT Plug and Play application with ST Micro SensorTile.

## Requirements

- Windows 10
- ST Micro SensorTile.Box <https://www.st.com/en/evaluation-tools/steval-mksbox1v1.html>
- Custom Built Firmware for SensorTile.Box
- Build Tools for Visual Studio or Visual Studio 2019
- Git client
- CMake

## Assumptions

This instruction assumes followings :

- This repo is cloned to `C:\IoT-PnP-Device-App`
- The app runs on the development device  
  - You may copy the generated executable to another machine to run

## Setting up your development environment

1. Install [Git client](https://git-scm.com/downloads)  
  You may use your favorite Git client

1. Install [CMake](https://cmake.org/download/)  

  Tested with <https://github.com/Kitware/CMake/releases/download/v3.17.3/cmake-3.17.3-win64-x64.msi>  
  Make sure to add CMake to the `PATH`  

  ![cmake](media/CMake.png)

1. Install [Build Tools for Visual Studio](https://visualstudio.microsoft.com/thank-you-downloading-visual-studio/?sku=BuildTools&rel=16)

  Please install following components  

  - C++ build tools  

  - Windows 10 SDK

  if you already have [Visual Studio (Community, Professional, or Enterprise) 2019, 2017 or 2015](https://www.visualstudio.com/downloads/), please make sure above workloads are installed

  ![VSTool](media/VSTool.png)

1. Clone this repo

  ```cmd
  cd \
  git clone https://github.com/daisukeiot/IoT-PnP-Device-App.git
  ```

1. Clone `public-preview` branch of [Azure IoT SDK C](https://github.com/Azure/azure-iot-sdk-c)

  ```cmd
  cd \IoT-PnP-Device-App\pnp-app-windows
  git clone https://github.com/Azure/azure-iot-sdk-c --recursive -b public-preview
  ```

1. Enable long path

  Open CMD (Admin) then set LongPathsEnabled registry key

  ```cmd
  reg add HKLM\SYSTEM\CurrentControlSet\Control\FileSystem /v LongPathsEnabled /t REG_DWORD /d 1 /f
  ```

1. Reboot the PC

## Setting up IoT Central

1. Please follow [this instruction](https://docs.microsoft.com/en-us/azure/iot-central/core/quick-deploy-iot-central) to create a new IoT Central Application

1. Browse to `Device templates` page, then click `+ New` to add a new device template

  ![IOTC_00](media/IOTC_00.png)

1. Select `IoT device` tile, then click `Next: Customize`

  ![IOTC_01](media/IOTC_01.png)

1. Give an unique name to the new device template, then click `Next: Review`

    For example : SensorTile.Box

  ![IOTC_02](media/IOTC_02.png)

1. Click `Create` to create the new device template

  ![IOTC_03](media/IOTC_03.png)

1. Select `Import capability model`

  ![IOTC_04](media/IOTC_04.png)

  This will open a file picker dialog

1. Browse to `C:\IoT-PnP-Device-App\DCM` folder and select `SensorTile.Box.json`

  ![IOTC_05](media/IOTC_05.png)

1. The new device template should now have `Device information` and `SensorTile.Box` interfaces

  ![IOTC_06](media/IOTC_06.png)

1. Browse to `Views`, then select `Generate default views`

  ![IOTC_07](media/IOTC_07.png)

1. Click `Generate default dashboard view(s)` to add `Overview` and `About` views

  ![IOTC_08](media/IOTC_08.png)

1. Confirm `Overview` and `About` views are added

  ![IOTC_09](media/IOTC_09.png)

1. Click on `Publish` to publish the device template

    The device template is now in `draft`.  Publish the device template in order to use it.

  ![IOTC_10](media/IOTC_10.png)

  Click `Publish` to publish the template

  ![IOTC_11](media/IOTC_11.png)

1. Confirm the device template is not in `Published` state

  ![IOTC_12](media/IOTC_12.png)

1. Browse to `Devices` page

    The new template should be listed

  ![IOTC_13](media/IOTC_13.png)

## Creating a new device identity

The IoT Central application is ready to accept device connections.  Each device is associated with one device template.  
A device identity needs to be created for each device to accept connection.

1. Browse to `Devices` page, then click on `+ New`

  ![IOTC_14](media/IOTC_14.png)

1. Give `Device name` and `Device ID` to the new device identity, then click `Create`

    - Device name : User friendly name for this device
    - Device ID : Unique ID for this device

  ![IOTC_15](media/IOTC_15.png)

1. Confirm the new device identity is listed in the devices page

    The device identity is in `Registered` status.  The device status will change to `Provisioned` once the device is provisioned.

  ![IOTC_16](media/IOTC_16.png)

## Parameters for the app

The sample application takes 4 parameters

1. Device ID  

    An unique Device ID used to register the device in the IoT Central Application

1. DPS ID Scope

    From IoT Central application

1. DPS Symmetric Key

    From IoT Central Application

1. COM Port number of SensorTile.Box

    Please check Device Manager to find COM port number.  The device should appear as `USB Serial Device (COMx)`

### ID Scope and Symmetric Key

Make notes of following information from IoT Central Application

- ID Scope
- SAS token  
    One of Primary or Secondary Keys

1. Browse to the device identity just created above, then click on the device name

  ![IOTC_17](media/IOTC_17.png)

1. Click `X Connect`

  ![IOTC_18](media/IOTC_18.png)

1. Click Blue Buttons to copy ID Scope, Device ID, and Primary Key

  Please paste these information in a text file.  We will use these information later when we run the sample app.

  ![IOTC_19](media/IOTC_19.png)

## Compiling the app

Compile the app in CMD console with :

```cmd
cd \IoT-PnP-Device-App\pnp-app-windows
mkdir cmake
cd cmake
cmake .. -Duse_prov_client=ON -Dhsm_type_symm_key:BOOL=ON -Dbuild_service_client=OFF -Dbuild_provisioning_service_client=OFF -Dskip_samples=ON
```

Then build an executable with :

```cmd
cmake --build . -- /p:Configuration=Release
```

This will generate `pnp-app-windows.exe` in `c:\IoT-PnP-Device-App\pnp-app-windows\cmake\Release` folder

## Running the app

In CMD window, run the application with :

Use information we copied in the step above as parameters for the application.

```cme
cd C:\IoT-PnP-Device-App\pnp-app-windows\cmake\Release
pnp-app-windows.exe <Device ID> <ID Scope> <Symmetric Key> <COM Port Number>
```

For example :

```cmd
pnp-app-windows.exe MyTestDevice-01 0ne00123ABC k9dfet4KdffWIs+Jm+dn56J+DgA+yUsOM7nvcdtKQmE= 3
```

Once the device is provisioned, the device status changes to `Provisioned` status and device information is reported by the app.

![IOTC_20](media/IOTC_20.png)

Telemetry should also appear in `Overview` tab within a min or so

![IOTC_21](media/IOTC_21.png)
