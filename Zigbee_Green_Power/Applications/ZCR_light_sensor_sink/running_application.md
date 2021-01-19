---
sort: 3
---

# Running the example

<img src="images/zcrdisplay_000.png" alt="" width="800" class="center">

## 1- Setup up the boards and utilities

 - Power up the 2 boards.
 - You can open a terminal for both boards. Settings are the usual 115200,8,N,1 et it is good to add local echo.
 - press reset buttons on both boards
 - look at the terminal on the Grren power device. you should get a print as follow:

 ```
 GPD main
 lux : 2243
  ```
  - on wstk side the terminal is waiting for an entry on you side. press ENTER on your keyboard and you should get this prompt:

  ```
  Z3LightGPComboSoc_gpdisplay>
  ```
  
## 2- commission the Green Power node (Thunderboard Sense 2)

To follow the steps and exchanges in that demo, you can open a terminal for both boards. Settings are the usual 115200,8,N,1 et it is good to add local echo.
As you power up the 2 boards, the router will scan for existing open networks to join and if none will form one.
