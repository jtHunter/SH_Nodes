//#include "WLAN_CONF.h"
//#include "Node_Base.h"
#include "Node_001.h"


bool stateLED;
Node *node;
//WLAN_CONF conf;
void setup() {
  Serial.begin(115200);
  Serial.print("SETUP\n");
  pinMode(2, OUTPUT);
  pinMode(10, INPUT);
  // put your setup code here, to run once:
  //conf.foo(ssid);
  //conf.SOMETHING;
  node = new Node("MyNode");
  stateLED = false;
  
}

void loop() {
  digitalWrite(2,stateLED);
  stateLED = !stateLED;
   Serial.print("LOOP\n");
  node->loop();
  Serial.print("NodeName from mainLoop: ");
  Serial.println(node->toString());
  delay(3000);

}
