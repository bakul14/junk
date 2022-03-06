﻿
//-------------------------------------------------<                   axlib v1.1                    >----------------------------------------------------
//-------------------------------------------------<       Библиотека для работы с шиной SPI         >----------------------------------------------------
//-------------------------------------------------<    Кузнецов Алексей 2015 http://www.avrki.ru    >----------------------------------------------------


#ifndef SPI_H_
#define SPI_H_

#if !defined(MAIN_INIT_H_)
#error "You must included (#include \"main_init.h\") befor use (#include \"axlib/spi.h\")."
#endif

#include <avr/interrupt.h>

volatile UBYTE SPI_DATA = 0;
volatile UBYTE SPI_FLAG = 0;

#ifdef SPDR

#if !defined (NULL)
#define NULL 0
#endif

// Включить SPI
#define SPI_ON			0x40

// Выключить SPI
#define SPI_OFF			0

// Режим Мастер
#define SPI_MASTER		0x10

// Режим Слейв
#define SPI_SLAVE		0

// Направление передачи (Младший разряд вперед)
#define SPI_DIRECT_LSB	0x20

// Направление передачи (Старший разряд вперед)
#define SPI_DIRECT_MSB	0

// Разрешить прерывание
#define SPI_INT_ON		0x80

// Запретить прерывание
#define SPI_INT_OFF		0

// Положительный тактовый сигнал
#define SPI_CPOL_LOW	0

// Отрицательный тактовый сигнал
#define SPI_CPOL_HIGHT	0x08

// Наростающий фронт сигнала
#define SPI_CPHA_1EDGE	0
// Спадающий фронт сигнала
#define SPI_CPHA_2EDGE	0x04

// Предделитель частоты (настройка скорости передачи для мастера)
#define SPI_PRESCALER_2		0
#define SPI_PRESCALER_4		1
#define SPI_PRESCALER_8		2
#define SPI_PRESCALER_16	3
#define SPI_PRESCALER_32	4
#define SPI_PRESCALER_64	5
#define SPI_PRESCALER_128	6
#define SPI_PRESCALER_NO	7

#if defined (_AVR_ATMEGA8A_H_INCLUDED) // Если MEGA8

#define SPI_M_PORT		(DDRB |= (1 << 3) | (1 << 5) | (1 << 2))
#define SPI_M_SS_ON		(PORTB &= ~(1 << 2))
#define SPI_M_SS_OFF	(PORTB |= (1 << 2))

#define SPI_S_PORT		(DDRB |= (1 << 4))
#define SPI_S_SS_PIN	2

#elif defined (_AVR_IOM328P_H_) // Если MEGA328P

#define SPI_M_PORT		(DDRB |= (1 << 3) | (1 << 5) | (1 << 2))
#define SPI_M_SS_ON		(PORTB &= ~(1 << 2))
#define SPI_M_SS_OFF	(PORTB |= (1 << 2))

#define SPI_S_PORT		(DDRB |= (1 << 4))
#define SPI_S_SS_PIN	2

#else // Для других МК

#define SPI_M_PORT		(DDRB |= ((1 << 5) | (1 << 7) | (1 << 4))
#define SPI_M_SS_ON		(PORTB &= ~(1 << 4))
#define SPI_M_SS_OFF	(PORTB |= (1 << 4))

#define SPI_S_PORT		(DDRB |= (1 << 6))
#define SPI_S_SS_PIN	4
#endif


// Флаг наличия данных в режиме Slave
#define FLAG_DATA	0
#define FLAG_OUT	1

#if defined(SPI_SLAVE_MODE)
	// Преывания по окончанию передачи для ведущего
	ISR(SPI_STC_vect)
	{
		SPI_DATA = SPDR;
		SPI_FLAG = 1;
	}
	#endif

// Объявление структур
typedef struct
{
	BYTE SPI_set;			// Включить/выключить SPI
	BYTE SPI_Mode;			// Выбор Мастер или Слейв
	BYTE SPI_Direct;		// Выбор направления передачи байта
	BYTE SPI_Prescaler;		// Выбор претделителя
	BYTE SPI_Polaric;		// Выбор полярности тактового сигнала
	BYTE SPI_Phase;			// Выбор фазы тактового сигнала
	
}SPI_InitTypeDef;

// Объявление функций

// Инициализация SPI
void SPI_init(SPI_InitTypeDef *spi);

// Чтение байта и передача по шине для мастер устройства
UBYTE SPI_M_byte_io(BYTE data);

// Чтение байта из шины для слейв устройства
UBYTE SPI_S_byte_io(BYTE data, BYTE timeout);


// Функции

//-------------------------------------------------------------------------------------------------------

// Функция инициализации SPI принимает в качестве аргумента указатель на структуру

void SPI_init(SPI_InitTypeDef *spi)
{
	if(spi == NULL)
	{
		return;
	}
	if(spi->SPI_Mode == SPI_MASTER)
	{
		SPI_M_PORT;
		SPI_M_SS_OFF;
		SPCR = (spi->SPI_set | spi->SPI_Mode | spi->SPI_Direct | spi->SPI_Polaric | spi->SPI_Phase);
	}
	else
	{
		SPI_S_PORT;
		SPCR = (spi->SPI_set | spi->SPI_Mode | spi->SPI_Direct | spi->SPI_Polaric | spi->SPI_Phase | (1 << SPIE));
		sei();
	}

	switch (spi->SPI_Prescaler)
	{
		case 0: // 2
		SPSR |= (1 << SPI2X);
		SPCR &= ~(1 << SPR0) | ~(1 << SPR1);
		break;
		
		case 1: // 4
		SPCR &= ~(1 << SPR0) | ~(1 << SPR1);
		break;
		
		case 2: // 8
		SPSR |= (1 << SPI2X);
		SPCR |= (1 << SPR0);
		SPCR &= ~(1 << SPR1);
		break;
		
		case 3: // 16
		SPCR |= (1 << SPR0);
		SPCR &= ~(1 << SPR1);
		break;
		
		case 4: // 32
		SPSR |= (1 << SPI2X);
		SPCR &= ~(1 << SPR0);
		SPCR |= (1 << SPR1);
		break;
		
		case 5: // 64
		SPCR &= ~(1 << SPR0);
		SPCR |= (1 << SPR1);
		break;
		
		case 6: //128
		SPCR |= 0x03;
		break;
		
		case 7: //SLAVE
		SPCR &= 0xFC;
		break;
	}
}

//-------------------------------------------------------------------------------------------------------

// Чтение байта и передача по шине для мастер устройства
UBYTE SPI_M_byte_io(BYTE data)
{
	UBYTE answer = 0;
	SPI_M_SS_ON;
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	answer = SPDR;
	SPI_M_SS_OFF;
	return answer;
}

//-------------------------------------------------------------------------------------------------------

// Чтение/запись байта из шины для слейв устройства
UBYTE SPI_S_byte_io(BYTE data, BYTE timeout)
{	
	// Ожидания единицы на входе SS
	while(!(PINB & (1 << SPI_S_SS_PIN)));
	// Загрузка байта для передачи Мастеру
	SPDR = data;
	// Ожидания завершения обмена
	while(SPI_FLAG == 0)
	{
		if(!timeout)
		{
			// Выход с записью в регистр данных 0xFF по таймауту
			SPDR = 0xFF;
			return FULL;
		}
		_delay_ms(1);
		timeout--;
	}
	// Сброс флага обмена
	SPI_FLAG = 0;
	// Возврат значения принятого от Мастера
	return SPI_DATA;
}


#else
#error "This is not the microcontroller SPI"
#endif // SPDR

#endif /* SPI_H_ */