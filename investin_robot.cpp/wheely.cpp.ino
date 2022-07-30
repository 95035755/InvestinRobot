#define SENSOR_TRIGGER_PIN 13
#define SENSOR_ECHO_PIN 12

#define LEFT_FWD 4
#define LEFT_REV 5
#define RIGHT_FWD 7
#define RIGHT_REV 6

class Servo {
private:
  int fwd_pin, rev_pin;
public:
  Servo(int fwd_pin, int rev_pin) : fwd_pin(fwd_pin), rev_pin(rev_pin) {}

  void Forward() {
    digitalWrite(this->fwd_pin, HIGH);
    digitalWrite(this->rev_pin, LOW);
  }

  void Stop() {
    digitalWrite(this->fwd_pin, LOW);
    digitalWrite(this->rev_pin, LOW);
  }
};

Servo *left, *right;

int get_distance() {
  digitalWrite(SENSOR_TRIGGER_PIN, LOW); // reset pulse
  delayMicroseconds(2);
  digitalWrite(SENSOR_TRIGGER_PIN, HIGH); // send pulse for 10 micro seconds
  delayMicroseconds(10);
  int duration = pulseIn(SENSOR_ECHO_PIN, HIGH); // wait for echo
  int distance = duration / 58.2; // convert into distance
  return distance;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(SENSOR_TRIGGER_PIN, OUTPUT);
  pinMode(SENSOR_ECHO_PIN, INPUT);

  pinMode(LEFT_FWD, OUTPUT);
  pinMode(LEFT_REV, OUTPUT);
  pinMode(RIGHT_FWD, OUTPUT);
  pinMode(RIGHT_REV, OUTPUT);

  left = new Servo(LEFT_FWD, LEFT_REV);
  right = new Servo(RIGHT_FWD, RIGHT_REV);
}

void loop() {
  // put your main code here, to run repeatedly:
  left->Reverse();
  right->Reverse();
  delay(300);
  left->Stop();
  count += 1;
}

  while (true) {
    
  }

  delay(10);
}
