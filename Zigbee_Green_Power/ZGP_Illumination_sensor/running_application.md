---
sort: 3
---

# Running the example

 Open a terminal on your kit.
-	Not working? Generate a bootloader project
-	Unreadable output? Retarget Vcom to enable through hardware configurator
-	Now, flash the remote-control binary on a second kit, and open a terminal.
-	Call the following CLI commands on it:

```console
zcl window up
```

or

```console
zcl window down
```

or

```console
zcl window stop
```

then

```console
bsend 1
```

And look at the output on the motor side