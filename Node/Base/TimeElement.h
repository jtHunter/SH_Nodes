#include Constants.h

class TimeElement {
    public:
        TimeElement(unsigned long initTime,
                    unsigned long doneTime,
                    TimeElement::Mode mode
                   );
        void tick();
    
    bool isFinished();
	
    
    
        
    
	
    enum static Mode {
        INCREMENTAL, // time increases on every Tick
        DECREMENTAL  // time decreases on every Tick
    };
    
    private:
        unsigned long _initTime;
        unsigned long _doneTime;
        unsigned long _passedTime;
        TimeElement::Mode _mode;
        
            
};




void TimeElement::TimeElement(unsigned long initTime,
                              unsigned long doneTime,
                              TimeElement::Mode mode){
    _initTime = initTime;
	_doneTime = doneTime;
	_mode = mode;
	_passedTime = _initTime;
}


void TimeElement::tick(){
	//TODO: gather loopDoration time
    unsigned long loopDurationTime = 10;
	
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