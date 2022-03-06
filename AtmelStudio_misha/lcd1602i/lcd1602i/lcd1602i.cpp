void init(void)
{
	com(0x30);		// ������� � 4-� ������ �����
	com(0x30);		// ������� � 4-� ������ �����
	com(0x30);		// ������� � 4-� ������ �����
	com(0x20);		// ������� � 4-� ������ �����
	com(0x20);		// ��������� ����������
	com(0x80);		// ��������� ����������
	com(0x00);		// ��������� �������
	com(0x80);		// ��������� �������
	com(0x00);		// ������� �������
	com(0x10);		// ������� �������
	com(0x00);		// ������������� ����� ����� ������
	com(0x60);		// ������������� ����� ����� ������
	com(0x00);		// �������� ������� � ��������� ��������
	com(0xC0);		// �������� ������� � ��������� ��������
}

void char_out(BYTE data)
{
	BYTE data_h = ((data & 0xF0) + 0x09);
	BYTE data_l = ((data << 4) + 0x09);
	
	pcf8574_byte_out(data_h, ADD); // �������� ������� 4 ���
	data_h |= 0x04;
	pcf8574_byte_out(data_h, ADD); // �������� ������� 4 ���
	data_h &= 0xF9;
	pcf8574_byte_out(data_h, ADD); // �������� ������� 4 ���
	
	pcf8574_byte_out(data_l, ADD); // �������� ������� 4 ���
	data_l |= 0x04;
	pcf8574_byte_out(data_l, ADD); // �������� ������� 4 ���
	data_l &= 0xF9;
	pcf8574_byte_out(data_l, ADD); // �������� ������� 4 ���
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