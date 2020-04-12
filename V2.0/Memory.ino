/* Author: Austin Stockwell
    Date: 04/08/2020
    Description: Memory()
      Access variables stored in memory for each preset
*/
void Memory(){
  // Preset 1
  k1newChannel = EEPROM.read(0);
  k2newChannel = EEPROM.read(1);
  k3newChannel = EEPROM.read(2);
  k4newChannel = EEPROM.read(3);
  k1newNumber = EEPROM.read(12);
  k2newNumber = EEPROM.read(13);
  k3newNumber = EEPROM.read(14);
  k4newNumber = EEPROM.read(15);

  // Preset 2
  k1newChannel2 = EEPROM.read(24);
  k2newChannel2 = EEPROM.read(25);
  k3newChannel2 = EEPROM.read(26);
  k4newChannel2 = EEPROM.read(27);
  k1newNumber2 = EEPROM.read(36);
  k2newNumber2 = EEPROM.read(37);
  k3newNumber2 = EEPROM.read(38);
  k4newNumber2 = EEPROM.read(39); 
}
