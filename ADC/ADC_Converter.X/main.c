#include <pic18f452.h>
#include <xc.h>

void DELAY(unsigned int);

int main()
{
    TRISC = 0;
    TRISD = 0;
    TRISAbits.TRISA0 = 0;
    ADCON0 = 0x81;
    ADCON1 = 0xCE;

    while (1)
    {
        DELAY(1);
        ADCON0bits.GO = 1;
        while (ADCON0bits.DONE == 1);
        PORTC = ADRESL;
        PORTD = ADRESH;
        DELAY(250);
    }
}

void DELAY(unsigned int i)
{
    for (int j = 0; j < i; j++)
        for (int k = 0; k < 5; k++);
}