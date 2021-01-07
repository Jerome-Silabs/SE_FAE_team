# Zigbee Green Power light sensor

<img src="images/tutorial_pitch.png" alt="" width="800" class="center">

This repository holds documentation and implementation on how to create a Zigbee Green Power sensor (here light sensor)  

In order to proceed, you will need to download EmberZNet SDK through Simplicity Studio
The SDK's access can only be requested using the serial number coming from this development kit :
[SLWSTK6000B](https://www.silabs.com/development-tools/wireless/zigbee/efr32mg-zigbee-thread-starter-kit)

At the time of writing, this is done using Simplicity Studio v5 and GSDK 3.1.0

{% include list.liquid all=true %}

## Description ##
This code is running on a Thunderboard Sense 2 using its Si1133 UV and ambient light sensor.
It can be commissioned to any Zigbee 3.0 network with a Sink for illuminance measurement cluster data.

To pair and use it, follow the steps described in the section *"Running the example"*

## Documentation ##

Official Zigbee documentation can be found at our [Developer Documentation](https://docs.silabs.com/zigbee/latest/) page.
Zigbee Green Power: [UG392](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&cad=rja&uact=8&ved=2ahUKEwiW8ujrhIruAhVOrxoKHXD-B4wQFjAAegQIBRAC&url=https%3A%2F%2Fwww.silabs.com%2Fdocuments%2Fpublic%2Fuser-guides%2Fug392-using-sl-green-power-with-ezp.pdf&usg=AOvVaw1z-XzjI55_ExlDnChtSArt)

## Disclaimer ##

The Gecko SDK suite supports development with Silicon Labs IoT SoC and module devices. Unless otherwise specified in the specific directory, all examples are considered to be EXPERIMENTAL QUALITY which implies that the code provided in the repos has not been formally tested and is provided as-is.  It is not suitable for production environments.  In addition, this code will not be maintained and there may be no bug maintenance planned for these resources. Silicon Labs may update projects from time to time.
