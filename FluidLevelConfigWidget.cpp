/*-------------------------------------------------------------------------------------------------


       /////// ////// //////  //////   /////     /////    ////  //    //
         //   //     //   // //   // //   //    //  //  //   // // //
        //   ////   //////  //////  ///////    /////   //   //   //
       //   //     //  //  // //   //   //    //   // //   //  // //
      //   ////// //   // //   // //   //    //////    ////  //   //

     
                 A R D U I N O   D I S T A N C E  S E N S O R S


                 (C) 2024, C. Hofman - cor.hofman@terrabox.nl

          <FluidLevelConfigWidget.cpp> - Library for LevelIndicators.
                               18 Aug 2024
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
#include <FluidLevelConfigWidget.h>

#define OFFSET  5

FluidLevelConfigWidget::FluidLevelConfigWidget(
                            Widget* parent,
							int16_t x, int16_t y,
							DistanceSensor* pSensor,
							char* theAreaName,
							char* theFluidName,
                            fluidTankLevelConfig* pConfig) :
                        Widget(parent, x, y, 0, 0) {

	strcpy(nameId, "FluidConfig");
	widgetSize = sizeof(FluidLevelConfigWidget);

	sensor     = pSensor;
	areaName   = theAreaName;
	fluidName  = theFluidName;
	config     = pConfig;

	int16_t formSideMargin = 20;
	int16_t formTopMargin  = 25;

    int16_t offset = OFFSET;
    int16_t startX = x + formSideMargin; // Relative to this widget

    //---------------------------------------
    //    First Row
    //
    int16_t currentX = startX;             // Relative to this widget
    int16_t currentY = y + formTopMargin;  // Relative to this widget

    //
    //     Max label
    //
    labelMax = new LabelMax(this, currentX, currentY);
    currentX += labelMax->width + offset;

    //
    //     Max button
    //
    buttonMax = new ButtonMax(this, currentX, currentY);
    currentX  = buttonMax->width  + offset;

    //---------------------------------------
    //  Next row
    //
    currentX  = startX;
    currentY += buttonMax->height + (offset/2);

    //
    //     Min label
    //
    labelMin  = new LabelMin(this, currentX, currentY);
    currentX += labelMin->width + offset;

    //
    //     Min button
    //
    buttonMin = new ButtonMin(this, currentX, currentY);
    currentX += buttonMin->width + offset;

    //-----------------------------------------
    //  Next row
    //
    currentX  = startX;
    currentY += buttonMin->height + offset;

    //
    //     Cancel button
    //
    buttonCancel = new ButtonCancel(this, currentX, currentY);
    currentX += buttonCancel->width + offset;

    //
    //     Ok button
    //
    buttonOk  = new ButtonOk(this, currentX, currentY);

    currentX += buttonOk->width + formSideMargin;
    currentY += buttonOk->height + offset;

    width  = currentX - x;
    height = currentY - y;

    //
    //  Make this screen invisible by default
    //
    setVisible(false);
}

/**----------------------------------------------------------------------------
 *
 *  Assign a value converter which must be updated if minimum or maximum
 *  levels are modified.
 *
 * @param c    The value converter
 *
 *---------------------------------------------------------------------------*/
void FluidLevelConfigWidget::setValueConverter(ValueConverter* c) {
	converter = c;
}

/**----------------------------------------------------------------------------
 *
 *  Make this widget and all its child widgets visible/invisible
 *
 *  @param v    True -> visible, False -> invisible
 *
 *---------------------------------------------------------------------------*/
void FluidLevelConfigWidget::setVisible(bool v) {

	Widget::setVisible(v);

	updateGuiMinimum(config->sensorMinimum);
    updateGuiMaximum(config->sensorMaximum);
}

/**----------------------------------------------------------------------------
 *
 *  Draws the title of this popup form.
 *
 *  @param title   The title
 *  @param color   The color
 *
 *---------------------------------------------------------------------------*/
