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
      m_passedTime = 0ul;
    };
    
    //#########################################
    String toString() {
      //TODO: this method seemes to be malicious; result of m_passedTime in this is pretty strange
      Serial.print("TE:toString | m_passedTime = ");
      Serial.println(m_passedTime);
      
      String retu = "TimeElement | passedTime = " + m_passedTime;
      retu += " | passedRatio : " + this->passedRatio();
      retu += " | endTime: " + m_endTime;
      return retu;
    };

    
    //#########################################
    void restart() {
      Serial.println("TimeElement::restart");
      m_passedTime = 0;
    };

    
    //#########################################
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
    
    //#########################################
    bool isFinished() {
      if (m_passedTime >= m_endTime) {
        return true;
      }
      return false;
    };
    
    //#########################################
    int passedRatio() {
      unsigned long result = (1000ul * m_passedTime) / m_endTime;
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

};
#endif
