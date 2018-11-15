#include "gpio.h"
#include <stdio.h>

/**
 * To configure the GPIO pin.
 *
 * Input:
 * 	port			the port to configure
 * 	pin				the pin to configure
 * 	configuration	the configuration setting for the pin
 * 					[1:0] Mode
 * 					[2:2] Driver Type
 * 					[4:3] Output Speed
 * 					[6:5] Pull Type
 *
 * 	E.g.:
 * 		gpioConfigurationPins(GpioA, GpioPin0, GPIO_OUTPUT |		\
 * 											  GPIO_OPEN_DRAIN |	\
 * 											  GPIO_HIGH_SPEED |	\
 * 											  GPIO_NO_PULL);
 */
void gpioConfigurePin(GpioRegs *port, GpioPin pin, int configuration) {

	uint32_t mode, driver, outSpeed, pullType, pinMask, pinTemp;

	pinMask = 0x01;

	mode 	=  configuration & 0x3;
	driver 	= (configuration >> 2) & 1;
	outSpeed= (configuration >> 3) & 3;
	pullType= (configuration >> 5) & 3;




	for(int i = 0; i < 16; i++) {
		pinTemp = pinMask & pin;
		if(pinTemp > 0) {
			port->mode &= ~(3 << (i * 2));
			port->mode |= mode << i * 2;

			port->driverType &= ~(1 << i);
			port->driverType |= driver << i;

			port->outSpeed &= ~(3 << (i * 2));
			port->outSpeed |= outSpeed << i * 2;

			port->pullType &= ~(3 << (i * 2));
			port->pullType |= pullType << i * 2;

		}
		pinMask = pinMask << 1;
	}

}

void gpioWritePins(GpioRegs *port, GpioPin pins, int state) {

	if(state == PIN_SET)
		port->outBits = pins;
	else if (state == PIN_RESET)
		port->outBits = pins << 16;
	//Use BSRR
}

void gpioTogglePins(GpioRegs *port, GpioPin pins) {
	port->outData ^= pins;
	//Use IDR and ODR
}

uint32_t gpioReadPins(GpioRegs *port, GpioPin pins) {
	if((port->inData & pins) == PIN_SET) {
		return PIN_SET;
	}
	else
		return PIN_RESET;
}

void gpioLockPins(GpioRegs *port, GpioPin pins) {

}
