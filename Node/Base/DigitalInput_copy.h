#ifndef DigitalInput_h
#define DigitalInput_h
#include "TimeElement.h"
#include "Constants.h"

class DigitalInput {
  public:

    DigitalInput(String name,
                 int id,
                 int parentId,
                 int port);

    DigitalInput(String name,
                 int id,
                 int parentId,
                 int port,
                 bool reverse,
                 unsigned long debounceTimeMillis);
    String toString();
    void tick(unsigned long passedTime);
    void setInputValueFromHardware(bool value);

    bool currentValue();
    unsigned long currentValueDuration();
    bool lastValue();
    unsigned long lastValueDuration();
    int port();
	String name();

  private:
    String _name;
    int _id;
    int _parentId;
    int _port;
    bool _reverse;


    bool _currentHardwareValue;
    bool _lastHardwareValue;
    bool _currentValue;
    bool _lastValue;
    unsigned long _lastValueDuration;

    TimeElement* _debounceTimer;
    TimeElement* _currentValueTimer;
};

DigitalInput::DigitalInput(String name,
                           int id,
                           int parentId,
                           int port) {
        DigitalInput(name, id, parentId, port, false, DEBOUNCE_DI_STD_MILLIS);
}


DigitalInput::DigitalInput(String name,
                           int id,
                           int parentId,
                           int port,
                           bool reverse,
                           unsigned long debounceTimeMillis) {

String log = "DigitalInput: name = " + name + " | id = " + id + " | parentId = " + parentId + " | port = " + port + " | reverse = " + reverse + " | debounceTimeMillis = " + debounceTimeMillis ;
Serial.println(log);
                            
  // store parameters
  _name = name;
  _id = id;
  _parentId = parentId;
  _port = port;
  _reverse = reverse;

  // initialize Timers
  _debounceTimer = new TimeElement(debounceTimeMillis);
  _currentValueTimer = new TimeElement();
  
  Serial.println(this->toString());
}

String DigitalInput::toString() {
  String ret = "DigitalInput: name = " + _name + " | id = " + _id + " | parentId = " + _parentId + " | port = " + _port + " | reverse = " + _reverse ;
  return ret;
}

void DigitalInput::tick(unsigned long passedTime) {
  _debounceTimer->tick(passedTime);
  _debounceTimer->restart();
}

void DigitalInput::setInputValueFromHardware(bool value) {
  Serial.print("DigitalInput::setInputValueFromHardware INIT\n");
  _lastHardwareValue = _currentHardwareValue;
  _currentHardwareValue = value;
  Serial.print("DigitalInput::setInputValueFromHardware 01 \n");
  if (_currentHardwareValue != _currentValue) {
    // input from Hardware is different to currentValue
    if (_currentHardwareValue != _lastHardwareValue) {
      // reset debounceTimer
      Serial.print("DigitalInput::setInputValueFromHardware 02 \n");
      _debounceTimer->restart();
      Serial.print("DigitalInput::setInputValueFromHardware 03 \n");
    } else {
      Serial.print("DigitalInput::setInputValueFromHardware 04 \n");
      // seemes to be stable signal so check if debounceTimer is finished
      if (_debounceTimer->isFinished()) {
        //timer finished so pass value to "real" value store old and resert valueTimer

        _lastValue = _currentValue;
        Serial.print("DigitalInput::setInputValueFromHardware 05 \n");
        _lastValueDuration = _currentValueTimer->passedTime();
        Serial.print("DigitalInput::setInputValueFromHardware 06 \n");
        _currentValue = _currentHardwareValue;
        Serial.print("DigitalInput::setInputValueFromHardware 07 \n");
        _currentValueTimer->restart();
        Serial.print(_name);
        Serial.print(": ");
        Serial.println(_currentValue);
      } else {
        // nothing to do here; still wait for next loop's setting hardwareValue
      }
    }
  } else {
    // input equals hardware so no debounce needed
    //_debounceTimer->pause();
  }
};

//***************************
// Getter / Setter
//***************************


bool DigitalInput::currentValue() {
  return _currentValue;
};

unsigned long DigitalInput::currentValueDuration() {
  _currentValueTimer->passedTime();
}

bool DigitalInput::lastValue() {
  return _lastValue;
};

unsigned long DigitalInput::lastValueDuration() {
  return _lastValueDuration;
};

int DigitalInput::port() {
  return _port;
}

String DigitalInput::name() {
	return _name;
}

#endif
