#include Constants.h

class TimeElement {
public:
	TimeElement();
	
	TimeElement(unsigned long endTime);
	
	TimeElement(unsigned long startTime,
				unsigned long endTime,
				TimeElement::Mode mode
				);
	
	
	void tick();
	
	bool isFinished();
	
	int passedRatio();
	
	unsigned long passedTime();
	
	void pause();
	
	void continue();
	
	void reset();
	
	
	
	enum static Mode {
		INCREMENTAL, // time increases on every Tick
		DECREMENTAL  // time decreases on every Tick
	};
	
private:
	unsigned long _startTime;
	unsigned long _endTime;
	unsigned long _passedTime;
	bool _isPaused;
	TimeElement::Mode _mode;
	
	
};
void TimeElement::TimeElement() {
	TimeElement(0ul, UNSIGNED_LONG_MAX, INCREMENTAL);
}

void TimeElement::TimeElement(unsigned long endTime) {
	TimeElement(0ul, endTime, INCREMENTAL);
}

void TimeElement::TimeElement(unsigned long startTime,
							  unsigned long endTime,
							  TimeElement::Mode mode){
	_initTime = initTime;
	_startTime = startTime;
	_mode = mode;
	_passedTime = _initTime;
	_isPaused = false;
}


void TimeElement::tick(unsigned long passedTime){
	if (this->isFinished() || _isPaused){
		return;
	}
	//TODO: gather loopDoration time
	unsigned long loopDurationTime = passedTime;
	
	if (_mode == INCREMENTAL) {
		
		var newPassedTime = _passedTime+=loopDurationTime;
		if (newPassedTime >= _passedTime) {
			// set _passedTime
			_passedTime = newPassedTime;
		} else {
			// looksLike overFlow
			_passedTime = UNSIGNED_LONG_MAX;
		}
	}
	
	if (_mode == DECREMENTAL) {
		var newPassedTime = _passedTime-=loopDurationTime;
		if (newPassedTime <= _passedTime) {
			// set _passedTime
			_passedTime = newPassedTime;
		} else {
			// looksLike overFlow
			_passedTime = UNSIGNED_LONG_MIN;
		}
	}
}

bool TimeElement::isFinished(){
	if (_mode == INCREMENTAL) {
		if (_passedTime >= _endTime) {
			return true;
		}
	}
	
	if (_mode == DECREMENTAL) {
		if (_passedTime <= _endTime) {
			return true;
		}
	}
	
	return false;
}

unsigned long TimeElement::passedTime() {
	unsigned long passed = 0;
	if (_mode == INCREMENTAL) {
		passed = _passedTime - _startTime;
	}
	
	if (_mode == DECREMENTAL) {
		complete = _startTime - _endTime;
		passed = _passedTime - _endTime;
		passed = complete - passed;
	}
	return passed;
}

int TimeElement::passedRatio(){
	unsigned long complete = 100
	unsigned long passed = 0;
	
	if (_mode == INCREMENTAL) {
		complete = _endTime - _startTime;
		passed = _passedTime - _startTime;
	}
	
	if (_mode == DECREMENTAL) {
		complete = _startTime - _endTime;
		passed = _passedTime - _endTime;
		passed = complete - passed;
	}
	
	unsigned long result = (1000ul * passed) / complete;
	if (result > 1000) {
		// someThing went wrong
		return 0;
	} else {
		return (int)result;
	}
}

void TimeElement::reset() {
	_passedTime = _initTime;
	_isPaused = false;
}

void TimeElement::pause() {
	_isPaused=true;
}

void TimeElement::continue() {
	_isPaused=false;
}

