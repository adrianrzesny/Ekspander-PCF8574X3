#include <PCF8574.h>
#include <Wire.h>

#ifndef PCF8574X3_H
#define PCF8574X3_H

enum MODE {INPUT_MODE, OUTPUT_MODE};
enum STATE {LOW_STATE, HIGH_STATE};

class PCF8574X3
{
    public:
        PCF8574X3();
        virtual ~PCF8574X3();

        bool _showLogPinModeExpander = false;
        bool _showLogDigitalWriteExpander = false;
        bool _showLogDigitalReadExpander = false;

        void init(int pin_digital_input, bool showLogPinModeExpander, bool showLogDigitalWriteExpander, bool showLogDigitalReadExpander);
        void init(int pin_digital_input);
        void pinModeExpander(int pin, MODE mode);
        void digitalWriteExpander(int pin, STATE state);
        void pullDownExpander(int pin);
        void pullUpExpander(int pin);
        byte digitalReadExpander(int pin);

        PCF8574 expander_x3_1;
        PCF8574 expander_x3_2;
        PCF8574 expander_x3_3;
        
    protected:

    private:
        int getPin(int pin);
        void setDevice(int pin);
        static void onInterrupt();
        
        PCF8574* expander = nullptr; 
};

#endif // PCF8574X3_H
