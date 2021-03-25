---
sort: 6
---

# 6- Adding BLE OTA to a CHIP example

## GATT configuration

GATT of chip examples is defined at this location "connectedhomeip\src\platform\EFR32\gatt.xml"
GATT already include OTA service. You should be able to see OTA service in EFR connect application when device is not provisionned yet.


## Add necessary files

3 files are necessary for OTA
 - application_properties.c
 - application_properties.h
 - binapploader.o

**binapploader.o** is already part of build file. So you don't need to add it. Apploader is a minimal BLE stack that will allow "in place" OTA update.

**application_properties.c** file must be added to your chip example build file. This file contains properties of the application that can be accessed by the bootloader. The structure contained in this file is necessary for OTA. Add **application_properties.c** file to **src/** repository of you example and add the following line to **BUILD.gn** file:

```
 sources = [
    "${examples_plat_dir}/LEDWidget.cpp",
    "${examples_plat_dir}/Service.cpp",
    "${examples_plat_dir}/init_efrPlatform.cpp",
    "src/AppTask.cpp",
    "src/ButtonHandler.cpp",
    "src/LightingManager.cpp",
    "src/ZclCallbacks.cpp",
    "src/main.cpp",
    "src/application_properties.c",
  ]

```

For **application_properties.h**, add **"${efr32_sdk_root}/platform/bootloader/api"** folder that contains application_properties.h to **"connectedhomeip/third_party/efr32_sdk/efr32_sdk.gni"** include_dirs section.

```
_include_dirs = [
  "${efr32_sdk_root}",
  "${efr32_sdk_root}/util/third_party/freertos/Source/include",
  "${efr32_sdk_root}/platform/radio/rail_lib/hal",
  "${efr32_sdk_root}/platform/radio/rail_lib/hal/efr32",
  "${efr32_sdk_root}/platform/bootloader/api",

```

## Modify linker script to add Apploader

Linker script is located in the following folder of your example: **"connectedhomeip\examples\xxxx-app\efr32\ldscripts"**

For EFR32MG21, add the following section before .text section:

```
SECTIONS
{
 .text_apploader :
  {
    KEEP(*(.binapploader*))
  } > FLASH
  .text_signature :
  {
    . = ALIGN(8192);
  } > FLASH

 .text :
  {
```

For EFR32MG12, add the following section before .text section:

```
SECTIONS
{
  .text_apploader :
  {
    KEEP(*(.binapploader*))
  } > FLASH
  .text_signature :
  {
    . = ALIGN(2048);
  } > FLASH

 .text :
  {
```

For OTA update, we will need a bootloader. On EFR32MG12, Bootloader is located in a dedicated region. On EFR32MG21, Bootloader uses address range **0x0-0x4000**. For this reason on EFR32MG21, you need to change the Flash region origin:

```
FLASH (rx) : ORIGIN = 0x00004000, LENGTH = 1048576 - 8192  /* 8K is reserved at top of flash on MG21 */
```
This is memory mapping of EFR32MG21:

![Memory Mapping of EFR32MG21](mmapEFR32MG21.JPG?raw=true "Memory Mapping of EFR32MG21")


## Modify BLE event manager to add OTA 

BLE event management is located in this file: **connectedhomeip\src\platform\EFR32\BLEManagerImpl.cpp**

We need to add the **sl_bt_evt_gatt_server_user_write_request_id** event:

```
// This event indicates that a remote GATT client is attempting to write
// a value of a user type attribute in to the local GATT database.
case sl_bt_evt_gatt_server_user_write_request_id:
  // If user-type OTA Control Characteristic was written, boot the device
  // into Device Firmware Upgrade (DFU) mode.
  if (bluetooth_evt->data.evt_gatt_server_user_write_request.characteristic
      == gattdb_ota_control) {
    // Set flag to enter OTA mode.
    boot_to_dfu = true;
    // Send response to user write request.
    sc = sl_bt_gatt_server_send_user_write_response(
      bluetooth_evt->data.evt_gatt_server_user_write_request.connection,
      gattdb_ota_control,
      SL_STATUS_OK);
    if (sc != SL_STATUS_OK)
      ChipLogProgress(DeviceLayer, "[E: 0x%04x] Failed to send response to user write request\n", (int)sc);
    // Close connection to enter to DFU OTA mode
    sc = sl_bt_connection_close(
      bluetooth_evt->data.evt_gatt_server_user_write_request.connection);
    if (sc != SL_STATUS_OK)
      ChipLogProgress(DeviceLayer, "[E: 0x%04x] Failed to close connection to enter to DFU OTA mode\n", (int)sc);
  }
  break;

```

And to modify existing **sl_bt_evt_connection_closed_id event**: 

```
case sl_bt_evt_connection_closed_id: {
    // Check if need to boot to OTA DFU mode.
    if (boot_to_dfu) {
      // Reset MCU and enter OTA DFU mode.
      sl_bt_system_reset(2);
      break;
    }
    sInstance.HandleConnectionCloseEvent(bluetooth_evt);
}
break;
```


You should normally be able to compile your example now. After that, flash your binary to your device. 

**You also need at this point to flash a bootloader in your device**


## Creating GBL file and testing OTA


The next step is the creation of a GBL that will contain an updated version of your chip application

To easily validate that your OTA procedure is successful, you can modify advertising name of your CHIP example.
Change advertise name in **src/main.cpp**


```
chip::DeviceLayer::ConnectivityMgr().SetBLEDeviceName("EFR32_LIGHT_UPDATED");

```
Compile this updated example.

To create your GBL file, first, create a variable to your CHIP output folder 

```
export OTA_OUTPUT_DIR=/path/to/your/output/
```

Then, extract text section that contains our new CHIP application and convert it to a SREC file with GCC binutils:

```
arm-none-eabi-objcopy -O srec -R .text_apploader -R .text_signature  $OTA_OUTPUT_DIR/chip-efr32-xxx-example.out  $OTA_OUTPUT_DIR/xxx-example.srec
```

Then we are going to create a GBL file based on this SREC file with commander tool:

```
commander gbl create $OTA_OUTPUT_DIR/xxx-example.gbl --app $OTA_OUTPUT_DIR/xxx-example.srec 
```

You should now be able to send this GBL file to your CHIP device with EFR connect application.


## Documentation ##

Official documentation can be found at our [Developer Documentation](https://docs.silabs.com/openthread/latest/) page.

OpenThread open source main page is available [here](https://openthread.io/).

Specific OTBR pages are [here](https://openthread.io/guides/border-router).

## Disclaimer ##

The Gecko SDK suite supports development with Silicon Labs IoT SoC and module devices. Unless otherwise specified in the specific directory, all examples are considered to be EXPERIMENTAL QUALITY which implies that the code provided in the repos has not been formally tested and is provided as-is.  It is not suitable for production environments.  In addition, this code will not be maintained and there may be no bug maintenance planned for these resources. Silicon Labs may update projects from time to time.


