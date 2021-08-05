#include <IRremote.h>
#include <NewTone.h>
#define ON_OFF_KEY 0xFF629D
#define LEFT_KEY 0xFF30CF
#define RIGHT_KEY 0xFF7A85
#define FORWARD_KEY 0xFF9867
#define BACKWARD_KEY 0xFF38C7
#define STOP_KEY  0xFF18E7
#define A 0xFF22DD

int motor1pin1 = 2;
int motor1pin2 = 3;

int motor2pin1 = 4;
int motor2pin2 = 5;
const int sensorPin = 6;
int LED = 13;
int Buzzer = 9;

IRrecv irrecv(sensorPin);  // Initialize IR Library
decode_results results;   // Initialize IR Library
bool isOn = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  irrecv.enableIRIn();  // Start the receiver
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:  
  Serial.print("IR Sensor Reading");
  if (irrecv.decode(&results)) {
    irrecv.resume(); // Receive the next value
    // Power switch
    if (results.value == ON_OFF_KEY) {
      if (isOn == true) {
        Serial.println("Turning Off"); 
        powerOff();
      }
      else if (isOn == false) {
        Serial.println("Turning On"); 
        powerOn();
        //Can we turn on an led?
      }
    }

    // Motor operations
    if (isOn == true) {
      
      if (results.value == LEFT_KEY)      // Move left
        left();
      else if (results.value == RIGHT_KEY) // Move right
        right();
      else if (results.value == FORWARD_KEY) // Move forward
        forward();
      else if (results.value == BACKWARD_KEY) // Move backward
        backward();
      else if (results.value == STOP_KEY) // Halt
	      halt();
      else if (results.value == A) // Honk
        honk();
    }
  }
  delay(100);
  
}

// Turn Off bot
void powerOff() {
  isOn = false;
  digitalWrite(LED, LOW);
  halt();
}
// Turn on bot
void powerOn() {
  isOn = true;
  digitalWrite(LED, HIGH);
  halt(); // can we do a dance
}

void halt() {
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
  delay(1000);
}

void forward() {
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  delay(1000);
}

void left() {
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
  delay(1000);
}

void right() {
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  delay(1000);
}

void backward() {
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
  delay(1000);
}

void honk() {
  NewTone(Buzzer, 1000);
  delay(500);
  noNewTone(Buzzer);
}
