#include <xc.h>
#define _XTAL_FREQ 4000000  // Asegúrate de que esto coincida con tu configuración de oscilador

// Configuración de los pines de ADC y LEDs
#define LED1 PORTBbits.RB0  // LED para temperatura baja
#define LED2 PORTBbits.RB1  // LED para temperatura media
#define LED3 PORTBbits.RB2  // LED para temperatura alta

// Prototipo de función para leer ADC
unsigned int read_ADC(unsigned char channel);

void main() {
    // Configuración inicial de puertos
    TRISB = 0x00;  // Configura PORTB como salida para los LEDs
    ADCON1 = 0x0E; // Configura pines AN0 como entrada analógica
    ADCON0 = 0x01; // Enciende el ADC

    unsigned int temp;

    while(1) {
        temp = read_ADC(0);  // Lee la temperatura del sensor conectado a AN0
        if(temp < 512) {  // Suponiendo que 512 corresponde a tu umbral de temperatura baja
            LED1 = 1; LED2 = 0; LED3 = 0;
        } else if(temp < 768) {  // Umbral para temperatura media
            LED1 = 0; LED2 = 1; LED3 = 0;
        } else {  // Temperatura alta
            LED1 = 0; LED2 = 0; LED3 = 1;
        }
        __delay_ms(1000);  // Retardo para la estabilidad visual de los LEDs
    }
}

unsigned int read_ADC(unsigned char channel) {
    ADCON0 &= 0xC5;  // Limpia los bits de selección de canal
    ADCON0 |= channel << 3;  // Configura el canal de entrada
    __delay_ms(2);  // Tiempo para que se estabilice el cambio de canal
    GO_nDONE = 1;  // Inicia la conversión
    while(GO_nDONE);  // Espera a que se complete la conversión
    return ((ADRESH << 8) + ADRESL);  // Retorna el resultado de 10 bits
}