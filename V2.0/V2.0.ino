/* Author: Austin Stockwell
    Date: 04/08/2020
    Description: This is the code of an Arduino
                 MIDI Controller that sends MIDI control data
                 to an external device via 5-PIN MIDI
                 cable without the use of Arduino MIDI libraries.

                 A user chooses between Session Mode and Edit
                 Mode via a single pushbutton...
                 
                 In Session Mode, the user can continuously send
                 MIDI to any device that recieves MIDI 
                 Control Messages.  The user does this by using
                 a combination of the 4 knobs.  Each knob features 
                 a dedicated LED controlled by Pulse-Width Modulation (PWM).
                 
                 In Edit Mode, the user can configure the messages.
                 Each knob can be configured to transmit any Control Number
                 (0-127) on any MIDI Channel (1-16).  Saved values
                 are stored to the board's internal EEPROM when a user
                 pushes the "COMMIT" button.
*/
/*  ------------------------------------------------------- */
// INCLUDED LIBRARIES 
/*  ------------------------------------------------------- */
#include <EEPROM.h>
#include <LiquidCrystal.h>

/*  ------------------------------------------------------- */
// DECLARED VARIABLES
/*  ------------------------------------------------------- */
/* LCD */
const int rs = 20, en = 21, d4 = 25, d5 = 24, d6 = 23, d7 = 22;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

/* LEDs */
const int knobLEDs[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
const int editModeLED = 26;
const int seshLED = 52;
const int sesh2LED = 50;

/* KNOBS / KNOB STATES*/
const int k1 = A0;
const int k2 = A1;
const int k3 = A2;
const int k4 = A3;
// Prest 1
int Preset1KnobStates[4];
int resetKnobFlag = 1;
int k1state;
int k2state;
int k3state;
int k4state;
int k1OldState = 0;
int k2OldState = 0;
int k3OldState = 0;
int k4OldState = 0;
// Preset 2
int Preset2KnobStates[4];
int resetKnobFlag2 = 1;
int k1state2;
int k2state2;
int k3state2;
int k4state2;
int k1OldState2 = 0;
int k2OldState2 = 0;
int k3OldState2 = 0;
int k4OldState2 = 0;

/* BUTTONS / BUTTON STATES */
const int seshButton = 53;
const int sesh2Button = 51;
const int editButton = 27; 
const int commitButton = 29;
int seshButtonState;
int sesh2ButtonState;
int editButtonState;    
int commitButtonState;

/* DEFAULT VALUES */
// Preset 1
int k1newChannel = 176;
int k2newChannel = 176;
int k3newChannel = 176;
int k4newChannel = 176;
int k1newNumber = 0;
int k2newNumber = 1;
int k3newNumber = 2;
int k4newNumber = 3;
// Preset 2
int k1newChannel2 = 177;
int k2newChannel2 = 177;
int k3newChannel2 = 177;
int k4newChannel2 = 177;
int k1newNumber2 = 0;
int k2newNumber2 = 1;
int k3newNumber2 = 2;
int k4newNumber2 = 3;

/*  ------------------------------------------------------- */
// SETUP 
/*  ------------------------------------------------------- */
void setup() {
 //Serial.begin(9600);
 Serial.begin(31250); // Used to communicate over MIDI cable
  Memory(); // Read in data from EEPROM

  /* LCD */
  lcd.begin(16, 2);

  /* LEDS */
  for (int index = 0; index < 4; index ++)
  {
    pinMode((knobLEDs[index]), OUTPUT);
  }
  pinMode(seshLED, OUTPUT);
  pinMode(sesh2LED, OUTPUT);
  pinMode(editModeLED, OUTPUT);

  /* KNOBS */
  pinMode(k1, INPUT);
  pinMode(k2, INPUT);
  pinMode(k3, INPUT);
  pinMode(k4, INPUT);
  
  /* BUTTONS */
  pinMode(seshButton, INPUT);
  pinMode(editButton, INPUT);
}

/*  ------------------------------------------------------- */
// MAIN 
/*  ------------------------------------------------------- */
void loop() {
  Preset1Mode();
}
