---
sort: 1
---

# Build the CHIP python package

## Clone Project CHIP repo:

```
> git clone https://github.com/project-chip/connectedhomeip.git
```

## Build:

```
> sudo scripts/build_python.sh
```

You will obtain a "chip-device-ctrl" binary located in out/python_env/bin/ directory

If you are facing error during building, you might need to install the following packages:

```
> sudo apt-get install libgirepository1.0-dev
> sudo apt-get install libcairo2-dev

```

and the following python packages:

```
> pip install pycairo
> pip install dmlib

```







 
