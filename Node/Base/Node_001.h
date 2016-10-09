#ifndef Node_h
#define Node_h
#include "Node_Base.h"
#include "DigitalInput.h"
#include "DigitalOutput.h"

//
class Node: public Node_Base {
  public:
    Node(String name);
    
    void loop();

    
    String name();
    String toString();
  private:
    //
    bool isFirstLoop;
    String m_name;

    DigitalOutput *led_01;
    DigitalInput* taster_01;
};

Node::Node(String name) {
  // initHardware
  Node_Base();
  m_name = name;
  //taster01 = new DigitalInput("Taster01", 1001, 1, 10);
  //Serial.println(taster01->toString());
  isFirstLoop = true;
  init_loopTime();
 

  // HardwareInit
  led_01 = new DigitalOutput("MyFirstLed");
  //taster_01 = new DigitalInput("MyFirstTaster", 1001, 1, 10, false);

   Serial.println(this->toString());
}

String Node::name() {
  return m_name;
}

String Node::toString() {
  String ret = "Node '" + m_name + "'\n ";
  ret += "\t- " + led_01->toString() + "'\n ";
  ret += "\t- " + taster_01->toString();
  return ret;
}


void Node::loop() {
  Serial.print("Node::loop\n");
  Serial.println(this->toString());
 
  /*
  
  if (isFirstLoop) {
    isFirstLoop = false;
    delay(10);
    Serial.print("Node::loop:firstLoop\n");
    return;
  }
  */
  // setHardwareValues to Inputs
    bool test = digitalRead(taster_01->port());
    Serial.print("Node::loop:digitalRead\n");
    Serial.print(test);
    Serial.print("Node::loop:setInputValueFromHardware\n");
    taster_01->setInputValueFromHardware(true);

    Serial.print("Node::loop:tick\n");
    
    
    //handleTick
    unsigned long lastLoopPassedMillis = this->lastLoopPassedMillis();
    Serial.print("Node::loop:lastLoopPassedMillis\n");
    taster_01->tick(lastLoopPassedMillis);

};

#endif
