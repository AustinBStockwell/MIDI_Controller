/* Author: Austin Stockwell
    Date: 04/08/2020
    Description: SetMIDIChannel()
       Sets the MIDI Channel of each knob
*/
int SetMIDIChannelPreset1() {
  Serial.println("PRESET 1 CHANNEL EDITING");
  
  lcd.clear();
  lcd.setCursor(0, 0); // (column, row)
  lcd.print("  EDIT CHANNEL");
  digitalWrite(seshLED, HIGH);
  digitalWrite(sesh2LED, LOW);
  
 // Ensure user wants to continue editing MIDI Channel...
  int SetMIDIChannelPreset1Flag = 0;
  while (SetMIDIChannelPreset1Flag != 1) {
    seshButtonState = digitalRead(seshButton);
    editButtonState = digitalRead(editButton);

// KNOB 1
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
          EditMode1();
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
          SetMIDIChannelPreset1();
          break;
        }    
      } // WHILE editing MIDI Channel...
    } // IF knob was turned...

// KNOB 2
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
          EditMode1();
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
    
          SetMIDIChannelPreset1();
          break;
        } 
      } 
    }

// KNOB 3
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
          EditMode1();
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
    
          SetMIDIChannelPreset1();
          break;
        }  
      } 
    }

// KNOB 4
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
          EditMode1();
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
    
          SetMIDIChannelPreset1();
          break;
        } 
      } 
    }

    // If user wants to continue in Edit Mode...
    if (editButtonState == 1) {
      SetMIDIChannelPreset1Flag == 1;
      delay(250); // Aids in button stability to return to Edit Mode...
      SetCCNumberPreset1();
      break;
    }
    // If user wants to return to Session Mode...
    if (seshButtonState == 1) {
      SetMIDIChannelPreset1Flag == 1;
      Preset2Mode();
      break;
    }
  } // while (SetMIDIChannelPreset2Flag !=1)
} // SetMIDIChannelPreset2() method

/******************************************************/
int SetMIDIChannelPreset2() {
  Serial.println("PRESET 2 CHANNEL EDITING");
  
  lcd.clear();
  lcd.setCursor(0, 0); // (column, row)
  lcd.print("  EDIT CHANNEL");
  
 // Ensure user wants to continue editing MIDI Channel...
  int setMIDIChannelPreset2Flag = 0;
  while (setMIDIChannelPreset2Flag != 1) {
    sesh2ButtonState = digitalRead(sesh2Button);
    editButtonState = digitalRead(editButton);

// KNOB 1
// Get value from knob IF KNOB MOVES
    int oldk1state2 = analogRead(k1);
    delay(5);
    k1state2 = analogRead(k1);
    if(abs(oldk1state2 - k1state2) > 8)    
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
        k1state2 = analogRead(k1);
        int k1mapChanDisp2 = map(k1state2, 0, 1021, 1, 16);  
        int k1mappedChannel2 = map(k1state2, 0, 1021, 176, 191);
        lcd.setCursor(8, 1);
        lcd.print(k1mapChanDisp2);
        
        if(editButtonState == 1){
          EditMode2();
          break;
        }
        
        if(commitButtonState == 1){
          // Write new channel value to newChannel var
          k1newChannel2 = k1mappedChannel2;
          EEPROM.write(24,k1newChannel2); // (address, val)

          // Dispaly new channel to LCD
          lcd.clear();
          lcd.setCursor(7,0);
          lcd.print("K1");
          lcd.setCursor(0,1);
          lcd.print("NEW CHANNEL: ");
          lcd.setCursor(12, 1); // (column, row);
          lcd.print(k1mapChanDisp2);
          delay(2000);
          lcd.clear();
    
          // Continue to edit MIDI Channels...
          SetMIDIChannelPreset2();
          break;
        }    
      } // WHILE editing MIDI Channel...
    } // IF knob was turned...

