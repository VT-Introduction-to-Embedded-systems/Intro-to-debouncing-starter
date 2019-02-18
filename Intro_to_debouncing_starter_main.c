// This application uses button 1 and LED 1
// The operation is such that if you press the left button, as long as you keep the button pressed,
// the LED is on. As soon as you release the button, LED is off and stays off until the button is pressed again.
// This program uses Hardware Abstraction Level (HAL) functions that hide away device-specific details.

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

// According to the schematics on page 37 of the Launchpad user guide,
// When a button is pressed, it is grounded (logic 0)
#define PRESSED 0
#define RELEASED 1
#define TENTH_OF_SEC_COUNT 300000

// A new type that enumerates the debouncing states of a button
// These will be used for debouncing FSM
typedef enum {Stable_P, Tran_PtoR} debounce_state_t;


// This function initializes all the peripherals
void initialize();

void TurnOn_Launchpad_LED1();
void TurnOff_Launchpad_LED1();
void Toggle_Launchpad_LED1();
char SwitchStatus_BoosterPack_S2();


int main(void)
{

    initialize();

    char cur_status, prev_status;
    prev_status = RELEASED;

    debounce_state_t debounce_state;

    while (1) {
/*
       // The first input of the FSM
        char rawButtonStatus = SwitchStatus_BoosterPack_S2();

        // The second input of the FSM
        bool timerExpired = (Timer32_getValue(TIMER32_0_BASE) == 0);

        // outputs of the FSM
        bool debouncedButtonStatus;
        bool startTimer;

        // The button struct holds info on the debouncing state of the button
        // e.g. it knows if the button is in transition or not
        switch (debounce_state)
        {
        case Stable_P:
            // for each arc
            // Change state
                debounce_state = ;

                // Update outputs, if different from default
                startTimer = ;

             }
            break;

        if (startTimer)



        }
*/
        cur_status = SwitchStatus_BoosterPack_S2();






    }
}


// Initialization part is always device dependent and therefore does not change much with HAL
void initialize()
{

    // step 1: Stop watchdog timer
    // We do this at the beginning of all our programs for now.Later we learn more about it.
    WDT_A_hold(WDT_A_BASE);

    // step 2: Initializing LED1, which is on Pin 0 of Port P1 (from page 37 of the Launchpad User Guide)
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

    // step 3: Initializing the BoosterPack S2
    GPIO_setAsInputPin(GPIO_PORT_P3, GPIO_PIN5);

    Timer32_initModule(TIMER32_0_BASE, // There are two timers, we are using the one with the index 0
                       TIMER32_PRESCALER_1, // The prescaler value is 1; The clock is not divided before feeding the counter
                       TIMER32_32BIT, // The counter is used in 32-bit mode; the alternative is 16-bit mode
                       TIMER32_PERIODIC_MODE); //This options is irrelevant for a one-shot timer

}

void TurnOn_Launchpad_LED1()
{
    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
}
void TurnOff_Launchpad_LED1()
{
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
}

void Toggle_Launchpad_LED1()
{
    GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
}
char SwitchStatus_BoosterPack_S2()
{
    return (GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN5));
}
