#include <Arduino.h>
#include <U8g2lib.h>
#include <Adafruit_GFX.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

// 1. PIN DEFINITIONS (Adjust for your specific wiring)
#define DISP_CS    5
#define DISP_DC    6
#define DISP_RESET 10

// 2. U8G2 CONSTRUCTOR for ST7305 300x400
// Use 'F' for Full Buffer mode (requires ~15KB RAM)
U8G2_ST7305_300X400_F_4W_HW_SPI u8g2(U8G2_R0, DISP_CS, DISP_DC, DISP_RESET);

// 2.0"
//U8G2_ST7305_168X384_F_4W_HW_SPI u8g2(U8G2_R0, DISP_CS, DISP_DC, DISP_RESET);

// 3. THE BRIDGE CLASS
// This allows Adafruit_GFX to draw directly into the U8g2 buffer
class U8g2_GFX_Bridge : public Adafruit_GFX {
  public:
    U8g2_GFX_Bridge(U8G2 &u8g2_ref) : Adafruit_GFX(u8g2_ref.getDisplayWidth(), u8g2_ref.getDisplayHeight()), _u8g2(u8g2_ref) {}
    
    // Mandatory override: Tells Adafruit_GFX how to draw a single pixel
    void drawPixel(int16_t x, int16_t y, uint16_t color) override {
      _u8g2.setDrawColor(color); 
      _u8g2.drawPixel(x, y);
    }
  private:
    U8G2 &_u8g2;
};

// Create the bridge instance
U8g2_GFX_Bridge display(u8g2);

void setup() {
  u8g2.begin(); // Initialise the U8g2 hardware
}

void loop() {
  u8g2.clearBuffer(); // Clear the internal U8g2 memory
  
  // --- Standard Adafruit_GFX Commands ---
  display.setCursor(10, 30);
  display.setTextColor(1);      // 1 = White/On for monochrome
  display.setTextSize(2);
  display.print("Adafruit GFX");

  display.drawLine(1,1, 298,1, 1);
  display.drawLine(1,1, 1,398, 1);
  display.drawLine(298,398,1,398, 1);
  display.drawLine(298,398,298,1, 1);
  
  display.drawRect(10, 50, 100, 50, 1);       // Draw a rectangle
  display.fillCircle(200, 100, 40, 1);       // Draw a filled circle
  display.drawLine(0, 0, 300, 400, 1);       // Draw a diagonal line
  
  // --- Send everything to the screen ---
  u8g2.sendBuffer(); // Required to actually update the display
  
  delay(2000);
}
