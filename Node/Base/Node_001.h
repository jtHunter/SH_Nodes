#include "Node_Base.h"
#include "DigitalInput.h"


class Node: public Node_Base {
  public:
    void init();
    void loop();
  private:
    DigitalInput* taster01;
    bool isFirstLoop;

};

void Node::init() {
  isFirstLoop = true;
  this->init_loopTime();

  // initHardware
  taster01 = new DigitalInput("Taster01", 1001, 1, 10);

}

void Node::loop() {
  Serial.print("Node::loop\n");
  if (isFirstLoop) {
    isFirstLoop = false;
    delay(10);
    Serial.print("Node::loop:firstLoop\n");
    return;
  }
Serial.print("Node::loop:before digitalRead \n");
  // setHardwareValues to Inputs
  bool test = digitalRead(taster01->port());
  Serial.print("Node::loop:digitalRead\n");
  Serial.print(test);
  Serial.print("Node::loop:setInputValueFromHardware\n");
  taster01->setInputValueFromHardware(true);

Serial.print("Node::loop:tick\n");
  //handleTick
  unsigned long lastLoopPassedMillis = this->lastLoopPassedMillis();
  Serial.print("Node::loop:lastLoopPassedMillis\n");
  taster01->tick(lastLoopPassedMillis);
};
