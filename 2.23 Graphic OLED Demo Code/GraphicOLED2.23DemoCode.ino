/*****************************************************************************
 
 Program for writing to Newhaven Display's NHD - 2.23 OLED
 This code is written for the Arduino Uno.
 Copyright (c) 2021 - Newhaven Display International, Inc.
 Newhaven Display invests time and resources providing this open source code,
 please support Newhaven Display by purchasing products from Newhaven Display!
 Author: Zachary Palrang - Applications Engineer
 
 *****************************************************************************/

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Serial Interface 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#define OLED_DC     8  //Register Select signal
#define OLED_RESET  9  //Reset signal
#define OLED_CS     10 //Chip select signal
#define OLED_SDIN   11 //Serial data signal
#define OLED_CLK    13 //Serial clock signal

/****************************************************
*             Hex Table for Example Images           *
*****************************************************/
const unsigned char NHD_Logo [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x38, 0x38, 0x10, 0x90, 0x50,
0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x00, 0xF0, 0x30, 0xC0, 0x00, 0xF0, 0x00, 0x00, 0xF0, 0x50,
0x50, 0x50, 0x00, 0x00, 0x10, 0xF0, 0x00, 0xE0, 0x10, 0xC0, 0x80, 0x70, 0x00, 0x00, 0x00, 0xF0,
0x40, 0x40, 0xF0, 0x00, 0x00, 0x80, 0xE0, 0x90, 0xE0, 0x80, 0x00, 0x00, 0x30, 0xE0, 0x00, 0xE0,
0x30, 0x00, 0x00, 0xF0, 0x50, 0x50, 0x50, 0x00, 0x00, 0x00, 0xF0, 0x30, 0xC0, 0xF0, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0x10, 0x10, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00,
0x70, 0x50, 0x50, 0x50, 0xD0, 0x00, 0x00, 0x00, 0xF0, 0x50, 0x50, 0x70, 0x00, 0x00, 0x00, 0xF0,
0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 0x90, 0xE0, 0x80, 0x00, 0x00, 0x30, 0xE0, 0x60, 0x30, 0x00,
0x00, 0x70, 0x70, 0x60, 0x20, 0x22, 0x27, 0x27, 0x22, 0x22, 0x22, 0x12, 0x11, 0x09, 0x04, 0x02,
0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01,
0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01,
0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
0x01, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char Field [] = {
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x12, 0x1F, 0x10, 0x0E, 0x11, 0x11,
0x0E, 0xFF, 0x00, 0x00, 0x00, 0x12, 0x19, 0x15, 0x13, 0x0E, 0x11, 0x11, 0x0E, 0xFF, 0x00, 0x00,
0x00, 0x00, 0x15, 0x15, 0x1B, 0x0E, 0x11, 0x11, 0x0E, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x07, 0x04,
0x1F, 0x0E, 0x11, 0x11, 0x0E, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x17, 0x15, 0x1D, 0x0E, 0x11, 0x11,
0x0E, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x07, 0x04, 0x1F, 0x0E, 0x11, 0x11, 0x0E, 0xFF, 0x00, 0x00,
0x00, 0x00, 0x15, 0x15, 0x1B, 0x0E, 0x11, 0x11, 0x0E, 0xFF, 0x00, 0x00, 0x00, 0x12, 0x19, 0x15,
0x13, 0x0E, 0x11, 0x11, 0x0E, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x12, 0x1F, 0x10, 0x0E, 0x11, 0x11,
0x0E, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x70, 0x88, 0x88, 0x70, 0x08, 0xF8, 
0x48, 0xFF, 0x00, 0x00, 0x00, 0x70, 0x88, 0x88, 0x70, 0xC8, 0xA8, 0x98, 0x48, 0xFF, 0x00, 0x00, 
0x00, 0x00, 0x70, 0x88, 0x88, 0x70, 0xD8, 0xA8, 0xA8, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x70, 0x88, 
0x88, 0x70, 0xF8, 0x20, 0xE0, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x70, 0x88, 0x88, 0x70, 0xB8, 0xA8, 
0xE8, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x70, 0x88, 0x88, 0x70, 0xF8, 0x20, 0xE0, 0xFF, 0x00, 0x00, 
0x00, 0x00, 0x70, 0x88, 0x88, 0x70, 0xD8, 0xA8, 0xA8, 0xFF, 0x00, 0x00, 0x00, 0x70, 0x88, 0x88,
0x70, 0xC8, 0xA8, 0x98, 0x48, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x70, 0x88, 0x88, 0x70, 0x08, 0xF8, 
0x48, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

const unsigned char USA_FLAG [] = {
0xFF, 0x01, 0x01,0x01,  0x01, 0x01, 0x01, 0x01, 0xF1, 0x01, 0x01, 0xF1, 0x01, 0x01, 0x61, 0x91, 
0x11, 0x61, 0x01, 0x01, 0xE1, 0x91, 0x91, 0xE1, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0xFF, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x08, 0x07, 0x00, 0x00, 0x06, 0x08, 
0x09, 0x06, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xFF, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xFF, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
0xFF, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F,
0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F,
0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F,
0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F,
0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F,
0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F,
0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F,
0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F
};



/****************************************************
*                 Function Commands                  *
*****************************************************/

void data_out(unsigned char d) //Data Output Serial Interface
{
   unsigned int n;
            digitalWrite(OLED_CS, LOW); 
            digitalWrite(OLED_DC, HIGH); 
            for(n=0;n<8;n++){
              if((d&0x80)==0x80)
              PORTB |=(1<< PORTB3);  //digitalWrite(OLED_SDIN, HIGH);
              else
              PORTB &= ~(1<<PORTB3); //digitalWrite(OLED_SDIN, LOW);
              while(0);
              d=(d<<1);
              PORTB &= ~(1<<PORTB5); //digitalWrite(OLED_CLK, LOW);
              while(0);
              PORTB |=(1<< PORTB5);  //digitalWrite(OLED_CLK, HIGH);
              while(0); 
              PORTB &= ~(1<<PORTB5); //digitalWrite(OLED_CLK, LOW);
              }
            digitalWrite(OLED_CS, HIGH); 
     
}

void comm_out(unsigned char d) //Command Output Serial Interface
{
  unsigned int n;
            digitalWrite(OLED_CS, LOW); 
            digitalWrite(OLED_DC, LOW); 
            for(n=0;n<8;n++){
              if((d&0x80)==0x80)
              PORTB |=(1<< PORTB3);  //digitalWrite(OLED_SDIN, HIGH);
              else
              PORTB &= ~(1<<PORTB3); //digitalWrite(OLED_SDIN, LOW);
              while(0);
              d=(d<<1);
              PORTB &= ~(1<<PORTB5); //digitalWrite(OLED_CLK, LOW);
              while(0);
              PORTB |=(1<< PORTB5);  //digitalWrite(OLED_CLK, HIGH);
              while(0);
              PORTB &= ~(1<<PORTB5); //digitalWrite(OLED_CLK, LOW); 
              }
            digitalWrite(OLED_CS, HIGH);
            
}



void Set_Start_Column_12832(unsigned char d)
{
  comm_out(0x00+d%16);    // Set Lower Column Start Address for Page Addressing Mode
            //   Default => 0x00
  comm_out(0x10+d/16);    // Set Higher Column Start Address for Page Addressing Mode
            //   Default => 0x10
}
//--------------------------------------------------------------------------

void Set_Addressing_Mode_12832(unsigned char d)
{
  comm_out(0x20);     // Set Memory Addressing Mode
  comm_out(d);      //   Default => 0x02
            //     0x00 => Horizontal Addressing Mode
            //     0x01 => Vertical Addressing Mode
            //     0x02 => Page Addressing Mode
}
//--------------------------------------------------------------------------

void Set_Column_Address_12832(unsigned char a, unsigned char b)
{
  comm_out(0x21);     // Set Column Address
  comm_out(a);      //   Default => 0x00 (Column Start Address)
  comm_out(b);      //   Default => 0x83 (Column End Address)
}
//--------------------------------------------------------------------------

void Set_Page_Address_12832(unsigned char a, unsigned char b)
{
  comm_out(0x22);     // Set Page Address
  comm_out(a);      //   Default => 0x00 (Page Start Address)
  comm_out(b);      //   Default => 0x07 (Page End Address)
}
//--------------------------------------------------------------------------

void Set_Start_Line_12832(unsigned char d)
{
  comm_out(0x40|d);     // Set Display Start Line
                      //   Default => 0x40 (0x00)
}
//--------------------------------------------------------------------------

void Set_Contrast_Control_12832(unsigned char d)
{
  comm_out(0x81);     // Set Contrast Control for Bank 0
  comm_out(d);      //   Default => 0x80
}
//--------------------------------------------------------------------------

void Set_Area_Brightness_12832(unsigned char d)
{
  comm_out(0x82);     // Set Brightness for Area Color Banks
  comm_out(d);      //   Default => 0x80
}
//--------------------------------------------------------------------------

void Set_Segment_Remap_12832(unsigned char d)
{
  comm_out(0xA0|d);     // Set Segment Re-Map
            //     Default => 0xA0
            //     0xA0 (0x00) => Column Address 0 Mapped to SEG0
            //     0xA1 (0x01) => Column Address 0 Mapped to SEG131
}
//--------------------------------------------------------------------------

void Set_Entire_Display_12832(unsigned char d)
{
  comm_out(0xA4|d);     // Set Entire Display On / Off
            //     Default => 0xA4
            //     0xA4 (0x00) => Normal Display
            //     0xA5 (0x01) => Entire Display On
}
//--------------------------------------------------------------------------

void Set_Inverse_Display_12832(unsigned char d)
{
  comm_out(0xA6|d);     // Set Inverse Display On/Off
            //     Default => 0xA6
            //     0xA6 (0x00) => Normal Display
            //     0xA7 (0x01) => Inverse Display On
}
//--------------------------------------------------------------------------

void Set_Multiplex_Ratio_12832(unsigned char d)
{
  comm_out(0xA8);     // Set Multiplex Ratio
  comm_out(d);      //   Default => 0x3F (1/64 Duty)
}
//--------------------------------------------------------------------------

void Set_Dim_Mode_12832(unsigned char a, unsigned char b)
{
  comm_out(0xAB);     // Set Dim Mode Configuration
  comm_out(0X00);     //           => (Dummy Write for First Parameter)
  comm_out(a);      //   Default => 0x80 (Contrast Control for Bank 0)
  comm_out(b);      //   Default => 0x80 (Brightness for Area Color Banks)
  comm_out(0xAC);     // Set Display On in Dim Mode
}
//--------------------------------------------------------------------------

void Set_Master_Config_12832(unsigned char d)
{
  comm_out(0xAD);     // Set Master Configuration
  comm_out(0x8E|d);     //   Default => 0x8E
            //     0x8E (0x00) => Select External VCC Supply
            //     0x8F (0x01) => Select Internal DC/DC Voltage Converter
}
//--------------------------------------------------------------------------

void Set_Display_On_Off_12832(unsigned char d)  
{
  comm_out(0xAE|d);     // Set Display On/Off
            //     Default => 0xAE
            //     0xAE (0x00) => Display Off
            //     0xAF (0x01) => Display On
}
//--------------------------------------------------------------------------

void Set_Start_Page_12832(unsigned char d)
{
  comm_out(0xB0|d);     // Set Page Start Address for Page Addressing Mode
            //   Default => 0xB0 (0x00)
}
//--------------------------------------------------------------------------

void Set_Common_Remap_12832(unsigned char d)
{
  comm_out(0xC0|d);     // Set COM Output Scan Direction
            //     Default => 0xC0
            //     0xC0 (0x00) => Scan from COM0 to 63
            //     0xC8 (0x08) => Scan from COM63 to 0
}
//--------------------------------------------------------------------------

void Set_Display_Offset_12832(unsigned char d)
{
  comm_out(0xD3);     // Set Display Offset
  comm_out(d);      //   Default => 0x00
}
//--------------------------------------------------------------------------

void Set_Display_Clock_12832(unsigned char d)
{
  comm_out(0xD5);     // Set Display Clock Divide Ratio / Oscillator Frequency
  comm_out(d);      //   Default => 0x70
            //     D[3:0] => Display Clock Divider
            //     D[7:4] => Oscillator Frequency
}
//--------------------------------------------------------------------------

void Set_Area_Color_12832(unsigned char d)
{
  comm_out(0xD8);     // Set Area Color Mode On/Off & Low Power Display Mode
  comm_out(d);      //   Default => 0x00 (Monochrome Mode & Normal Power Display Mode)
}
//--------------------------------------------------------------------------

void Set_Precharge_Period_12832(unsigned char d)
{
  comm_out(0xD9);     // Set Pre-Charge Period
  comm_out(d);      //   Default => 0x22 (2 Display Clocks [Phase 2] / 2 Display Clocks [Phase 1])
            //     D[3:0] => Phase 1 Period in 1~15 Display Clocks
            //     D[7:4] => Phase 2 Period in 1~15 Display Clocks
}
//--------------------------------------------------------------------------

void Set_Common_Config_12832(unsigned char d)
{
  comm_out(0xDA);     // Set COM Pins Hardware Configuration
  comm_out(0x02|d); //   Default => 0x12 (0x10)
            //     Alternative COM Pin Configuration
            //     Disable COM Left/Right Re-Map
}
//--------------------------------------------------------------------------

void Set_VCOMH_12832(unsigned char d)
{
  comm_out(0xDB);     // Set VCOMH Deselect Level
  comm_out(d);      //   Default => 0x34 (0.77*VCC)
}
//--------------------------------------------------------------------------

void Set_Read_Modify_Write_12832(unsigned char d)
{
  comm_out(0xE0|d);     // Set Read Modify Write Mode
            //     Default => 0xE0
            //     0xE0 (0x00) => Enter Read Modify Write
            //     0xEE (0x0E) => Exit Read Modify Write
}
//--------------------------------------------------------------------------

void Set_NOP_12832()
{
  comm_out(0xE3);     // Command for No Operation
}
//--------------------------------------------------------------------------


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Show Checkboard (Full Screen)
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Checkerboard_12832()
{
unsigned char i,j;
  
  for(i=0;i<4;i++)
  {
    Set_Start_Page_12832(i);
    Set_Start_Column_12832(0x00);

    for(j=0;j<66;j++)
    {
      data_out(0x55);
      data_out(0xaa);
    }
  }
}
void Checkerboard_12832INVERSE() // Fills Inverse Boxes
{
unsigned char i,j;
  
  for(i=0;i<4;i++)
  {
    Set_Start_Page_12832(i);
    Set_Start_Column_12832(0x00);

    for(j=0;j<66;j++)
    {
      data_out(0xAA);
      data_out(0x55);
    }
  }
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Show Regular Pattern (Full Screen)
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Fill_RAM_12832(unsigned char Data)
{
unsigned char i,j;

  for(i=0;i<4;i++)
  {
    Set_Start_Page_12832(i);
    Set_Start_Column_12832(0x00);

    for(j=0;j<132;j++)
    {
      data_out(Data);
    }
  }
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Show Image (Full Screen)
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

void ImageDisplay(const unsigned char *image)
{
  unsigned int i,j;
  for(i=0;i<4;i++){       
    Set_Start_Page_12832(i);
    Set_Start_Column_12832(0x04);
    for(j=0;j<128;j++){     //128 columns wide
      data_out(*image);    //send picture data
      image++; 
    }
  }
}


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Show Regular Pattern (Partial or Full Screen)
//
//    a: Start Page
//    b: End Page
//    c: Start Column
//    d: Total Columns
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Fill_Block_12832(unsigned char Data, unsigned char a, unsigned char b, unsigned char c, unsigned char d)
{
unsigned char i,j;
  
  for(i=a;i<(b+1);i++)
  {
    Set_Start_Page_12832(i);
    Set_Start_Column_12832(c);

    for(j=0;j<d;j++)
    {
      data_out(Data);
    }
  }
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Bank Color & Look Up Table Setting (Partial Screen)
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Set_LUT_12832(unsigned char a, unsigned char b, unsigned char c, unsigned char d)
{
  comm_out(0x91);     // Define Look Up Table of Area Color
  comm_out(a);      //   Define Bank 0 Pulse Width
  comm_out(b);      //   Define Color A Pulse Width
  comm_out(c);      //   Define Color B Pulse Width
  comm_out(d);      //   Define Color C Pulse Width
}


void Set_Bank_Color_12832()
{
  comm_out(0x92);     // Define Area Color for Bank 1~16 (Page 0)
  comm_out(0x00);     //   Define Bank 1~4 as Color A
  comm_out(0x55);     //   Define Bank 5~8 as Color B
  comm_out(0xAA);     //   Define Bank 9~12 as Color C
  comm_out(0xFF);     //   Define Bank 13~16 as Color D

  comm_out(0x93);     // Define Area Color for Bank 17~32 (Page 1)
  comm_out(0xFF);     //   Define Bank 17~32 as Color D
  comm_out(0xFF);
  comm_out(0xFF);
  comm_out(0xFF);
}


/****************************************************
*           Initialization For controller           *
*****************************************************/

void OLED_Init_12832()
{
  
  unsigned char i;
  unsigned char Max_Column = 128;
  unsigned char Max_Row = 32; 
  unsigned char Brightness = 0xBF;
  unsigned char XLevelL = 0x04;
  unsigned char XLevelH = 0x10;
  Set_Display_On_Off_12832(0x00);         // Display Off (0x00/0x01) 
  Set_Display_Clock_12832(0x10);          // Set Clock as 160 Frames/Sec
  Set_Multiplex_Ratio_12832(0x1F);        // 1/32 Duty (0x0F~0x3F)
  Set_Display_Offset_12832(0x00);         // Shift Mapping RAM Counter (0x00~0x3F)
  Set_Start_Line_12832(0x00);             // Set Mapping RAM Display Start Line (0x00~0x3F)
  Set_Master_Config_12832(0x00);          // Disable Embedded DC/DC Converter (0x00/0x01)
  Set_Area_Color_12832(0x05);             // Set Monochrome & Low Power Save Mode
  Set_Addressing_Mode_12832(0x02);        // Set Page Addressing Mode (0x00/0x01/0x02)
  Set_Segment_Remap_12832(0x01);          // Set SEG/Column Mapping (0x00/0x01)
  Set_Common_Remap_12832(0x08);           // Set COM/Row Scan Direction (0x00/0x08)
  Set_Common_Config_12832(0x10);          // Set Alternative Configuration (0x00/0x10)
  Set_LUT_12832(0x3F,0x3F,0x3F,0x3F);     // Define All Banks Pulse Width as 64 Clocks
  Set_Contrast_Control_12832(Brightness); // Set SEG Output Current
  Set_Area_Brightness_12832(Brightness);  // Set Brightness for Area Color Banks  
  Set_Precharge_Period_12832(0xD2);       // Set Pre-Charge as 13 Clocks & Discharge as 2 Clock
  Set_VCOMH_12832(0x08);                  // Set VCOM Deselect Level
  Set_Entire_Display_12832(0x00);         // Disable Entire Display On (0x00/0x01)
  Set_Inverse_Display_12832(0x00);        // Disable Inverse Display On (0x00/0x01)

  Fill_RAM_12832(0xff);                   // Clear Screen

  Set_Display_On_Off_12832(0x01);         // Display On (0x00/0x01)
}

/*****************************************************
*           Setup Function, to run once              *
*****************************************************/

void setup()
{
  DDRB |= (1<<DDB5); //Enable CLK as Output
  DDRB |= (1<<DDB3); //Enable SDIN / SDA_IN as Output

  pinMode(OLED_RESET, OUTPUT);  // Declaring pin outputs
  pinMode(OLED_CS, OUTPUT);
  pinMode(OLED_DC, OUTPUT);
  pinMode(OLED_SDIN, OUTPUT);  
  digitalWrite(OLED_RESET, LOW);
  delay(150);
  digitalWrite(OLED_RESET, HIGH);
  delay(150);
  OLED_Init_12832(); //Initialization Sequence
  Set_Column_Address_12832(0x00,0x83);}
 
  
            



/*****************************************************
*           Loop Function, to run repeatedly         *
*****************************************************/

void loop() {
  ImageDisplay(NHD_Logo);  // Newhaven logo
  delay(5000);
  ImageDisplay(Field);  // Basic design of american football field
  delay(5000);
  ImageDisplay(USA_FLAG); // Flag function w/ USA located in Top Left
  delay(5000);
  Checkerboard_12832(); // Fill squares w/ space between appearing as checkerboard
  delay(5000);
  Checkerboard_12832INVERSE(); // Inverse of Checkerboard
  delay(5000);}