// KNOB 2
    int oldk2state2 = analogRead(k2);
    delay(5);
    k2state2 = analogRead(k2);
    if(abs(oldk2state2 - k2state2) > 8)    
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

        k2state2 = analogRead(k2);
        int k2mapChanDisp2 = map(k2state2, 0, 1021, 1, 16); 
        int k2mappedChannel2 = map(k2state2, 0, 1021, 176, 191);
 
        lcd.setCursor(8, 1);
        lcd.print(k2mapChanDisp2);
        
        if(editButtonState == 1){
          EditMode2();
          break;
        }
        
        if(commitButtonState == 1){
           k2newChannel2 = k2mappedChannel2;
           EEPROM.write(25,k2newChannel2); 

          lcd.clear();
          lcd.setCursor(7,0);
          lcd.print("K2");
          lcd.setCursor(0,1);
          lcd.print("NEW CHANNEL: ");
          lcd.setCursor(12, 1); 
          lcd.print(k2mapChanDisp2);
          delay(2000);
          lcd.clear();
    
          SetMIDIChannelPreset2();
          break;
        } 
      } 
    }

// KNOB 3
    int oldk3state2 = analogRead(k3);
    delay(5);
    k2state2 = analogRead(k3);
    if(abs(oldk3state2 - k3state2) > 8)    
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

        k3state2 = analogRead(k3);
        int k3mapChanDisp2 = map(k3state2, 0, 1021, 1, 16); 
        int k3mappedChannel2 = map(k3state2, 0, 1021, 176, 191);
 
        lcd.setCursor(8, 1);
        lcd.print(k3mapChanDisp2);
        
        if(editButtonState == 1){
          EditMode2();
          break;
        }
        
        if(commitButtonState == 1){
           k3newChannel2 = k3mappedChannel2;
           EEPROM.write(26,k3newChannel2); 

          lcd.clear();
          lcd.setCursor(7,0);
          lcd.print("K3");
          lcd.setCursor(0,1);
          lcd.print("NEW CHANNEL: ");
          lcd.setCursor(12, 1); 
          lcd.print(k3mapChanDisp2);
          delay(2000);
          lcd.clear();
    
          SetMIDIChannelPreset2();
          break;
        }  
      } 
    }

// KNOB 4
    int oldk4state2 = analogRead(k4);
    delay(5);
    k4state2 = analogRead(k4);
    if(abs(oldk4state2 - k4state2) > 8)    
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

        k4state2 = analogRead(k4);
        int k4mapChanDisp2 = map(k4state2, 0, 1021, 1, 16); 
        int k4mappedChannel2 = map(k4state2, 0, 1021, 176, 191);
 
        lcd.setCursor(8, 1);
        lcd.print(k4mapChanDisp2);
        
        if(editButtonState == 1){
          EditMode2();
          break;
        }
        
        if(commitButtonState == 1){
          k4newChannel2 = k4mappedChannel2;
          EEPROM.write(27,k4newChannel2); 
    
          lcd.clear();
          lcd.setCursor(7,0);
          lcd.print("K4");
          lcd.setCursor(0,1);
          lcd.print("NEW CHANNEL: ");
          lcd.setCursor(12, 1); 
          lcd.print(k4mapChanDisp2);
          delay(2000);
          lcd.clear();
    
          SetMIDIChannelPreset2();
          break;
        } 
      } 
    }

    // If user wants to continue in Edit Mode...
    if (editButtonState == 1) {
      setMIDIChannelPreset2Flag == 1;
      delay(250); // Aids in button stability to return to Edit Mode...
      SetCCNumberPreset2();
      break;
    }
    // If user wants to return to Session Mode...
    if (sesh2ButtonState == 1) {
      setMIDIChannelPreset2Flag == 1;
      Preset2Mode();
      break;
    }
  } // while (setMIDIChannelFlag !=1)
} // SetMIDIChannel() method
