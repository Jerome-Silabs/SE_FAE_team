---
sort: 1
---

# GATT configuration :

GATT of chip example is defined at this location "connectedhomeip\src\platform\EFR32\gatt.xml"
GATT already include OTA service. You should be able to see OTA service in EFR connect application when device is not provisionned yet.


#Add necessary files

3 files are necessary for OTA
 - application_properties.c
 - application_properties.h
 - binapploader.o

Apploader is already part of build file. So you don't need to add it. Apploader is a minimal BLE stack that will allow "in place" OTA update.

application_properties.c
Add app_properties.c to "connectedhomeip/third_party/efr32_sdk/efr32_sdk.gni" file.
Add "${efr32_sdk_root}/platform/bootloader/api" folder that contains application_properties.h to "connectedhomeip/third_party/efr32_sdk/efr32_sdk.gni" include_dirs section.

```
_include_dirs = [
  "${efr32_sdk_root}",
  "${efr32_sdk_root}/util/third_party/freertos/Source/include",
  "${efr32_sdk_root}/platform/radio/rail_lib/hal",
  "${efr32_sdk_root}/platform/radio/rail_lib/hal/efr32",
  "${efr32_sdk_root}/platform/bootloader/api",

```

This file contains properties of the application that can be accessed by the bootloader. The strcuture contained in this file is necessary for OTA.

```
source_set(sdk_target_name) {
    sources = [
      "application_properties.c",
      "${chip_root}/third_party/mbedtls/repo/include/mbedtls/platform.h",
      "${efr32_sdk_root}/hardware/kit/common/bsp/bsp_bcc.c",
...
```

#Edit linker script to add Apploader

Linker scripts are located in the example project folders: "connectedhomeip\examples\xxxx-app\efr32\ldscripts"


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

FLASH (rx) : ORIGIN = 0x00004000, LENGTH = 1048576 - 8192 - 0x4000  /* 8K is reserved at top of flash on MG21 */

For EFR32MG12, add the following section before .text section:


On EFR32MG12, Apploader is located at address 0x0 since bootloader is stored in a dedicated region. On EFR32MG21, Apploader is located at address 0x4000 because bootloader use address range 0x0-0x4000

![](mmapEFR32MG21.JPG?raw=true "Memory Mapping of EFR32MG21")


# Modify BLE event manager to add OTA 

BLE event management is done in file: connectedhomeip\src\platform\EFR32\BLEManagrImpl.cpp

We need to add 

```
// This event indicates that a remote GATT client is attempting to write
// a value of a user type attribute in to the local GATT database.
case sl_bt_evt_gatt_server_user_write_request_id:
  // If user-type OTA Control Characteristic was written, boot the device
  // into Device Firmware Upgrade (DFU) mode.
  if (evt->data.evt_gatt_server_user_write_request.characteristic
      == gattdb_ota_control) {
    // Set flag to enter OTA mode.
    boot_to_dfu = true;
    // Send response to user write request.
    sc = sl_bt_gatt_server_send_user_write_response(
      evt->data.evt_gatt_server_user_write_request.connection,
      gattdb_ota_control,
      SL_STATUS_OK);
    sl_app_assert(sc == SL_STATUS_OK,
                  "[E: 0x%04x] Failed to send response to user write request\n",
                  (int)sc);
    // Close connection to enter to DFU OTA mode
    sc = sl_bt_connection_close(
      evt->data.evt_gatt_server_user_write_request.connection);
    sl_app_assert(sc == SL_STATUS_OK,
                  "[E: 0x%04x] Failed to close connection to enter to DFU OTA mode\n",
                  (int)sc);
  }
  break;

// -------------------------------
// This event indicates that a connection was closed.
case sl_bt_evt_connection_closed_id:
  // Check if need to boot to OTA DFU mode.
  if (boot_to_dfu) {
    // Reset MCU and enter OTA DFU mode.
    sl_bt_system_reset(2);
  }
  break;
```

#Creating GBL file


Create a variable to the output folder 

```
export OTA_OUTPUT_DIR=/path/to/your/output/
```

We are going to extract text section that contains our new CHIP application and convert it to an SREC file:

```
arm-none-eabi-objcopy -O srec -R .text_apploader -R .text_signature  $OTA_OUTPUT_DIR/chip-efr32-xxx-example.out  $OTA_OUTPUT_DIR/xxx-example.srec
```

Then we are going to create a GBL file based on this text section:

```
commander gbl create $OTA_OUTPUT_DIR/xxx-example.gbl --app $OTA_OUTPUT_DIR/xxx-example.srec 
```


#Flash a bootloader to your device

