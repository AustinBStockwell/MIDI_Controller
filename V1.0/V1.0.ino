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

/* KNOBS / KNOB STATES*/
const int k1 = A0;
const int k2 = A1;
const int k3 = A2;
const int k4 = A3;
int k1state;
int k2state;
int k3state;
int k4state;
int k1OldState = 0;
int k2OldState = 0;
int k3OldState = 0;
int k4OldState = 0;

/* BUTTONS / BUTTON STATES */
const int seshButton = 53;
const int editButton = 52; 
const int commitButton = 27;
int seshButtonState;
int editButtonState;    
int commitButtonState;

/* DEFAULT VALUES */
int k1newChannel = 176;
int k2newChannel = 176;
int k3newChannel = 176;
int k4newChannel = 176;
int k1newNumber = 0;
int k2newNumber = 1;
int k3newNumber = 2;
int k4newNumber = 3;

/*  ------------------------------------------------------- */
// SETUP 
/*  ------------------------------------------------------- */
void setup() {
  Serial.begin(31250); // Used to communicate over MIDI cable
  Memory(); // Read in data from EEPROM

  /* LCD */
  lcd.begin(16, 2);

  /* LEDS */
  for (int index = 0; index < 4; index ++)
  {
    pinMode((knobLEDs[index]), OUTPUT);
  }
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
  SessionMode();
}

/*  ------------------------------------------------------- */
// METHODS 
/*  ------------------------------------------------------- */
/* Allows use r to send MIDI data on all knobs in real-time */
void SessionMode() {
  Serial.println("SESSION MODE");
  
  // Setup LCD & LED for Session Mode 
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  SESSION MODE  ");
  digitalWrite(editModeLED, LOW);
  
  int sessionFlag = 0;
  // Stay in Session MODE until user chooses another MODE
  while (sessionFlag != 1) {
    // Ensure user does not want to leave Session Mode
    editButtonState = digitalRead(editButton); 
    
    /* Read value of knobs */
    ReadKnobs();
    
    // If user wants to enter CC Edit Mode...
    if (editButtonState == 1) {
      Serial.println("Setting sessionFlag = 1");
      sessionFlag = 1;
    }
  }
  sessionFlag = 0; // Reset flag for next use of Session Mode
  EditMode(); // Returns to Edit Mode
}

/******************************************************/
/* Samples potentiometers and transmits MIDI Messages for each knob */
void ReadKnobs(){
  Serial.println("READ KNOBS ");
    
    // Array to holds each knobs CC CONTROL CHANGE VALUE
    int mappedValArray[4];

   // Continuously read knob values to see if knob has been moved
    k1state = analogRead(k1);
    k2state = analogRead(k2);
    k3state = analogRead(k3);
    k4state = analogRead(k4);
    
    // Map recieved potentiomter values to control LED w/PWM (0-255)
    int k1mappedLED = map(k1state, 0, 1021, 0, 255);
    int k2mappedLED = map(k2state, 0, 1021, 0, 255);
    int k3mappedLED = map(k3state, 0, 1021, 0, 255);
    int k4mappedLED = map(k4state, 0, 1021, 0, 255);
    analogWrite(2, k1mappedLED);
    analogWrite(3, k2mappedLED);
    analogWrite(4, k3mappedLED);
    analogWrite(5, k4mappedLED);

      // IF knob1 moves send midi message
      if(abs (k1state - k1OldState) >= 5){
         Serial.println("KNOB HAS MOVED!");   
          
          // Re-read value and map to MIDI message format (0 - 127)
          k1state = analogRead(k1);
          mappedValArray[0] = map(k1state, 0, 1021, 0, 127);       

          // SEND MIDI MESSAGE!!!
          byte k1MIDIMess[3] = {k1newChannel, k1newNumber, mappedValArray[0]};
          for (int k1index = 0; k1index < 3; k1index++)
          {
           Serial.write(k1MIDIMess[k1index]);
          }    
  
          // Holds the most recent value of the knob for use in determining
          // if the knob has moved in the next iteration of ReadKnobs()
          k1OldState = k1state;
      }     
      
      if (abs(k2state - k2OldState) >= 5){
          k2state = analogRead(k2);
          mappedValArray[1] = map(k2state, 0, 1021, 0, 127);

        byte k2MIDIMess[3] = {k2newChannel, k2newNumber, mappedValArray[1]};
        for (int k2index = 0; k2index < 3; k2index++)
        {
           Serial.write(k2MIDIMess[k2index]);
        }    
          k2OldState = k2state;
      }  

      if (abs(k3state - k3OldState) >= 5){
          k3state = analogRead(k3);
          mappedValArray[2] = map(k3state, 0, 1021, 0, 127);

        byte k3MIDIMess[3] = {k3newChannel, k3newNumber, mappedValArray[2]};
        for (int k3index = 0; k3index < 3; k3index++)
        {
           Serial.write(k3MIDIMess[k3index]);
        }    
          k3OldState = k3state;
      }  

      if (abs(k4state - k4OldState) >= 5){
          k4state = analogRead(k4);
          mappedValArray[3] = map(k4state, 0, 1021, 0, 127);

        byte k4MIDIMess[3] = {k4newChannel, k4newNumber, mappedValArray[3]};
        for (int k4index = 0; k4index < 3; k4index++)
        {
           Serial.write(k4MIDIMess[k4index]);
        }    
          k4OldState = k4state;
      }  
}

