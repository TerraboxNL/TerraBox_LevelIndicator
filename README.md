/*-------------------------------------------------------------------------------------------------


       /////// ////// //////  //////   /////     /////    ////  //    //
         //   //     //   // //   // //   //    //  //  //   // // //
        //   ////   //////  //////  ///////    /////   //   //   //
       //   //     //  //  // //   //   //    //   // //   //  // //
      //   ////// //   // //   // //   //    //////    ////  //   //

     
                 A R D U I N O  L E V E L  I N D I C A T O R


                 (C) 2024, C. Hofman - cor.hofman@terrabox.nl

               README.md - Library for fluid level indicator.
                                12 Sep 2024
                       Released into the public domain
              as GitHub project: TerraboxNL/TerraBox_LevelIndicator
                   under the GNU General public license V3.0
                          
      This program is free software: you can redistribute it and/or modify
      it under the terms of the GNU General Public License as published by
      the Free Software Foundation, either version 3 of the License, or
      (at your option) any later version.

      This program is distributed in the hope that it will be useful,
      but WITHOUT ANY WARRANTY; without even the implied warranty of
      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
      GNU General Public License for more details.

      You should have received a copy of the GNU General Public License
      along with this program.  If not, see <https://www.gnu.org/licenses/>.


Releases
========

Release V1.0.1-beta:
A first release of the fluid level indicator using a DYP-A02 Automatic ultra sound based distance sensor. 

Installation
============
Locate the Arduino/library folder on your system. Create the folder TerraBox_LevelIndicator in the library folder and copy the contents of this release into it.
Do not forget to download the dependent packages: MCUFRIENDS_kbv, TerraBox_Scheduler 1.0.1-beta.1, TerraBox_Distance 1.0.1-beta.1, TerraBox_Widgets 1.0.1.beta.1, TerraBox_Persistence 1.0.1-beta.1.

Abstract
========
This library provides you with a fluid level indicator. It runs on a Arduino Mega256 with a Touch capable TFT screen.

Sketch
======
After downloading this library and all its dependent libraries, copy the TerraBox_FluidLevelIndicator sketch from in the Examples directory to the Arduino folder.
Before opening and uploading the sketch make sure the persistent memeory (EEPROM in a Mega256) must be in virging state. That is all its bytes contain 0xFF. 
Then open the TerraBox_FluidLevelIndicator sketch, compile and upload it to an Arduino Mega2560 having a touch enabled TFT screen.
The persistent memory (i.e. EEPROM) must be in virgin state. That is, it should contain 0xFF at all bytes. 
The sketch TerraBox_ClearEEPROM can be used to clear the persistent memory in the proper way.
Running the Fluid level indicator will show a splash at start up. If started for the first time it will ask you to calibrate the screen first.
For this a vertical and a horizontal row of red crosses is drawn on the screen. You will have to tap each cross 3 times. The white corss is the one you need to tap.
If the three taps are too far apart then the cross will turn blue and the sequence of three taps start again for that cross. After you have tapped all crosses the screen will be cleared and you have the option of starting some diagnostic function. 
If you wait the fluid level indicator will automatically start.

Once you see the level indicator, a message right above it tells you that you can tap the title bar on top, which contains the text "Water".
If tapped a dialog popup will apear just above the level indicator with which you can calibrate a maximum level and a minimum fluid level.
The easiest way to do this calibration is with the sensor installed on your fluid tank.
If the tank is empty, then you tap on the button called Minimum. Then fill the tank to its maximum and you then tap the button titled maximum.
When pressing the buttons the measured level will be displayed at left side from the button pressed. You can press the level button multiple times if you wish. Each time you press the button an new measurement is made and the result is displayed.
The measured values may vary slightly.
After having set the minimum and maximum level you tap the OK button, the dialog will disapear and you are all set.
Note that the minimum level measured is greater than the maximum level. This is because the sensor measures the distance from the top of the tank to the fluid surface.
Which of course is smaller with a full tank than it is with an empty tank.

LevelIndicatorWidget
====================
This is the foundation of the level indicator. It is a compound widget which contains a button containing supporting a title and if clicked it will make the setup dialog visible.
The middle part shows the level indication. Together with the highhigh, high, low and lowlow level ticks.
These levels are associated with a specific color for that level. At that point the indicator will the color. In this way visual level feedback is provided.

FluidLevelConfigWidget
======================
This widget contains the the setup screen and consists of a cancel and OK button, labels for the minimum and maximum levels and button to register the minimum and maximum fluid levels.

DistanceMonitor
===============
This Monitor class implements the periodical sensor measurements and is based on the Task class of the TerraBox_Scheduler library.

FluidTankLevelGUI
=================
This class builds upon the DistanceMonitor class and implements the integrating of the sensor and level indicator resulting in the completed fluid level GUI, where the periodic sensor measurements are used to visualize the current fluid level using the LevelIndicatorWidget.
Because it inherits the Task properties it can easily be scheduled at specific time interval keeping the level indicator up to date with the sensor data.
Have a look at the TerraBox_FLuidLevelIndicator to see how the scheduling is implemented.

