#include "CCAMD_VT100_Lib.h"

// Globals
const int ANALOGUE_X  =   A0;
const int ANALOGUE_Y  =   A1;
const int BUTTON      =   8 ;

uint8_t ditherChars[4] = { 
    ASCII_BLOCK_DITHERED_LIGHT, 
    ASCII_BLOCK_DITHERED_MEDIUM, 
    ASCII_BLOCK_DITHERED_DARK, 
    ASCII_BLOCK_SOLID
};

void setup() {
    Serial.begin(115200);
    pinMode(ANALOGUE_X, INPUT);
    pinMode(ANALOGUE_Y, INPUT);
    pinMode(BUTTON, INPUT);

    VT100_Boot();
    delay(300);

    VT100_SetCursor(12, 0);
    Serial.write("\n\rReady:");


    VT100_SendCmd( VT100_HIDE_CURSOR );
}

void loop() {
    static int playerX = 40;
    static int playerY = 12;
    static uint8_t animation = 1;

    // Reading joystick and button
    int joystickX = analogRead(ANALOGUE_X);
    int joystickY = analogRead(ANALOGUE_Y);
    int8_t buttonPress = digitalRead(BUTTON);

    // Movement logic
    if (joystickX > (512 + 80))
        playerX++;
    else if (joystickX < (512 - 80))
        playerX--;

    if (joystickY > (512 + 80))
        playerY--;
    else if (joystickY < (512 - 80))
        playerY++;

    // Animation update
    animation = (animation + 1) % 4;  

    Serial.write(ditherChars[animation]);

    VT100_ClearScreen();  
    VT100_SetCursor(playerY, playerX);

    delay(100);
}
