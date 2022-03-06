void init(void)
{
	com(0x30);		// Переход в 4-х битный режим
	com(0x30);		// Переход в 4-х битный режим
	com(0x30);		// Переход в 4-х битный режим
	com(0x20);		// Переход в 4-х битный режим
	com(0x20);		// Установка параметров
	com(0x80);		// Установка параметров
	com(0x00);		// Выключаем дисплей
	com(0x80);		// Выключаем дисплей
	com(0x00);		// Очищаем дисплей
	com(0x10);		// Очищаем дисплей
	com(0x00);		// Устанавливаем режим ввода данных
	com(0x60);		// Устанавливаем режим ввода данных
	com(0x00);		// Включаем дисплей с выбранным курсором
	com(0xC0);		// Включаем дисплей с выбранным курсором
}

void char_out(BYTE data)
{
	BYTE data_h = ((data & 0xF0) + 0x09);
	BYTE data_l = ((data << 4) + 0x09);
	
	pcf8574_byte_out(data_h, ADD); // Передача старших 4 бит
	data_h |= 0x04;
	pcf8574_byte_out(data_h, ADD); // Передача старших 4 бит
	data_h &= 0xF9;
	pcf8574_byte_out(data_h, ADD); // Передача старших 4 бит
	
	pcf8574_byte_out(data_l, ADD); // Передача младших 4 бит
	data_l |= 0x04;
	pcf8574_byte_out(data_l, ADD); // Передача младших 4 бит
	data_l &= 0xF9;
	pcf8574_byte_out(data_l, ADD); // Передача младших 4 бит
}

void str_out(BYTE *str)
{
	while((*str) != '\0')
	{
		char_out(*str);
		str++;
	}
}

int main(void)
{
	
	init();
	str_out("kokokoko!");
	
	while(1)
	{
		
	}
}