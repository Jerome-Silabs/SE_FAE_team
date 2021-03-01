---
sort: 1
---

# Compile Lihting example:

## move to directory and configure target:

```
> cd example/lighting-app/efr32
> source third_party/connectedhomeip/scripts/activate.sh
> export EFR32_BOARD=BRD4166A
> export EFR_SDK_ROOT=~/sdk_support
```

## Compile:

```
> gn gen out/debug
> ninja -C out/debug
```

binaries are in the out/debug directory.

flash chip-efr32-lighting-example.s37 using commander tool.







 
