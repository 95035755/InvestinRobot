#include <Servo.h>
#include <NewPing.h>

#define SENSOR_TRIGGER_PIN A1
#define SENSOR_ECHO_PIN A2
#define MAX_DISTANCE 250

#define TABLE_TRIGGER_PIN A3
#define TABLE_ECHO_PIN A4

#define SERVO_PIN 10

#define RIGHT_FWD 4
#define RIGHT_REV 5
#define LEFT_FWD 7
#define LEFT_REV 6

class Motor {
private:
  int fwd_pin, rev_pin;
public:
  Motor(int fwd_pin, int rev_pin) : fwd_pin(fwd_pin), rev_pin(rev_pin) {}

  void Forward() {
    digitalWrite(this->fwd_pin, HIGH);
    digitalWrite(this->rev_pin, LOW);
  }

  void Reverse() {
    digitalWrite(this->fwd_pin, LOW);
    digitalWrite(this->rev_pin, HIGH);
  }

  void Stop() {
    digitalWrite(this->fwd_pin, LOW);
    digitalWrite(this->rev_pin, LOW);
  }
};

Motor *left, *right;
Servo *servo;
NewPing *sensor;

void setup() {
  // put your setup code here, to run once:
  pinMode(LEFT_FWD, OUTPUT);
  pinMode(LEFT_REV, OUTPUT);
  pinMode(RIGHT_FWD, OUTPUT);
  pinMode(RIGHT_REV, OUTPUT);

  left = new Motor(LEFT_FWD, LEFT_REV);
  right = new Motor(RIGHT_FWD, RIGHT_REV);

  servo = new Servo;
  servo->attach(SERVO_PIN);
  servo->write(90);
  
  sensor = new NewPing(SENSOR_TRIGGER_PIN, SENSOR_ECHO_PIN, MAX_DISTANCE);
  tableSensor = new NewPing(TABLE_TRIGGER_PIN, TABLE_ECHO_PIN, MAX_DISTANCE);
}

int get_distance() {
  delay(100);
  int dist = sensor->ping_cm();
  return dist == 0 ? MAX_DISTANCE : dist;
}

int get_table_distance() {
  delay(100);
  int dist = tableSensor->ping_cm();
  return dist == 0 ? MAX_DISTANCE : dist;
}

void loop() {
  // put your main code here, to run repeatedly:
  int distance = get_table_distance();
  if (distance < 10) {
    left->Forward();
    right->Forward();
  } else {
    left->Stop();
    right->Stop();
    delay(100);
    right->Reverse();
    delay(400);
    left->Stop();
    delay(300);
    
    delay(500);
  }
  delay(10);
}
