/*-------------------------------------------------------------------------------------------------


       /////// ////// //////  //////   /////     /////    ////  //    //
         //   //     //   // //   // //   //    //  //  //   // // //
        //   ////   //////  //////  ///////    /////   //   //   //
       //   //     //  //  // //   //   //    //   // //   //  // //
      //   ////// //   // //   // //   //    //////    ////  //   //

     
                 A R D U I N O   D I S T A N C E  S E N S O R S


                 (C) 2024, C. Hofman - cor.hofman@terrabox.nl

               <DistanceMonitor.cpp> - Library for GUI widgets.
                               16 Aug 2024
                       Released into the public domain
               as GitHub project: TerraboxNL/TerraBox_Widgets
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
#include <DistanceMonitor.h>
#include <DistanceSensor.h>

DistanceMonitor::DistanceMonitor(char* name) : Task(name) {

}

DistanceMonitor::DistanceMonitor(char* name, uint16_t cycleTime) :
		Task(name, cycleTime) {

}


/*------------------------------------------------------------------------------
 *
 *  The constructor creating the monitor
 *
 *  name        The name of the monitoring task
 *  pSensor     The sensor used to measure the distance
 *  pConverter  Converts the sensor value to GUI presentable value
 *  pIndicator  The GUI widget displaying the level
 *
 *----------------------------------------------------------------------------*/
DistanceMonitor::DistanceMonitor(char* name, DistanceSensor* pSensor, ValueConverter* pConverter, LevelIndicatorWidget* pIndicator) :
                 Task(name) {

	  init(pSensor, pConverter, pIndicator);

}

/*------------------------------------------------------------------------------
 *
 *  The constructor creating the monitor
 *
 *  name        The name of the monitoring task
 *  cycleTime   The interval at which the level indicator is refreshed
 *  pSensor     The sensor used to measure the distance
 *  pConverter  Converts the sensor value to GUI presentable value
 *  pIndicator  The GUI widget displaying the level
 *
 *----------------------------------------------------------------------------*/
DistanceMonitor::DistanceMonitor(char* name, uint16_t cycleTime, DistanceSensor* pSensor, ValueConverter* pConverter, LevelIndicatorWidget* pIndicator) :
                 Task(name, cycleTime) {

  init(pSensor, pConverter, pIndicator);

}

void DistanceMonitor::init(DistanceSensor* pSensor, ValueConverter* pConverter, LevelIndicatorWidget* pIndicator) {
    strcpy(nameId, "DistanceMonitor");
	sensor    = pSensor;
    converter = pConverter;
    indicator = pIndicator;
}

void DistanceMonitor::begin() {

	indicator->draw();

}

/*-----------------------------------------------------------------------------
 *
 *  Implementation of the monitoring logic. Converting the distance to %
 *  and passing it to the LevelIndicatorWidget
 *
 *---------------------------------------------------------------------------*/
void DistanceMonitor::exec() {
       uint16_t distance   = sensor->getDistance();
       uint16_t percentage = converter->convert2Target(distance);
       indicator->update(percentage);
}

