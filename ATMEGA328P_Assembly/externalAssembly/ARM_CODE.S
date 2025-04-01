#include "avr/io.h"

;--------------------------------------------------------------------------------

.equ    counter, 0xFFFF

;--------------------------------------------------------------------------------

;exporting assembly functions to cpp.

;void TurnLEDOn();
.global TurnLEDOn

;void TurnLEDOff();
.global TurnLEDOff

;void setLED(uint8_t value);
.global setLED


.text
;----------------------------------------------------------------------------------
.func TurnLEDOn
TurnLEDOn:
  push r17
  ldi r17, (1<<PINB5)              ; PIN5 = 5 its shifting 1 5 times
  out _SFR_IO_ADDR(DDRB), r17     ;Special Register Field Input/Output Address
  out _SFR_IO_ADDR(PORTB), r17
  pop r17
  ret

.endfunc

.func TurnLEDOff
TurnLEDOff:
  push r17
  ldi r17, 0x00
  out _SFR_IO_ADDR(PORTB), r17
  pop r17
  ret

.endfunc
;---------------------------------------------------------------------------------
;in assembly the first parameter is stored in r24,25 second in r22,23 all 16 bit
.func setLED
setLED:
  push r17
  ldi r17 , (1<<PINB5)
  out _SFR_IO_ADDR(DDRB), r17
  cpi r24 , 0x00
  brne setLED_on

  setLED_off:
    out _SFR_IO_ADDR(PORTB), 00
    rjmp setLED_end

  setLED_on:
    out _SFR_IO_ADDR(PORTB), r17

  setLED_end:
  pop r17

.endfunc

