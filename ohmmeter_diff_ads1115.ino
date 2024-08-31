#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;

const float R_known = 9830.0;  // Known 10kΩ resistor
const float V_in=5.051;  // Input voltage from ESP32
//const float adc0=5.04825;
 //const float adc1=0.461;
 
void setup(void) {
  Serial.begin(9600);
  
  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS1115.");
    while (1);
  }
  
  // Set the gain to +/- 4.096V range (1 bit = 0.125mV)
  ads.setGain(GAIN_TWOTHIRDS);
}

void loop(void) {
  int16_t adc0,adc1;
  float V_out, I, R_unknown,V,Vref;
  
  adc0 = ads.readADC_Differential_0_1();
  Vref = adc0 * 0.1875 / 1000.0;
  
 adc1 =  ads.readADC_Differential_2_3();
  V_out= adc1 * 0.1875 / 1000.0;
  //V= adc0 -adc1;
V=Vref-V_out;
  I=V/R_known;
 R_unknown=V_out/I;
 
 
  // Print the measured voltage
  Serial.print("Voltage across A0&A1: ");
  Serial.print(Vref, 10);
  Serial.println(" V");
   
   
  Serial.print("Voltage across A2&A3: ");
  Serial.print(V_out, 10);
  Serial.println(" V");
  // Print the calculated current
  Serial.print("Current through circuit: ");
  Serial.print(I, 10);
  Serial.println(" A");
  
  // Print the calculated unknown resistance
  Serial.print("R_unknown: ");
  Serial.print(R_unknown);
  Serial.println(" ohms");
  
  delay(1000);

 
}



