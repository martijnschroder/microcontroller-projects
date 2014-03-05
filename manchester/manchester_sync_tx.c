#include "manchester.h"
#include <avr/interrupt.h>

static volatile uint8_t *_port;
static volatile uint8_t *_ddr;
static uint8_t _pin;

static volatile uint8_t buf;
static volatile uint8_t bit_count;
static volatile uint8_t signal_state; // signal position in the bit (1 = T, 0 = 2T)

/*
 * Using timer 0 the baud rate can range from 300 to 62500 at 16 MHz
 */
void manchester_init_tx(volatile uint8_t *port, uint8_t pin, uint16_t baud){
	_port = port;
	_pin = pin;
	_ddr = port - 0x1;
	*_ddr |= _BV(pin);	//Enable output on selected pin
	
	TCCR0A = 0x0; 				// normal mode
	TCCR0B |= _BV(CS02);        // F_CPU / 256 prescaler
	OCR0A = F_CPU / 256 / baud; // compare value
	TIMSK0 = 0x00;		// do not enable compare interrupt yet; this is done in write()
	
	sei();
}

void write(uint8_t data) {
	PORTD ^= _BV(PORTD2);	//TODO
	while (TIMSK0 & _BV(OCIE0A));	//Wait until the compare a interrupt is no longer enabled
	PORTD ^= _BV(PORTD3);	//TODO
	buf = data;
	bit_count = 0;
	signal_state = 0;
	TCNT0 = 0;				// reset timer counter
	TIMSK0 |= _BV(OCIE0A);			// enable compare a interrupt
}

void manchester_write(uint8_t data) {
	write(0x7F);
	write(data);
}

EMPTY_INTERRUPT(TIMER0_COMPB_vect)
EMPTY_INTERRUPT(TIMER0_OVF_vect)
ISR(TIMER0_COMPA_vect) {
	TCNT0 = 0x00;		//reset timer counter
	PORTD ^= _BV(PORTD4);	//TODO
	uint8_t bit = (buf & _BV(bit_count));
	if (bit) {
		PORTD |= _BV(PORTD5);	//TODO
		if (signal_state == 0) {
			*_port &= ~_BV(_pin); // low
		} else {
			*_port |= _BV(_pin);  // to high
		}
	} else {
		PORTD &= ~_BV(PORTD5);	//TODO
		if (signal_state == 0) {
			*_port |= _BV(_pin);  // high
		} else {
			*_port &= ~_BV(_pin); // to low
		}
	}
	
	signal_state ^= 0x01;
	
	if (signal_state == 0) bit_count++;
	
	PORTD ^= _BV(PORTD7);	//TODO
	
	if (bit_count >= 8) {
		TIMSK0 &= ~_BV(OCIE0A);		// disable timer
		PORTD = 0x00;	//TODO
	}
}

