#include "s3c44b0x.h"
#include "s3cev40.h"
#include "iic.h"

extern uint32 mclk; // Frecuencia actual del reloj (Hz)

extern void DelayMs(int ms_time);

void iic_init() {
	// Activar el reloj para los bloques ICC, GPIO y BDMA.
	// NOTA: Si no se activa BDMA, el controlador IIC no es accesible.
	CLKCON |= (1 << 13); // ICC = 1
	CLKCON |= (1 << 10); // GPIO = 1
	CLKCON |= (1 <<  7); // BDMA = 1

	PCONF = (PCONF & (~0xF)) | 0xA; // PF1 = 10 (IICSDA), PF0 = 10 (IICSCL)
	PUPF &= 0xFC;                   // Pull-up enable: PF1 = 0, PF0 = 0
	
	// Configurar la direcci�n del slave:
	IICADD = S3C44B0X_SLAVE_ADDRESS;

	// Generaci�n ACK habilitada, interrupciones habilitadas:
	// ACK = 1, Interrupci�n Tx/Rx = 1, Preescalado: ((mclk / 16) / 250000) - 1
	IICCON = (1 << 7) | (1 << 5) | ((mclk / 4000000 - 1) & 0x0F);

	// Activa Tx/Rx:
	IICSTAT = (1 << 4);
}

void iic_putByte_start(uint8 byte) {
	// Escribe el dato
	IICDS = byte;
	// M�ster Tx, start condition, Tx/Rx habilitada
	IICSTAT = (IICSTAT & 0x0F) | 0xF0;
	// Comienza la transmisi�n (borrando pending bit del IICCON)
	IICCON &= ~(1 << 4);
	// Espera la recepci�n de ACK
	while (!(IICCON & 0x10)); //while (IICSTAT & 0x1);
}

void iic_putByte(uint8 byte) {
	// Escribe el dato
	IICDS = byte;
	// Comienza la transmisi�n del dato (borrando pending bit del IICCON)
	IICCON &= ~(1 << 4);
	// Espera la recepci�n de ACK
	while (!(IICCON & 0x10)); //while (IICSTAT & 0x1);
}

void iic_putByte_stop(uint8 byte) {
	// Escribe el dato
	IICDS = byte;
	// Comienza la trasmisi�n del dato (borrando pending bit del IICCON)
	IICCON &= ~(1 << 4);
	// Espera la recepci�n de ACK
	while (!(IICCON & 0x10)); //while (IICSTAT & 0x1);

	// M�ster Tx, stop condition, Tx/Rx habilitada
	IICSTAT = (IICSTAT & 0x0F) | 0xD0;
	// Comienza la trasmisi�n de STOP (borrando pending bit del IICCON)
	IICCON &= ~(1 << 4);
	// Espera a que la stop condition tenga efecto (5 ms para la at24c04)
	DelayMs(5);
}

void iic_getByte_start(uint8 byte) {
	// Escribe el dato
	IICDS = byte;
	// M�ster Rx, start condition, Tx/Rx habilitada
	IICSTAT = (IICSTAT & 0x0F) | 0xB0;
	// Comienza la transmisi�n (borrando pending bit del IICCON)
	IICCON &= ~(1 << 4);
	// Espera la rececpi�n de ACK
	while (!(IICCON & 0x10)); //while (IICSTAT & 0x1);
}

uint8 iic_getByte() {
	// Reanuda la recepci�n (borrando pending bit del IICCON)
	IICCON &= ~(1 << 4);
	// Espera la recepci�n del dato
	while (!(IICCON & 0x10)); //while (IICSTAT & 0x1);
	return IICDS; // Lee el dato
}

uint8 iic_getByte_stop(int8 ack) {
	IICCON = (IICCON & ~(1 << 7)) | (ack << 7); // Activa o no la generaci�n de ACK.

	// Reanuda la recepci�n (borrando pending bit del IICCON)
	IICCON &= ~(1 << 4);
	// Espera la recepci�n del dato
	while (!(IICCON & 0x10)); //while (IICSTAT & 0x1);
	uint8 byte = IICDS; // Lee el dato

	// M�ster Rx, stop condition, Tx/Rx habilitada
	IICSTAT = (IICSTAT & 0x0F) | 0x90;
	// Comienza la trasmisi�n de STOP (borrando pending bit del IICCON)
	IICCON &= ~(1 << 4);
	// Espera a que la stop condition tenga efecto (5 ms para la at24c04)
	DelayMs(5);

	IICCON |= (1 << 7); // Habilita la generaci�n de ACK
	return byte;
}
