#ifndef Node_Base_h
#define Node_Base_h
#include "WLAN_CONF.h"
#include "Constants.h"
#include "Arduino.h"

class Node_Base {
 
public:
 
	void init();
	void init_loopTime();
	void loop();
	void loop_loopTime();
	unsigned long lastLoopPassedMillis();
	
	
private:
	unsigned long _lastLoopPassedMillis;
	unsigned long _lastLoopMillis;
};

void Node_Base::init_loopTime() {
	_lastLoopMillis = 0;
	_lastLoopPassedMillis = 0;
}

void Node_Base::loop_loopTime(){
	unsigned long currentMillis = millis();
	
	// start after first loop
	if (_lastLoopMillis != 0) {
		if (currentMillis < _lastLoopPassedMillis) {
			// looks like uLong overflow
			_lastLoopPassedMillis = (UNSIGNED_LONG_MAX - _lastLoopMillis) + currentMillis;
		} else {
			_lastLoopPassedMillis = _lastLoopMillis - currentMillis;
		}
	}
	_lastLoopMillis = currentMillis;
	
};

unsigned long Node_Base::lastLoopPassedMillis() {
	return _lastLoopPassedMillis;
}

#endif
