// C++ code

// Declaring variables for motor pins
int LMF = 5;
int LMB = 4;
int RMF = 9;
int RMB = 8;

//LED LIGHTS
int redledlight = 7;
int greenledlight = 6;

// Defining variables for sensor pins
#define trigpin A0
#define echopin A1
#include <Servo.h> //including servo 
Servo microservo; //defining servo

// Defining variables for duration of the ping and distance
long duration; // Time for echo pin to return in microseconds
long distance; // Distance to target in cm for forward

// Sensor distance directions
int distanceleft;
int distanceright;

void setup() // Code only runs once 
{
  // Setting all motor pins as OUTPUTS
  pinMode(LMF, OUTPUT);
  pinMode(LMB, OUTPUT);
  pinMode(RMF, OUTPUT);
  pinMode(RMB, OUTPUT);
  //setting up microservo 
  microservo.attach(10);
  pinMode(echopin, INPUT); // Set echo pin as INPUT
  pinMode(trigpin, OUTPUT); // Set trig pin as OUTPUT
  Serial.begin(9600);
}

void loop() // Code runs forever
{
  distance = sensordata();
  if(distance < 20) // Car stops when sensor detects object within 20cm
  {
    stop(); //stops the car 
    delay(1000);
    backward(); //goes backwards
    delay(300);
    stop(); //stop for a bit 
    delay(1000);

    //scanning nearby objects by using microservo
    microservo.write(0); //turn servo to 0 degrees (left)
    delay(1000); //wait for servo to reach 0 degrees 
    distanceleft = sensordata(); //measure distance at 0 degrees

    microservo.write(100); //turn servo to 180 degrees (right)
    delay(1000); //wait for servo to reach 180 degrees 
    distanceright = sensordata(); //measure distance at 180 degrees

    microservo.write(50); //turn servo to straight direction 

    //Determine which direction to go based on sensor data
    if(distanceleft > distanceright) 
    {
      goleft();
    }
    else
    {
      goright();
    }
  } 
  distance = sensordata(); 
    if (distance >= 20) {
      forward(); // Move forward if no obstacles are detected within 20cm
    }
}
long sensordata()
{
  // Trigger ultrasonic sensor
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);
  duration = pulseIn(echopin, HIGH);
  return duration / 29 / 2;
}
//Green LED light would turn on whenever the vehicle is on the move
//Red LED light would turn on whenever the vehicle stops
//Just like traffic lights 
void forward() // Car go forward
{
  digitalWrite(greenledlight, HIGH); 
  digitalWrite(redledlight, LOW);
  digitalWrite(LMF, HIGH);
  digitalWrite(LMB, LOW);
  digitalWrite(RMF, HIGH);
  digitalWrite(RMB, LOW);
}
void backward() // Car go backward
{
  digitalWrite(greenledlight, HIGH);
  digitalWrite(redledlight, LOW);
  digitalWrite(LMF, LOW);
  digitalWrite(LMB, HIGH);
  digitalWrite(RMF, LOW);
  digitalWrite(RMB, HIGH);
}
void goright() // Car go right
{
  digitalWrite(greenledlight, HIGH);
  digitalWrite(redledlight, LOW);
  digitalWrite(LMF, HIGH);
  digitalWrite(LMB, LOW);
  digitalWrite(RMF, LOW);
  digitalWrite(RMB, HIGH);
}
void goleft() // Car go left
{
  digitalWrite(greenledlight, HIGH);
  digitalWrite(redledlight, LOW);
  digitalWrite(LMF, LOW);
  digitalWrite(LMB, HIGH);
  digitalWrite(RMF, HIGH);
  digitalWrite(RMB, LOW);
}
void stop() // Stopping motor
{
  digitalWrite(redledlight, HIGH);
  digitalWrite(greenledlight, LOW);
  digitalWrite(LMF, LOW);
  digitalWrite(LMB, LOW);
  digitalWrite(RMF, LOW);
  digitalWrite(RMB, LOW);
}
