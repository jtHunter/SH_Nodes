#ifndef DigitalInput_h
#define DigitalInput_h
#include "TimeElement.h"
#include "Constants.h"

class DigitalInput {
  private:
    String m_name;
    int m_id;
    int m_parentId;
    int m_port;
    bool m_reverse;

    bool m_currentHardwareValue;
    bool m_lastHardwareValue;
    bool m_currentValue;
    bool m_lastValue;
    unsigned long m_lastValueDuration;

    TimeElement* m_debounceTimer;
    TimeElement* m_currentValueTimer;

  public:
    DigitalInput(String name,
                 int id,
                 int parentId,
                 int port,
                 bool reverse) {
      // store parameters
      m_name = name;
      m_id = id;
      m_parentId = parentId;
      m_port = port;
      m_reverse = reverse;

      m_currentHardwareValue = false;
      m_lastHardwareValue = false;
      m_currentValue = false;
      m_lastValue = false;
      m_lastValueDuration = 0;

      //TODO: inititalize timers here
      Serial.println(this->toString());
    };


    String toString() {
      String ret = "DigitalInput | " + m_name;
      return ret;
    };

    void tick(unsigned long passedTime) {
      //TODO
      m_debounceTimer->tick(passedTime);
    }

    void setInputValueFromHardware(bool value) {
      m_lastHardwareValue = m_currentHardwareValue;
      m_currentHardwareValue = value;
      if (m_currentHardwareValue != m_currentValue) {
        // input from Hardware is different to currentValue

        if (m_currentHardwareValue != m_lastHardwareValue) {
          // reset debounceTimer
          //TODO
          m_debounceTimer->restart();
        } else {
          // seemes to be stable signal the last loops so check if debounceTimer is finished
          if (true/*_debounceTimer->isFinished()*/) {
            //timer finished so pass value to "real" value store old and resert valueTimer

            m_lastValue = m_currentValue;
            //TODO
            m_lastValueDuration = m_currentValueTimer->passedTime();
            m_currentValue = m_currentHardwareValue;
            //TODO
            m_currentValueTimer->restart();
          } else {
            // nothing to do here; still wait for next loop's setting hardwareValue
          }
        }
      } else {
        // input equals hardware so every thing is fine: no debounce needed

        //TODO:check if needed
        //_debounceTimer->pause();
      }
    }




    //***************************
    // Getter / Setter
    //***************************


    bool currentValue() {
      return m_currentValue;
    };

    unsigned long currentValueDuration() {
      return m_currentValueTimer->passedTime();
    }

    bool lastValue() {
      return m_lastValue;
    };

    unsigned long lastValueDuration() {
      return m_lastValueDuration;
    };

    int port() {
      return m_port;
    }
    /*
        //getter - setter
        int getPort() {
          return m_port;
        };

        String getName() {
          return m_name;
        };
    */

    /*

      void tick(unsigned long passedTime);
      void setInputValueFromHardware(bool value);

      bool currentValue();
      unsigned long currentValueDuration();
      bool lastValue();
      unsigned long lastValueDuration();
    */



    /*


      };
      /*
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





      String DigitalInput::name() {
      return _name;
      }
    */
};
#endif
