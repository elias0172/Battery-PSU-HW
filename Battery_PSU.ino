/*  C 2021 Elias Klimsch
 *  MCU: ATTINY85 */

#include <SoftwareSerial.h>
SoftwareSerial mySerial(0, 1); //RX TX

int transistor = 3;
int led = 4;
int voltage = A1;
float R1 = 10000; //Value from Resistor to VCC in Ohm
float R2 = 1000; //Value from Resistor to GND in Ohm
float VCC_MCU = 5.0; //Supply voltage of µC in Volts
int ADC_Res = 1023; //ADC Resolution in values minus 1
int cells = 10; //Quantity of cells in Series
float threshold = 3.0; //Minimun Voltage per cell
bool state = 1;

void setup()
{
  pinMode(voltage, INPUT);
  pinMode(transistor, OUTPUT);
  pinMode(led, OUTPUT);
  mySerial.begin(4800);
  delay(5000);
}

void loop()
{
  delay(300);
  float act_voltage = ((analogRead(voltage) * (VCC_MCU / ADC_Res)) / (R2 / (R1 + R2))); //Voltage conversion
  mySerial.println(act_voltage);
  if (act_voltage < (cells * threshold)) //calculating threshold voltage
  {
    state = 0;
  }
  mySerial.println(state);
  switch (state)
  {
    case 0: //Lockout
      digitalWrite(transistor, LOW);
      digitalWrite(led, HIGH);
      break;
    case 1: // O.K.
      digitalWrite(transistor, HIGH);
      digitalWrite(led, LOW);
      break;
    default:
      break;
  }
}
