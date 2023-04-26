#include <PZEM004Tv30.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 4);

PZEM004Tv30 pzem(10, 11 ); // Software Serial pin 8 (RX) & 9 (TX)

double switchTarget = pzem.energy() + 0.005;

void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print("ENERGY METER");
  lcd.setCursor(3, 1);
  lcd.print("BY OWAISSS");
  delay(3000);
  lcd.clear(); 
 
 
}

void loop() {
  float voltage = pzem.voltage();
  if (voltage != NAN) {
    Serial.print("Voltage: ");
    Serial.print(voltage);
    Serial.println("V");
    lcd.setCursor(0, 0);
    lcd.print("V:");
    lcd.print(voltage);
  } else {
    Serial.println("Error reading voltage");
  }

  float current = pzem.current();
  if (current != NAN) {
    Serial.print("Current: ");
    Serial.print(current);
    Serial.println("A");
    lcd.setCursor(9, 0);
    lcd.print("I:");
    lcd.print(current);
  } else {
    Serial.println("Error reading current");
  }

  float power = pzem.power();
  if (current != NAN) {
    Serial.print("Power: ");
    Serial.print(power);
    Serial.println("W");

    lcd.setCursor(0, 2);
    lcd.print("P:");
    lcd.print(power);
  } else {
    Serial.println("Error reading power");
  }

  float energy = pzem.energy();

  if (current != NAN) {
    Serial.print("Energy: ");
    Serial.print(energy*1000);
    Serial.println("Wh");
   
    lcd.setCursor(0, 3);
    lcd.print("E:");
    lcd.print(energy, 4);

  } else {
    Serial.println("Error reading energy");
  }

  float frequency = pzem.frequency();
  if (current != NAN) {
    Serial.print("Frequency: ");
    Serial.print(frequency);
    Serial.println("Hz");

    lcd.setCursor(9, 1);
    lcd.print("F:");
    lcd.print(frequency);
  } else {
    Serial.println("Error reading frequency");
  }

  float pf = pzem.pf();
  if (current != NAN) {
    Serial.print("PF: ");
    Serial.println(pf);
    lcd.setCursor(0, 1);
    lcd.print("Pf:");
    lcd.print(pf);
  } else {
    Serial.println("Error reading power factor");
  }
 
  Serial.println();
  delay(5000);
  

// --Conditions for Meter switch--
 
 if( pzem.energy() <= switchTarget ){
    
  digitalWrite(LED_BUILTIN, HIGH);
}
else{
  digitalWrite(LED_BUILTIN, LOW);

  if( pzem.energy() >= switchTarget + 0.005 ){

    switchTarget = switchTarget + (0.005 * 2);
  }
}
}