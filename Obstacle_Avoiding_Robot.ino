const int trigL = 10; //Left Sensor
const int echoL = 11; //pins

const int trigR = 12; //Right Sensor
const int echoR = 13; //pins

const int leftForward = 2;  //Left motor
const int leftBackward = 4;
const int enA = 3;          //PWM out

const int rightForward = 5; //Right motor
const int rightBackward = 7;
const int enB = 6;          //PWM out

int durationL = 0;    //Measurement duration of the left sensor
int distanceL = 0;    //Distance measured by the left sensor

int durationR = 0;    //Measurement duration of the right sensor
int distanceR = 0;    //Distance measured by the left sensor

void setup() 
{
  pinMode(trigL , OUTPUT);  //assigning input output pins
  pinMode(echoL , INPUT);   
  pinMode(trigR , OUTPUT);  
  pinMode(echoR , INPUT);
  pinMode(leftForward , OUTPUT);
  pinMode(leftBackward , OUTPUT);
  pinMode(rightForward , OUTPUT);
  pinMode(rightBackward , OUTPUT);
  
  Serial.begin(9600);

}

void loop()   //start of main function
{
  digitalWrite(trigL , LOW); //trigL pin initially off
  delayMicroseconds(2);      
  digitalWrite(trigL , HIGH);//trigL 10uS on
  delayMicroseconds(10);


  durationL = pulseIn(echoL , HIGH); //echoL on
  distanceL = (durationL/2) / 28.1 ; //distance calculation
  delay(10);                        //Converting the speed of sound to cm 
                                    
  digitalWrite(trigR , LOW);//trigR pin initially off
  delayMicroseconds(2);
  digitalWrite(trigR , HIGH);//trigR 10uS on
  delayMicroseconds(10);


  durationR = pulseIn(echoR , HIGH);//echoL on
  distanceR = (durationR/2) / 28.1 ;
  delay(10);


  if ( (distanceL < 20) || (distanceR < 20) )
  {
    analogWrite(enA, 50);
    analogWrite(enB, 50);                    //slow down
    
    digitalWrite(leftForward , HIGH);
    digitalWrite(leftBackward , LOW);
    digitalWrite(rightForward , HIGH);
    digitalWrite(rightBackward , LOW);
    delay(100);

    if(distanceL > distanceR) 
    {
      analogWrite(enA, 150);    //turn right
      analogWrite(enB, 150);
      digitalWrite(leftForward , HIGH);
      digitalWrite(leftBackward , LOW);
      digitalWrite(rightForward , LOW);
      digitalWrite(rightBackward , HIGH);
      delay(300);
    }
    else if(distanceL < distanceR)
    {
      analogWrite(enA, 150);
      analogWrite(enB, 150);
      digitalWrite(leftForward , LOW);    //turn left
      digitalWrite(leftBackward , HIGH);
      digitalWrite(rightForward , HIGH);
      digitalWrite(rightBackward , LOW);
      delay(300);
    }
    else
    {
      analogWrite(enA, 150);
      analogWrite(enB, 150);
      digitalWrite(leftForward , LOW);
      digitalWrite(leftBackward , HIGH);  //go forward
      digitalWrite(rightForward , LOW);
      digitalWrite(rightBackward , HIGH);
      delay(1000);
    }
  }
  else
  {
      analogWrite(enA, 75);
      analogWrite(enB, 75);             //go back
      digitalWrite(leftForward , HIGH);
      digitalWrite(leftBackward , LOW);
      digitalWrite(rightForward , HIGH);
      digitalWrite(rightBackward , LOW);
      delay(100);
  }
}
