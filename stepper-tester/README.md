💡 Stepper Motor Tester

← Back to Main

📖 Description

This exercise demonstrates how to control a 28BYJ-48 unipolar stepper motor
using a ULN2003 driver board and the built-in Arduino Stepper library. It
practices converting angular positions (in degrees) into exact motor step
counts, as well as handling continuous bidirectional movement (moving 360° back
and forth).

🛠️ Hardware Required

| Component     | Details                                              |
| ------------- | ---------------------------------------------------- |
| Board         | Arduino Mega 2560 (or any board exposing pins 36–39) |
| Stepper Motor | 28BYJ-48 (5V)                                        |
| Driver Module | ULN2003 Stepper Driver Board                         |
| Power Supply  | External 5V DC power source                          |
| Wires         | Jumper wires (Male-to-Female / Male-to-Male)         |

📋 How It Works

1.  Library & Pin Setup:
    The Stepper library is initialized with 2048 steps per revolution. Pins are
    passed in the order 36, 38, 37, 39 to match the sequence IN1, IN3, IN2, IN4
    required by the ULN2003 driver.
2.  Speed Configuration:
    In setup(), the motor speed is set to 10 RPM via motor.setSpeed(10).
3.  Forward Rotation:
    The sketch computes the steps needed to reach angle2 (-360°) using the
    formula:
    steps = (angle2 - currentAngle) * stepsPerRevolution / 360.0
    The motor executes the steps, sets currentAngle = angle2, and waits for 1
    second.
4.  Return Rotation:
    The sketch calculates the steps needed to return to angle1 (0°), executes
    the movement, resets currentAngle = angle1, and waits for 1 second before
    repeating the loop.

🚀 How to Run

1.  Connect the ULN2003 pins IN1, IN2, IN3, IN4 to Arduino pins 36, 37, 38, 39.
2.  Connect driver + and - to an external 5V power supply and share a common GND
    with the Arduino.
3.  Open stepper_tester.ino in Arduino IDE.
4.  Select your board and COM port under Tools.
5.  Upload the sketch to observe the motor rotating 360° back and forth.

📝 Notes

  - Pin Order Trick: The Arduino Stepper library defaults to firing pins
    1-2-3-4, but the 28BYJ-48 sequence requires 1-3-2-4. Declaring the
    constructor with pins 36, 38, 37, 39 fixes the sequence without modifying
    the library.
  - External Power: Avoid running the stepper directly from the 5V pin of the
    board; motors draw high current spikes that can cause resets or damage the
    board.
  - Max Speed: Setting setSpeed() above ~15 RPM may cause the 28BYJ-48 to slip
    or stall due to internal gear friction.
