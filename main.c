#define DURATION 4

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/* Globals */
volatile uint8_t porthistory = 0xFF;  //Default is high because of pull-up.
//volatile uint8_t debounce = 1;
volatile uint16_t buttonCount0 = 0;
volatile uint16_t buttonCount1 = 0;
volatile uint16_t buttonCount2 = 0;
volatile uint16_t buttonCount3 = 0;


void setupPorts() {
  //LEDs as output
  DDRD |= ((1 << DDD0) | (1 << DDD1) | (1 << DDD2) | (1 << DDD3) | (1 << DDD7));
  DDRB |= (1 << DDB7);
  //Button pull-up resistors
  PORTB |= ((1 << PORTB0) | (1 << PORTB1) | (1 << PORTB2) | (1 << PORTB3) | (1 << PORTB4) | (1 << PORTB5) | (1 << PORTB6));
}

void setupInterrupts() {
  // Enable pin-change interrupts
  PCICR |= 1 << PCIE0;
  PCMSK0 |= ((1 << PCINT0) | (1 << PCINT1) | (1 << PCINT2) | (1 << PCINT3) | (1 << PCINT4) | (1 << PCINT5) | (1 << PCINT6));
  sei();
}

int main()
{
  setupPorts();
  setupInterrupts();
  while(1)
  {
    // Beat 1
    if (buttonCount0) {
      if (buttonCount0 == 1) {
        PORTB ^= (1 << PORTB7);  // Toggle LED.
      }
      buttonCount0--;
    }
    _delay_ms(100);

    // Beat 2
    if (buttonCount1) {
      if (buttonCount1 == 1) {
        PORTB ^= (1 << PORTB7);  // Toggle LED.
      }
      buttonCount1--;
    }
    _delay_ms(100);

    // Beat 3
    if (buttonCount2) {
      if (buttonCount2 == 1) {
        PORTB ^= (1 << PORTB7);  // Toggle LED.
      }
      buttonCount2--;
    }
    _delay_ms(100);

    // Beat 4
    if (buttonCount3) {
      if (buttonCount3 == 1) {
        PORTB ^= (1 << PORTB7);  // Toggle LED.
      }
      buttonCount3--;
    }
    _delay_ms(1000);
  }
}

/*
  This code was partially inspired by an example found online. Source:
  https://sites.google.com/site/qeewiki/books/avr-guide/external-interrupts-on-the-atmega328
*/
ISR(PCINT0_vect) {
  // debounce = (debounce + 1) % 2;
  uint8_t changedbits = PINB ^ porthistory; //Single out changed bits.

  // if (debounce && (changedbits & (1 << PINB0))) {
  if (changedbits & (1 << PINB0)) {
    if (buttonCount0 == 0) {
      PORTB ^= (1 << PORTB7);  // Toggle LED.
    }
    buttonCount0 = DURATION;
  }

  // if (debounce && (changedbits & (1 << PINB1))) {
  if (changedbits & (1 << PINB1)) {
    buttonCount1 = DURATION;
  }

  // if (debounce && (changedbits & (1 << PINB2))) {
  if (changedbits & (1 << PINB2)) {
    buttonCount2 = DURATION;
  }

  // if (debounce && (changedbits & (1 << PINB3))) {
  if (changedbits & (1 << PINB3)) {
    buttonCount3 = DURATION;
  }

  porthistory = PINB; // Update port history
}
