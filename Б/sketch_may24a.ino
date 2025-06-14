#include <std_msgs/ColorRGBA.h>

ros::NodeHandle nh;

#define RED_PIN   13
#define GREEN_PIN 12
#define BLUE_PIN  8

void colorCallback(const std_msgs::ColorRGBA& msg) {
  if (msg.r == 1.0f) {
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);
  } else if (msg.g == 1.0f) {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(BLUE_PIN, LOW);
  } else if (msg.b == 1.0f) {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, HIGH);
  } else {
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);
  }
}

ros::Subscriber<std_msgs::ColorRGBA> sub("computer/traffic_light/cmd", &colorCallback);

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);

  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  nh.spinOnce();    
  delay(1);          
}