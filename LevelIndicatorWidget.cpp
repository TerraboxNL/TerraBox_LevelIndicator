/*-------------------------------------------------------------------------------------------------


       /////// ////// //////  //////   /////     /////    ////  //    //
         //   //     //   // //   // //   //    //  //  //   // // //
        //   ////   //////  //////  ///////    /////   //   //   //
       //   //     //  //  // //   //   //    //   // //   //  // //
      //   ////// //   // //   // //   //    //////    ////  //   //


                 A R D U I N O   D I S T A N C E  S E N S O R S


                 (C) 2024, C. Hofman - cor.hofman@terrabox.nl

               <LevelIndicatorWidget.cpp> - Library forGUI Widgets.
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
#include <TerraBox_Widgets.h>
#include <LevelIndicatorWidget.h>
#include <PopupButton.h>

/*==============================================================================
 *
 *  The LevelIndicatorWidget is a composite class, which combines
 *  an indicator title label, a bar dynamically visualizing a rising and falling
 *  (fluid) level and a label displaying level as a numerical value.
 *
 *============================================================================*/

/*------------------------------------------------------------------------------
 *
 *  Create the level widget
 *
 *----------------------------------------------------------------------------*/
LevelIndicatorWidget::LevelIndicatorWidget(
                         Widget* parent,
                         const char *name, uint16_t labelSize, 
                         int16_t px, int16_t py, uint16_t pwidth, uint16_t pheight,
                         uint16_t pBgColor, uint16_t pStroke, uint16_t pStrokeColor, 
                         uint16_t pTickLength, uint16_t pTickStroke, Levels* pLevels,
                         String pUnit, Widget* configurator)
            : Widget(parent, px, py, pwidth, pheight) {

  strcpy(nameId, "LevelIndicator");
  widgetSize = sizeof(LevelIndicatorWidget);

  unit = pUnit;

  // Set the text size
  Screen.tft->setTextSize(labelSize);

  //
  // Calculate the text height for the title
  //
  uint16_t xr, yr, titleWidth, titleHeight, valueHeight;
  Screen.tft->getTextBounds(name, x, y, &xr, &yr, &titleWidth, &titleHeight);
  valueHeight = titleHeight;    //  Same test size, so same height.

  //
  //  Create the title label and set the title text.
  //
  title = new PopupButton(this, BUTTON_SQUARE,
                       x,         y, 
                       pwidth,    titleHeight + 2*pStroke, 
                       labelSize,         GRAY_D,
                       pStroke,   WHITE,      WHITE, name, configurator);

  currentHeight  = title->height;

  //
  //  Create the Bar widget.
  //
  bar = new BarWidget(this,
                      x,           y + currentHeight, 
                      width,       height+2*pStroke, pBgColor, 
                      pStroke,     pStrokeColor, 
                      pTickLength, pTickStroke, 
                      pLevels,     unit);
  currentHeight += bar->height;

  //
  //  Create the value label and set the initial value
  //
  value = new LabelWidget(this, x,         y + currentHeight,
                       width,     valueHeight + 2*pStroke, 
                       labelSize, "", GRAY_D,   
                       pStroke,   WHITE,        WHITE);

  value->setText("0");
  currentHeight += value->height;

}

/*------------------------------------------------------------------------------
 *
 *  Draw the widget
 *
 *----------------------------------------------------------------------------*/
void LevelIndicatorWidget::draw() {

 if (!isVisible())
	return;

  title->draw();
  bar  ->draw();
  value->draw();
}

/*---------------------------------------------------------------------------------
 *
 *  Redraw it as it was drawn the last time.
 *
 *-------------------------------------------------------------------------------*/
void LevelIndicatorWidget::redraw() {

  if (!isVisible())
 	return;

  if (!inverted) {
	  title->redraw();
	  bar  ->redraw();
	  value->redraw();
  }
  else
	drawInverted();

  //
  // Set to the last percentage
  //
  update(0);
}

/*---------------------------------------------------------------------------------
 *
 *  Redraw it as it was drawn the last time.
 *
 *-------------------------------------------------------------------------------*/
void LevelIndicatorWidget::drawInverted() {
	 if (!isVisible())
		return;

	  title->drawInverted();
	  bar  ->drawInverted();
	  value->drawInverted();

}

/*------------------------------------------------------------------------------
 *
 *  Update the level indicator displaying the newly measured value
 *
 *  newValue    The newly measured value
 *
 *----------------------------------------------------------------------------*/
void LevelIndicatorWidget::update(uint16_t newValue) {

  if (!isVisible())
	  return;

  char buff [16];  
  //
  //  Show the new percentage explicitly
  //
  sprintf(buff, "%d", newValue);
  value->setTextPercent(buff);

  //
  //  Show the new percentage on the bar as well
  //
  bar->update(newValue);
}
