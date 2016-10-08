#ifndef DigitalOutput_h
#define DigitalOutput_h
#include "TimeElement.h"
#include "Constants.h"

class DigitalOutput {
public:
	
	DigitalOutput(String name) {
		m_name = name;
	};
	
	String getName() {
		return m_name;
	}
	
	String toString() {
		return "DigitalOutput | " + m_name + " | " + this->getName() + " |";
	}
	
private:
	String m_name;
};


#endif