void FluidLevelConfigWidget::drawTitle(char* title, uint16_t color) {

    Screen.fillRect(x+2, y+2, width-2, height-2, GRAY_D);
    Screen.fillRect(x, y, width-2, height-2, GRAY_L);

	//
	//  Calculate the text width & heoght
	//
	Screen.setTextSize(2);
    uint16_t xr, yr, textWidth, textHeight;
    Screen.getTextBounds(title, x, y, &xr, &yr, &textWidth, &textHeight);

    Screen.fillRect(x+1, y+2, width-3, textHeight+4, BLACK);
    Screen.fillRect(x+2, y+1, width-3, textHeight+4, GRAY_D);
    //
    //  Calculate the coordinates
    //
    int16_t titleX = x + (width - textWidth)/2;
    int16_t titleY = y + OFFSET;

    //
    //  Draw the title
    //
    Screen.setCursor(titleX, titleY);
    Screen.setTextColor(color);
    Screen.print(title);

    Screen.setCursor(titleX-1, titleY-1);
    Screen.setTextColor(~color);
    Screen.print(title);

}

/**---------------------------------------------------------------------------
 *
 *  Draw the Fluid Level Configuration widget.
 *
 *--------------------------------------------------------------------------*/
void FluidLevelConfigWidget::draw() {

	inverted = false;
    if (! isVisible())
    	return;

    drawTitle("S E T U P", BLACK);

	labelMin->draw();
	labelMax->draw();
	buttonMin->draw();
	buttonMax->draw();
	buttonOk->draw();
	buttonCancel->draw();
}

/**----------------------------------------------------------------------------
 *
 *  Draw the configurator with inverted colors
 *
 *---------------------------------------------------------------------------*/
void FluidLevelConfigWidget::drawInverted() {

	inverted = true;
    if (! isVisible())
    	return;

    Screen.fillRect(x, y, width, height, ~GRAY_L);
    drawTitle("S E T U P", ~BLACK);

	labelMin->drawInverted();
	labelMax->drawInverted();
	buttonMin->drawInverted();
	buttonMax->drawInverted();
	buttonOk->drawInverted();
	buttonCancel->drawInverted();
}

/**----------------------------------------------------------------------------
 *
 *  Redraw the configurator
 *
 *---------------------------------------------------------------------------*/
void FluidLevelConfigWidget::redraw() {
    if (! isVisible())
    	return;

	if (!inverted)
		draw();
	else
		drawInverted();
}

/**----------------------------------------------------------------------------
 *
 *  Assign a fluidName to this configuration
 *
 * @param fluidName  The name to assign
 *
 *---------------------------------------------------------------------------*/
void FluidLevelConfigWidget::setFluidName(char* fluidName) {
	strncpy(config->title, fluidName, sizeof(config->title-1));

	updateGuiFluidName(fluidName);
}

/**----------------------------------------------------------------------------
 *
 *   Update the fluid name in the configurator GUI
 *
 * @param fluid  The name of the Fluid the level indicator resembles
 *
 *---------------------------------------------------------------------------*/
void FluidLevelConfigWidget::updateGuiFluidName(char* fluid) {
  // Currently the name is not shown in the configurator GUI
}

/**----------------------------------------------------------------------------
 *
 *  Return the assigned fluidName.
 *
 * @return    The assigned name
 *
 *---------------------------------------------------------------------------*/
const char* FluidLevelConfigWidget::getFluidName() {
  return config->title;
}

/**----------------------------------------------------------------------------
 *
 *   Assign the minimum level in millimeters.
 *   Note that the minimum does not have to be smaller than the maximum.
 *   This is useful with fluid tanks, which can have a level sensor
 *   on top of the tank and measure the distance to the fluid surface.
 *   In this configuration the distance of the minimum fluid surface has
 *   a greater distance, than the maximum fluid surface.
 *
 * @param m  The millimeters representing the distance to the minimum level.
 *
 *---------------------------------------------------------------------------*/
void FluidLevelConfigWidget::setMinimum(uint16_t m) {
	config->sensorMinimum = m;

	updateGuiMinimum(m);
}

/**----------------------------------------------------------------------------
 *
 *  Update ths minimum fluid level in the configuration GUI.
 *
 * @param m   The minimum level in mm.
 *
 *---------------------------------------------------------------------------*/
void FluidLevelConfigWidget::updateGuiMinimum(uint16_t m) {
	if (!isVisible())
		return;

	if (converter)
	  converter->updateMinRaw(m);

	char buff [16];
	//
	//  Show the new percentage explicitly
	//
	sprintf(buff, "%d", m);
	labelMin->setText(buff);

}

/**----------------------------------------------------------------------------
 *
 *   Assign the maximum level in millimeters.
 *
 * @return  The millimeters representing the distance to the minimum level.
 *
 *---------------------------------------------------------------------------*/
