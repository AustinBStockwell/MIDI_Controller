/* Author: Austin Stockwell
    Date: 04/08/2020
    Description: SessionMode()
      Ensure user wants to send MIDI data or switch to Edit Modes...
*/
void Preset1Mode() {
  Serial.println("SESSION MODE");
  
  // Setup LCD & LED for Session Mode 
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  SESSION MODE  ");
  digitalWrite(seshLED, LOW);
  digitalWrite(sesh2LED, LOW);
  digitalWrite(editModeLED, LOW);
  
  // Stay in Session MODE until user chooses another MODE
  int sessionFlag = 0;
  while (sessionFlag != 1) {
    editButtonState = digitalRead(editButton); 
    sesh2ButtonState = digitalRead(sesh2Button);
    
    // Read Value and compose MIDI message for Preset 1...
    ReadKnobsPreset1();
   
    // IF user wants to switch to Preset 2...
    if(sesh2ButtonState == 1){
      // Pass last Preset 1 knob states...
      Preset1KnobStates[0] = k1OldState;
      Preset1KnobStates[1] = k2OldState;
      Preset1KnobStates[2] = k3OldState;
      Preset1KnobStates[3] = k4OldState;    
      resetKnobFlag2 = 1; // Ensures Preset 2 values are not overwritten
      Preset2Mode();
    }
    
    // If user wants to enter Edit Mode...
    if(editButtonState == 1) {
      Serial.println("Leaving Session 1...");
      sessionFlag = 1;
    }
  }
  sessionFlag = 0; // Reset flag for next use of Session Mode
  EditMode1(); // Returns to Edit Mode
}

/******************************************************/
void Preset2Mode(){
  Serial.println("SESSION 2 MODE");
  
  // Setup LCD & LED for Session2 Mode 
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" SESSION 2 MODE  ");
  digitalWrite(seshLED, LOW);
  digitalWrite(sesh2LED, LOW);
  digitalWrite(editModeLED, LOW);

  // Stay in Session 2 Mode until user chooses another MODE
  int session2Flag = 0;
  while (session2Flag != 1) {
    editButtonState = digitalRead(editButton); 
    seshButtonState = digitalRead(seshButton);
    
    // Read value of knobs...
    ReadKnobsPreset2();

    // IF user wants to switch to Prest 1...
    if(seshButtonState == 1){
      // Save current state of Preset 2 knob states to pass back to
      // Preset 1 so Preset 1 values do not change to what they were set
      // to previously...
      Preset2KnobStates[0] = k1OldState2;
      Preset2KnobStates[1] = k2OldState2;
      Preset2KnobStates[2] = k3OldState2;
      Preset2KnobStates[3] = k4OldState2;   
      resetKnobFlag = 1; // Ensures Preset 1 previous values are not overwritten
      Preset1Mode();
    }
    
    // If user wants to enter CC Edit Mode...
    if(editButtonState == 1) {
      Serial.println("Leaving Session 2...");
      session2Flag = 1;
    }
  }
  session2Flag = 0; // Reset flag for next use of Session Mode
  EditMode2(); // Returns to Edit Mode
}

