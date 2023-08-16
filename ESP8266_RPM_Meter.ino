//DIY Tachometer to Measure Accurate RPM using ESP8266 - NodeMCU
//This code is published by https://www.circuitschools.com
//Attribution required to republish.
#include <LiquidCrystal_I2C.h>
 
// Create the lcd object address 0x3F and 16 columns x 2 rows 
LiquidCrystal_I2C lcd(0x27, 16,2);  //

uint8_t irport = D6;
unsigned long lastflash;
int RPM;
void ICACHE_RAM_ATTR sens() {
  RPM++;
}
 
void setup() {
Serial.begin(9600);
lcd.init();
  
  // Turn on the backlight on LCD.
  lcd.backlight();
 
// IR Infrared sensor
pinMode(irport, INPUT_PULLUP); 
attachInterrupt(digitalPinToInterrupt(irport), sens, RISING);
 //SENSOR: GPIO0(NodeMCU - D3)
}
 
void loop() {
  noInterrupts();
  int wings= 1;  // no of wings of rotating object, for disc object use 1 with white tape on one side
  int RPMnew = RPM/wings;  //here we used fan which has 3 wings
  Serial.print(RPMnew);
  Serial.print(" sec^-1");  //Revolutions per second
  lcd.clear();
  lcd.print(RPMnew);
  lcd.print(" sec^-1");
  Serial.print((RPMnew*60));
  Serial.println(" min^-1");   //Revolutions per minute
  lcd.setCursor(0, 1);
  lcd.print(RPMnew*60);
  lcd.print(" min^-1");
  RPM=0;
  interrupts(); 
  delay(1000);  //1 second.
}