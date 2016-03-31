#define F_CPU 16000000
#define DURATION 4

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/* Globals */
volatile uint8_t porthistory = 0xFF;  //Default is high because of pull-up.
volatile uint8_t debounce = 1;
volatile uint16_t buttonCount0 = 0;
volatile uint16_t buttonCount1 = 0;
volatile uint16_t buttonCount2 = 0;
volatile uint16_t buttonCount3 = 0;


void setupPorts() {
  //LEDs and buzzer as output
  DDRD |= ((1 << DDD0) | (1 << DDD1) | (1 << DDD2) | (1 << DDD3) | (1 << DDD7));
  //Button pull-up resistors
  PORTB |= ((1 << PORTB0) | (1 << PORTB1) | (1 << PORTB2) | (1 << PORTB3));
}

void setupInterrupts() {
  // Enable pin-change interrupts
  PCICR |= 1 << PCIE0;
  PCMSK0 |= ((1 << PCINT0) | (1 << PCINT1) | (1 << PCINT2) | (1 << PCINT3));
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
      if (buttonCount0 == DURATION || buttonCount0 == 1) {
        PORTD ^= (1 << PORTD0);  // Toggle LED.
      }
      // Buzzer
      int j;
      for (j=0; j<10; j++) {
        PORTD |= (1 << PORTD7);
        _delay_ms(10);
        PORTD &= ~(1 << PORTD7);
        _delay_ms(10);
      }
      buttonCount0--;
    }
    _delay_ms(100);

    // Beat 2
    if (buttonCount1) {
      if (buttonCount1 == DURATION || buttonCount1 == 1) {
        PORTD ^= (1 << PORTD1);  // Toggle LED.
      }
      // Buzzer
      int j;
      for (j=0; j<10; j++) {
        PORTD |= (1 << PORTD7);
        _delay_ms(10);
        PORTD &= ~(1 << PORTD7);
        _delay_ms(10);
      }
      buttonCount1--;
    }
    _delay_ms(100);

    // Beat 3
    if (buttonCount2) {
      if (buttonCount2 == DURATION || buttonCount2 == 1) {
        PORTD ^= (1 << PORTD3);  // Toggle LED.
      }
      // Buzzer
      int j;
      for (j=0; j<10; j++) {
        PORTD |= (1 << PORTD7);
        _delay_ms(10);
        PORTD &= ~(1 << PORTD7);
        _delay_ms(10);
      }
      buttonCount2--;
    }
    _delay_ms(100);

    // Beat 4
    if (buttonCount3) {
      if (buttonCount3 == DURATION || buttonCount3 == 1) {
        PORTD ^= (1 << PORTD2);  // Toggle LED.
      }
      // Buzzer
      int j;
      for (j=0; j<10; j++) {
        PORTD |= (1 << PORTD7);
        _delay_ms(10);
        PORTD &= ~(1 << PORTD7);
        _delay_ms(10);
      }
      buttonCount3--;
    }
    _delay_ms(100);
  }
}

/*
  This code was partially inspired by an example found online. Source:
  https://sites.google.com/site/qeewiki/books/avr-guide/external-interrupts-on-the-atmega328
*/
ISR(PCINT0_vect) {
  debounce = (debounce + 1) % 2;
  uint8_t changedbits = PINB ^ porthistory; //Single out changed bits.

  if (debounce && (changedbits & (1 << PINB0))) {
    buttonCount0 = DURATION;
  }

  if (debounce && (changedbits & (1 << PINB1))) {
    buttonCount1 = DURATION;
  }

  if (debounce && (changedbits & (1 << PINB2))) {
    buttonCount2 = DURATION;
  }

  if (debounce && (changedbits & (1 << PINB3))) {
    buttonCount3 = DURATION;
  }

  porthistory = PINB; // Update port history
}
