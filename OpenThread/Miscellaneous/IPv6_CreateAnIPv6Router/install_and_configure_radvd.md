---
sort: 1
---

# Installation of radvd daemon and configuration

## Installing radvd
Open a Linux console and use the package manager of your choice to install radvd
``` console
sudo apt install radvd
```

## Configuring radvd
radvd does not come with a default configuration file, instead we need to create one

- Create a new file under /etc/radvd.conf using the text editor of your choice (nano, vim...)
  ```console 
  sudo nano /etc/radvd/radvd.conf
  ```

  We're going to set it so radvd advertises a new prefix on eth0:
  ``` sh
  interface eth0
  {
    AdvSendAdvert on; 
    MaxRtrAdvInterval 30; 
    AdvManagedFlag on; 
    AdvOtherConfigFlag on;

    prefix fd50:43e1:cede:4587::/64
    {
                  AdvOnLink on;
                  AdvAutonomous on;
    };

  };
  ```
  As you can see, these settings apply only for *eth0*
  If you would like to get further information about the other settings that are used : [radvd.conf](https://linux.die.net/man/5/radvd.conf)

- Enable and start the the deamon
  ```console
  sudo systemctl enable radvd.service
  sudo systemctl start radvd.service
  ```

At this point, every single machine that has an IPv6 stack, bridged to eth0 will generate one based on the prefix we set
However we haven't enable routing yet, 