/******************************************************/
/* Accesses MIDI Channel / Control Number editing */
void EditMode() {
  Serial.println("EDIT MODE");
  // Setup LCD & LEDs for CCMode
  lcd.clear();
  lcd.setCursor(0, 0); // (column, row)
  lcd.print("     EDIT   ");
  digitalWrite(editModeLED, HIGH);
  for (int index = 0; index < 4; index++) {
    digitalWrite(knobLEDs[index], LOW);
  }

  // Stay in CCMode until user presses Session Button
  int editFlag = 0;
  while (editFlag != 1) {
    seshButtonState = digitalRead(seshButton);
    editButtonState = digitalRead(editButton);
  
  /* State detection sub-circuit toggles between MIDI CH /CC NUM editing */
    int buttonPushCounter;   // Counter for the number of button presses
    int localbuttonState = 0;     // Current state of the button
    int lastButtonState = 0;     // Previous state of the button

        if (editButtonState != lastButtonState) {
          buttonPushCounter++; 
          
          if (editButtonState = HIGH) {
            lastButtonState = 0;  // If its high, it was low before...
             delay(250);  // Debouncing of button presses for accuracy
          }
          if (editButtonState = LOW) {
            lastButtonState = 1;  
            delay(250);  
          }
            // SET MIDI CHANNEL
            if (buttonPushCounter % 2) {
              SetMIDIChannel();
            }
            // SET CONTROL NUMBER 
            else{
              SetCCNumber();
            }
        }
    // If user wants to enter Session Mode...
    if (seshButtonState == 1) {
      editFlag = 1;
    }
  } // while(editFlag != 1)
  editFlag = 0;  // Resets editFlag for next use
  digitalWrite(editModeLED, LOW); // Light off (leaving Edit Mode)
  SessionMode();  // Return to Session Mode
}

