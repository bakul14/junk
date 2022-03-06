﻿
//-------------------------------------------------<                axlib v1.1                 >----------------------------------------------------
//-------------------------------------------------<       Библиотека для работы с USART       >----------------------------------------------------
//-------------------------------------------------< Кузнецов Алексей 2015 http://www.avrki.ru >----------------------------------------------------

#ifndef USART_H_
#define USART_H_

#if !defined(MAIN_INIT_H_)
#error "You must included (#include \"main_init.h\") befor use (#include <axlib/usart.h>)."
#endif

//-------------------------------------------------------------------------
//						Объявление служебных псевдонимов
//-------------------------------------------------------------------------

#define RXCIE_ON	(UCSRB |= (1 << RXCIE))
#define RXCIE_OFF	(UCSRB &= ~(1 << RXCIE))
#define TXCIE_ON	(UCSRB |= (1 << TXCIE))
#define TXCIE_OFF	(UCSRB |= ~(1 << TXCIE))

//-------------------------------------------------------------------------
//							Подключаемые библиотеки
//-------------------------------------------------------------------------
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <axlib/type_var.h>
#include <axlib/cicle_buffer.h>

//-------------------------------------------------------------------------
//							Объявление функций
//-------------------------------------------------------------------------

//------------------------------------------------------------------------- 
//	Функция инициализации USART.
//
//	Принимает аргументы:
//
//		USART_WORD baudrate - Передает функции значение скорости передачи в БОД.
//-------------------------------------------------------------------------

void usart_init(DWORD baudrate)
{
#if defined(UCSR0A)
	UCSR0A = 0x00;
	UCSR0B |= (3 << TXEN0) | (1 << RXCIE0);
	UCSR0C = (3 << UCSZ00);
	
	UBRR0H = ((F_CPU/16/baudrate-1) >> 8);
	UBRR0L = (F_CPU/16/baudrate-1);
#else
	UCSRA = 0x00;
	UCSRB |= (3 << TXEN) | (1 << RXCIE);
	UCSRC = (1 << URSEL) | (3 << UCSZ0);
	
	UBRRH = ((F_CPU/16/baudrate-1) >> 8);
	UBRRL = (F_CPU/16/baudrate-1);
#endif
	
	
	sei();
}

//-------------------------------------------------------------------------
//	Функция передачи байта в USART.
//	Принимает аргументы:
//
//		BYTE data - Передает функции байт, который необходимо послать в порт.
//						  Данная функция не использует прерывания USART.
//-------------------------------------------------------------------------

void usart_char_out(BYTE data)
{
#if defined(UCSR0A)
	while (!( UCSR0A & (1 << UDRE0)));
	UDR0 = data;
#else
	while (!( UCSRA & (1 << UDRE)));
	UDR = data;
#endif

}

//-------------------------------------------------------------------------
//	Функция чтения байта из USART.
//
//	Возвращаемые данные функцией:
//
//		BYTE - Возвращает принятый байт из USART.
//					 Данная функция не использует прерывания USART.
//-------------------------------------------------------------------------

BYTE usart_char_in(void)
{
#if defined(UCSR0A)
	while (!(UCSR0A & (1 << RXC0)));
	return UDR0;
#else
	while (!(UCSRA & (1 << RXC)));
	return UDR;
#endif
}

//-------------------------------------------------------------------------
//	Функция передачи строки в USART.
//
//	Принимает аргументы:
//
//		BYTE *str - Передает функции указатель на адрес первого элемента 
//						  массива, который необходимо послать в порт.
//						  Строковый массив обязательно должен заканчивотся
//						  нулевым символом \0.
//-------------------------------------------------------------------------

void usart_str_out(BYTE *str, BYTE count)
{
	BYTE i = 0;
	while(i < count)
	{
		usart_char_out(*str);
		str++;
		i++;
	}
}

//-------------------------------------------------------------------------
//	Функция передачи строки в USART для RS-485 MH-BUS.
//
//	Принимает аргументы:
//
//		BYTE *str - Передает функции указатель на адрес первого элемента
//						  массива, который необходимо послать в порт.
//						  
//-------------------------------------------------------------------------

void usart_mhbus_out(BYTE *str)
{
	BYTE i = 0;
	while(i < 11)
	{
		usart_char_out(*str);
		str++;
		i++;
	}
}

//-------------------------------------------------------------------------
//	Функция получения строки записанную в буфер из USART
//
//	Передаваемые параметры параметры:
//
//			BYTE *str - Указатель на адрес первой ячейки массива
//							  Длину массива рекомендуется брать равной
//							  длине буфера. В противном случае возможны
//							  переполнение массива. Либо нужно точно знать
//							  что полученная строка умещается в массив.
//-------------------------------------------------------------------------

BYTE usart_str_in(BYTE *str, BYTE count)
{
	BYTE out = 0;
	BYTE data = 0;
	BYTE timeout = 0;
	
	while(count > data)
	{
		data = GetData();
		
		// Если в течении пол секунды данные не пришли
		// то выйти из функции и вернуть 0
		if(timeout >= 500)
		{
			ClearBuffer();
			return out;
		}
		
		timeout++;
		_delay_ms(1);
	}
	
	out = OutBufferStr(str, count);
	return out;
}

//-------------------------------------------------------------------------
//	Функция передачи строки в USART.
//
//	Принимает аргументы:
//
//		BYTE *str - Передает функции указатель на адрес первого элемента
//						  массива, который необходимо послать в порт.
//						  Строковый массив обязательно должен заканчивотся
//						  нулевым символом \0. После передачи строки в порт
//						  передается два служебных символа \r\n. 
//-------------------------------------------------------------------------

void usart_str_rn(BYTE *str)
{
	BYTE i=0;
	while(str[i])
	{
		usart_char_out(str[i]);
		i++;
	}
	usart_char_out('\r');
	usart_char_out('\n');
	
}

//-------------------------------------------------------------------------
//	Функция получения количества байт записанные в буфер из USART
//
//	Возвращаемые параметры:
//
//			BYTE - Количество байт в буфере
//-------------------------------------------------------------------------

BYTE usart_data(void)
{
	return GetData();
}

//-------------------------------------------------------------------------



#endif /* USART_H_ */