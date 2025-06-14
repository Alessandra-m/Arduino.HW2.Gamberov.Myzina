#include <ros.h>
#include <LiquidCrystal.h>
#include <std_msgs/ColorRGBA.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
ros::NodeHandle nh;
int x = 0;
int y = 0;
void commandCallback(const std_msgs::ColorRGBA& msg) {
  if (msg.r == 1.0f) {
    x += 1;
  } else if (msg.g == 1.0f) {
    y -= 1;
  } else if (msg.b == 1.0f) {
    x -= 1;
  } else if (msg.a == 1.0f) {
    y += 1;
  }
  if (x < 0) x = 15;
  if (x > 15) x = 0;
  if (y < 0) y = 1;
  if (y > 1) y = 0;
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(x, y);
  lcd.print('.');
}

ros::Subscriber<std_msgs::ColorRGBA> sub("computer/lcd/cmd", &commandCallback);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  nh.initNode();
  nh.subscribe(sub);
  lcd.setCursor(0, 0);
  lcd.print('.');

}
void loop() {
  nh.spinOnce();     
  delay(1);          
}