/******************************************************/
/* Edit / save MIDI Channel of knobs */
int SetMIDIChannel() {
  Serial.println("CHANNEL MODE");
  lcd.clear();
  lcd.setCursor(0, 0); // (column, row)
  lcd.print("  EDIT CHANNEL");
  
 // Ensure user wants to continue editing MIDI Channel...
  int setMIDIChannelFlag = 0;
  while (setMIDIChannelFlag != 1) {
    seshButtonState = digitalRead(seshButton);
    editButtonState = digitalRead(editButton);

/* Knob 1 */
    // Get value from knob IF KNOB MOVES
    int oldk1state = analogRead(k1);
    delay(5);
    k1state = analogRead(k1);
    if(abs(oldk1state - k1state) > 8)    
    {
      while(commitButtonState == 0 || editButtonState == 0)
      {  
        commitButtonState = digitalRead(commitButton);
        editButtonState = digitalRead(editButton);

        // Continuously clear old value to write new value
        delay(100);  // Aids stability of LCD screen
        lcd.setCursor(8, 1);
        lcd.print("            ");
        lcd.setCursor(0, 1); // (column, row);
        lcd.print("MIDI CH: ");  // Continue to display "MIDI CH"

        // Read and write k1 value to LCD
        k1state = analogRead(k1);
        int k1mapChanDisp = map(k1state, 0, 1021, 1, 16);  
        int k1mappedChannel = map(k1state, 0, 1021, 176, 191);
        lcd.setCursor(8, 1);
        lcd.print(k1mapChanDisp);
        
        if(editButtonState == 1){
          EditMode();
          break;
        }
        
        if(commitButtonState == 1){
          // Write new channel value to newChannel var
          k1newChannel = k1mappedChannel;
          EEPROM.write(0,k1newChannel); // (address, val)

          // Dispaly new channel to LCD
          lcd.clear();
          lcd.setCursor(7,0);
          lcd.print("K1");
          lcd.setCursor(0,1);
          lcd.print("NEW CHANNEL: ");
          lcd.setCursor(12, 1); // (column, row);
          lcd.print(k1mapChanDisp);
          delay(2000);
          lcd.clear();
    
          // Continue to edit MIDI Channels...
          SetMIDIChannel();
          break;
        }    
      } // WHILE editing MIDI Channel...
    } // IF knob was turned...

/* Knob 2 */
    int oldk2state = analogRead(k2);
    delay(5);
    k2state = analogRead(k2);
    if(abs(oldk2state - k2state) > 8)    
    {
      while(commitButtonState == 0 || editButtonState == 0)
      {  
        commitButtonState = digitalRead(commitButton);
        editButtonState = digitalRead(editButton);

        delay(100);  // Aids stability of LCD screen
        lcd.setCursor(8, 1);
        lcd.print("            ");
        lcd.setCursor(0, 1); // (column, row);
        lcd.print("MIDI CH: ");  // Continue to display "MIDI CH"

        k2state = analogRead(k2);
        int k2mapChanDisp = map(k2state, 0, 1021, 1, 16); 
        int k2mappedChannel = map(k2state, 0, 1021, 176, 191);
 
        lcd.setCursor(8, 1);
        lcd.print(k2mapChanDisp);
        
        if(editButtonState == 1){
          EditMode();
          break;
        }
        
        if(commitButtonState == 1){
           k2newChannel = k2mappedChannel;
           EEPROM.write(1,k2newChannel); 

          lcd.clear();
          lcd.setCursor(7,0);
          lcd.print("K2");
          lcd.setCursor(0,1);
          lcd.print("NEW CHANNEL: ");
          lcd.setCursor(12, 1); 
          lcd.print(k2mapChanDisp);
          delay(2000);
          lcd.clear();
    
          SetMIDIChannel();
          break;
        } 
      } 
    }

/* Knob 3 */
    int oldk3state = analogRead(k3);
    delay(5);
    k2state = analogRead(k3);
    if(abs(oldk3state - k3state) > 8)    
    {
      while(commitButtonState == 0 || editButtonState == 0)
      {  
        commitButtonState = digitalRead(commitButton);
        editButtonState = digitalRead(editButton);

        delay(100);  
        lcd.setCursor(8, 1);
        lcd.print("            ");
        lcd.setCursor(0, 1); 
        lcd.print("MIDI CH: ");  

        k3state = analogRead(k3);
        int k3mapChanDisp = map(k3state, 0, 1021, 1, 16); 
        int k3mappedChannel = map(k3state, 0, 1021, 176, 191);
 
        lcd.setCursor(8, 1);
        lcd.print(k3mapChanDisp);
        
        if(editButtonState == 1){
          EditMode();
          break;
        }
        
        if(commitButtonState == 1){
           k3newChannel = k3mappedChannel;
           EEPROM.write(2,k3newChannel); 

          lcd.clear();
          lcd.setCursor(7,0);
          lcd.print("K3");
          lcd.setCursor(0,1);
          lcd.print("NEW CHANNEL: ");
          lcd.setCursor(12, 1); 
          lcd.print(k3mapChanDisp);
          delay(2000);
          lcd.clear();
    
          SetMIDIChannel();
          break;
        }  
      } 
    }

/* Knob 4 */
    int oldk4state = analogRead(k4);
    delay(5);
    k4state = analogRead(k4);
    if(abs(oldk4state - k4state) > 8)    
    {
      while(commitButtonState == 0 || editButtonState == 0)
      {  
        commitButtonState = digitalRead(commitButton);
        editButtonState = digitalRead(editButton);

        delay(100);  
        lcd.setCursor(8, 1);
        lcd.print("            ");
        lcd.setCursor(0, 1); 
        lcd.print("MIDI CH: ");  

        k4state = analogRead(k4);
        int k4mapChanDisp = map(k4state, 0, 1021, 1, 16); 
        int k4mappedChannel = map(k4state, 0, 1021, 176, 191);
 
        lcd.setCursor(8, 1);
        lcd.print(k4mapChanDisp);
        
        if(editButtonState == 1){
          EditMode();
          break;
        }
        
        if(commitButtonState == 1){
          k4newChannel = k4mappedChannel;
          EEPROM.write(3,k4newChannel); 
    
          lcd.clear();
          lcd.setCursor(7,0);
          lcd.print("K4");
          lcd.setCursor(0,1);
          lcd.print("NEW CHANNEL: ");
          lcd.setCursor(12, 1); 
          lcd.print(k4mapChanDisp);
          delay(2000);
          lcd.clear();
    
          SetMIDIChannel();
          break;
        } 
      } 
    }

    // If user wants to continue in Edit Mode...
    if (editButtonState == 1) {
      setMIDIChannelFlag == 1;
      delay(250); // Aids in button stability to return to Edit Mode...
      SetCCNumber();
      break;
    }
    // If user wants to return to Session Mode...
    if (seshButtonState == 1) {
      setMIDIChannelFlag == 1;
      SessionMode();
      break;
    }
  } // while (setMIDIChannelFlag !=1)
} // SetMIDIChannel() method

