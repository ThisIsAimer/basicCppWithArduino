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

;int16_t multiply (int16_t num1, int16_t num2)
.global multiply


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
  ret

.endfunc
;----------------------------------------------------------------------------------
;in assembly the first parameter is stored in r24,25 second in r22,23 all 16 bit
.func multiply

multiply:
  push r0
  push r1

  muls r24,r22 ;

  ;8-bit Return Value (char, uint8_t) The return value is stored in r24

  ;16-bit Return Value (int, uint16_t)
  ;The return value is stored in r24:r25 (low byte in r24, high byte in r25)

  ;32-bit Return Value (long, uint32_t)
  ;he return value is stored in r22:r23:r24:r25
  ;lowest byte 22 and highest 25

  movw r24, r0 ;copy register word r0,r1 to r25,r24

  pop r1
  pop r0
  ret

.endfunc


