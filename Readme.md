## ADC in PIC

**Objectives: -**

- To understand what is ADC (Analog to Digital Converter).
- To work with ADC and see what are the applications of ADC.
- To write a C language code for PIC for ADC.

**Apparatus: -**

- Laptop
- MPLAB X
- Proteus Circuit Simulator

**Class Task: -**

- Write a code for ADC in C for PIC.

**Theory: -**

- **ADC: -**

ADC (Analog-Digital Convert) are used to convert analog data to digital data. These devices are very commonly used in daily life gadgets and electronic components. In real world every quantity is an analog quantity for example temperature, pressure and humidity etc. are analog and these types of quantities can be measured using electrical devices called _transducers_. These are also called _sensors_. These are commonly in todays life. For these transistors to work with digital controllers their output needs to be converted to digital data.

![](RackMultipart20220929-1-v08x57_html_d506a089eac9a467.png)

**Figure 7.1: Processing of Sensor Data in Microcontrollers**

- **Resolution: -**

ADC has n-bit resolution where n is 8, 10, 12, 16 or even up to 24 bits. The higher resolution ADC provides a small step size and more accuracy. The step size and resolution of ADC is decided during designing and can't be changed.

**Table 7.1: Resolution Table for ADCs**

| **n-bit** | **Number of Steps** | **Step Size (mV)****5 / Steps** |
| --- | --- | --- |
| 8 | 256 | 19.53125 |
| 10 | 1024 | 4.882813 |
| 12 | 4096 | 1.220703 |
| 16 | 65536 | 0.076294 |

- **V**** REF ****: -**

VREF is the input voltage used for the reference voltage. The voltage connected to the pin, along with the resolution of ADC chip, dictate the step size. For an 8-bit ADC the step size is VREF/28.

- **Digital Output: -**

In an 8-bit ADC we have 8-bit digital signal that is the output of the ADC from D0 to D7 while in the 10-bit the output will be from D0 to D9. So, to calculate the voltage we use,

- **ADC Programming in PIC: -**

In PIC18F452 we have 8 ADC channels on pins RA0 – RA3 and RA5 then RE0 – RE2. There are two registers associated with ADC are, ADCON0 register and ADCON1 register. The bits of each are shown below figures: -

![Shape2](RackMultipart20220929-1-v08x57_html_b47a2d1ea359ef41.gif)

**Figure 7.2: Bits of ADCON0 Register**

This register is used to set the conversion time and the channel analog input channel which is going to be used this register can be used to control the power consumption of the ADC and can be turned off when the microcontroller is powered up.

![Shape3](RackMultipart20220929-1-v08x57_html_96de496525aa248b.gif)

**Figure 7.3: Bits of ADCON1 Register**

This register used to set the VREF for ADC and it is used to make the result registers ADRESL and S+ADRESH left or right justified. These are the steps to program and ADC using Polling method: -

- Turn on the ADC module using ADCON0, ADON bit.
- Make the pin for the selected ADC channel the input pin using TRIS register of that pin.
- Select the reference voltage and A / C input channel. We use registers ADCON0 and ADCON1 for that purpose.
- Select the conversion speed. For that use ADCCON0 and ADCCON1 registers.
- Activate the required acquisition time.
- Wait for the conversion to be completed by polling the end-of-conversion using GO / DONE bit.
- After that GO / DONE bit will become LOW and read the values of the ADRESL and ADRESH registers and display the value on whatever it should.
- Repeat step 5 and continue to do so.

**Program: -**

- **Code: -**

#include \<pic18f452.h\>

#include \<xc.h\>

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

    for (int j = 0; j \< i; j++)

        for (int k = 0; k \< 5; k++);

}

- **Explanation: -**

The code is simple and gets the analog data from analog pin RA0 which is used as analog input 0 in the PIC. Then ADC runs and converts the analog data to digital.

After some delay the bit ADCON, DONE is checked and if it is low the data will be sent to the PORTC and PORTD which will be in digital format.

**Circuit: -**

![](RackMultipart20220929-1-v08x57_html_a8389aa73000fb2.gif)

**Figure 7.4: Simple Circuit for ADC**

![](RackMultipart20220929-1-v08x57_html_aead32725390ad54.gif) ![](RackMultipart20220929-1-v08x57_html_50801e429b25c821.gif)

**Figure 7.5: Working of ADC and Visualization of Digital Data**

**Conclusion: -**

- In this lab ADC (Analog-Digital Converter) was seen and learnt how to work with these components in PIC.
- Learnt about ADC used in PIC18 and seen its specifications.
- I learnt how digital data can be converted to analog data using ADC and write a program for this purpose.
- Learnt how sensors works and how the sensor data is analyzed in microcontrollers.