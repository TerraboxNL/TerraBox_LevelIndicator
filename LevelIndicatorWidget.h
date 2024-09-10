/*-------------------------------------------------------------------------------------------------


       /////// ////// //////  //////   /////     /////    ////  //    //
         //   //     //   // //   // //   //    //  //  //   // // //
        //   ////   //////  //////  ///////    /////   //   //   //
       //   //     //  //  // //   //   //    //   // //   //  // //
      //   ////// //   // //   // //   //    //////    ////  //   //

     
               A R D U I N O   L E V E L   I N D I C A T O R


                 (C) 2024, C. Hofman - cor.hofman@terrabox.nl

               <LevelIndicatorWidget.h> - Library forGUI Widgets.
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
#include <TerraBox_Widgets.h>
#include <BarWidget.h>
#include <LabelWidget.h>

#ifndef LEVELINDICATORWIDGET_h
#define LEVELINDICATORWIDGET_h

#define WELCOME_MESSAGE_TIMEOUT  60000    // Time the welcome message is shown

/*============================================================================
 *  L E V E L  I N D I C A T O R  W I D G E T
 *===========================================================================*/
class LevelIndicatorWidget : public Widget {
  private:
    LabelWidget* welcomeMessage = nullptr; // Keeps track of welcom message timing
    uint32_t     welcomeTimeout = 0;

    bool         welcomeShown   = false;

    LabelWidget *title;
    LabelWidget *value;
    uint16_t    currentHeight;
    const String unit;


  public:

    BarWidget   *bar;

             LevelIndicatorWidget(
                   Widget* parent, const char *name, uint16_t labelSize, 
                   int16_t px, int16_t py, uint16_t pwidth, uint16_t pheight, 
                   uint16_t pBgColor, uint16_t pStroke, uint16_t pStrokeColor, 
                   uint16_t pTickLength, uint16_t pTickStroke, Levels* pLevels,
                   String pUnit, Widget* configurator);
//    virtual ~LevelIndicatorWidget();

    virtual void draw();
    virtual void redraw();
    virtual void clear();
    virtual void drawInverted();
    void         update(uint16_t newValue);

//    virtual void onEvent(TouchEvent* event);
};

#endif
