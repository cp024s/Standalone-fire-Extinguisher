#include <Servo.h>

// FLAME SENSORS IN EACH AXIS
const int flameSensor1 = A0;
const int flameSensor2 = A1;
const int flameSensor3 = A2;
const int flameSensor4 = A3;

//SMOKE SENSOR FOR ADDITIONAL SAFETY
const int smokeSensor1 = A4;
const int smokeSensor2= A5;

//SERVO PINS
const int headServoPin = 3;
const int armServoPin = 2;

//PERIPHERAL CONNECTIONS
const int buzzerPin = 8;
const int relayPin = 7;

//THRESHOLD VALUES
const int FlameThreshold = 100;
const int smokeThreshold = 500;

//SERVO DECLARATIONS
Servo headServo;
Servo armServo;

//INITIAL SETUP PART
void setup() {
  Serial.begin(9600);

  headServo.attach(headServoPin);
  armServo.attach(armServoPin);

  headServo.write(0); // Adjust the value to set the initial head position
  armServo.write(0); // Adjust the value to set the initial arm position

  pinMode(buzzerPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
}

//LOOP PART
void loop() {

  int flame1Value = analogRead(flameSensor1);
  int flame2Value = analogRead(flameSensor2);
  int flame3Value = analogRead(flameSensor3);
  int flame4Value = analogRead(flameSensor4);
  
  int smoke1Value = analogRead(smokeSensor1);
  int smoke2Value = analogRead(smokeSensor2);

  if (flame1Value > FlameThreshold || flame2Value > FlameThreshold || flame3Value > FlameThreshold || flame4Value > FlameThreshold) {
    activateBuzzer();
  }
  if(smoke1Value > smokeThreshold || smoke2Value > smokeThreshold) {
    activateBuzzer();
  }
  
// FOR POSITION MOVEMENT
  if (flame1Value <100) {
    northpos();
  }
  else if (flame2Value <100) {
    eastpos();
  }
  else if (flame3Value <100) {
    southpos();
  }
  else if (flame4Value <100) {
    westpos();
  }
  else {
    idle();
  }
  // Delay for stability
  delay(100);
}

//FUNCTION CALLS
  void activateExtinguisher() {
    digitalWrite(relayPin,HIGH);
    delay(2000);
    digitalWrite(relayPin,LOW);
  }

//BUZZER SOUND
  void activateBuzzer() {
    digitalWrite(buzzerPin,HIGH);
    delay(1000);
    digitalWrite(buzzerPin,LOW);
  }

//POSITION 
  void northpos()
  {
    //move to sensor1 position
    armServo.write(0);
    delay(10);
    headServo.write(0);
    delay(10);
    Serial.println("NORTH");
    activateBuzzer();
    activateExtinguisher();
  }

  void eastpos()
  {
    //move to sensor2 position
    armServo.write(0);
    delay(10);
    headServo.write(90);
    delay(10);
    Serial.println("EAST");
    activateBuzzer();
    activateExtinguisher();
  }

void southpos()
  {
    //move to sensor3 position
    armServo.write(180);
    delay(10);
    headServo.write(0);
    delay(10);
    Serial.println("SOUTH");
    activateBuzzer();
    activateExtinguisher();
  }

  void westpos()
  {
    //move to sensor4 position
    armServo.write(180);
    delay(10);
    headServo.write(90);
    delay(10);
    Serial.println("WEST");
    activateBuzzer();
    activateExtinguisher();
  }

  void idle() {
    //IDLE STATE
    armServo.write(0);
    delay(10);
    headServo.write(90);
    Serial.println("IDLE");
  }
