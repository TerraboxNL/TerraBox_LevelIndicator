/*-------------------------------------------------------------------------------------------------


       /////// ////// //////  //////   /////     /////    ////  //    //
         //   //     //   // //   // //   //    //  //  //   // // //
        //   ////   //////  //////  ///////    /////   //   //   //
       //   //     //  //  // //   //   //    //   // //   //  // //
      //   ////// //   // //   // //   //    //////    ////  //   //

     
                 A R D U I N O   D I S T A N C E  S E N S O R S


                 (C) 2024, C. Hofman - cor.hofman@terrabox.nl

          <FluidTankLevelGUI.cpp> - Library for LevelIndicators.
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
#include <Persistence.h>
#include <FluidLevelConfigWidget.h>
#include "FluidTankLevelGUI.h"

/**----------------------------------------------------------------------------
 *
 *  Constructs the Fluid level monitoring task.
 *  It is based on the DistanceMonitor object, which provides the bare bone
 *  functionality of measuring the level and presenting it in the GUI.
 *
 * @param name        The task name of this monitor
 * @param fluidName   The name of the fluid that is being monitored.
 * @param sensor      The distance sensor to be used
 *
 *---------------------------------------------------------------------------*/
FluidTankLevelMonitor::FluidTankLevelMonitor(char* name, const char* fluidName, DistanceSensor* sensor) :
	                      DistanceMonitor (name) {
    init(fluidName, sensor);

}

/**----------------------------------------------------------------------------
 *
 *  Constructs the Fluid level monitoring task.
 *  It is based on the DistanceMonitor object, which provides the bare bone
 *  functionality of measuring the level and presenting it in the GUI.
 *
 * @param name        The task name of this monitor
 * @param cycleTime   The scheduling time interval for this monitor.
 * @param fluidName   The name of the fluid that is being monitored.
 * @param sensor      The distance sensor to be used
 *
 *---------------------------------------------------------------------------*/
FluidTankLevelMonitor::FluidTankLevelMonitor(char* name, uint16_t cycleTime,
			                                   const char* fluidName, DistanceSensor* sensor) :
		                  DistanceMonitor (name, cycleTime) {
    init(fluidName, sensor);

}


/**----------------------------------------------------------------------------
 *
 *  Initialize this FluidTankLevelMonitor.
 *
 *  @param fluidName   The name of the fluid, which shows up in the GUI
 *
 *---------------------------------------------------------------------------*/
void FluidTankLevelMonitor::init(const char* fluidName, DistanceSensor* sensor) {

	strcpy(nameId, "FluidTank");

	theSensor = sensor;

	//
	//  Initialize High, Max, High, Low and LowLow, Min levels
	//  Which is passed on as an argument to the LevelIndicator.
	//
	theLevels    = new Levels(0, 5, 10, 90, 95, 100);

	//
	//  Create the converter for Field to GUI Widget data
	//
	theValueConverter = new ValueConverter();

	//
	//  Create the configurator
	//
	theConfigurator = new FluidLevelConfigWidget(&Screen, 85, 10, sensor, name, fluidName, &configuration);
    theConfigurator->setValueConverter(theValueConverter);
    theConfigurator->setVisible(false);

	//
	//  Create the Level indicator GUI Widget
	//  Which passed on as an argument to the LevelMonitor.
	//
	theIndicator = new LevelIndicatorWidget(
		                          &Screen    //                         Widget* parent,
		                          ,fluidName //  Title        const char *name,
		                          ,3         //  Label font size         uint16_t labelSize,
		                          ,85        //  X position              int16_t px,
		                          ,120       //  Y position              int16_t py,
		                          ,150       //  Widget width            uint16_t pwidth,
		                          ,200       //  Bar height              uint16_t pheight,
		                          ,WHITE     //  Bar background color    uint16_t pBgColor,
		                          ,2         //  Stroke width            uint16_t pStroke,
		                          ,WHITE     //  Stroke color            uint16_t pStrokeColor,
		                          ,5         //  Tick length             uint16_t pTickLength,
		                          ,2         //  Tick stroke             uint16_t pTickStroke,
		                          ,theLevels //  Threshold levels        Levels* pLevels,
		                          ,"%"       //  Unit                    String pUnit
		                          ,theConfigurator);


	//
	//  Call the init() of the Base class
	//
	DistanceMonitor::init(sensor, theValueConverter, theIndicator);
}

void FluidTankLevelMonitor::begin() {
	//
	//  See if we need configuration
	//
	if (!isConfigured()) {
	  configure(theSensor);
	}

	//
	//  Create the converter for Raw Field data to GUI Widget Target data
	//
	theValueConverter->setConversionData(
			                      configuration.sensorMinimum,
			                      configuration.sensorMaximum,
								  0, 100);

	//
	//  Call the begin of the distance monitor
	//
	DistanceMonitor::begin();

}

/**----------------------------------------------------------------------------
 *
 *  Finds out of the level indicator has already been configured or not.
 *
 *  @return   True if already configured, otherwise false.
 *
 *---------------------------------------------------------------------------*/
bool FluidTankLevelMonitor::isConfigured() {

	if (theConfigurator->readConfiguration())
		return true;

    theConfigurator->createConfiguration();
	return false;
}

/**----------------------------------------------------------------------------
 *
 *  Configuration dialog to define minimum and maximum fluid levels.
 *
 *  @param sensor  The sensor needed to optionally measure the distances with
 *
 *---------------------------------------------------------------------------*/
void FluidTankLevelMonitor::configure(DistanceSensor* sensor) {

	//
	// Perform the configuration of this fluid level indicator.
	//
	theConfigurator->setVisible(true);
    theConfigurator->draw();
}

