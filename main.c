/*
 * Hardware Connection:
 *
 *   --+--------------------+-----------------+---------
 *     |                    |                 | 
 *   --|------+-------------|-----+-----------|-----+--- 
 *     |      |             |     |           |     | 
 *  +-PB10---PB11-+      +-SCK---SDA-+     +-SCL---SDA-+
 *  |             |      |           |     |           |
 *  |             |      |           |     |           |
 *  |             |      |           |     |           |
 *  |             |      |           |     |           |
 *  |             |      |           |     |           |
 *  +-------------+      +-----------+     +-----------+
 *   STM32F104C8T6          SSD1306            SHT30
 */

#include "stm32f10x.h"

unsigned char font5x7_seperator = 0x00;

unsigned char font5x7[] = {
	0x00, 0x00, 0x00, 0x00, 0x00,// ' '
	0x00, 0x00, 0x5F, 0x00, 0x00,// !
	0x00, 0x07, 0x00, 0x07, 0x00,// "
	0x14, 0x7F, 0x14, 0x7F, 0x14,// #
	0x24, 0x2A, 0x07, 0x2A, 0x12,// $
	0x23, 0x13, 0x08, 0x64, 0x62,// %
	0x37, 0x49, 0x55, 0x22, 0x50,// &
	0x00, 0x05, 0x03, 0x00, 0x00,// '
	0x00, 0x1C, 0x22, 0x41, 0x00,// (
	0x00, 0x41, 0x22, 0x1C, 0x00,// )
	0x08, 0x2A, 0x1C, 0x2A, 0x08,// *
	0x08, 0x08, 0x3E, 0x08, 0x08,// +
	0x00, 0x50, 0x30, 0x00, 0x00,// ,
	0x08, 0x08, 0x08, 0x08, 0x08,// -
	0x00, 0x60, 0x60, 0x00, 0x00,// .
	0x20, 0x10, 0x08, 0x04, 0x02,// /
	0x3E, 0x51, 0x49, 0x45, 0x3E,// 0
	0x00, 0x42, 0x7F, 0x40, 0x00,// 1
	0x42, 0x61, 0x51, 0x49, 0x46,// 2
	0x21, 0x41, 0x45, 0x4B, 0x31,// 3
	0x18, 0x14, 0x12, 0x7F, 0x10,// 4
	0x27, 0x45, 0x45, 0x45, 0x39,// 5
	0x3C, 0x4A, 0x49, 0x49, 0x30,// 6
	0x01, 0x71, 0x09, 0x05, 0x03,// 7
	0x36, 0x49, 0x49, 0x49, 0x36,// 8
	0x06, 0x49, 0x49, 0x29, 0x1E,// 9
	0x00, 0x36, 0x36, 0x00, 0x00,// :
	0x00, 0x56, 0x36, 0x00, 0x00,// ;
	0x00, 0x08, 0x14, 0x22, 0x41,// <
	0x14, 0x14, 0x14, 0x14, 0x14,// =
	0x41, 0x22, 0x14, 0x08, 0x00,// >
	0x02, 0x01, 0x51, 0x09, 0x06,// ?
	0x32, 0x49, 0x79, 0x41, 0x3E,// @
	0x7E, 0x11, 0x11, 0x11, 0x7E,// A
	0x7F, 0x49, 0x49, 0x49, 0x36,// B
	0x3E, 0x41, 0x41, 0x41, 0x22,// C
	0x7F, 0x41, 0x41, 0x22, 0x1C,// D
	0x7F, 0x49, 0x49, 0x49, 0x41,// E
	0x7F, 0x09, 0x09, 0x01, 0x01,// F
	0x3E, 0x41, 0x41, 0x51, 0x32,// G
	0x7F, 0x08, 0x08, 0x08, 0x7F,// H
	0x00, 0x41, 0x7F, 0x41, 0x00,// I
	0x20, 0x40, 0x41, 0x3F, 0x01,// J
	0x7F, 0x08, 0x14, 0x22, 0x41,// K
	0x7F, 0x40, 0x40, 0x40, 0x40,// L
	0x7F, 0x02, 0x04, 0x02, 0x7F,// M
	0x7F, 0x04, 0x08, 0x10, 0x7F,// N
	0x3E, 0x41, 0x41, 0x41, 0x3E,// O
	0x7F, 0x09, 0x09, 0x09, 0x06,// P
	0x3E, 0x41, 0x51, 0x21, 0x5E,// Q
	0x7F, 0x09, 0x19, 0x29, 0x46,// R
	0x46, 0x49, 0x49, 0x49, 0x31,// S
	0x01, 0x01, 0x7F, 0x01, 0x01,// T
	0x3F, 0x40, 0x40, 0x40, 0x3F,// U
	0x1F, 0x20, 0x40, 0x20, 0x1F,// V
	0x7F, 0x20, 0x18, 0x20, 0x7F,// W
	0x63, 0x14, 0x08, 0x14, 0x63,// X
	0x03, 0x04, 0x78, 0x04, 0x03,// Y
	0x61, 0x51, 0x49, 0x45, 0x43,// Z
	0x00, 0x00, 0x7F, 0x41, 0x41,// [
	0x02, 0x04, 0x08, 0x10, 0x20,// "\"
	0x41, 0x41, 0x7F, 0x00, 0x00,// ]
	0x04, 0x02, 0x01, 0x02, 0x04,// ^
	0x40, 0x40, 0x40, 0x40, 0x40,// _
	0x00, 0x01, 0x02, 0x04, 0x00,// `
	0x20, 0x54, 0x54, 0x54, 0x78,// a
	0x7F, 0x48, 0x44, 0x44, 0x38,// b
	0x38, 0x44, 0x44, 0x44, 0x20,// c
	0x38, 0x44, 0x44, 0x48, 0x7F,// d
	0x38, 0x54, 0x54, 0x54, 0x18,// e
	0x08, 0x7E, 0x09, 0x01, 0x02,// f
	0x08, 0x14, 0x54, 0x54, 0x3C,// g
	0x7F, 0x08, 0x04, 0x04, 0x78,// h
	0x00, 0x44, 0x7D, 0x40, 0x00,// i
	0x20, 0x40, 0x44, 0x3D, 0x00,// j
	0x00, 0x7F, 0x10, 0x28, 0x44,// k
	0x00, 0x41, 0x7F, 0x40, 0x00,// l
	0x7C, 0x04, 0x18, 0x04, 0x78,// m
	0x7C, 0x08, 0x04, 0x04, 0x78,// n
	0x38, 0x44, 0x44, 0x44, 0x38,// o
	0x7C, 0x14, 0x14, 0x14, 0x08,// p
	0x08, 0x14, 0x14, 0x18, 0x7C,// q
	0x7C, 0x08, 0x04, 0x04, 0x08,// r
	0x48, 0x54, 0x54, 0x54, 0x20,// s
	0x04, 0x3F, 0x44, 0x40, 0x20,// t
	0x3C, 0x40, 0x40, 0x20, 0x7C,// u
	0x1C, 0x20, 0x40, 0x20, 0x1C,// v
	0x3C, 0x40, 0x30, 0x40, 0x3C,// w
	0x44, 0x28, 0x10, 0x28, 0x44,// x
	0x0C, 0x50, 0x50, 0x50, 0x3C,// y
	0x44, 0x64, 0x54, 0x4C, 0x44,// z
	0x00, 0x08, 0x36, 0x41, 0x00,// {
	0x00, 0x00, 0x7F, 0x00, 0x00,// |
	0x00, 0x41, 0x36, 0x08, 0x00,// }
	0x02, 0x01, 0x02, 0x04, 0x02,// ~
	0xff, 0xff, 0xff, 0xff, 0xff,// black block
	0x03, 0x03, 0x38, 0x44, 0x44,// "'c"
};

