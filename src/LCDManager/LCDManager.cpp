/*
 * 
 * 
 */

//
#include "LCDManager.h"

// Constructor
LCDManager::LCDManager(BoardType boardType, int cols, int rows) 
    : lcd(0x27, cols, rows), board(boardType), cols(cols), rows(rows) {

    // Initialize I2C pins based on board type.
    switch (boardType) {
        case UNO:
            Wire.begin();       // SDA and SCL are hardware-defined
            break;
        case D1R1:
            Wire.begin();       // GPIO4 (SDA), GPIO5 (SCL)
            break;
        case D1R1MC:
            Wire.begin();       // GPIO4 (SDA), GPIO5 (SCL)
            break;
    }

}

// Initialize LCD
void LCDManager::init() {
  lcd.init();
  lcd.backlight();
}

// Clear LCD
void LCDManager::clear() {
  lcd.clear();
}

// Print text on a specific line.
void LCDManager::print(int line, String text) {
  lcd.setCursor(0, line);
  lcd.print(text);
}

// Print text at a specific position.
void LCDManager::print(int line, int row, String text) {
  lcd.setCursor(row, line);
  lcd.print(text);
}

// Print custom hourglass emoji at a specific position.
void LCDManager::printHourglassEmoji(int line, int row) {

  // Load custom emoji
  lcd.createChar(0, hourglassEmoji);
  lcd.setCursor(row, line);

  // Display custom character
  lcd.write(byte(0));

}

//
void LCDManager::simulateMatrixRain() {
  
  static int columnPositions[20];  // Track the current position of "rain" in each column
  static int columnCharacters[20]; // Track the characters currently falling in each column
  static int bottomCharacters[20]; // Track characters currently "resting" at the bottom
  static int bottomTimers[20];     // Track how long characters stay at the bottom

  // Initialize columns (only on the first run).
  static bool initialized = false;

  if (!initialized) {
    for (int col = 0; col < cols; col++) {
      columnPositions[col] = random(-rows, 0);  // Start drops above the visible area
      columnCharacters[col] = random(166, 224); // Assign a random character
      bottomCharacters[col] = ' ';              // No character resting initially
      bottomTimers[col] = 0;                    // No lingering timer initially
    }
    initialized = true;
  }

  // Update each column.
  for (int col = 0; col < cols; col++) {

    // Add a probability check to reduce density.
    // 50% chance to update this column (adjust probability as needed).
    if (random(0, 100) < 50) {

      // Erase the previous character in this column.
      if (columnPositions[col] > 0 && columnPositions[col] < rows) {
        lcd.setCursor(col, columnPositions[col] - 1);
        lcd.print(' '); // Clear the previous position
      }

      // Draw the new character at the current position.
      if (columnPositions[col] >= 0 && columnPositions[col] < rows) {
        lcd.setCursor(col, columnPositions[col]);
        lcd.write(columnCharacters[col]);
      }

      // Move the character downward.
      columnPositions[col]++;

      // If the character reaches the bottom, make it "rest" there.
      if (columnPositions[col] == rows) {
        bottomCharacters[col] = columnCharacters[col];
        bottomTimers[col] = random(3, 8);         // Set a random linger time (in updates)
        columnPositions[col] = -1;                // Reset column for a new drop
        columnCharacters[col] = random(166, 224); // Assign a new random character
      }
    }

    // Handle bottom characters lingering.
    if (bottomTimers[col] > 0) {
      lcd.setCursor(col, rows - 1);
      lcd.write(bottomCharacters[col]); // Keep the character displayed at the bottom
      bottomTimers[col]--;              // Decrease the linger timer
    }
    else if (bottomTimers[col] == 0) {
      // Clear the bottom character when the timer expires.
      lcd.setCursor(col, rows - 1);
      lcd.print(' ');
      bottomCharacters[col] = ' ';
    }

  }

  // Adjust for speed of the rain.
  delay(150);

}


// Test LCD by printing all ASCII characters.
void LCDManager::testAscii(int asciiStart, int asciiEnd, int interval) {

  //
  Serial.print("Testing LCD matrix...");
  Serial.print(cols);
  Serial.print("x");
  Serial.print(rows);
  Serial.println(".");

  //
  clear();

  //
  for (int ascii = asciiStart; ascii <= asciiEnd; ascii++) {

    // Calculate row and column based on position.
    //Serial.println(ascii);

    // Cycle through all positions.
    int position = (ascii - 32) % (cols * rows);

    // Determine row.
    int row = position / cols;

    // Determine column.
    int col = position % cols;

    // Set cursor to calculated position.
    lcd.setCursor(col, row);

    // Write character to the LCD.
    lcd.write(ascii);

    // Delay to observe each character.
    delay(interval);

    // Clear the LCD when restarting.
    if (position == (cols * rows) - 1) {

      // Clear the screen after all positions are filled.
      lcd.clear();

    }

  }

}
