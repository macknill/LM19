/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */
 
 #include <ModbusRtu.h>
 
uint16_t au16data[5] = {
  3, 1415, 1, 1, 1};
 Modbus slave(1,0,0); // this is slave @1 and RS-232 or USB-FTDI
 
int VssLM19 = 14,  Temperature1 =  15, GndLM19 =  16, Temperature2 =  18, VccADC = 18;


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  pinMode(VssLM19, OUTPUT);  
  digitalWrite(VssLM19, HIGH);
  pinMode(17, OUTPUT);  
  digitalWrite(17, HIGH);
  pinMode(Temperature1, INPUT);
  pinMode(Temperature2, INPUT);
  pinMode(GndLM19, OUTPUT);
  digitalWrite(GndLM19, LOW);
  pinMode(19, OUTPUT);
  digitalWrite(19, LOW);
  slave.begin(9600);
}

float GiveMeTemp(int number)
{  
  float vin;
  float temp;
  float PowerVoltage = (1024.0/(float)analogRead(VccADC)) * 1.8; //read avr power voltage, using external ref 1.8 volt
  switch(number){
    case 15: 
       vin = PowerVoltage * (float)analogRead(number) / 1024.0;
       temp =  -1481.96 + sqrt(2.1962 + (1.8639 - vin) / 3.88) * 1000.0 + 0.5;
       return temp;
       break;
    case 18: 
       vin = 5000.0 * analogRead(number) / 1024.0;
       //temp =  (vin - 500) / 10 ;
       return temp;
       break;
    default:
      return 0;
       break;
       
  }
  //float temp = (1.8663 - vin) / (3.88* 0.000001);
  //temp = sqrt(2.1962*0.000001 + temp);
  //temp = temp - 1481.96;
}


//almost rms
#define rms_deep 100
float rms_array[2][rms_deep];
float rms[2] = {0,0};
uint16_t rms_count = 0;

void rms_calc(void)
{
  if (rms_count < rms_deep)
  {
      rms_array[0][rms_count] = GiveMeTemp(Temperature1);
      rms_array[1][rms_count] = GiveMeTemp(Temperature2);
      rms_count++;
  }
  else
  {
    float temp[2] = {0,0};
    for (uint16_t count = 0; count < rms_deep; count++)
    {
      temp[0] += rms_array[0][count];
      temp[1] += rms_array[1][count];
    }
    rms[0] = temp[0]/rms_deep;
    rms[1] = temp[1]/rms_deep;
    rms_count = 0;
  }
}
// the loop function runs over and over again forever
void loop() {
  
  slave.poll( au16data, 5);
  au16data[0] = rms[0]*100;
  au16data[1] = rms[1]*100;
  slave.setID((uint8_t)au16data[4]);
  rms_calc();
  //delay(1000);
}
