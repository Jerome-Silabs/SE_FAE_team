---
sort: 5
---

# 5- CHIP CustomizeClusterSupport
This repository aims to explain how to custmoize your CHIP sample application Cluster Configuration 
This is going to make use of ZAP Generator and connectedhomeip repo

{% include list.liquid all=true %}

You can find a fork that has a branch bringing Window Covering Client Commands support to CHIP Tool [here](https://github.com/brian-silabs/connectedhomeip)

It is assumed that you already have checked out the connectedhomeip repo on your computer

## Note ##
At the time of writing, the ZAP tool using the connectedhomeip templates for source controller *DO NOT WORK* with Client Custers only
It is mandatory to add the Serverside of the clusterto get a working generation (will submit a PR later)


## Disclaimer ##

The Gecko SDK suite supports development with Silicon Labs IoT SoC and module devices. Unless otherwise specified in the specific directory, all examples are considered to be EXPERIMENTAL QUALITY which implies that the code provided in the repos has not been formally tested and is provided as-is.  It is not suitable for production environments.  In addition, this code will not be maintained and there may be no bug maintenance planned for these resources. Silicon Labs may update projects from time to time.
