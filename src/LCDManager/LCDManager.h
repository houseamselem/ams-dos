/*

 UNO
 SDA: Analog pin A4
 SCL: Analog pin A5

 D1
 SDA: D14
 SCL: D15

 D1 Mini
 SDA: Digital pin D2 (GPIO4)
 SCL: Digital pin D1 (GPIO5)

 Power
 VCC: 5V/3.3V
 GND: G

 */

//
#ifndef LCD_MANAGER_H
#define LCD_MANAGER_H

//
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Arduino.h>

//
enum BoardType {
  UNO,
  D1R1,
  D1R1MC
};

//
class LCDManager {

private:
  LiquidCrystal_I2C lcd;
  BoardType board;
  int cols; // Number of columns
  int rows; // Number of rows
    
  // Custom characters
  // Clock emoji character bitmap (8x8 pixels)
  byte clockEmoji[8] = {
    B01110,
    B10001,
    B10101,
    B10011,
    B10001,
    B10101,
    B10001,
    B01110
  };
  
  //
  byte hourglassEmoji[8] = {
    B11111,
    B10001,
    B01010,
    B00100,
    B01010,
    B10001,
    B11111,
    B00000
  };
  
  // Define the custom sun emoji character
  byte sunEmoji[8] = {
    B00000,
    B01010,
    B00100,
    B00000,
    B10001,
    B01110,
    B00000,
    B00000
  };

public:
  // Constructor
  LCDManager(BoardType boardType, int cols, int rows);

  // Initialization
  void init();

  // Clear the screen.
  void clear();

  // Print text
  void print(int line, String text);
  void print(int line, int row, String text);

  // Print custom emoji.
  void printHourglassEmoji(int line, int row);

  // Matrix rain
  void simulateMatrixRain();

  // Test LCD by printing ASCII characters
  void testAscii(int asciiStart, int asciiEnd, int interval);

};

#endif // LCD_MANAGER_H
