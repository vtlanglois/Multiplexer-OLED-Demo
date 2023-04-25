#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSerif9pt7b.h>

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

#define MAX_DEMOS 3

const int interruptPin = 2;  // digital input pin for recieiving button presses

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

/**
* Array of all available screens
*/
int screens[] = { SCREEN_1, SCREEN_2, SCREEN_3, SCREEN_4 };

int currentDemo = 0;  //the currently displayed demo

/**
 Switches multiplexer bus to a different bus.
 @param bus multiplexer id
*/
void switchToDisplay(uint8_t bus) {
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
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  // Clear the buffer
  display.clearDisplay();
}

void setup() {
  Serial.begin(9600);

  // Start I2C communication with the Multiplexer
  Wire.begin();

  // initialize all displays
  for (int screen : screens) {
    initDisplay(screen);
  }
  // set up interrupt
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), goToNextDemo, RISING);
}

void loop() {
  switch(currentDemo) {
    case 0:
      drawRandomCirclesDemo();
      break;
    case 1:
      drawPyramidDemo();
      break;
    case 2:
      drawTextDemo();
      break;
  }
}

void drawRandomCirclesDemo() {
  for (int screen : screens) {
    randomSeed(millis());
    Serial.println(screen);
    switchToDisplay(screen);
    display.clearDisplay();
    int x = (int)random(0, SCREEN_WIDTH);
    int y = (int)random(0, SCREEN_HEIGHT);
    int r = (int)random(1, 10);
    display.fillCircle(x, y, r, WHITE);
    display.display();
  }
}

void drawPyramidDemo() {
  //Screen 1 - Moon + top right;
  switchToDisplay(SCREEN_1);
  display.clearDisplay();
  display.fillCircle(20, 20, 20, WHITE);
  display.fillCircle(18, 18, 20, BLACK);
  display.fillTriangle(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2 * 2, SCREEN_HEIGHT * 2, WHITE);
  display.display();
  //Screen 2 - top left
  switchToDisplay(SCREEN_2);
  display.clearDisplay();
  display.fillTriangle(-SCREEN_WIDTH / 2, SCREEN_HEIGHT, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT, WHITE);
  display.display();

  //Screen 3 - bottom right
  switchToDisplay(SCREEN_3);
  display.clearDisplay();
  display.fillTriangle(0, SCREEN_HEIGHT, SCREEN_WIDTH, -SCREEN_HEIGHT, SCREEN_WIDTH / 2 * 2, SCREEN_HEIGHT * 2, WHITE);
  display.display();

  //Screen 4 - bottom left
  switchToDisplay(SCREEN_4);
  display.clearDisplay();
  /**
    @TODO: refactor this to use the fillTriangle function call. 
  */
  display.fillRect(0, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT, WHITE);
  int x = SCREEN_WIDTH / 2;
  int y = SCREEN_HEIGHT - 1;
  for (int i = 0; i < SCREEN_HEIGHT; i++) {
    display.drawFastHLine(x, y, SCREEN_WIDTH / 2 - i, WHITE);
    y--;
  }
  display.display();
}

void drawTextDemo() {
  //Screen 1 - Haiku
  switchToDisplay(SCREEN_1);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("In the Cicada's cry");
  display.println("No sign can foretell");
  display.println("How soon it must die.");
  display.println(" - Matsuo Basho");
  display.display();

  //Screen 2 - Joke
  switchToDisplay(SCREEN_2);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("The FitnessGram Pacer Test is a multistage aerobic capacity test that progressively gets more difficult as it continues. ");
  display.display();

  //Screen 2 - Elden Ring Stats
  switchToDisplay(SCREEN_3);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Vigor: 26");
  display.println("Mind: 15");
  display.println("Endurance: 20");
  display.println("Strength: 16");
  display.println("Dexerity: 24");
  display.println("Intelligence: 9");
  display.println("Faith: 12");
  display.println("Arcane: 14");
  display.display();

    //Screen 2 - Demo Stats
  switchToDisplay(SCREEN_4);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Time (MS) since start: ");
  display.println(millis());
  display.display();
}

void goToNextDemo() {
  // Circular loop for demo selection
  currentDemo = (currentDemo + 1) % MAX_DEMOS;
}
