#include <Persistence.h>
#include <Dump.h>

void setup() {
 
   //
   //  Initialize Serial for monitoring
   //
   Serial.begin(9600);
   while (!Serial) ;
   delay(1000);

   //
   //  Announce start of EEPROM clearing
   //
   Serial.println();
   Serial.print("Start clearing persistent memory on "); Serial.print(BOARD); Serial.println("...");

   //
   //  Mark current time stamp
   //
   uint32_t now = millis();

   //
   //  Clear the persistent memory area
   //
   uint16_t inspected  = 0;
   uint16_t modified   = 0;
   uint16_t unmodified = 0;
   uint16_t failures   = 0;
   for (uint16_t addr  = 0; addr < EEPROM_SIZE; addr++) {

    //
    //  Show progress
    //
    if (addr % 0x100 == 0) {
      Serial.print(F("At address: 0x")); Serial.println(addr, HEX);
    }

    //
    // Write a byte, if needed.
    //
    inspected++;
    if (EEPROM.read(addr) != 0xff) {
      EEPROM.write(addr, 0xff);
      modified++;

      //
      //  Check for a write failure
      //
      if (EEPROM.read(addr) != 0xff) {
        Serial.println(F("Write error at: 0x"));Serial.println(EEPROM.read(addr));
        failures;
      }
    }
    else {
      unmodified++;
    }

   }
   Serial.print(F("At address: 0x")); Serial.print(EEPROM_SIZE, HEX);

   //
   //  If desired visually inspect the EEPROM
   //
   if (failures) {

     if (ask("\n\nInspect memory due to write failures (y/n)? :")) {
       for (uint16_t addr = 0; addr < EEPROM_SIZE; addr += 256) {

        dumpSerial.dumpEeprom(addr, 0xff);

       }
     }
   }

   //
   //  Report we are ready clearing
   //
   Serial.print(F(" Ready clearing ")); Serial.print(EEPROM_SIZE); Serial.println(F(" bytes of persistent memory."));
   Serial.print(F("It took ")); Serial.print((millis() - now)); Serial.println(F(" ms."));

   Serial.println();
   Serial.println(F("Results summary:"));
   Serial.println("-------------------------");
   Serial.print(F("Inspected   : ")); Serial.println(inspected);
   Serial.print(F("Modified    : ")); Serial.println(modified);
   Serial.print(F("Unmodifed   : ")); Serial.println(unmodified);
   Serial.print(F("Write errors: ")); Serial.println(failures);
   Serial.println();
   if (failures == 0) {
     Serial.println(F("--- Memory is OK --- This Arduino is now ready to run TerraBox sketches"));
   }
   else {
     Serial.println(F("*** Memory failures *** You cannot use this Arduino for TerraBox provided sketches"));
   }
}

void loop() {
  // put your main code here, to run repeatedly:

}

bool ask(char* prompt) {
     
     Serial.println(prompt);
     while (!Serial.available());
     char c;

     while ((c = Serial.read())) {
       Serial.print(c);

       switch (c) {
         case 'y':
         case 'Y':
           return true;

        case 'n':
        case 'N':
          return false;

        default:
          Serial.println("Enter y/n: ");
          while (!Serial.available());
      }
     }

}