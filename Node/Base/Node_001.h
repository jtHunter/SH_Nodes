#ifndef Node_h
#define Node_h
#include "Node_Base.h"
#include "DigitalInput.h"
#include "DigitalOutput.h"

//
class Node: public Node_Base {
public:
	void loop();
  Node(String name);
  String name();
  String toString();
private:
	//DigitalInput* taster01;
	bool isFirstLoop;
 String m_name;

 DigitalOutput *led_01;
	
};

Node::Node(String name) {
    // initHardware
    Node_Base();
    m_name = name;
  //taster01 = new DigitalInput("Taster01", 1001, 1, 10);
  //Serial.println(taster01->toString());
    isFirstLoop = true;
  init_loopTime();
  Serial.println(this->toString());

  led_01 = new DigitalOutput("MyFirstLed");
}

String Node::name() {
  return m_name;
}

String Node::toString() {
  return "Node " + m_name + " | " + this->name() + " |";
}


void Node::loop() {
	Serial.print("Node::loop\n");
  Serial.println(led_01->toString());




 
 Serial.print(m_name);
	if (isFirstLoop) {
		isFirstLoop = false;
		delay(10);
		Serial.print("Node::loop:firstLoop\n");
		return;
	}
	Serial.print("Node::loop:before digitalRead \n");
	// setHardwareValues to Inputs
	/*Serial.print("Name: ");
	Serial.println(taster01->name());
	Serial.print("Port: ");
	Serial.println(taster01->port());
	
	
	bool test = digitalRead(taster01->port());
	Serial.print("Node::loop:digitalRead\n");
	Serial.print(test);
	Serial.print("Node::loop:setInputValueFromHardware\n");
	taster01->setInputValueFromHardware(true);
	
	Serial.print("Node::loop:tick\n");
	//handleTick
	unsigned long lastLoopPassedMillis = this->lastLoopPassedMillis();
	Serial.print("Node::loop:lastLoopPassedMillis\n");
	taster01->tick(lastLoopPassedMillis);*/
 
};

#endif
