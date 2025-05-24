# Arduino Serial Control

This project provides a simple C program that allows a computer to communicate with an Arduino board via serial port (COM4). The user can interact with a menu on the terminal to control the Arduino's built-in LED, flash the LED, or compute a factorial using the Arduino.

## Features

- Turn Arduino LED on and off from the PC
- Flash Arduino LED 5 times
- Send a number to Arduino and compute its factorial (result returned from Arduino)
- Turn on an external LED connected to Arduino
- All communication is done via serial port (COM4, 9600 baudrate)
- Arduino code (sketch) and C source code are both included

## How to Use

1. Upload the included `.ino` sketch to your Arduino board.
2. Connect the Arduino to your computer via USB.
3. On Windows, ensure that your Arduino is connected to `COM4` or update the port in the C source code if necessary.
4. Compile the C program (use gcc on Windows, e.g. with MinGW):
    ```bash
    gcc muhammed_korkmaz_220104004043.c -o arduino_serial_control
    ```
5. Run the compiled program:
    ```bash
    ./arduino_serial_control
    ```
6. Follow the menu prompts to control the Arduino.

## Menu Options

- `1`: Turn on Arduino LED
- `2`: Turn off Arduino LED
- `3`: Flash Arduino LED 5 times
- `4`: Send a number for Arduino to compute its factorial (result is returned and displayed)
- `5`: Turn on external LED
- `0`: Exit

## Requirements

- Windows OS
- Arduino board with USB connection
- gcc compiler for Windows (MinGW or similar)
- The Arduino board should be connected to `COM4` (or update code for your port)

## Author

Muhammed Korkmaz  
Gebze Technical University  
Student ID: 220104004043

