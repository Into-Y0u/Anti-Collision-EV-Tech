#include<LiquidCrystal.h>  //Inclusion of the library for LCD display
LiquidCrystal LCD(11, 10, 9, 2, 3, 4, 5);   //Declaring all the pins for the LCD display

int trigPin = 12;    //Declaring the 'trig' pin of the ultrasonic sensor for the pin no. 12 of Arduino digital output
int echoPin = 13;    //Declaring the 'echo' pin of the ultrasonic sensor for the pin no. 13 of Arduino digital output

int M = 6;  //Declaring the motor output for the pin no. 6(PWM) of Arduino digital output

int buzzer = 7;  //Declaring the buzzerer and red LED for the pin no. 7 of Arduino digital output
int green = 8;  //Declaring the green LED for the pin no. 12 of Arduino digital output


int val1 = 255; //Declaring a variable 'val1' for the speed control of the motors
int val2 = 100;  //Declaring a variable 'val2' for the speed control of the motors
int val3 = 0;

int red = A4;
int yellow = A5;

long duration, distance, inch; //Declaring the variables to measure the duration and distance in the sensor

void setup() {

  //Setting all the pin outputs of the arduino module according to the pin declared variables
  
  pinMode(M, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);

  //Setting the LCD display output
  
  LCD.begin(16,2);
  LCD.setCursor(0,0);
  LCD.print("Object Distance:");
}

void loop() {
  //The functions of the pins starts here.
  //The sensor is given instructions to transmit the signal.
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  inch = (distance/2.54);

  //Providing instructions to the display to show the measured distance continuously

  LCD.setCursor(0,1);
  LCD.print("     ");
  LCD.setCursor(0,1);
  LCD.print(distance);
  LCD.print("  cm");
  LCD.print("   ");
  LCD.print(inch);
  LCD.print("  inch");
  delay(250);

  //The logic behind the speed controlling of the motor via the sensor starts


  if(distance <= 120 && distance > 70){
    analogWrite(M, val1);  //The speed of the motor will be controlled w.r.t the distance of the object
    digitalWrite(yellow, HIGH);
    digitalWrite(green, LOW);
    delay(45);
    digitalWrite(green, HIGH);
    digitalWrite(yellow, LOW);
   
    digitalWrite(red, LOW);
  
    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(200);         // ...for 1 sec
    noTone(buzzer);     // Stop sound...
    delay(200);
    }

   else if (distance <= 15){
    analogWrite(M, val3);
    digitalWrite(buzzer, LOW);
    digitalWrite(green, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(red, LOW);
    }

  else if(distance <= 70){
    analogWrite(M, val2);
    digitalWrite(yellow, LOW);
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(buzzer, HIGH);
    }

   else{
    analogWrite(M, val1);
    digitalWrite(buzzer, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(yellow, LOW);
    digitalWrite(red, LOW);
    }
  
}
