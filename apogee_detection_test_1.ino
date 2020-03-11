

#include <Servo.h>

Servo myservo; //create servo object to control the servo
int potpin = A0; //analog pin to connect a potentiometer (LATER TO BE ALTITUDE READINGS)
int index = 0;
int altitude[100]; //later might change to double for precision 
int sensorMax = 0;
int sensorMin = 0;

void setup() 
{
  Serial.begin(9600);
  
  myservo.attach(9);  //attached the servo on pin 9 to the servo object
  myservo.write(0);   //set the initial position of the servo to 0
  
  sensorMax = analogRead(potpin);
  sensorMin = sensorMax;
}


void loop()
{
  // MEASUREMENTS
  int val = analogRead(potpin);
  altitude[index] = val;
  index++;
  
  // DO SOME MATH
  if (val > sensorMax) sensorMax = val; 
  if (val < sensorMin) sensorMin = val; 

  // TO TRIGGER PARACHUTE DEPLOYMENT
  if (val == 0 ) {
    myservo.write(0);
   }else if(val == 1023){
    myservo.write(180);
   } 
  int i;
  int difference = analogRead(potpin)- sensorMax;
  if(difference<=0) {
     for(i=1 && difference <=0;i<=100;i++) //need to say that if the previous reading minus max is negative then increment
      { if (i==100){Serial.println("APOGEE");} }
     } else{i=1;}
    
  // OUTPUT TO SERIAL
  Serial.print("\tMIN:\t");
  Serial.print(sensorMin);
  Serial.print("\tMAX:\t");
  Serial.print(sensorMax);
  Serial.print("\tDIFFERENCE:\t");Serial.print(difference);
  Serial.print("\t count:\t");Serial.print(i);
  Serial.print("\tVALUE:\t");
  Serial.println(analogRead(potpin));
}




  // For calculating an AVERAGE of selected values:
  /* every iteration of loop makes one additional measurement,
  // so the first 10 readings will display too low average
  /*int numReadings = 10;
    int altitude[10];
  if (index >= numReadings) index = 0; 
  //running average
  float total = 0;
  for (int i = 0; i< numReadings; i++) total += altitude[i];
  //float average = total /numReadings;   
  //Serial.print("\tAVG:\t");
  //Serial.println(average, 1);  // 1 decimal*/    
