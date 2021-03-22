---
sort: 1
---

# Compile the examples with subG support:

## Hardware needed:

only few radio boards have subGigaHz support.

BRD4170A is both 2.4GHz and 915MHz. Examples compiled below will support both frequency bands.
This is an EFR32MG12 based radio board.

- SubG channels are 1 to 10
- 2.4G channels are 11 to 26

## compiling the examples:

```
> cd openthread
> make -f examples/Makefile-efr32mg12 BOARD=BRD4170A clean
> make -f examples/Makefile-efr32mg12 BOARD=BRD4170A CHANNEL_MANAGER=1  CHANNEL_MONITOR=1
```

## prepare files to be flashed:

files have been generated in output/efr32mg12/bin directory.
They still need an action to be flashable.

prepare the RCP file to be used by the border router.
```
> arm-none-eabi-objcopy -O ihex ./output/efr32mg12/bin/ot-rcp  ./output/efr32mg12/bin/ot-rcp.hex
```

use simplicity commander to flash it.

Your border router may be down due to this action if you followed the install tutorial above.

just restart the otbr-agent service with the following command:

```
> sudo systemctl restart otbr-agent
```

Now the border router is back on.

Let's focus on one node and program a basic cli-mtd node binary.

```
> arm-none-eabi-objcopy -O ihex ./output/efr32mg12/bin/ot-cli-mtd  ./output/efr32mg12/bin/ot-cli-mtd.hex
```

flash ot-cli-mtd using commander tool on a second BRD4170A radio board.

We are ready to commission and test the network in subG (906MHz) mode.





 
