/*
 /*****************************************************************************
 
 Program for writing to Newhaven Display's NHD - 2.23 OLED
 This code is written for the Arduino Uno.
 Copyright (c) 2021 - Newhaven Display International, Inc.
 Newhaven Display invests time and resources providing this open source code,
 please support Newhaven Display by purchasing products from Newhaven Display!
 Author: Zachary Palrang - Applications Engineer
 
 *****************************************************************************/
 */

#define DC   8
#define RW   9
#define WR   9
#define E   10
#define RD  10
#define RES 11
#define CS  12
#define BS2 A0
#define BS1 A1

const unsigned char interface = 1; // 0 = 6800, 1 = 8080

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

/****************************************************
*                  Short ASCII Table                *
*****************************************************/

unsigned char Ascii[8][5]={     // Refer to "Times New Roman" Font Database...
                        //   Basic Characters

    {0x3E,0x49,0x49,0x49,0x30},     //   ( 0)   6
    {0x3E,0x49,0x49,0x49,0x3E},     //   ( 1)   8
    {0x3E,0x41,0x41,0x41,0x3E},     //   ( 2)   0
    {0x3E,0x41,0x41,0x41,0x3E},     //   ( 3)   0
   
    
    {0x3E,0x49,0x49,0x49,0x3E},     //   ( 4)   8
    {0x3E,0x41,0x41,0x41,0x3E},     //   ( 5)   0
    {0x3E,0x49,0x49,0x49,0x3E},     //   ( 6)   8
    {0x3E,0x41,0x41,0x41,0x3E},     //   ( 7)   0 
      
};

void comm_out(unsigned char c){
  switch(interface)
   {
      case 0:   digitalWrite(CS, LOW);               
                digitalWrite(DC, LOW);
                PORTD = c;
                digitalWrite(RW, LOW);
                digitalWrite(E, HIGH);
                digitalWrite(E, LOW);
                digitalWrite(CS, HIGH);
                break;
      case 1:   digitalWrite(CS, LOW);               
                digitalWrite(DC, LOW);
                PORTD = c;
                digitalWrite(WR, LOW);
                digitalWrite(WR, HIGH);
                digitalWrite(CS, HIGH);
                break;
                default:break;}}

void data_out(unsigned char d){
   switch(interface)
   {
      case 0:   digitalWrite(CS, LOW);
                digitalWrite(DC, HIGH);
                PORTD = d;
                digitalWrite(RW, LOW);
                digitalWrite(E, HIGH);
                digitalWrite(E, LOW);
                digitalWrite(CS, HIGH);
                break;
      case 1:   digitalWrite(CS, LOW);               
                digitalWrite(DC, HIGH);
                PORTD = d;
                digitalWrite(WR, LOW);
                digitalWrite(WR, HIGH);
                digitalWrite(CS, HIGH);
                break;
                default:break;
}}

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
void Checkerboard_12832INVERSE()
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
//  Call ASCII Letter from Software Font Table 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

void Show_Letter(unsigned char page, unsigned char column, unsigned char Letter)
{
  int i;
  int count = 0;

  Set_Start_Page_12832(page);
  Set_Start_Column_12832(column);

  for(i=0;i<5;i++)
  {
    data_out(Ascii[Letter][count]);
    count++;
  }
  data_out(0x00);         //Space
  delay(50);
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
  digitalWrite(RES,LOW);
  delay(100);
  digitalWrite(RES,HIGH);
  delay(100);
  
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

void setup() {
  DDRD = 0xFF; // Pins 0-7 are DB0-DB7
  pinMode(DC, OUTPUT);
  pinMode(RES, OUTPUT);
  pinMode(CS,OUTPUT);
  pinMode(BS2,OUTPUT);
  pinMode(BS1,OUTPUT);
  digitalWrite(CS,HIGH);
  switch(interface)
  {
    case 0: 
            pinMode(RW,OUTPUT);
            pinMode(E,OUTPUT);
            digitalWrite(BS2,HIGH);
            digitalWrite(BS1,LOW);
            digitalWrite(RW,LOW);
            digitalWrite(E,HIGH);
            break;
    case 1:
            pinMode(WR,OUTPUT);
            pinMode(RD,OUTPUT);
            digitalWrite(BS2,HIGH);
            digitalWrite(BS1,HIGH);
            digitalWrite(WR,HIGH);
            digitalWrite(RD,HIGH);
            break;
            default:break;}

  OLED_Init_12832();
  Set_Column_Address_12832(0x00,0x83);
  delay(500);
  ImageDisplay(NHD_Logo);

  switch(interface)
  {
    case 0:
            Show_Letter(0x03,0x38,0); //6
            Show_Letter(0x03,0x3E,1); //8
            Show_Letter(0x03,0x44,2); //0
            Show_Letter(0x03,0x4A,3); //0
            break;
    case 1:
            Show_Letter(0x03,0x38,4); //8
            Show_Letter(0x03,0x3E,5); //0
            Show_Letter(0x03,0x44,6); //8
            Show_Letter(0x03,0x4A,7); //0
            break;
            default:break;
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
