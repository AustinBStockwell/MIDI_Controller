/* Author: Austin Stockwell
    Date: 04/08/2020
    Description: SetCCNumber()
       Sets the Control Number of each knob
*/
int SetCCNumberPreset1(){
  Serial.println("PRESET 1 CONTROL NUMBER EDITING");
  
  lcd.clear();
  lcd.setCursor(0, 0); // (column, row)
  lcd.print("    EDIT NUM   ");
  
  // Ensure user wants to continue editing CC Number...
  int setCCNumberPreset1Flag = 0;
  while (setCCNumberPreset1Flag != 1) {
    seshButtonState = digitalRead(seshButton);
    editButtonState = digitalRead(editButton);

// KNOB 1
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
              EditMode1();
              break;
            }
            
            if(commitButtonState == 1){
              // Write new channel value to newChannel var
              k1newNumber = k1mappedNumber;
              EEPROM.write(12,k1newNumber); // (address,val)

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
              SetCCNumberPreset1();
            }
          } // WHILE editing CC Number...
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
              EditMode1();
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
        
              SetCCNumberPreset1();
              break;
            }
          } 
        } 

// KNOB 3
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
              EditMode1();
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
        
              SetCCNumberPreset1();
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
            lcd.print("CC NUM: ");
    
            k4state = analogRead(k4);
            int k4mappedNumber = map(k4state, 0, 1021, 0, 127);  
            lcd.setCursor(8, 1);
            lcd.print(k4mappedNumber);
            
            if(editButtonState == 1){
              EditMode1();
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
        
              SetCCNumberPreset1();
              break;
            }
          } 
        } 

    // If user wants to continue in Edit Mode...
    if (editButtonState == 1) {
      setCCNumberPreset1Flag = 1;
      delay(250); // Aids in button stability to return to Edit Mode...
      SetMIDIChannelPreset1();
      break;
    }
    // If user wants to return to Session Mode...
    if (seshButtonState == 1) {
      setCCNumberPreset1Flag = 1; 
      Preset2Mode(); 
      break;
    }
  } // while(SetCCNumberPreset2Flag != 1)
} // SetCCNumberPreset2() method

/******************************************************/
int SetCCNumberPreset2(){
  Serial.println("PRESET 2 CONTROL NUMBER EDITING");

 // Edit / save Control Number of knobs of Preset 2
  lcd.clear();
  lcd.setCursor(0, 0); // (column, row)
  lcd.print("    EDIT NUM   ");
  
  // Ensure user wants to continue editing CC Number...
  int setCCNumberPreset2Flag = 0;
  while (setCCNumberPreset2Flag != 1) {
    sesh2ButtonState = digitalRead(sesh2Button);
    editButtonState = digitalRead(editButton);

// KNOB 1
        int oldk1state2 = analogRead(k1);
        delay(5);
        k1state2 = analogRead(k1);
        if(abs(oldk1state2 - k1state2) > 8)    
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
            k1state2 = analogRead(k1);
            int k1mappedNumber2 = map(k1state2, 0, 1021, 0, 127);  
            lcd.setCursor(8, 1);
            lcd.print(k1mappedNumber2);
            
            if(editButtonState == 1){
              EditMode2();
              break;
            }
            
            if(commitButtonState == 1){
              // Write new channel value to newChannel var
              k1newNumber2 = k1mappedNumber2;
              EEPROM.write(36,k1newNumber2); // (address,val)

              // Dispaly new channel to LCD
              lcd.clear();
              lcd.setCursor(7,0);
              lcd.print("K1");
              lcd.setCursor(0,1);
              lcd.print("NEW cc NUM:");
              lcd.setCursor(11, 1); // (column, row);
              lcd.print(k1newNumber2);
              delay(2000); // Display message for 2 seconds to confirm...
              lcd.clear();
        
              // Continue to edit MIDI Channels...
              SetCCNumberPreset2();
            }
          } // WHILE editing CC Number...
        } // IF knob was turned...

// KNOB2
        int oldk2state2 = analogRead(k2);
        delay(5);
        k2state2 = analogRead(k2);
        if(abs(oldk2state2 - k2state2) > 8)    
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
    
            k2state2 = analogRead(k2);
            int k2mappedNumber2 = map(k2state2, 0, 1021, 0, 127);  
            lcd.setCursor(8, 1);
            lcd.print(k2mappedNumber2);
            
            if(editButtonState == 1){
              EditMode2();
              break;
            }
            
            if(commitButtonState == 1){
              k2newNumber2 = k2mappedNumber2;
              EEPROM.write(37,k2newNumber2); 

              lcd.clear();
              lcd.setCursor(7,0);
              lcd.print("K2");
              lcd.setCursor(0,1);
              lcd.print("NEW cc NUM:");
              lcd.setCursor(11, 1);
              lcd.print(k2newNumber2);
              delay(2000);  
              lcd.clear();
        
              SetCCNumberPreset2();
              break;
            }
          } 
        } 

//KNOB 3
        int oldk3state2 = analogRead(k3);
        delay(5);
        k3state2 = analogRead(k3);
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
            lcd.print("CC NUM: ");
    
            k3state2 = analogRead(k3);
            int k3mappedNumber2 = map(k3state2, 0, 1021, 0, 127);  
            lcd.setCursor(8, 1);
            lcd.print(k3mappedNumber2);
            
            if(editButtonState == 1){
              EditMode2();
              break;
            }
            
            if(commitButtonState == 1){
              k3newNumber2 = k3mappedNumber2;
              EEPROM.write(38, k3newNumber2); 

              lcd.clear();
              lcd.setCursor(7,0);
              lcd.print("K3");
              lcd.setCursor(0,1);
              lcd.print("NEW cc NUM:");
              lcd.setCursor(11, 1); 
              lcd.print(k3newNumber2);
              delay(2000);  
              lcd.clear();
        
              SetCCNumberPreset2();
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
            lcd.print("CC NUM: ");
    
            k4state2 = analogRead(k4);
            int k4mappedNumber2 = map(k4state2, 0, 1021, 0, 127);  
            lcd.setCursor(8, 1);
            lcd.print(k4mappedNumber2);
            
            if(editButtonState == 1){
              EditMode2();
              break;
            }
            
            if(commitButtonState == 1){
              k4newNumber2 = k4mappedNumber2;
              EEPROM.write(39, k4newNumber2); 
        
              lcd.clear();
              lcd.setCursor(7,0);
              lcd.print("K4");
              lcd.setCursor(0,1);
              lcd.print("NEW cc NUM:");
              lcd.setCursor(11, 1); 
              lcd.print(k4newNumber2);
              delay(2000);  
              lcd.clear();
        
              SetCCNumberPreset2();
              break;
            }
          } 
        } 

    // If user wants to continue in Edit Mode...
    if (editButtonState == 1) {
      setCCNumberPreset2Flag = 1;
      delay(250); // Aids in button stability to return to Edit Mode...
      SetMIDIChannelPreset2();
      break;
    }
    // If user wants to return to Session Mode...
    if (sesh2ButtonState == 1) {
      setCCNumberPreset2Flag = 1; 
      Preset2Mode(); 
      break;
    }
  } // while(SetCCNumberPreset2Flag != 1)
} // SetCCNumberPreset2() method 
