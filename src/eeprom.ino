#include <EEPROM.h>

// The current address in the EEPROM (i.e. which byte we're going to write to next).
int addr = 0;

/**/
void eeprom_setup() {
  
  // Stores values read from analog input 0 into the EEPROM. These values will stay in the
  //EEPROM when the board is turned off and may be retrieved later by another sketch.
  Serial.begin(9600);
  Serial.println("\nStarting AMS-DOS...");
  
  //
  EEPROM.begin(512);

  //
  for (int i = 0 ; i < EEPROM.length() ; i++) {

    //
    EEPROM.write(i, 0);
    
  }
  
  //
  Serial.println("EEPROM cleared.");

}

/*
Board Name    | Model No.
--------------|----------
UNO           | 1
MEGA          | 2
NANO          | 3
ATTINY85      | 85
ESP8266       | 22
ESP8266 MINI  | 23
ESP32         | 32
*/

// Note: EEPROM.begin(512) must be called in setup()

/**/
void clearEEPROM() {

  // Divide by 4 because analog inputs range from 0 to 1023 and each byte of the
  // EEPROM can only hold a value from 0 to 255.
  int val = analogRead(A0) / 4;

  // Write the value to the appropriate byte of the EEPROM. These values will
  // remain there when the board is turned off.
  EEPROM.write(addr, val);

  // Advance to the next address. There are 512 bytes in the EEPROM, so go back
  // to 0 when we hit 512. Save all changes to the flash.
  addr = addr + 1;

  //
  if (addr == 512) {
    
    //
    addr = 0;
    
    //
    if (EEPROM.commit()) {
      
      //
      Serial.println("EEPROM successfully committed.");
    
    } else {
      
      //
      Serial.println("EEPROM commit failed.");
    
    }
    
  }
  
}

/**/
int readEEPROM(int addr) {
  
  //
  //EEPROM.begin(512);
  
  //
  int val = EEPROM.read(addr);
  
  //
  return val;
  
}

/**/
bool writeEEPROM(int addr, int val) {

  //
  //EEPROM.begin(512);
  
  //
  delay(500);

  //
  EEPROM.write(addr, val);

  //
  delay(500);

  //
  if (EEPROM.commit()) {
    Serial.println("EEPROM: Write OK");
    return true;
  }
  else {
    Serial.println("EEPROM: Write Failed");
    return false;
  }
  
}
