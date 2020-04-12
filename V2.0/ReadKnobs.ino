/* Author: Austin Stockwell
    Date: 04/08/2020
    Description: ReadKnobs()
       Samples voltages read on potentiometers to create MIDI Messages & control knob LEDs
*/
void ReadKnobsPreset1(){
  Serial.println("READ KNOBS PRESET 1 ");

    // Array to holds each knobs CC CONTROL CHANGE VALUE
    int mappedValArray[4];

      Serial.println("Prest 2 last state");
      Serial.println(Preset2KnobStates[0]);
      Serial.println("This preset's last state");
      Serial.println(k1OldState);      

      while(resetKnobFlag == 1){
         Serial.println("IN WHILE");

      /* When the user switches back to this preset (Preset 1), this circuit prevents the 
         previous values of Preset 1 from being overwritten to the values of Preset 2. */
        if(k1OldState != Preset2KnobStates[0]){
          k1OldState = Preset2KnobStates[0];
          Serial.println("WE HAVE CHANGED K1OLDSTATE TO THE PRESET 2 VALUE");
          Serial.println(k1OldState);
        }
        if(k2OldState != Preset2KnobStates[1]){
          k2OldState = Preset2KnobStates[1];
        }
         if(k3OldState != Preset2KnobStates[2]){
          k3OldState = Preset2KnobStates[2];
        }
        if(k4OldState != Preset2KnobStates[3]){
          k4OldState = Preset2KnobStates[3];
        }
        break;
      }
        resetKnobFlag = 0; // Set flag to 0 so we only set prest 2 values once

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
               Serial.println("KNOB HAS MOVED PRESET 1");   
                
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
                // if the knob has moved in the next iteration of ReadKnobsPreset1()
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
void ReadKnobsPreset2(){
  Serial.println("READ KNOBS PRESET 2");

    // Array to holds each knobs CC CONTROL CHANGE VALUE
    int mappedValArray2[4];  

      /* When the user switches back to this preset (Preset 2), this circuit prevents the 
         previous values of Preset 2 from being overwritten to the values of Preset 1. */
      while(resetKnobFlag2 == 1){
        Serial.println("IN WHILE");
        // If the last state of Preset 2 DOES NOT equal the last state of Preset 1....
        // Set the last state of Preset 1 equal to last state of Preset 2...
        if(k1OldState2 != Preset1KnobStates[0]){
          Serial.println("WE HAVE CHANGED K1OLDSTATE2 TO THE PRESET 1 VALUE");
          k1OldState2 = Preset1KnobStates[0];
        }
        if(k2OldState2 != Preset1KnobStates[1]){
          k2OldState2 = Preset1KnobStates[1];
        }
         if(k3OldState2 != Preset1KnobStates[2]){
          k3OldState2 = Preset1KnobStates[2];
        }
        if(k4OldState2 != Preset1KnobStates[3]){
          k4OldState2 = Preset1KnobStates[3];
        }
        break;
      }
        resetKnobFlag2 = 0; // Set resetKnobFlag to 0 so we only reset the values of Preset 2
                          // to the values of Preset 1 one time (prevents data overwrite)...

   // Continuously read knob values to see if knob has been moved
    k1state2 = analogRead(k1);
    k2state2 = analogRead(k2);
    k3state2 = analogRead(k3);
    k4state2 = analogRead(k4);
    
    // Map recieved potentiomter values to control LED w/PWM (0-255)
    int k1mappedLED2 = map(k1state2, 0, 1021, 0, 255);
    int k2mappedLED2 = map(k2state2, 0, 1021, 0, 255);
    int k3mappedLED2 = map(k3state2, 0, 1021, 0, 255);
    int k4mappedLED2 = map(k4state2, 0, 1021, 0, 255);
    analogWrite(2, k1mappedLED2);
    analogWrite(3, k2mappedLED2);
    analogWrite(4, k3mappedLED2);
    analogWrite(5, k4mappedLED2);

      // IF knob1 moves send midi message
      if(abs (k1state2 - k1OldState2) >= 5){
         Serial.println("KNOB HAS MOVED PRESET 2");   
          
          // Re-read value and map to MIDI message format (0 - 127)
          k1state2 = analogRead(k1);
          mappedValArray2[0] = map(k1state2, 0, 1021, 0, 127);       

          // SEND MIDI MESSAGE!!!
          byte k1MIDIMess2[3] = {k1newChannel2, k1newNumber2, mappedValArray2[0]};
          for (int k1index2 = 0; k1index2 < 3; k1index2++)
          {
           Serial.write(k1MIDIMess2[k1index2]);
          }    
  
          // Holds the most recent value of the knob for use in determining
          // if the knob has moved in the next iteration of ReadKnobsPreset1()
          k1OldState2 = k1state2;
      }     

      if (abs(k2state2 - k2OldState2) >= 5){
          k2state2 = analogRead(k2);
          mappedValArray2[1] = map(k2state2, 0, 1021, 0, 127);

        byte k2MIDIMess2[3] = {k2newChannel2, k2newNumber2, mappedValArray2[1]};
        for (int k2index2 = 0; k2index2 < 3; k2index2++)
        {
           Serial.write(k2MIDIMess2[k2index2]);
        }    
          k2OldState2 = k2state2;
      }  

      if (abs(k3state2 - k3OldState2) >= 5){
          k3state2 = analogRead(k3);
          mappedValArray2[2] = map(k3state2, 0, 1021, 0, 127);

        byte k3MIDIMess2[3] = {k3newChannel2, k3newNumber2, mappedValArray2[2]};
        for (int k3index2 = 0; k3index2 < 3; k3index2++)
        {
           Serial.write(k3MIDIMess2[k3index2]);
        }    
          k3OldState2 = k3state2;
      }  

      if (abs(k4state2 - k4OldState2) >= 5){
          k4state2 = analogRead(k4);
          mappedValArray2[3] = map(k4state2, 0, 1021, 0, 127);

        byte k4MIDIMess2[3] = {k4newChannel2, k4newNumber2, mappedValArray2[3]};
        for (int k4index2 = 0; k4index2 < 3; k4index2++)
        {
           Serial.write(k4MIDIMess2[k4index2]);
        }    
          k4OldState2 = k4state2;
      }  
}
