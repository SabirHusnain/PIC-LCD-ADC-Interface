// PIC18F452 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1H
#pragma config OSC = XT         // Oscillator Selection bits (XT oscillator)
#pragma config OSCS = OFF       // Oscillator System Clock Switch Enable bit (Oscillator system clock switch option is disabled (main oscillator is source))

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bit (Brown-out Reset disabled)
#pragma config BORV = 20        // Brown-out Reset Voltage bits (VBOR set to 2.0V)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 128      // Watchdog Timer Postscale Select bits (1:128)

// CONFIG3H
#pragma config CCP2MUX = ON     // CCP2 Mux bit (CCP2 input/output is multiplexed with RC1)

// CONFIG4L
#pragma config STVR = OFF       // Stack Full/Underflow Reset Enable bit (Stack Full/Underflow will not cause RESET)
#pragma config LVP = OFF        // Low Voltage ICSP Enable bit (Low Voltage ICSP disabled)

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000200-001FFFh) not code protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot Block (000000-0001FFh) not code protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000200-001FFFh) not write protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0001FFh) not write protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000200-001FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from Table Reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0001FFh) not protected from Table Reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <pic18f452.h>

#define ldata PORTD
#define rs PORTBbits.RB0
#define rw PORTBbits.RB1
#define en PORTBbits.RB2

int ADCLower = 0x33;
int ADCHigher = 0x3;

int finalNum;

int num1;
int num2;
int num3;
int num4;

void lcdcmd(unsigned char value);
void lcddata(unsigned char value);
void MSDelay(unsigned int itime);
void Delay(unsigned int);
void ADC_CONV();
void Seperate_Digit();

int main() {
    TRISD = 0;
    TRISB = 0;

    TRISAbits.TRISA0 = 1;
    ADCON0 = 0x81;
    ADCON1 = 0xCE;


    en = 0;
    MSDelay(10);
    lcdcmd(0x38);
    MSDelay(10);

    lcdcmd(0x0E);
    MSDelay(15);
    lcdcmd(0x01);
    MSDelay(15);
    lcdcmd(0x06);
    MSDelay(15);
    lcdcmd(0x84);
    MSDelay(15);

    while (1) {
        ADC_CONV();
        Seperate_Digit();

        lcddata((char) (num4 + 48));
        Delay(3);
        lcddata((char) (num3 + 48));
        Delay(3);
        lcddata((char) (num2 + 48));
        Delay(3);
        lcddata((char) (num1 + 48));
        MSDelay(350);
        lcdcmd(0x01);
        Delay(2);
    }
    return 0;
}

void ADC_CONV() {
    Delay(1);
    ADCON0bits.GO = 1;
    while (ADCON0bits.DONE == 1);
    ADCLower = ADRESL;
    ADCHigher = ADRESH;
    Delay(250);
}

void Seperate_Digit() {
    finalNum = (ADCHigher * 256) + ADCLower;
    num1 = finalNum % 10;
    finalNum /= 10;
    num2 = finalNum % 10;
    finalNum /= 10;
    num3 = finalNum % 10;
    finalNum /= 10;
    num4 = finalNum;
}

void lcdcmd(unsigned char value) {
    ldata = value;
    rs = 0;
    rw = 0;
    en = 1;
    MSDelay(1);
    en = 0;
}

void lcddata(unsigned char value) {
    ldata = value;
    rs = 1;
    rw = 0;
    en = 1;
    MSDelay(1);
    en = 0;
}

void MSDelay(unsigned int itime) {
    unsigned int i, j;
    for (i = 0; i < itime; i++)
        for (j = 0; j < 135; j++);
}

void Delay(unsigned int i) {
    for (int j = 0; j < i; j++)
        for (int k = 0; k < 5; k++);
}