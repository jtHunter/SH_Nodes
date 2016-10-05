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
  if (isFirstLoop) {
    isFirstLoop = false;
    delay(10);
  }

  // setHardwareValues to Inputs
  taster01->setInputValueFromHardware(digitalRead(taster01->port()));

  //handleTick
  unsigned long lastLoopPassedMillis = this->lastLoopPassedMillis();
  taster01->tick(lastLoopPassedMillis);
};
