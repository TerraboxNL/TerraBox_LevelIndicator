/*-------------------------------------------------------------------------------------------------


       /////// ////// //////  //////   /////     /////    ////  //    //
         //   //     //   // //   // //   //    //  //  //   // // //
        //   ////   //////  //////  ///////    /////   //   //   //
       //   //     //  //  // //   //   //    //   // //   //  // //
      //   ////// //   // //   // //   //    //////    ////  //   //

     
                 A R D U I N O   D I S T A N C E  S E N S O R S


                 (C) 2024, C. Hofman - cor.hofman@terrabox.nl

               <DistanceMonitor.h> - Library forGUI Widgets.
                              16 Aug 2024
                      Released into the public domain
            as GitHub project: TerraboxNL/TerraBox_LevelIndicators
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
#include <Task.h>
#include <DistanceSensor.h>
#include <ValueConverter.h>
#include <LevelIndicatorWidget.h>


#ifndef DISTANCE_MONITOR_H_
#define DISTANCE_MONITOR_H_

/*=============================================================================
 *
 *  Simple monitoring task which measures a distance and passes
 *  the optional converted value to a GUI widget.
 *
 *===========================================================================*/
class DistanceMonitor : public Task {

  private:
    DistanceSensor* sensor          = nullptr;  // The sensor used to measure the distance
    ValueConverter* converter       = nullptr;  // Converter translate field data into GUI data (i.e. % values)
    LevelIndicatorWidget* indicator = nullptr;  // The GUI widget

  public:

    DistanceMonitor(char* name);

    DistanceMonitor(char* name, uint16_t cycleTime);

    DistanceMonitor(char* name,
    		DistanceSensor* pSensor,
			ValueConverter* pConverter,
			LevelIndicatorWidget* pIndicator);

    DistanceMonitor(char* name, uint16_t cycleTime,
    		DistanceSensor* pSensor,
			ValueConverter* pConverter,
			LevelIndicatorWidget* pIndicator);

    void init(DistanceSensor* pSensor,
    		  ValueConverter* pConverter,
			  LevelIndicatorWidget* pIndicator);

    virtual void begin();
    virtual void exec();

};

#endif
