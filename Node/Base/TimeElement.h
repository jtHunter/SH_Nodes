#ifndef TimeElement_h
#define TimeElement_h

#include "Constants.h"

class TimeElement {

  private:
    unsigned long m_endTime;
    unsigned long m_passedTime;

  public:
    TimeElement(unsigned long endTime) {
      if (endTime == 0) {
        m_endTime = 3000000;//UNSIGNED_LONG_MAX;
      } else {
        m_endTime = endTime;
      }
      m_passedTime = 0;

    };

    String toString() {
      String retu = "TimeElement | passedTime = " + m_passedTime;
      retu += " | passedRatio : " + this->passedRatio();
      retu += " | endTime: " + m_endTime;
      return retu;
    };


    void restart() {
      Serial.println("TimeElement::restart");
      m_passedTime = 0;
    };

    void tick(unsigned long passedTime) {
      Serial.println("TE: tick");
      if (this->isFinished()) {
        Serial.println("TE: isFinished ");
        return;
      } else {
        Serial.print("TE: old passedTime");
        Serial.println(m_passedTime);
        unsigned long newPassedTime = m_passedTime += passedTime;
        if (newPassedTime >= m_passedTime) {
          // set _passedTime
          m_passedTime = newPassedTime;
          Serial.print("TE: new passedTime  ");
          Serial.println(m_passedTime);
        } else {
          // looksLike overFlow
          m_passedTime = UNSIGNED_LONG_MAX;
        }
      }
    };

    bool isFinished() {
      if (m_passedTime >= m_endTime) {
        return true;
      }
      return false;
    };

    int passedRatio() {
      unsigned long result = (1000ul * m_passedTime) / m_endTime;
      if (result > 1000) {
        // someThing went wrong
        return 0;
      } else {
        return (int)result;
      }
    };

    unsigned long passedTime() {
      m_passedTime;
    };



};

/*
  void TimeElement::restart() {
  m_passedTime
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
*/
#endif
