#include <SoftwareSerial.h>
#include <NewPing.h>
#include <Servo.h>

//L298n Motor Driver direction pins.
#define in1 5
#define in2 6
#define in3 9
#define in4 10
//servo motor starting point
#define spoint 106

//ultrasonic sensor
#define Echo1 A0
#define Trig1 A1
#define Echo2 A2
#define Trig2 A3
//servo motor
#define motor A4


// boolean flags for forward and backward check
bool isMovingForward = false;
bool isMovingBackward = false;

String voice;
Servo servo;
//ultrasonic check variables
int Left;
int Right;
int L = 0;
int R = 0;

//L298N Enable pins to control speed
const int ENA = 3;
const int ENB = 11;

void setup()
{
  Serial.begin(9600);  //Set the baud rate to your Bluetooth module.
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(Trig1, OUTPUT);
  pinMode(Echo1, INPUT);
  pinMode(Trig2, OUTPUT);
  pinMode(Echo2, INPUT);
  servo.attach(motor);
  servo.write(spoint);
  setMotorSpeed(ENA, ENB, 125);
}
void forward()
{
  isMovingForward = true;
  isMovingBackward = false;
  Serial.println("Entered Forward Function");
  digitalWrite(in1, HIGH);
  digitalWrite(in3, HIGH);
}

void back()
{
  isMovingForward = false;
  isMovingBackward = true;
  digitalWrite(in2, HIGH);
  digitalWrite(in4, HIGH);
}

void left()
{
  isMovingForward = true;
  isMovingBackward = false;
  L = leftsee();
  servo.write(spoint);
  if (L >= 10 )
  {
  digitalWrite(in3, HIGH);
  digitalWrite(in2, HIGH);
  delay(400);
  Stop();
  }
  else if (L < 10)
  {
    Stop();
  }
}

void right()
{
  isMovingForward = true;
  isMovingBackward = true;
  R = rightsee();
  servo.write(spoint);
  if (R >= 10 )
  {
  digitalWrite(in4, HIGH);
  digitalWrite(in1, HIGH);
  delay(400);
  Stop();
  }
  else if (L < 10)
  {
    Stop();
  }
}

void Circle()
{
  digitalWrite(in4, HIGH);
  digitalWrite(in1, HIGH);
  delay(100);
}

void Dance() {
  isMovingForward = true;
  isMovingBackward = true;
  servo.write(180);
  digitalWrite (in4, LOW);
  digitalWrite (in2, HIGH);
  digitalWrite (in3, LOW);
  digitalWrite (in1, LOW);
  delay (400);
  servo.write(spoint);
  digitalWrite (in4, HIGH);
  digitalWrite (in2, HIGH);
  digitalWrite (in3, LOW);
  digitalWrite (in1, LOW);
  delay(600);
  servo.write(20);
  digitalWrite (in4, LOW);
  digitalWrite (in2, HIGH);
  digitalWrite (in3, HIGH);
  digitalWrite (in1, LOW);
  delay (500);
  servo.write(spoint);
  digitalWrite (in4, HIGH);
  digitalWrite (in2, LOW);
  digitalWrite (in3, LOW);
  digitalWrite (in1, HIGH);
  delay (500);
  servo.write(180);
  digitalWrite (in4, LOW);
  digitalWrite (in2, HIGH);
  digitalWrite (in3, LOW);
  digitalWrite (in1, LOW);
  delay (400);
  servo.write(spoint);
  Stop();
}


int rightsee()
{
  servo.write(20);
  delay(800);
  Right = ultrasonicFront();
  return Right;
}
int leftsee()
{
  servo.write(180);
  delay(800);
  Left = ultrasonicFront();
  return Left;
}
int ultrasonicFront()
{
  digitalWrite(Trig1, LOW);
  delayMicroseconds(4);
  digitalWrite(Trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig1, LOW);
  long t = pulseIn(Echo1, HIGH);
  long cm = t / 29 / 2; //time convert distance
  return cm;
}

int ultrasonicRare()
{
  digitalWrite(Trig2, LOW);
  delayMicroseconds(4);
  digitalWrite(Trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig2, LOW);
  long t = pulseIn(Echo2, HIGH);
  long cm = t / 29 / 2; //time convert distance
  return cm;
}

void checkFrontObstacle()
{
  int distance = ultrasonicFront();
  delay(50);
  if (distance <= 50) {  // Adjust the threshold distance as needed
    Serial.print("Object detected at ");
    Serial.print(distance);
    Serial.println(" cm. Stopping the car.");
    Stop();
  }
}

void checkRearObstacle()
{
  int distance = ultrasonicRare();
  delay(50);
  if (distance <= 50) {  // Adjust the threshold distance as needed
    Serial.print("Object detected at ");
    Serial.print(distance);
    Serial.println(" cm. Stopping the car.");
    Stop();
  }
}

void Stop()
{
  isMovingForward = false;
  isMovingBackward = false;
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void setMotorSpeed(int enA, int enB, int Speed)
{
  analogWrite(enA, Speed);
  analogWrite(enB, Speed);
}
void loop()
{
  while (Serial.available()) {
    delay(10);
    char c = Serial.read();
    if (c == '#')
    {
      break;
    }
    voice += c;
  }

  if (voice.length() > 0)
  {
    Serial.println(voice);
    if (voice == "*forward")
    {
      forward();
    }
    else if (voice == "*backward")
    {
      back() ;
    }
    else if (voice == "*left")
    {
      left() ;
    }
    else if (voice == "*right")
    {
      right() ;
    }
    else if (voice == "*control")
    {
      Stop() ;
    }
    else if (voice == "*dance" or voice == "Dance")
    {
      Dance() ;
    }
    else if (voice == "*circle" or voice == "Circle")
    {
      Circle() ;
    }
    else if (voice == "*speed 10")
    {
      setMotorSpeed(ENA, ENB, 50);
    }
    else if (voice == "*speed 20")
    {
      setMotorSpeed(ENA, ENB, 100);
    }
    else if (voice == "*speed 30")
    {
      setMotorSpeed(ENA, ENB, 125);
    }
    else if (voice == "*speed 40")
    {
      setMotorSpeed(ENA, ENB, 150);
    }
    else if (voice == "*speed 50")
    {
      setMotorSpeed(ENA, ENB, 180);
    }
    else if (voice == "*speed 60")
    {
      setMotorSpeed(ENA, ENB, 200);
    }
    else if (voice == "*speed 70")
    {
      setMotorSpeed(ENA, ENB, 220);
    }
    else if (voice == "*speed 80")
    {
      setMotorSpeed(ENA, ENB, 230);
    }
    else if (voice == "*speed 90")
    {
      setMotorSpeed(ENA, ENB, 240);
    }
    else if (voice == "*speed 100")
    {
      setMotorSpeed(ENA, ENB, 255);
    }
    voice = "";
  }
  Serial.println(voice);
  if (isMovingForward)
  {
    checkFrontObstacle();
  }
  else if (isMovingBackward)
  {
    checkRearObstacle();
  }

}
