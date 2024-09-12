/*-------------------------------------------------------------------------------------------------


       /////// ////// //////  //////   /////     /////    ////  //    //
         //   //     //   // //   // //   //    //  //  //   // // //
        //   ////   //////  //////  ///////    /////   //   //   //
       //   //     //  //  // //   //   //    //   // //   //  // //
      //   ////// //   // //   // //   //    //////    ////  //   //

     
                  A R D U I N O  L E V E L  I N D I C A T O R


                 (C) 2024, C. Hofman - cor.hofman@terrabox.nl

           <FluidLevelConfigWidget.h> - Library for LevelIndicators.
                                18 Aug-2024
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
#include <Terrabox_Widgets.h>
#include <LabelWidget.h>
#include <ButtonWidget.h>
#include <DistanceSensor.h>
#include <Persistence.h>
#include <ValueConverter.h>

#ifndef FLUID_LEVEL_CONFIG_H_
#define FLUID_LEVEL_CONFIG_H_

#define FLUID_TANK_LEVEL_CONFIG_SIZE  32

/*=============================================================================
 *
 *  The persistent information struct for the FluidTankLevelMonitor
 *
 *===========================================================================*/
struct fluidTankLevelConfig {
	char     title[PERSISTENT_AREA_NAME_SIZE] = "Water"; // A unique tank/fluid name
	int16_t  sensorMinimum;       // The absolute minimum level, i.e. empty
	int16_t  sensorMaximum;       // The absolute maximum level, i.e. full
	char     spare[FLUID_TANK_LEVEL_CONFIG_SIZE -
				  (
				   PERSISTENT_AREA_NAME_SIZE +
		           sizeof(uint16_t) +
				   sizeof(uint16_t)
				  )];
};

/*============================================================================
 *
 * Class implementing the configuration dialog for the FluidTankLevelWidget
 *
 *==========================================================================*/
class FluidLevelConfigWidget : public Widget {
  protected:
     fluidTankLevelConfig*  config;
     DistanceSensor*        sensor;
     uint32_t               min;
     uint32_t               max;
     char*                  areaName;
     char*                  fluidName;

     ValueConverter*        converter = nullptr;

  public:
	/**------------------------------------------------------------------------
	 *
	 *  Creates a label to show the measured min value in.
	 *
	 *-----------------------------------------------------------------------*/
	class LabelMin : public LabelWidget {
	public:
		LabelMin(Widget* parent, int16_t x, int16_t y) :
			LabelWidget(parent, LABEL_ROUNDED,
                 x, y, 50, 20,
                 3, "--", GRAY_D, 0, GRAY_D,
                 WHITE) {

		}
	};
	LabelMin* labelMin;

	/**------------------------------------------------------------------------
	 *
	 *  ButtonMin is an internal class creating a button with which
	 *  the minimum (i.e. 0%) can be specified.
	 *
	 *-----------------------------------------------------------------------*/
	class ButtonMin : public ButtonWidget {

	  public:
		ButtonMin(Widget* parent, int16_t x, int16_t y) :
			ButtonWidget(parent, BUTTON_ROUNDED,
	                x, y, 50, 20,
	                3, GRAY_D, 2, WHITE,
	                WHITE, "Minimum") {
		}

	    void action(TouchEvent* event) {

	    	//
	    	// Read out the sensor for the current distance.
	    	//
	    	(((FluidLevelConfigWidget*)parent)->sensor)->exec();  // Measure the distance
	    	((FluidLevelConfigWidget*)parent)->min = (((FluidLevelConfigWidget*)parent)->sensor)->getDistance();

	    	//
	    	// Live update of the value converter/Level indicattor results
	    	//
	    	((FluidLevelConfigWidget*)parent)->converter->updateMinRaw(((FluidLevelConfigWidget*)parent)->min);

	    	//
	    	// Update the new value in the configuration screen
	    	//
	    	char buf[16];
            sprintf(buf, "%d", ((FluidLevelConfigWidget*)parent)->min);
            (((FluidLevelConfigWidget*)parent)->labelMin)->setText(buf);
	    }
	};
	ButtonMin*     buttonMin;

	/**------------------------------------------------------------------------
	 *
	 *  Creates a label to show the measured max value in.
	 *
	 *-----------------------------------------------------------------------*/
	class LabelMax : public LabelWidget {
	public:
		LabelMax(Widget* parent, int16_t x, int16_t y) :
			LabelWidget(parent, LABEL_ROUNDED,
                 x, y, 50, 20,
                 3, "--", GRAY_D, 0, GRAY_D,
                 WHITE) {

		}
	};
    LabelMax* labelMax;

