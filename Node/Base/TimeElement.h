#ifndef TimeElement_h
#define TimeElement_h

#include "Constants.h"

class TimeElement {

  private:
    unsigned long m_endTime;
    unsigned long m_passedTime;

  public:
	//#########################################
 
    TimeElement(unsigned long endTime) {
      if (endTime == 0) {
        m_endTime = UNSIGNED_LONG_MAX;
      } else {
        m_endTime = endTime;
      }
      m_passedTime = 0;
    };
    
    //#########################################
    
    String toString() {
      String retu = "TimeElement | passedRatio: "+ String(passedRatio());
      retu+= " | passedTime: " + String(m_passedTime);
      retu+= " | endTime: " + String(m_endTime);
      return retu;
    };

    //#########################################
    
    void restart() {
      m_passedTime = 0;
    };
    
    //#########################################
    
    void tick(unsigned long passedTime) {
      if (this->isFinished()) {
        return;
      } else {
        unsigned long newPassedTime = m_passedTime += passedTime;
        if (newPassedTime >= m_passedTime) {
          // set _passedTime
          m_passedTime = newPassedTime;
          if (m_passedTime > m_endTime) {
            m_passedTime = m_endTime;
          }
        } else {
          // looksLike overFlow
          m_passedTime = UNSIGNED_LONG_MAX;
        }
      }
    };
    
    //#########################################
    
    bool isFinished() {
      if (m_passedTime >= m_endTime) {
        return true;
      }
      return false;
    };
    
    //#########################################
    
    int passedRatio() {
      //TODO check for passed Time > endTimer
      unsigned long result = (1000 * m_passedTime) / m_endTime;
      if (result > 1000) {
        // someThing went wrong
        return 0;
      } else {
        return (int)result;
      }
    };
    
    //#########################################
    
    unsigned long passedTime() {
      m_passedTime;
    };

     //#########################################
};
#endif
