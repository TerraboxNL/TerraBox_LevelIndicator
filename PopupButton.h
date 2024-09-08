/*-------------------------------------------------------------------------------------------------


       /////// ////// //////  //////   /////     /////    ////  //    //
         //   //     //   // //   // //   //    //  //  //   // // //
        //   ////   //////  //////  ///////    /////   //   //   //
       //   //     //  //  // //   //   //    //   // //   //  // //
      //   ////// //   // //   // //   //    //////    ////  //   //

     
                 A R D U I N O   D I S T A N C E  S E N S O R S


                 (C) 2024, C. Hofman - cor.hofman@terrabox.nl

               PopupButton.h - Library for LevelIndicators.
                                 7 Sep 2024
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
#include <TerraBox_Widgets.h>
#include <ButtonWidget.h>

#ifndef POPUP_BUTTON_H_
#define POPUP_BUTTON_H_

class PopupButton : public ButtonWidget {

public:
	Widget* popup = nullptr;

	PopupButton(Widget* parent, int16_t x, int16_t y, char* name, Widget* thePopup) :
		ButtonWidget(parent, BUTTON_SQUARE,
			                x, y, 50, 20,
			                3, GRAY_D, 2, WHITE,
			                WHITE, name) {
		strcpy(nameId, "PopupButton");
		popup = thePopup;
	}

	PopupButton(
	         Widget*  parent,
	   	     uint16_t pType,
	         int16_t  pX,       int16_t  pY,
	         uint16_t pWidth,   uint16_t pHeight,
	         uint16_t pTextSize,
	         uint16_t pBgColor,
	         uint16_t pStroke,  uint16_t pStrokeColor,
	         uint16_t pFgColor, char* pText, Widget* thePopup) :
	                    	   ButtonWidget(
	                    	         parent,
	                    	   	     pType,
	                    	         pX,       pY,
	                    	         pWidth,   pHeight,
	                    	         pTextSize,
	                    	         pBgColor,
	                    	         pStroke,  pStrokeColor,
	                    	         pFgColor, pText
	                    	   ) {

		strcpy(nameId, "PopupButton");
		popup = thePopup;
	}


	void action(TouchEvent* event) {

    	if (! popup->isVisible())
    	  popup->setVisible(true);

	}

};

#endif
