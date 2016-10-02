#include "TimeElement.h"

class DigitalInput {
public:
	DigitalInput(int id,
				 int parentId,
				 int port,
				 bool reverse,
				 unsigned long debounceTimeMillis);
	
	void tick(unsigned long passedTime);
	void setInputValueFromHardware(bool value);
	
/*ToDo*/	bool currentValue();
/*ToDo*/	bool currentValueTime();
/*ToDo*/	bool lastValue();
/*ToDo*/	bool lastValueTime();
	
private:
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




void DigitalInput::DigitalInput(String name,
								int id,
								int parentId,
								int port,
								bool reverse,
								unsigned long debounceTimeMillis){
	// store parameters
	_name = name
	_id = id;
	_parentId = parentId;
	_port = port;
	_reverse = reverse;
	
	// initialize Timers
	_debounceTimer = new TimeElement(debounceTimeMillis);
	_currentValueTimer = new TimeElement();
}

void DigitalInput::tick(unsigned long passedTime) {
	_debounceTimer->tick(passedTime);
}

void DigitalInput::setInputValueFromHardware(bool value) {
	_lastHardwareValue = _currentHardwareValue;
	_currentHardwareValue = value;
	
	
	
	if (_currentHardwareValue != _currentValue) {
		// input from Hardware is different to currentValue
		if (_currentHardwareValue != _lastHardwareValue) {
			// reset debounceTimer
			_debounceTimer.reset();
		} else {
			// seemes to be stable signal so check if debounceTimer is finished
			if(_debounceTimer->isFinished()) {
				//timer finished so pass value to "real" value store old and resert valueTimer
				
				_lastValue = _currentValue;
				_lastValueDuration = _currentValueTimer->passedTime();
				_currentValue = _currentHardwareValue;
				_currentValueTimer.reset();
			} else {
				// nothing to do here; still wait for next loop's setting hardwareValue
			}
		}
	} else {
		// input equals hardware so no debounce needed
		_debounceTimer.pause();
	}
}
