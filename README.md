# DeskArm
DeskArm is a desk-sized robotic arm with 5 degrees of freedom. It uses the MSP432E401Y microcontroller along with various stepper and servo motors to achieve precise movements. 

## General Description: 
DeskArm is a 3D printed miniture 5-axis robotic arm that can be controlled from a computer using a python script that logs keystrokes. Certain Keys have been mapped to certain movements. The PC communicates with the uC via UART. 

<p align="center">
  <img width="400" alt="Isometric View" src="https://github.com/justinalexchan/DeskArm/blob/master/images/isometric.png">
</p>

### Design:
DeskArm was designed and in Fusion 360. Given that each component had to be 3D printed, the design focused on reducing the number of overhangs to ensure that the use of support structures were minimized. The following are the left, back and top view of the design:

<p align="center">
  <img width="270" alt="Left View" src="https://github.com/justinalexchan/DeskArm/blob/master/images/left.png">
  <img width="230" alt="Back View" src="https://github.com/justinalexchan/DeskArm/blob/master/images/back.png">
  <img width="280" alt="Back View" src="https://github.com/justinalexchan/DeskArm/blob/master/images/top.png">
</p>

Each part was printed in PLA using an Creality Ender 3 (Nozle Temp: 200C, Bed Temp: 50C). As a result each part was as requried to fit on a 220 x 220 mm printing bed. 

### Electronics:
#### Microcontoller: Texas Instrument MSP432E401Y
<p align="center">
  <img width="350" alt="Left View" src="https://cdn11.bigcommerce.com/s-3fd3md1ghs/images/stencil/1280x1280/products/26747/7688/msp-exp432e401y-evm-board__29136.1561068341.png?c=2&imbypass=on">
</p>

#### Stepper Motors: 28BYJ-48 x 4
<p align="center">
  <img width="350" alt="Left View" src="https://components101.com/sites/default/files/component_pin/28BYJ-48-Pinout-Wirings.png">
</p>

#### Servo Motors: 9g Micro Servo x 3
<p align="center">
  <img width="350" alt="Left View" src="https://cdn11.bigcommerce.com/s-am5zt8xfow/images/stencil/1280x1280/products/401/1038/apingl5ma__52811.1548546758.jpg?c=2&imbypass=on">
</p>



