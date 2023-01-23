#include <PCF8574X3.h>

PCF8574X3 expander;
bool whiteLed = false;
int iterator = 0;

void setup() {
  Serial.begin(9600);

  expander.init(8, true, false, false);

  expander.pinModeExpander(3, OUTPUT_MODE);
  expander.pinModeExpander(4, OUTPUT_MODE);
  expander.pinModeExpander(21, INPUT_MODE);
  expander.pullDownExpander(21);
  expander.pinModeExpander(6, OUTPUT_MODE);
  expander.pinModeExpander(12, OUTPUT_MODE);
}

void loop()
{

  byte readPin = expander.digitalReadExpander(21);
  Serial.println(readPin);
  if (readPin == LOW)
  {
    whiteLed = true;
    iterator = 0;
    delay(150);
  }
  else
  {
    if (whiteLed)
    {
      expander.digitalWriteExpander(4, HIGH_STATE);
    }
    else
    {
      expander.digitalWriteExpander(4, LOW_STATE);
    }

    iterator++;
    if (iterator > 5)
    {
      whiteLed = false;
    }
    
    expander.digitalWriteExpander(6, LOW_STATE);
    delay(300);
    expander.digitalWriteExpander(3, HIGH_STATE);
    delay(300);
    expander.digitalWriteExpander(12, HIGH_STATE);
    delay(300);

    expander.digitalWriteExpander(6, HIGH_STATE);
    delay(300);
    expander.digitalWriteExpander(3, LOW_STATE);
    delay(300);
    expander.digitalWriteExpander(12, LOW_STATE);
    delay(330);
  }
}
