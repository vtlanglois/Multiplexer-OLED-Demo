#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/**
* OLED Screen Specs
*/
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  // change depending on I1C or I2C Screen

/**
* Multiple Screen Specs
*/
#define MAX_SCREENS 4
#define SCREEN_1 2
#define SCREEN_2 3
#define SCREEN_3 4
#define SCREEN_4 5

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

/**
* Array of all available screens
*/
int screens[] = {SCREEN_1, SCREEN_2, SCREEN_3, SCREEN_4};

/**
  Data representation of a planet for the solar system demo
*/
struct Planet {
  int center_x;  // x positon of the planet
  int center_y;  // y positon of the planet
  int radius;    // radius (half of diameter) of the planet
  float angle;   // current angle of the planet
};

/**
 Switches multiplexer bus to a different bus.
 @param bus multiplexer id
*/
void switchToDisplay(uint8_t bus){
  Wire.beginTransmission(0x70);  // TCA9548A address
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
  Serial.print(bus);
}

/**
 Initializes a display. If a screen fails, run an infinite loop to prevent further issues.
 @param screen the macro for the OLED screen
*/
void initDisplay(int screen) {
  // Init OLED display on bus number 2
  switchToDisplay(screen);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  } 
  // Clear the buffer
  display.clearDisplay();
}
 
void setup() {
  Serial.begin(9600);

  // Start I2C communication with the Multiplexer
  Wire.begin();

  // initialize all displays
  for(int screen : screens) {
      initDisplay(screen);
  }

}
 
void loop() {
  for(int screen : screens) {
      randomSeed(millis());
      Serial.println(screen);
      switchToDisplay(screen);
      display.clearDisplay();
      int x = (int) random(0, SCREEN_WIDTH);
      int y = (int) random(0, SCREEN_HEIGHT);
      int r = (int) random(1, 5);
      display.fillCircle(x, y, r, WHITE);
      display.display();
  }
}