	/**------------------------------------------------------------------------
	 *
	 *  ButtonMin is an internal class creating a button with which
	 *  the maximum (i.e. 100%) can be specified.
	 *
	 *-----------------------------------------------------------------------*/
	class ButtonMax : public ButtonWidget {

	  public:
		ButtonMax(Widget* parent, int16_t x, int16_t y) :
			ButtonWidget(parent, BUTTON_ROUNDED,
	                x, y, 50, 20,
	                3, GRAY_D, 2, WHITE,
	                WHITE, "Maximum") {
		}

	    void action(TouchEvent* event) {
	    	//
	    	// Read out the sensor for the current distance.
	    	//
	    	(((FluidLevelConfigWidget*)parent)->sensor)->exec();  // Measure the distance
	    	((FluidLevelConfigWidget*)parent)->max = (((FluidLevelConfigWidget*)parent)->sensor)->getDistance();

	    	//
	    	// Live update of the value converter/Level indicattor results
	    	//
	    	((FluidLevelConfigWidget*)parent)->converter->updateMaxRaw(((FluidLevelConfigWidget*)parent)->max);

	    	//
	    	// Update the new value in the configuration screen
	    	//
	    	char buf[16];
            sprintf(buf, "%d", ((FluidLevelConfigWidget*)parent)->max);
            (((FluidLevelConfigWidget*)parent)->labelMax)->setText(buf);
	    }

	};
	ButtonMax*     buttonMax;

	/**------------------------------------------------------------------------
	 *
	 *  ButtonCancel is an internal class creating an OK button
	 *
	 *-----------------------------------------------------------------------*/
	class ButtonOk : public ButtonWidget {

	  public:
		ButtonOk(Widget* parent, int16_t x, int16_t y) :
			ButtonWidget(parent, BUTTON_ROUNDED,
	                x, y, 50, 20,
	                3, GRAY_D, 2, WHITE,
	                WHITE, "OK") {
		}

	    void action(TouchEvent* event) {

	    	//
	    	//  Persist the modified maximum and minimum levels
	    	//
	    	((FluidLevelConfigWidget*)parent)->config->sensorMinimum =
	    			((FluidLevelConfigWidget*)parent)->min;

	    	((FluidLevelConfigWidget*)parent)->config->sensorMaximum =
	    			((FluidLevelConfigWidget*)parent)->max;

	    	persistentWriteArea(((FluidLevelConfigWidget*)parent)->areaName,
	    			sizeof(fluidTankLevelConfig),
					(char*)((FluidLevelConfigWidget*)parent)->config);


            parent->setVisible(false);
		}

	    void onUntouch(TouchEvent* event) {

	    }
	};
	ButtonOk*     buttonOk;

	/**------------------------------------------------------------------------
	 *
	 *  ButtonCancel is an internal class creating a Cancel button
	 *
	 *-----------------------------------------------------------------------*/
	class ButtonCancel : public ButtonWidget {

	  public:
		ButtonCancel(Widget* parent, int16_t x, int16_t y) :
			ButtonWidget(parent, BUTTON_ROUNDED,
	                x, y, 50, 20,
	                3, GRAY_D, 2, WHITE,
	                WHITE, "Cancel") {
		}

	    void action(TouchEvent* event) {

	          parent->setVisible(false);
		}

	    void onUntouch(TouchEvent* event) {

	    }
	};
	ButtonCancel* buttonCancel;

  public:
	FluidLevelConfigWidget::FluidLevelConfigWidget(
			Widget* parent,                        // The parent
			int16_t x, int16_t y,                  // x, y coordinates
			DistanceSensor *sensor,                // Sensor to read min/max
			char* areaName,                        // name for persistentArea
			char* fluidName,                       // name of the fluid
			fluidTankLevelConfig* pConfig);        // Dialog constructor

	virtual void draw();
	virtual void drawInverted();
	virtual void redraw();
	virtual void setVisible(bool v);

	uint16_t    getMinimum();
	uint16_t    getMaximum();
	const char* getFluidName();

	void        setMinimum(uint16_t minimum);
	void        setMaximum(uint16_t maximum);
	void        setFluidName(char* name);

	void        setValueConverter(ValueConverter* c);

	fluidTankLevelConfig* readConfiguration();
	fluidTankLevelConfig* createConfiguration();

private:
	void         drawTitle(char* title, uint16_t color);
	void         updateGuiMinimum(uint16_t m);
	void         updateGuiMaximum(uint16_t m);
	void         updateGuiFluidName(char* fluid);


};

#endif