uint16_t FluidLevelConfigWidget::getMinimum() {
	return config->sensorMinimum;
}

/**----------------------------------------------------------------------------
 *
 *   Assign the maximum level in millimeters.
 *   Note that the maximum does not have to be greater than the minimum.
 *   This is useful with fluid tanks, which can have a level sensor
 *   on top of the tank and measure the distance to the fluid surface.
 *   In this configuration the distance of the minimum fluid surface level
 *   has a greater distance to the fluid surface than the maximum level.
 *
 * @param m  The millimeters representing the distance to the minimum level.
 *
 *---------------------------------------------------------------------------*/
void FluidLevelConfigWidget::setMaximum(uint16_t m) {
	config->sensorMaximum = m;

	updateGuiMaximum(m);
}

/**----------------------------------------------------------------------------
 *
 *  Updates the maxmimum level in the configuration GUI
 *
 * @param m   The maximum level in mm
 *
 *---------------------------------------------------------------------------*/
void FluidLevelConfigWidget::updateGuiMaximum(uint16_t m) {
	if (!isVisible())
		return;

	if (converter)
	  converter->updateMaxRaw(m);

	char buff [16];
	//
	//  Show the new percentage explicitly
	//
	sprintf(buff, "%d", m);
	labelMax->setText(buff);
}

/**----------------------------------------------------------------------------
 *
 *   Returns the configured distance to the maximum level in millimeters.
 *
 * @return  The millimeters representing the distance to the maximum level.
 *
 *---------------------------------------------------------------------------*/
uint16_t FluidLevelConfigWidget::getMaximum() {
	return config->sensorMaximum;
}

/**----------------------------------------------------------------------------
 *
 *  Reads an existing configuration
 *
 * @return         The filled configuration data structure
 *
 *---------------------------------------------------------------------------*/
fluidTankLevelConfig* FluidLevelConfigWidget::readConfiguration() {
	uint16_t size = sizeof(fluidTankLevelConfig);
	char* data    = (char*) config;

	if (hasPersistentArea(areaName)) {
		uint16_t rc   = persistentReadArea(areaName, size, data);  // Read the configuration

		//
		// Check if the are could be read
		//
		if (rc > 0) {

			//
			//  Check if the minimum ad maximum levels are unequal.
			//  Since an equal min and max value would be useless.
			//
			if (config->sensorMinimum != config->sensorMaximum) {

				//
				//  Check if we have a title
				//
				if (strlen(config->title) > 0) {
					updateGuiMinimum(config->sensorMinimum);
					updateGuiMaximum(config->sensorMaximum);
					setFluidName(config->title);
					return config;
				}
				else {
			        Screen.setCursor(0, 0);
			        Screen.print(F("No fluid name was found"));
				}
			}
			else {
		      Screen.setCursor(0, 0);
		      Screen.print(F("No fluid name was found"));
			}
		}
		else {
		  Screen.setCursor(0, 0);
		  Screen.print(F("Area "));Screen.print(areaName);Screen.print(" could not be read, rc=");Screen.println(rc);
		}
	}

	return nullptr;
}

/**----------------------------------------------------------------------------
 *
 *  Create a new persistent data area for the tank configuration.
 *
 * @return         The initialized configuration
 *
 *---------------------------------------------------------------------------*/
fluidTankLevelConfig* FluidLevelConfigWidget::createConfiguration() {
	uint16_t size = sizeof(fluidTankLevelConfig);
	char* data    = (char*) config;


	uint32_t addr = newPersistentArea(areaName, size);  // Create new area
	if (addr > 0)  {
	  config->sensorMinimum = 200;
	  config->sensorMaximum = 0;
	  strcpy(config->title, fluidName);

	  updateGuiMinimum(config->sensorMinimum);  // Default value, minimal fluid -> far away distance
	  updateGuiMaximum(config->sensorMaximum);	  // Default value, maximal fluid -> near by distance
      updateGuiFluidName(config->title);

      Screen.setCursor(0, 0);

	  if (persistentWriteArea(areaName, size, (char*)config) == size) { // Store in Eeprom
		Screen.print(F("Stored default fluid levels"));
		return config;
	  }

	  Screen.print(F("Unable to store default fluid levels"));
    }
    else {
      Screen.setCursor(0, 0);
      Screen.print(F("Could not allocate persisent storage, rc="));Screen.print(addr);
	}

	return nullptr;
}
