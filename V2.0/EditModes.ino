/* Author: Austin Stockwell
    Date: 04/08/2020
    Description: EditModes()
       Accesses the MIDI Channel / Control Number editing for each preset...
*/
void EditMode1(){
  Serial.println("PRESET 1 EDIT MODE");
  
  // Setup LCD & LEDs for Preset 2 Edit Mode
  lcd.clear();
  lcd.setCursor(0, 0); // (column, row)
  lcd.print("  EDIT SESH 1 ");
  digitalWrite(editModeLED, HIGH);
  digitalWrite(seshLED, HIGH);
  digitalWrite(sesh2LED, LOW);
  for (int index = 0; index < 4; index++) {
    digitalWrite(knobLEDs[index], LOW);
  }
  
  // Stay in Edit Mode until user presses Session 1 Button...
  int edit1Flag = 0;
  while (edit1Flag != 1) {
    seshButtonState = digitalRead(seshButton);
    editButtonState = digitalRead(editButton);  
  
  // State detection sub-circuit toggles between MIDI CH /CC NUM editing 
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
              SetMIDIChannelPreset1();
            }
            // SET CONTROL NUMBER 
            else{
              SetCCNumberPreset1();
            }
        }
        
    // If user wants to enter Session Mode...
    if (seshButtonState == 1){
      edit1Flag = 1;
    } 
  } // while(edit2Flag != 1)
  edit1Flag = 0;  // Resets editFlag for next use
  digitalWrite(editModeLED, LOW); // Light off (leaving Edit Mode)
  Preset1Mode();  // Return to Session Mode
}

/******************************************************/
void EditMode2(){
  Serial.println("PRESET 2 EDIT MODE");
  
  // Setup LCD & LEDs for Preset 2 Edit Mode
  lcd.clear();
  lcd.setCursor(0, 0); // (column, row)
  lcd.print("  EDIT SESH 2 ");
  digitalWrite(editModeLED, HIGH);
  digitalWrite(sesh2LED, HIGH);
  digitalWrite(seshLED, LOW);
  for (int index = 0; index < 4; index++) {
    digitalWrite(knobLEDs[index], LOW);
  }
  
  // Stay in CCMode until user presses Session 2 Button
  int edit2Flag = 0;
  while (edit2Flag != 1) {
    sesh2ButtonState = digitalRead(sesh2Button);
    editButtonState = digitalRead(editButton);  
  
  // State detection sub-circuit toggles between MIDI CH /CC NUM editing 
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
              SetMIDIChannelPreset2();
            }
            // SET CONTROL NUMBER 
            else{
              SetCCNumberPreset2();
            }
        }
    // If user wants to enter Session 2 Mode...
    if (sesh2ButtonState == 1){
      edit2Flag = 1;
    }
  } // while(edit2Flag != 1)
  edit2Flag = 0;  // Resets editFlag for next use
  digitalWrite(editModeLED, LOW); // Light off (leaving Edit Mode)
  Preset2Mode();  // Return to Session Mode
}
