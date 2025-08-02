/*

Name: Measurement vehicle
Email: marcotinocososa@gmail.com
Team: Marco Tinoco


My project is a remote-controlled vehicle, allowing it to measure distance. We will use this feature to measure distance, 
allowing the user to pick between length, width, and distance modes. The first two modes measure the height and width of a given space, 
and the distance mode allows the user to measure the distance traveled by the vehicle. All of this information will be displayed on the LCD on 
the controller.

This the the code for the remote-controlled car
*/

#include <SPI.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN
const uint64_t pipeOut = 0xE8E8F0F0E1LL; // Set the pipe address for outgoing data
const uint64_t pipeIn = 0xE8E8F0F0E2LL; // Set the pipe address for incoming data
// Motor pins

const int in1 = 14; // Analog pin A0 - Green
const int in2 = 15; // Analog pin A1 - Blue
const int in3 = 4; // Purple
const int in4 = 7; // Grey
const int enA = 5; // Yellow
const int enB = 6; // White

int left_intr = 0;
int right_intr = 0;
const double radius = 0.03175;
double distance = 0;
int DEBOUNCE_DELAY = 10;
volatile unsigned long lastLeftInterrupt = 0;
volatile unsigned long lastRightInterrupt = 0;

bool connectionEstablished = false;  // flag to check if data has been received

void setup() {
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_2MBPS);
  radio.setChannel(124);
  radio.openWritingPipe(pipeIn);
  radio.openReadingPipe(1, pipeOut);
  radio.startListening();
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  Serial.begin(9600); // Initialize serial communication
  Serial.println("Waiting for data...");
  attachInterrupt(digitalPinToInterrupt(3), Left_ISR, CHANGE); //Left_ISR is called when left wheel sensor is triggered
  attachInterrupt(digitalPinToInterrupt(2), Right_ISR, CHANGE);//Right_ISR is called when right wheel sensor is triggered
}

void loop() {
  if (radio.available()) { //if we've made a connection to the remote control

    int data[2]; // array to hold joystick values
    radio.read(&data, sizeof(data));
    int x = data[0];
    int y = data[1];
    int motorSpeedA = map(y, 0, 1023, -255, 255);
    int motorSpeedLeft = motorSpeedA + (x - 512) / 2;
    int motorSpeedRight = motorSpeedA - (x - 512) / 2;
    motorSpeedLeft = constrain(motorSpeedLeft, -255, 255);
    motorSpeedRight = constrain(motorSpeedRight, -255, 255);

    // Set motor directions
    if (motorSpeedLeft > 0) {
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
    } else {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      motorSpeedLeft = -motorSpeedLeft;
    }
    if (motorSpeedRight > 0) {
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
    } else {
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      motorSpeedRight = -motorSpeedRight;
    }

    // Set motor speeds
    analogWrite(enA, motorSpeedLeft);
    analogWrite(enB, motorSpeedRight);


    unsigned long totalInterrupts = left_intr + right_intr;
    if (totalInterrupts > 0) {
      double wheelCircumference = 2 * 3.1415 * radius;
      double rotations = (left_intr + right_intr) / 2.0 / 40.0; // Assuming 40 pulses per revolution
      distance = wheelCircumference * rotations;
      // Serial.print(distance);
      // Serial.print("\n");
      radio.stopListening();
      double dist = distance;
      radio.write(&dist, sizeof(double));
      radio.startListening();
    }
    
    //Serial print for debugging
    // Serial.print("X: ");
    // Serial.print(x);
    // Serial.print(" - Y: ");
    // Serial.print(y);
    // Serial.print(" - Left: ");
    // Serial.print(motorSpeedLeft);
    // Serial.print(" - Right: ");
    // Serial.println(motorSpeedRight);
  }
}

void Left_ISR()
{
  unsigned long currentTime = millis();
  if (currentTime - lastLeftInterrupt > DEBOUNCE_DELAY) {
    left_intr++;
    lastLeftInterrupt = currentTime;
  }
}


void Right_ISR()
{
  unsigned long currentTime = millis();
  if (currentTime - lastRightInterrupt > DEBOUNCE_DELAY) {
    right_intr++;
    lastRightInterrupt = currentTime;
  }
}
