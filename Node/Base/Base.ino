//#include "WLAN_CONF.h"
//#include "Node_Base.h"
#include "Node_001.h"



Node* node;
//WLAN_CONF conf;
void setup() {
  // put your setup code here, to run once:
  //conf.foo(ssid);
  //conf.SOMETHING;
  node = new Node();
  node->init();

}

void loop() {
  node->loop();

}