void delay(int i) {
	while (i--);
}

void SSD1306_WriteCmd(u8 cmd) {
	I2C_AcknowledgeConfig(I2C2, ENABLE);
	
	I2C_GenerateSTART(I2C2, ENABLE);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));

	// 0x78 - The device's IIC address
	I2C_Send7bitAddress(I2C2, 0x78, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	// 0x00 - After this byte is command
	I2C_SendData(I2C2, 0x00);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_SendData(I2C2, cmd);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_GenerateSTOP(I2C2, ENABLE);
}

void SSD1306_WriteData(u8 *data, int size) {
	int i;
	
	I2C_AcknowledgeConfig(I2C2, ENABLE);
	
	I2C_GenerateSTART(I2C2, ENABLE);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));

	// 0x78 - The device's IIC address
	I2C_Send7bitAddress(I2C2, 0x78, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	// 0x40 - After this byte is data
	I2C_SendData(I2C2, 0x40);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	for (i=0;i<size;i++) {
		I2C_SendData(I2C2, data[i]);
		while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	}

	I2C_GenerateSTOP(I2C2, ENABLE);
}

void SHT30_Write(u8 msb, u8 lsb) {
	I2C_AcknowledgeConfig(I2C2, ENABLE);
	
	I2C_GenerateSTART(I2C2, ENABLE);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C2, 0x88, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	I2C_SendData(I2C2, msb);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	I2C_SendData(I2C2, lsb);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	I2C_GenerateSTOP(I2C2, ENABLE);	
}

int SHT30_ReadTempAndHumi(u8 *data) {
	int i;
	
	I2C_AcknowledgeConfig(I2C2, ENABLE);
	
	I2C_GenerateSTART(I2C2, ENABLE);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C2, 0x88, I2C_Direction_Transmitter);
	i = 0;
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) {
		if (++i > 200) {
			return -1;
		}
	}
	
	I2C_SendData(I2C2, 0xE0);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_SendData(I2C2, 0x00);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	I2C_GenerateSTART(I2C2, ENABLE);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C2, 0x89, I2C_Direction_Receiver);
	i = 0;
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)) {
		if (++i > 200) {
			return -1;
		}
	}
	
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED));
	data[0] = I2C_ReceiveData(I2C2);
	
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED));
	data[1] = I2C_ReceiveData(I2C2);

	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED));
	data[2] = I2C_ReceiveData(I2C2);

	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED));
	data[3] = I2C_ReceiveData(I2C2);
	
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED));
	data[4] = I2C_ReceiveData(I2C2);

	I2C_AcknowledgeConfig(I2C2, DISABLE);

	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED));
	data[5] = I2C_ReceiveData(I2C2);

	I2C_GenerateSTOP(I2C2, ENABLE);	
	I2C_AcknowledgeConfig(I2C2, ENABLE);
	
	return 0;
}

