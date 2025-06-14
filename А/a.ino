#include <std_msgs/Bool.h>

ros::NodeHandle nh;

std_msgs::Bool _msg;
ros::Publisher chatter("arduino/led", &_msg);

// boolean msg = false;
int led_pin = 8;
int button_pin = 11;
boolean lastBt = false;
boolean currentBt = false;
boolean ledOn = LOW;

boolean debvence(boolean last) {
  boolean current = digitalRead(button_pin);
  if (last != current) {
    delay(5);                
    current = digitalRead(button_pin);
    return current;
  }
  return current;
}

void setup() {
  pinMode(led_pin, OUTPUT);
  pinMode(button_pin, INPUT);

  nh.initNode();
  nh.advertise(chatter);
  _msg.data = false;
}

void loop() {
  currentBt = debvence(lastBt);
  if (lastBt == HIGH && currentBt == LOW) {
    ledOn = !ledOn;

    if (ledOn == HIGH) {
      // Serial.println("LED: on");
      // msg = true;
      _msg.data = true;
    } else {
      // Serial.println("LED: off");
      // msg = false;
      _msg.data = false;
    }
  }

  digitalWrite(led_pin, ledOn);
  lastBt = currentBt;

  chatter.publish(&_msg);
  nh.spinOnce();
  }