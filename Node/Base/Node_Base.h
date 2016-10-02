#include "WLAN_CONF.h"

class Node_Base {
 
 public:
 
 void init();

 void startNodeBeforeWSInit();
 
 void startWS();

 void loop_All();
 void loop_WS();
 
 };
