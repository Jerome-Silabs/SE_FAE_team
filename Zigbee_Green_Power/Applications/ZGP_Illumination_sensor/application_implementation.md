---
sort: 2
---

# Modify the callbacks to integrate your application

- Open the file gpd-sensor-callbacks.c. This is the implementation for the default sensor.

- to support Si1133 UV and Ambiant light sensor we need to add several files into the project.
  We will first create a directory named "drivers"
  Then copy there the following files from the SDK:
  C:\SiliconLabs\SimplicityStudio\v5\developer\sdks\gecko_sdk_suite\v3.1\hardware\kit\common\bsp\thunderboard
  . Si1133.c and Si1133.h  (Si1133 driver functions)
  . board_4166.c and board_4166.h  (Thunderboard Sense 2 driver functions)
  . utils.c and utils.h (utilities functions used by the above files)

- Because Si1133 is an I2C device we will also add I2CSPM drivers from:
  C:\SiliconLabs\SimplicityStudio\v5\developer\sdks\gecko_sdk_suite\v3.1\hardware\kit\common\drivers
  . i2cspm.c and i2cspm.h

- We also need to add this directory to the project 'C' path to have it taken into account.

```c
"${workspace_loc:/${ProjName}/drivers}"
```
<img src="../images/gpsensor_03.png" alt="" width="700" class="center">

- in the same way we need to add the Thunderboard Sense 2 (BRD4166A) configuration files support path:

```c
"${StudioSdkPath}/hardware/kit/EFR32MG12_BRD4166A/config"
```


-	Build and flash the generated binary.
