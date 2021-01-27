---
sort: 2
---

# Modify the callbacks to integrate your application

## Modify the default callback file with our code:

Open Z3LightGPCombo_gpdisplay_callbacks.c. This is the implementation of the project callbacks interactions.

- We have 2 additions to integrate to this project in order to:
  - get the light measurement value
  - display it on the kit Sharp Memory LCD

- Getting the measurement value is quite simple. The Green Power sensor is the server for this measurement, therefore the data will be sent to the Zigbee endpoint and illumination cluster client by the SINK feature.
this is the purpose of emberAfReportAttributesCallback() to enable an action upon getting a report from the server.
We will here trigger an update of the display if the cluster Id is the illuminance measurement one (ZCL_ILLUM_MEASUREMENT_CLUSTER_ID).
As we know reports are organised like this:

  Attribute ID (2 bytes)  Attribute Data Type (1 Byte)   Attribute data (variable)

the uint16 illumination measurement is therefore contained in bytes 3 and 4  

```c
boolean emberAfReportAttributesCallback(EmberAfClusterId clusterId,
                                     int8u *buffer,
                                     int16u bufLen)
{
  EmberAfClusterCommand *currentCommand = emberAfCurrentCommand();
  uint16_t measuredValue = 0;

  switch (clusterId) {
      case ZCL_ILLUM_MEASUREMENT_CLUSTER_ID:
        measuredValue = (uint16_t)(buffer[3] | (buffer[4] << 8));
        emberAfCorePrintln("Received report from 0x%x: %d", (currentCommand->source), measuredValue);
        updateDisplay(measuredValue);
        break;
      default:
        break;
    }
}
```

- adding the display support and using the glib functions is done in 2 steps:

  - first we will initialize the display support by adding includes, defines and add the initialization to the emberAfMainInitCallback() which is the first function to be called after the boot for the application.

after the #include of the file, add:

```c
#include "glib.h"
#include "display.h"
#include <string.h>
#include <stdio.h>

extern GLIB_Context_t glibContext;          /* Global glib context */
uint8_t y_position = 20;

void updateDisplay (uint16_t);              /* update display with new sensor value */

```

Then look for emberAfMainInitCallback() and change it to:

```c
void emberAfMainInitCallback(void)
{
  char *line1, *line2;
  EMSTATUS status;

  line1 = " GREEN POWER ";
  line2 = " SENSOR    ";

  /* Initialize the display module. */
  status = DISPLAY_Init();
  if (DISPLAY_EMSTATUS_OK != status) {
    while (1) ;
  }

  /* Initialize the DMD module for the DISPLAY device driver. */
  status = DMD_init(0);
  if (DMD_OK != status) {
    while (1) ;
  }

  /* Initialize the glib context */
  status = GLIB_contextInit(&glibContext);
  if (GLIB_OK != status) {
    while (1) ;
  }

  glibContext.backgroundColor = White;
  glibContext.foregroundColor = Black;
  GLIB_clear(&glibContext);
  GLIB_setFont (&glibContext,   (GLIB_Font_t *)&GLIB_FontNormal8x8);
  GLIB_drawString(&glibContext, line1, strlen(line1) + 1, 2, y_position, 0);
  GLIB_drawString(&glibContext, line2, strlen(line2) + 1, 2, y_position + 10, 0);
  DMD_updateDisplay();

  emberEventControlSetActive(commissioningLedEventControl);

}
```

  - create the updateDisplay() function called from the report:

```c
void updateDisplay (uint16_t value)
{
  char text[16];
  GLIB_Rectangle_t lowerArea = {1, 40, LS013B7DH03_WIDTH - 1, LS013B7DH03_HEIGHT - 1};

  GLIB_setClippingRegion(&glibContext, &lowerArea);
  GLIB_applyClippingRegion(&glibContext);
  GLIB_clearRegion(&glibContext);
  sprintf(text, " %d lux", value);
  GLIB_drawString(&glibContext, text , strlen(text) + 1, 2, y_position + 20, 0);
  DMD_updateDisplay();
}
```

## Compile time:

Build and flash the generated binary (be sure to have flashed a bootloader as well!).

Bootloader can be generated from the Gecko bootloader examples, but if you want to shortcut for this tutorial, you can flash any of the demos before flashing this project's binary. Just avoid erasing the memory as this may erase the bootloader as well.