int main(void) {
	int i;
	u8 data[6];
	int temp;
	int humi;
	
	GPIO_InitTypeDef GPIO_InitStructure;
	I2C_InitTypeDef  I2C_initStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_10 | GPIO_Pin_11);
	
	I2C_initStructure.I2C_ClockSpeed = 400000; // 400KHz
	I2C_initStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_initStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_initStructure.I2C_OwnAddress1 = 0x77;
	I2C_initStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_initStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Init(I2C2, &I2C_initStructure);
	
	I2C_Cmd(I2C2, ENABLE);

	delay(100000);
	
	SSD1306_WriteCmd(0x00);	
	SSD1306_WriteCmd(0x10);
	SSD1306_WriteCmd(0x20);
	SSD1306_WriteCmd(0x00);	
	SSD1306_WriteCmd(0x8D);
	SSD1306_WriteCmd(0x14);
	SSD1306_WriteCmd(0xA1); 
	SSD1306_WriteCmd(0xC8);
	SSD1306_WriteCmd(0xAF);

	// Clear screen
	SSD1306_WriteCmd(0x21);
	SSD1306_WriteCmd(0);
	SSD1306_WriteCmd(127);

	SSD1306_WriteCmd(0x22);
	SSD1306_WriteCmd(0);
	SSD1306_WriteCmd(7);

	for (i=0;i<128*8;i++) {
		SSD1306_WriteData(&font5x7_seperator, 1);
	}

	// Set Repeatability High, mps 1
	SHT30_Write(0x21, 0x30);	
	
	while (1) {
		delay(10000000);

		SHT30_ReadTempAndHumi(data);
		temp = -450 + 1750 * (data[0] * 256 + data[1]) / 0xffff;
		humi = 1000 * (data[3] * 256 + data[4]) / 0xffff;

		SSD1306_WriteCmd(0x21);
		SSD1306_WriteCmd(45);    // X
		SSD1306_WriteCmd(127);
		
		SSD1306_WriteCmd(0x22);
		SSD1306_WriteCmd(2);     // Y
		SSD1306_WriteCmd(2);

		SSD1306_WriteData(&font5x7[('T'-' ')*5], 5);
		SSD1306_WriteData(&font5x7_seperator, 1);
		SSD1306_WriteData(&font5x7[(' '-' ')*5], 5);
		SSD1306_WriteData(&font5x7_seperator, 1);
		SSD1306_WriteData(&font5x7[('0'-' '+((temp/100)%10))*5], 5);
		SSD1306_WriteData(&font5x7_seperator, 1);
		SSD1306_WriteData(&font5x7[('0'-' '+((temp/10)%10))*5], 5);
		SSD1306_WriteData(&font5x7_seperator, 1);
		SSD1306_WriteData(&font5x7[('.'-' ')*5], 5);
		SSD1306_WriteData(&font5x7_seperator, 1);
		SSD1306_WriteData(&font5x7[('0'-' '+((temp/1)%10))*5], 5);
		SSD1306_WriteData(&font5x7_seperator, 1);
		SSD1306_WriteData(&font5x7[('~'-' '+2)*5], 5);
		SSD1306_WriteData(&font5x7_seperator, 1);
		
		SSD1306_WriteCmd(0x21);
		SSD1306_WriteCmd(45);    // X
		SSD1306_WriteCmd(127);
		
		SSD1306_WriteCmd(0x22);
		SSD1306_WriteCmd(5);     // Y
		SSD1306_WriteCmd(5);

		SSD1306_WriteData(&font5x7[('H'-' ')*5], 5);
		SSD1306_WriteData(&font5x7_seperator, 1);
		SSD1306_WriteData(&font5x7[(' '-' ')*5], 5);
		SSD1306_WriteData(&font5x7_seperator, 1);
		SSD1306_WriteData(&font5x7[('0'-' '+((humi/100)%10))*5], 5);
		SSD1306_WriteData(&font5x7_seperator, 1);
		SSD1306_WriteData(&font5x7[('0'-' '+((humi/10)%10))*5], 5);
		SSD1306_WriteData(&font5x7_seperator, 1);
		SSD1306_WriteData(&font5x7[('.'-' ')*5], 5);
		SSD1306_WriteData(&font5x7_seperator, 1);
		SSD1306_WriteData(&font5x7[('0'-' '+((humi/1)%10))*5], 5);
		SSD1306_WriteData(&font5x7_seperator, 1);
		SSD1306_WriteData(&font5x7[('%'-' ')*5], 5);
		SSD1306_WriteData(&font5x7_seperator, 1);
	}
}
