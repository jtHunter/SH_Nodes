//#include "Node_Base.h"

class DigitalInput {
    public:
        DigitalInput(int id, 
                     int parentId, 
                     int portNoOnParentHardware, 
                     bool reverseValue,
                     int debounceTimeMillis);
        void tick();
        void setInputValueFromHardware(bool value);
        bool currentValue();
    private:
        int id;
        int parentId;
        int portNumber;
        bool reverseOutput;
        bool currentHardwareValue;
};




void DigitalInput::DigitalInput(int id, 
                     int parentId, 
                     int portNoOnParentHardware, 
                     bool reverseValue){
    
}

void DigitalInput::tick()
void setInputValueFromHardware(bool value) {
    
}
