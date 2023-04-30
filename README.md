# Multiplexer OLED Screen Demo for Arduino

This repository provides code and instructions for building an Arduino-based device that showcases the capabilities of four OLED screens and a mulitplexer. The device consists of four OLED screens, a multiplexer, a button, a breadboard, wires, and an Arduino UNO, and it displays three demonstrations that illustrate various aspects of multiplexer and OLED screen usage.

This project was created for INFO-341 **Prototyping with Arduino Tools**, a class taught at Indiana University in Spring 2023.

## **Note**

This project is built to use a I1C OLED Screen. Using a I2C screen will not work with this codebase.

## Hardware Setup

To assemble the device, you will need:

- 4x I1C OLED screen
- Multiplexer
- Button
- Breadboard
- Jumper wires
- Arduino UNO

Follow these steps to set up the hardware:

1. Connect **5V** and **Ground** from the Arduino UNO to the breadboard in their appropriate buses.
2. Connect the multiplexer to the breadboard.
3. Connect the multiplexer pins **VCC** and **Ground** to **5V** and **Ground** from the breadboard bus.
4. Connect the multiplexer pins **A0**, **A1**, **A2** to **Ground** from the breadboard bus
5. Connect a jumper wire from **Analog Input A4** to **SDA** on the OLED screen.
6. Connect a jumper wire from **Analog Input A5** to **SCL** on the OLED screen.
7. For each screen, do the following:
   1. Connect **VCC** and **Ground** to **5V** and **Ground** on the breadboard bus
   2. Connect a jumper wire from **SD#** to **SDA** on the OLED screen.
   3. Connect a jumper wire from **SC#** to **SCL** on the OLED screen.
8. Connect the button to the breadboard.
9.  Connect a jumper wire to the top-left corner of the button, and connect a ground wire to the top-right corner.
10. Connect the jumper wire to **Digital Input 2** on the Arduino UNO

## Software Setup

To run the code, you will need to install the Arduino Integrated Development Environment (IDE) from the official [Arduino website](https://www.arduino.cc/en/software/) and follow these steps:

1. Clone this repository to your computer or download the ZIP file and extract its contents.
2. Open the `Multiplexer-OLED-demo.ino` file in the Arduino IDE.
3. Connect the Arduino UNO to your computer via USB cable.
4. Select the appropriate board and port from the "Tools" menu.
5. Click "Upload" to upload the code to the Arduino UNO.

## Usage

Once the code has been uploaded to the device, the button can be used to switch between the three demos:

1. **Solar System Animation**: This demo showcases circles appearing and disappearing at random positions on each screen. This serves to demonstrate how each screen can handle a seperate image.
2. **Pyramid in the Night**: This demo depicts a pyramid in the night with a crescent moon above it. This aims to demonstrate how a developer can use all available screens to draw a bigger, more complex image.
3. **Earth Data**: This demo displays four distinct textboxes on each screen. This serves to demonstrate printing text and variables to the OLED screen.

The device is designed to loop back to the first demo once the user clicks the button on the last demo.

## Credits

This demo was created by Vincent Langlois and relies on the Adafruit SSD1306 library for OLED screens. 
