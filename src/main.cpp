#include <Arduino.h>
#include <ibus.h>

void IBUS_eventCallback(int eventCode, int eventParam) {
  switch(eventCode) {
    case IBUS_EVENT_FAILSAFE:
      Serial.printf("Failsafe event: %s\n", eventParam?"true":"false");
      break;
    case IBUS_EVENT_TIMEOUT:
      Serial.printf("Timeout event: %s\n", eventParam?"true":"false");
      break;
    case IBUS_EVENT_VALUE_CHANGED:
      Serial.printf("Channel %d changed: %d\n", eventParam, IBUS.getChannel(eventParam));
      break;
    case IBUS_EVENT_CLICKED:
      Serial.printf("Channel %d clicked\n", eventParam);
      break;
    case IBUS_EVENT_PRESSED:
      Serial.printf("Channel %d pressed\n", eventParam);
      break;
    case IBUS_EVENT_LONG_CLICKED:
      Serial.printf("Channel %d long clicked\n", eventParam);
      break;
    case IBUS_EVENT_LONG_PRESSED:
      Serial.printf("Channel %d long pressed\n", eventParam);
      break;
    case IBUS_EVENT_RELEASED:
      Serial.printf("Channel %d released\n", eventParam);
      break;
    default:
      break;
  }
}

void IBUS_callback(int eventCode, int eventParam) {
  Serial.printf("Channel 1: %d\nChannel 2: %d\nChannel 3: %d\n", IBUS.getChannel(0), IBUS.getChannel(1), IBUS.getChannel(2));
  Serial.printf("Channel 4: %d\nChannel 5: %d\nChannel 6: %d\n", IBUS.getChannel(3), IBUS.getChannel(4), IBUS.getChannel(5));
  Serial.printf("Frame lost: %s\nFailsafe: %s\nTimeout: %s\n\n", IBUS.getLostFrame()?"true":"false", IBUS.getFailsafe()?"true":"false", IBUS.getTimeout()?"true":"false");
}

void setup() {
  Serial.begin(115200);
  while(!Serial);

  Serial1.begin(100000, SERIAL_8E2);
  Serial1.setTimeout(6);
  IBUS.begin(Serial1);

  // steering config
  IBUS.setEnabled(0, true);
  // IBUS.setReverse(0, true);
  // IBUS.setNeutral(0, 32);
  IBUS.setDeadzone(0, 100);

  // throttle config
  IBUS.setEnabled(1, true);
  IBUS.setDeadzone(1, 10);

  // switch F1
  IBUS.setEnabled(3, true);
  IBUS.setDigital(3, true);

  // switch F2
  IBUS.setEnabled(4, true);
  IBUS.setDigital(4, true);

  // switch F3
  IBUS.setEnabled(5, true);
  IBUS.setDigital(5, true);

  // IBUS.attach(IBUS_callback);
  IBUS.attachEvent(IBUS_EVENT_FAILSAFE, IBUS_eventCallback);
  IBUS.attachEvent(IBUS_EVENT_TIMEOUT, IBUS_eventCallback);
  IBUS.attachEvent(IBUS_EVENT_VALUE_CHANGED, IBUS_eventCallback);
  IBUS.attachEvent(IBUS_EVENT_CLICKED, IBUS_eventCallback);
  IBUS.attachEvent(IBUS_EVENT_LONG_CLICKED, IBUS_eventCallback);
  IBUS.attachEvent(IBUS_EVENT_PRESSED, IBUS_eventCallback);
  IBUS.attachEvent(IBUS_EVENT_LONG_PRESSED, IBUS_eventCallback);
  IBUS.attachEvent(IBUS_EVENT_RELEASED, IBUS_eventCallback);

  Serial.println("Ready!");
}

void loop() {
  IBUS.processInput();
}
