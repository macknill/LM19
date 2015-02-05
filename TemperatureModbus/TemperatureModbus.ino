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
int VssLM19 = 14,  Temperature1 =  15, GndLM19 =  16, Temperature2 =  18;

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
  Serial.begin(9600);
}

float GiveMeTemp(int number)
{
  float vin;
  float temp;
  switch(number){
    case 15: 
       vin = 5 * analogRead(number) / 1024.0;
       temp =  -1481.96 + sqrt(2.1962 + (1.8639 - vin) / 3.88) * 1000 + 0.5;
       //temp=((-3.88*0.000001)*(temp*temp))+(-1.15*0.01*temp)+1.8639;       
       //temp =  -1481.96 + sqrt(2.1962 + (1.8639 - vin) / 3.88) * 1000 + 0.5;
       return temp;
       break;
    case 18: 
       vin = 5000.0 * analogRead(number) / 1024.0;
       
  Serial.println(vin);
       temp =  (vin - 500) / 10 ;
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

// the loop function runs over and over again forever
void loop() {
  
  Serial.println(GiveMeTemp(Temperature1));
  Serial.println(GiveMeTemp(Temperature2));
  Serial.println("all");
  delay(1000);
}
