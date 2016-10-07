#ifndef TimeElement_h
#define TimeElement_h

#include "Constants.h"

class TimeElement {

  public:
    TimeElement();
    TimeElement(unsigned long endTime);
    TimeElement(unsigned long startTime,
                unsigned long endTime,
                bool decremental
               );

    void restart();
    void tick(unsigned long passedTime);

    bool isFinished();

    int passedRatio();

    unsigned long passedTime();

    void pause();

    void unpause();

    unsigned long sTime();

  protected:
    unsigned long _startTime;
    unsigned long _endTime;
    unsigned long _passedTime;
    bool _isPaused;
    bool _decremental;


};
unsigned long TimeElement::sTime() {
  Serial.println("TimeElement::sTime\n");
  //Serial.println(_isPaused);
  Serial.println("---");
  //Serial.println(_decremental);
  Serial.println("---");
  //Serial.println(_endTime);
  Serial.println("---");
  //Serial.println(_startTime);
  Serial.println("---");
  return 0;//_passedTime;
}
void TimeElement::restart() {
  //TODO: print all values before setting;
  Serial.println("TimeElement::reset");
  Serial.println("TimeElement::restart");
  Serial.println(this->sTime());
  Serial.print("TimeElement::reset 0x\n");
  //Serial.println(_passedTime);
  Serial.print("TimeElement::reset 00\n");
  //_passedTime = _startTime;
  Serial.print("TimeElement::reset 01\n");
  //_isPaused = false;
  Serial.print("TimeElement::reset end\n");
};

TimeElement::TimeElement() {
  TimeElement(0ul, UNSIGNED_LONG_MAX, false);
}

TimeElement::TimeElement(unsigned long endTime) {
  TimeElement(0ul, endTime, false);
}

TimeElement::TimeElement(unsigned long startTime,
                         unsigned long endTime,
                         bool decremental) {

  Serial.print("TimeElement::TimeElement\n");
  Serial.println(startTime);
  Serial.println(endTime);
  Serial.println(decremental);
  _startTime = startTime;
  _passedTime = _startTime;
  _endTime = endTime;
  _isPaused = false;
  _decremental = decremental;
  Serial.println("---");
  Serial.println(_startTime);
  Serial.println(_endTime);
  Serial.println(_decremental);
  Serial.println("---");
}


void TimeElement::tick(unsigned long passedTime) {
  if (this->isFinished() || _isPaused) {
    return;
  }
  //TODO: gather loopDoration time
  unsigned long loopDurationTime = passedTime;

  if (!_decremental) {

    unsigned long newPassedTime = _passedTime += loopDurationTime;
    if (newPassedTime >= _passedTime) {
      // set _passedTime
      _passedTime = newPassedTime;
    } else {
      // looksLike overFlow
      _passedTime = UNSIGNED_LONG_MAX;
    }
  }

  if (!_decremental) {
    unsigned long newPassedTime = _passedTime -= loopDurationTime;
    if (newPassedTime <= _passedTime) {
      // set _passedTime
      _passedTime = newPassedTime;
    } else {
      // looksLike overFlow
      _passedTime = UNSIGNED_LONG_MIN;
    }
  }
}

bool TimeElement::isFinished() {
  return true;
  if (!_decremental) {
    if (_passedTime >= _endTime) {
      return true;
    }
  }

  if (_decremental) {
    if (_passedTime <= _endTime) {
      return true;
    }
  }

  return false;
}

unsigned long TimeElement::passedTime() {
  unsigned long passed = 0;
  if (!_decremental) {
    passed = _passedTime - _startTime;
  }

  if (_decremental) {
    unsigned long complete = _startTime - _endTime;
    passed = _passedTime - _endTime;
    passed = complete - passed;
  }
  return passed;
}

int TimeElement::passedRatio() {
  unsigned long complete = 100;
  unsigned long passed = 0;

  if (!_decremental) {
    complete = _endTime - _startTime;
    passed = _passedTime - _startTime;
  }

  if (_decremental) {
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



void TimeElement::pause() {
  _isPaused = true;
}

void TimeElement::unpause() {
  _isPaused = false;
}

#endif
