---
sort: 1
---

# IPv6 - Create an IPv6 Router
This repository aims to explain how to create an IPv6 router that can:
* Advertise prefixes on several interfaces
* Route accross its interfaces

This is going to make use of the *radvd* Daemon, taking advantage of IPv6 stateless adressing 
I strongly recommend to get familiar with IPv6 in general first in order to completely get every step of this guide

## Note ##
This guide is written to be used in the context of an OpenThread Border Router sample application

{% include list.liquid all=true %}

## Disclaimer ##

The Gecko SDK suite supports development with Silicon Labs IoT SoC and module devices. Unless otherwise specified in the specific directory, all examples are considered to be EXPERIMENTAL QUALITY which implies that the code provided in the repos has not been formally tested and is provided as-is.  It is not suitable for production environments.  In addition, this code will not be maintained and there may be no bug maintenance planned for these resources. Silicon Labs may update projects from time to time.
