#include "avr/io.h"

;--------------------------------------------------------------------------------

.equ    counter, 0xFFFF

;--------------------------------------------------------------------------------

;exporting assembly functions to cpp.
;setting function initials
;.global lets the c compiler interract with the methods

;void TurnLEDOn();
.global TurnLEDOn

;void TurnLEDOff();
.global TurnLEDOff


.text

.func TurnLEDOn
TurnLEDOn:   ;defining function
  push r17
  ldi r17, (1<<PIN5)              ; PIN5 = 5 its shifting 1 5 times
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