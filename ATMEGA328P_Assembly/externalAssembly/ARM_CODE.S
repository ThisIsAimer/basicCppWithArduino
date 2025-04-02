#include "avr/io.h"
;variables

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

;int8_t primeNums (int8_t index)
.global primeNums

;int16_t playerPower();
.global playerPower

;void digitalSetAsm(int8_t port, int8_t bit)
.global digitalSetAsm

;void digitalclrAsm(int8_t port, int8_t bit)
.global digitalclrAsm



.data ;data part in sram
;----------------------------------------
.comm playerLevel, 1 ;1 byte stored in playerLevel 
.global playerLevel

.comm playerLives, 1
.global playerLives


.text
;----------------------------------------------------------------------------------


primeNumbers:
  ;     1 2 3 4 05 06 07 08 09 10 11 12 13 14 15 16
  .byte 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53


_playerLevel: .byte 100
_playerLives: .byte 5



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
;------------------------------------------------------------------------------
.func primeNums
primeNums:

  push r17
  push r30
  push r31
  ldi ZL , lo8(primeNumbers) ; the z pointer low is r30
  ldi ZH , hi8(primeNumbers) ; the z pointer high is r30
  ;adding the index to the pointer

  ldi r25, 0x00 ;; r25 nay contain garbage value

  clc
  add ZL , r24
  adc ZH , r25

  ;storing the value in z pointer to r17
  lpm r17 , Z ;load from program memory

  mov r24, r17

  pop r31
  pop r30
  pop r17
 
  ret

.endfunc

;------------------------------------------------------------------
.func playerPower
playerPower:
  push r0
  push r1
  push r17
  push r18

  ldi ZL, lo8(_playerLevel);_powerlevel is stored in flash
  ldi ZH, hi8(_playerLevel)

  lpm r17, Z
  sts playerLevel, r17 ;powerlevel is stored in sram

  ldi ZL, lo8(_playerLives)
  ldi ZH, hi8(_playerLives)

  lpm r17, Z
  sts playerLives, r17

  lds r17, playerLevel
  lds r18, playerLives

  mul r17, r18

  movw r24,r0 ;copyCopy Register Word r25:r25, r1,r0

  pop r18
  pop r17
  pop r1
  pop r0
  ret

.endfunc

.func digitalSetAsm
digitalSetAsm:
  push r0
  push r1

  adiw r24,0x20 ; gets data address

  clr XH
  mov XL, r24 ; st pointer

WriteOne:
  ld r20, X

  or r20, r22 ; just changes one value
  st X, r20 ;x is a pointer pointing to r24

  pop r1
  pop r0
  ret

.endfunc


.func digitalClrAsm
digitalClrAsm:
  push r0
  push r1

  adiw r24,0x20 ; gets data address

  clr XH
  mov XL, r24 ; st pointer

WriteZero:
  ld r20, X 

  com r20 
  and r20, r22 ; just changes one value
  st X, r20 ;x is a pointer pointing to r24

  pop r1
  pop r0
  ret

.endfunc
