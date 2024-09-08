/*-------------------------------------------------------------------------------------------------


       /////// ////// //////  //////   /////     /////    ////  //    //
         //   //     //   // //   // //   //    //  //  //   // // //
        //   ////   //////  //////  ///////    /////   //   //   //
       //   //     //  //  // //   //   //    //   // //   //  // //
      //   ////// //   // //   // //   //    //////    ////  //   //

     
                 A R D U I N O   D I S T A N C E  S E N S O R S


                 (C) 2024, C. Hofman - cor.hofman@terrabox.nl

            <FluidTankLevelWidget.cpp> - Library for LevelIndicators.
                              16 Aug 2024
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

 *---------------------------------------------------------------------------*
 *
 *  C H A N G E  L O G :
 *  ==========================================================================
 *  P0001 - Initial release 
 *  ==========================================================================
 *
 *--------------------------------------------------------------------------*/
//#include <TerraBox_Widgets.h>        // For Levels class
//#include <TaskScheduler.h>           // For Task
//#include <A02_UART_Auto.h>           // A02_UART_Auto sensor
#include <DistanceSensor.h>            // Simulated Distance Sensor
#include <DistanceMonitor.h>           // DistanceMonitor
//#include <LevelIndicatorWidget.h>    // LevelIndicator
#include <FluidLevelConfigWidget.h>    // Configurator for Fluid levels
#include <PopupButton.h>               // Popup button to activate config

#ifndef FLUID_TANK_LEVEL_MONITOR_H_
#define FLUID_TANK_LEVEL_MONITOR_H_

/*=============================================================================
 *
 *  THe FluiTankLevelMonitor with which the fluid level within a tank
 *  is visualized.
 *
 *===========================================================================*/
class FluidTankLevelMonitor : public DistanceMonitor {
private:

	//
	// The persistent user specifiable configuration Setting
	//
	struct fluidTankLevelConfig configuration;

	//
	//  Contains the title of the monitor.
	//  Normally the fluid name or the tank name.
	//
	char  title[32];
	//
	//  Initialize High, Max, High, Low and LowLow, Min levels
	//  Which is passed on as an argument to the LevelIndicator.
	//
	Levels* theLevels                  = nullptr;

	//
	//  Create the Level indicator GUI Widget
	//  Which passed on as an argument to the LevelMonitor.
	//
	LevelIndicatorWidget* theIndicator = nullptr;

	//
	//  Create the converter for Field to GUI Widget data
	//
	ValueConverter* theValueConverter  = nullptr;


	//
	//  Create the distance sensor
	//
	DistanceSensor* theSensor          = nullptr;

	//
	//  FluidLevelConfig configuration screen
	//
	FluidLevelConfigWidget* theConfigurator = nullptr;

	//
	//  The Popup button for activating the configurator
	//
	PopupButton* popUpConfigure = nullptr;

public:
	FluidTankLevelMonitor(char* name, const char* fluidName, DistanceSensor* sensor);
	FluidTankLevelMonitor(char* name, uint16_t cycleTime, const char* fluidName, DistanceSensor* sensor);

	bool isConfigured();                   // True if configured
	void configure(DistanceSensor* senor); // User specified configuration
    void init(const char* FluidName, DistanceSensor *sensor);      // Object constructor initialization

    void begin();
};

#endif