/******************************************************/
/* Edit / save Control Number of knobs */
int SetCCNumber() {
  Serial.println("NUMBER MODE");
  lcd.clear();
  lcd.setCursor(0, 0); // (column, row)
  lcd.print("    EDIT NUM   ");
  
  // Ensure user wants to continue editing CC Number...
  int setCCNumberFlag = 0;
  while (setCCNumberFlag != 1) {
    seshButtonState = digitalRead(seshButton);
    editButtonState = digitalRead(editButton);

/* Knob 1 */
        int oldk1state = analogRead(k1);
        delay(5);
        k1state = analogRead(k1);
        if(abs(oldk1state - k1state) > 8)    
        {
          while(commitButtonState == 0 || editButtonState == 0)
          {  
            commitButtonState = digitalRead(commitButton);
            editButtonState = digitalRead(editButton);
    
            delay(100);  // Aids stability of LCD screen 
            lcd.setCursor(8, 1);
            lcd.print("            ");
            lcd.setCursor(0, 1); // (column, row);
            lcd.print("CC NUM: ");
    
            // Read and write k1 value to LCD
            k1state = analogRead(k1);
            int k1mappedNumber = map(k1state, 0, 1021, 0, 127);  
            lcd.setCursor(8, 1);
            lcd.print(k1mappedNumber);
            
            if(editButtonState == 1){
              EditMode();
              break;
            }
            
            if(commitButtonState == 1){
              // Write new channel value to newChannel var
              k1newNumber = k1mappedNumber;
              EEPROM.write(12,k1newNumber); // (val,address)

              // Dispaly new channel to LCD
              lcd.clear();
              lcd.setCursor(7,0);
              lcd.print("K1");
              lcd.setCursor(0,1);
              lcd.print("NEW cc NUM:");
              lcd.setCursor(11, 1); // (column, row);
              lcd.print(k1newNumber);
              delay(2000); // Display message for 2 seconds to confirm...
              lcd.clear();
        
              // Continue to edit MIDI Channels...
              SetCCNumber();
              break;
            }
          } // WHILE editing CC Number...
        } // IF knob was turned...

/* Knob 2 */
        int oldk2state = analogRead(k2);
        delay(5);
        k2state = analogRead(k2);
        if(abs(oldk2state - k2state) > 8)    
        {
          while(commitButtonState == 0 || editButtonState == 0)
          {  
            commitButtonState = digitalRead(commitButton);
            editButtonState = digitalRead(editButton);
    
            delay(100);  
            lcd.setCursor(8, 1);
            lcd.print("            ");
            lcd.setCursor(0, 1); 
            lcd.print("CC NUM: ");
    
            k2state = analogRead(k2);
            int k2mappedNumber = map(k2state, 0, 1021, 0, 127);  
            lcd.setCursor(8, 1);
            lcd.print(k2mappedNumber);
            
            if(editButtonState == 1){
              EditMode();
              break;
            }
            
            if(commitButtonState == 1){
              k2newNumber = k2mappedNumber;
              EEPROM.write(13,k2newNumber); 

              lcd.clear();
              lcd.setCursor(7,0);
              lcd.print("K2");
              lcd.setCursor(0,1);
              lcd.print("NEW cc NUM:");
              lcd.setCursor(11, 1);
              lcd.print(k2newNumber);
              delay(2000);  
              lcd.clear();
        
              SetCCNumber();
              break;
            }
          } 
        } 

/* Knob 3 */
        int oldk3state = analogRead(k3);
        delay(5);
        k3state = analogRead(k3);
        if(abs(oldk3state - k3state) > 8)    
        {
          while(commitButtonState == 0 || editButtonState == 0)
          {  
            commitButtonState = digitalRead(commitButton);
            editButtonState = digitalRead(editButton);
    
            delay(100);   
            lcd.setCursor(8, 1);
            lcd.print("            ");
            lcd.setCursor(0, 1); 
            lcd.print("CC NUM: ");
    
            k3state = analogRead(k3);
            int k3mappedNumber = map(k3state, 0, 1021, 0, 127);  
            lcd.setCursor(8, 1);
            lcd.print(k3mappedNumber);
            
            if(editButtonState == 1){
              EditMode();
              break;
            }
            
            if(commitButtonState == 1){
              k3newNumber = k3mappedNumber;
              EEPROM.write(14, k3newNumber); 

              lcd.clear();
              lcd.setCursor(7,0);
              lcd.print("K3");
              lcd.setCursor(0,1);
              lcd.print("NEW cc NUM:");
              lcd.setCursor(11, 1); 
              lcd.print(k3newNumber);
              delay(2000);  
              lcd.clear();
        
              SetCCNumber();
              break;
            }
          } 
        } 

/* Knob 4 */
        int oldk4state = analogRead(k4);
        delay(5);
        k4state = analogRead(k4);
        if(abs(oldk4state - k4state) > 8)    
        {
          while(commitButtonState == 0 || editButtonState == 0)
          {  
            commitButtonState = digitalRead(commitButton);
            editButtonState = digitalRead(editButton);
    
            delay(100);  
            lcd.setCursor(8, 1);
            lcd.print("            ");
            lcd.setCursor(0, 1); 
            lcd.print("CC NUM: ");
    
            k4state = analogRead(k4);
            int k4mappedNumber = map(k4state, 0, 1021, 0, 127);  
            lcd.setCursor(8, 1);
            lcd.print(k4mappedNumber);
            
            if(editButtonState == 1){
              EditMode();
              break;
            }
            
            if(commitButtonState == 1){
              k4newNumber = k4mappedNumber;
              EEPROM.write(15, k4newNumber); 
        
              lcd.clear();
              lcd.setCursor(7,0);
              lcd.print("K4");
              lcd.setCursor(0,1);
              lcd.print("NEW cc NUM:");
              lcd.setCursor(11, 1); 
              lcd.print(k4newNumber);
              delay(2000);  
              lcd.clear();
        
              SetCCNumber();
              break;
            }
          } 
        } 

    // If user wants to continue in Edit Mode...
    if (editButtonState == 1) {
      setCCNumberFlag = 1;
      delay(250); // Aids in button stability to return to Edit Mode...
      SetMIDIChannel();
      break;
    }
    // If user wants to return to Session Mode...
    if (seshButtonState == 1) {
      setCCNumberFlag = 1; 
      SessionMode(); 
      break;
    }
  } // while(SetCCNumber != 1)
} // SetCCNumber() method

/******************************************************/
/* Access stored variables in EEPROM memory */
void Memory(){
  k1newChannel = EEPROM.read(0);
  k2newChannel = EEPROM.read(1);
  k3newChannel = EEPROM.read(2);
  k4newChannel = EEPROM.read(3);

  k1newNumber = EEPROM.read(12);
  k2newNumber = EEPROM.read(13);
  k3newNumber = EEPROM.read(14);
  k4newNumber = EEPROM.read(15);
}
