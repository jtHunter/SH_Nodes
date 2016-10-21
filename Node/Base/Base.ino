//#include "WLAN_CONF.h"
//#include "Node_Base.h"
#include "Node_001.h"
#include "TimeElement.h"


bool stateLED;
Node *node;
TimeElement* timeTest;
//WLAN_CONF conf;
void setup() {
  Serial.begin(115200);
  Serial.print("SETUP\n");
  pinMode(2, OUTPUT);
  pinMode(10, INPUT);
  // put your setup code here, to run once:
  //conf.foo(ssid);
  //conf.SOMETHING;
  //node = new Node("MyNode");
  stateLED = false;

  timeTest = new TimeElement(20);
  Serial.print("SETUP END\n");
}

void loop() {
  digitalWrite(2,stateLED);
  stateLED = !stateLED;
   //Serial.print("LOOP\n");
  //node->loop();
  //Serial.println("NodeName from mainLoop: ");
  //Serial.println(node->toString());
  timeTest->tick(1);
  
  
Serial.println(timeTest->toString());
if (timeTest->isFinished()) {
    timeTest->restart();
  }
  delay(2000);

}
