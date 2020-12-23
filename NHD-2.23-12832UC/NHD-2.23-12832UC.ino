/*
/ Program for writing to NHD-2.23-12832 display series with the SSD1305 controller. 
/ This code is written for the Arduino Uno R3 using Serial & I2C Interface
/ Example Code below utilizes port manipulation for Data & Clock lines for faster data transmission. 
/
/ Newhaven Display invests time and resources providing this open source code,
/ Please support Newhaven Display by purchasing products from Newhaven Display!

* Copyright (c) 2020 Alee S, Newhaven Display International
*
* This code is provided as an example only and without any warranty by Newhaven Display. 
* Newhaven Display accepts no responsibility for any issues resulting from its use. 
* The developer of the final application incorporating any parts of this 
* sample code is responsible for ensuring its safe and correct operation
* and for any consequences resulting from its use.
* See the GNU General Public License for more details. 
* 
* Use Vertical Orientation when converting BMP to hex code to display custom image using LCD assistant.  
*/

/****************************************************
*       2.23" OLED Display Interface Selection      *
*****************************************************
**      Adjust to Desired Interface As Necessary   **
****************************************************/

unsigned char mode = 1;  //1 = Serial
                         //2 = I2C

/****************************************************
*     PINOUT: Arduino Uno -> 2.23" OLED Display     *
****************************************************/

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Serial Interface 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#define OLED_DC     8  //Register Select signal
#define OLED_RESET  9  //Reset signal
#define OLED_CS     10 //Chip select signal
#define OLED_SDIN   11 //Serial data signal
#define OLED_CLK    13 //Serial clock signal

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  I2C Interface 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  NOTE: SDAout pin left disconnected.  
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#define OLED_SA0    8  //Slave Address signal
                       // SA0=0 => 0x78 (Write Mode) | 0x79 (Read Mode)
                       // SA0=1 => 0x7A (Write Mode) | 0x7B (Read Mode)
#define OLED_RESET  9  //Reset signal                     
#define OLED_SDA_IN 11 //Serial data in signal |   Tie external 4.7KΩ - 10KΩ pull-up resistor -> Vdd   
#define OLED_CLK    13 //Serial clock signal   |   Tie external 4.7KΩ - 10KΩ pull-up resistor -> Vdd              

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  MPU Interface Signals
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#define BS2        18 //MPU Interface Select 2
#define BS1        19 //MPU Interface Select 1

/****************************************************
*             Hex Table for Example Image           *
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

/****************************************************
*                  Short ASCII Table                *
*****************************************************/

unsigned char Ascii[9][5]={     // Refer to "Times New Roman" Font Database...
                        //   Basic Characters

    {0x46,0x49,0x49,0x49,0x31},     //   ( 0)  S - 0x0053 Latin Capital Letter S
    {0x7F,0x49,0x49,0x49,0x41},     //   ( 1)  E - 0x0045 Latin Capital Letter E
    {0x7F,0x09,0x19,0x29,0x46},     //   ( 2)  R - 0x0052 Latin Capital Letter R
    {0x00,0x41,0x7F,0x41,0x00},     //   ( 3)  I - 0x0049 Latin Capital Letter I
    {0x7E,0x11,0x11,0x11,0x7E},     //   ( 4)  A - 0x0041 Latin Capital Letter A
    {0x7F,0x40,0x40,0x40,0x40},     //   ( 5)  L - 0x004C Latin Capital Letter L

    {0x00,0x41,0x7F,0x41,0x00},     //   ( 6)  I - 0x0049 Latin Capital Letter I
    {0x42,0x61,0x51,0x49,0x46},     //   ( 7)  2 - 0x0032 Digit Two
    {0x3E,0x41,0x41,0x41,0x22},     //   ( 8)  C - 0x0043 Latin Capital Letter C    
};

/****************************************************
*                 Function Commands                  *
*****************************************************/

void data_out(unsigned char d) //Data Output Serial Interface
{
  switch(mode)
  {
    case 1: unsigned int n;
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
            break;
    case 2: I2C_Start_Transmission();
            I2C_Transmission_Out(0x7A);            
            I2C_Ack_Ignore();          
            I2C_Transmission_Out(0x40);
            I2C_Ack_Ignore();        
            I2C_Transmission_Out(d);
            I2C_Ack_Ignore();          
            I2C_Stop_Transmission();
            break;
  }
}

void comm_out(unsigned char d) //Command Output Serial Interface
{
  switch(mode)
  {
    case 1: unsigned int n;
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
            break;
    case 2: I2C_Start_Transmission();
            I2C_Transmission_Out(0x7A);
            I2C_Ack_Ignore();        //SDAout disconnected            
            I2C_Transmission_Out(0x00);
            I2C_Ack_Ignore();        //SDAout disconnected
            I2C_Transmission_Out(d);
            I2C_Ack_Ignore();        //SDAout disconnected
            I2C_Stop_Transmission();
            break;
  }
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  I2C Interface: Set Start Condition 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

void I2C_Start_Transmission()
{
  PORTB |=(1<< PORTB5);  //digitalWrite(OLED_CLK, HIGH);
              while(0);
  PORTB |=(1<< PORTB3);  //digitalWrite(OLED_SDA_IN, HIGH);
              while(0);    
  PORTB &= ~(1<<PORTB3); //digitalWrite(OLED_SDA_IN, LOW);
              while(0);
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  I2C Interface: I2C Byte Transmission Function
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

void I2C_Transmission_Out(unsigned char b)
{
  unsigned int n;
  for(n=0;n<8;n++){
    if((b&0x80)==0x80)
    PORTB |=(1<< PORTB3);  //digitalWrite(OLED_SDA_IN, HIGH);
    else
    PORTB &= ~(1<<PORTB3); //digitalWrite(OLED_SDA_IN, LOW);
    while(0);
    b=(b<<1);
    PORTB &= ~(1<<PORTB5); //digitalWrite(OLED_CLK, LOW);
    while(0);
    PORTB |=(1<< PORTB5);  //digitalWrite(OLED_CLK, HIGH);
    while(0);
    PORTB &= ~(1<<PORTB5); //digitalWrite(OLED_CLK, LOW);
    while(0);
    }  
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Ignore Acknowledgment Function
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  -If SDAout (Pin 9) is disconnected, ACK can be ignored on I2C bus.
//  -Must pulse 1 Clock Cycle to account for ACK signal being ignored. 
//  -For more information, please visit the excerpts and figures on
//    pages 21-24 of the SSD1305 datasheet. 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

void I2C_Ack_Ignore()
{
    PORTB &= ~(1<<PORTB5); //digitalWrite(OLED_CLK, LOW);
    while(0);
    PORTB |=(1<< PORTB5);  //digitalWrite(OLED_CLK, HIGH);
    while(0);    
    PORTB &= ~(1<<PORTB5); //digitalWrite(OLED_CLK, LOW);
    while(0);     
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  I2C Interface: Set Stop Condition
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

void I2C_Stop_Transmission()
{
  PORTB |=(1<< PORTB5);  //digitalWrite(OLED_CLK, HIGH);
  while(0);
  PORTB &= ~(1<<PORTB3); //digitalWrite(OLED_SDA_IN, LOW);
  while(0);
  PORTB |=(1<< PORTB3);  //digitalWrite(OLED_SDA_IN, HIGH);
  while(0);
}

/****************************************************
*                 Display Commands                   *
*****************************************************/

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

void Set_Start_Column_12832(unsigned char d)
{
	comm_out(0x00+d%16);		// Set Lower Column Start Address for Page Addressing Mode
						//   Default => 0x00
	comm_out(0x10+d/16);		// Set Higher Column Start Address for Page Addressing Mode
						//   Default => 0x10
}
//--------------------------------------------------------------------------

void Set_Addressing_Mode_12832(unsigned char d)
{
	comm_out(0x20);			// Set Memory Addressing Mode
	comm_out(d);			//   Default => 0x02
						//     0x00 => Horizontal Addressing Mode
						//     0x01 => Vertical Addressing Mode
						//     0x02 => Page Addressing Mode
}
//--------------------------------------------------------------------------

void Set_Column_Address_12832(unsigned char a, unsigned char b)
{
	comm_out(0x21);			// Set Column Address
	comm_out(a);			//   Default => 0x00 (Column Start Address)
	comm_out(b);			//   Default => 0x83 (Column End Address)
}
//--------------------------------------------------------------------------

void Set_Page_Address_12832(unsigned char a, unsigned char b)
{
	comm_out(0x22);			// Set Page Address
	comm_out(a);			//   Default => 0x00 (Page Start Address)
	comm_out(b);			//   Default => 0x07 (Page End Address)
}
//--------------------------------------------------------------------------

void Set_Start_Line_12832(unsigned char d)
{
	comm_out(0x40|d);			// Set Display Start Line
						          //   Default => 0x40 (0x00)
}
//--------------------------------------------------------------------------

void Set_Contrast_Control_12832(unsigned char d)
{
	comm_out(0x81);			// Set Contrast Control for Bank 0
	comm_out(d);			//   Default => 0x80
}
//--------------------------------------------------------------------------

void Set_Area_Brightness_12832(unsigned char d)
{
	comm_out(0x82);			// Set Brightness for Area Color Banks
	comm_out(d);			//   Default => 0x80
}
//--------------------------------------------------------------------------

void Set_Segment_Remap_12832(unsigned char d)
{
	comm_out(0xA0|d);			// Set Segment Re-Map
						//     Default => 0xA0
						//     0xA0 (0x00) => Column Address 0 Mapped to SEG0
						//     0xA1 (0x01) => Column Address 0 Mapped to SEG131
}
//--------------------------------------------------------------------------

void Set_Entire_Display_12832(unsigned char d)
{
	comm_out(0xA4|d);			// Set Entire Display On / Off
						//     Default => 0xA4
						//     0xA4 (0x00) => Normal Display
						//     0xA5 (0x01) => Entire Display On
}
//--------------------------------------------------------------------------

void Set_Inverse_Display_12832(unsigned char d)
{
	comm_out(0xA6|d);			// Set Inverse Display On/Off
						//     Default => 0xA6
						//     0xA6 (0x00) => Normal Display
						//     0xA7 (0x01) => Inverse Display On
}
//--------------------------------------------------------------------------

void Set_Multiplex_Ratio_12832(unsigned char d)
{
	comm_out(0xA8);			// Set Multiplex Ratio
	comm_out(d);			//   Default => 0x3F (1/64 Duty)
}
//--------------------------------------------------------------------------

void Set_Dim_Mode_12832(unsigned char a, unsigned char b)
{
	comm_out(0xAB);			// Set Dim Mode Configuration
	comm_out(0X00);			//           => (Dummy Write for First Parameter)
	comm_out(a);			//   Default => 0x80 (Contrast Control for Bank 0)
	comm_out(b);			//   Default => 0x80 (Brightness for Area Color Banks)
	comm_out(0xAC);			// Set Display On in Dim Mode
}
//--------------------------------------------------------------------------

void Set_Master_Config_12832(unsigned char d)
{
	comm_out(0xAD);			// Set Master Configuration
	comm_out(0x8E|d);			//   Default => 0x8E
						//     0x8E (0x00) => Select External VCC Supply
						//     0x8F (0x01) => Select Internal DC/DC Voltage Converter
}
//--------------------------------------------------------------------------

void Set_Display_On_Off_12832(unsigned char d)	
{
	comm_out(0xAE|d);			// Set Display On/Off
						//     Default => 0xAE
						//     0xAE (0x00) => Display Off
						//     0xAF (0x01) => Display On
}
//--------------------------------------------------------------------------

void Set_Start_Page_12832(unsigned char d)
{
	comm_out(0xB0|d);			// Set Page Start Address for Page Addressing Mode
						//   Default => 0xB0 (0x00)
}
//--------------------------------------------------------------------------

void Set_Common_Remap_12832(unsigned char d)
{
	comm_out(0xC0|d);			// Set COM Output Scan Direction
						//     Default => 0xC0
						//     0xC0 (0x00) => Scan from COM0 to 63
						//     0xC8 (0x08) => Scan from COM63 to 0
}
//--------------------------------------------------------------------------

void Set_Display_Offset_12832(unsigned char d)
{
	comm_out(0xD3);			// Set Display Offset
	comm_out(d);			//   Default => 0x00
}
//--------------------------------------------------------------------------

void Set_Display_Clock_12832(unsigned char d)
{
	comm_out(0xD5);			// Set Display Clock Divide Ratio / Oscillator Frequency
	comm_out(d);			//   Default => 0x70
						//     D[3:0] => Display Clock Divider
						//     D[7:4] => Oscillator Frequency
}
//--------------------------------------------------------------------------

void Set_Area_Color_12832(unsigned char d)
{
	comm_out(0xD8);			// Set Area Color Mode On/Off & Low Power Display Mode
	comm_out(d);			//   Default => 0x00 (Monochrome Mode & Normal Power Display Mode)
}
//--------------------------------------------------------------------------

void Set_Precharge_Period_12832(unsigned char d)
{
	comm_out(0xD9);			// Set Pre-Charge Period
	comm_out(d);			//   Default => 0x22 (2 Display Clocks [Phase 2] / 2 Display Clocks [Phase 1])
						//     D[3:0] => Phase 1 Period in 1~15 Display Clocks
						//     D[7:4] => Phase 2 Period in 1~15 Display Clocks
}
//--------------------------------------------------------------------------

void Set_Common_Config_12832(unsigned char d)
{
	comm_out(0xDA);			// Set COM Pins Hardware Configuration
	comm_out(0x02|d);	//   Default => 0x12 (0x10)
						//     Alternative COM Pin Configuration
						//     Disable COM Left/Right Re-Map
}
//--------------------------------------------------------------------------

void Set_VCOMH_12832(unsigned char d)
{
	comm_out(0xDB);			// Set VCOMH Deselect Level
	comm_out(d);			//   Default => 0x34 (0.77*VCC)
}
//--------------------------------------------------------------------------

void Set_Read_Modify_Write_12832(unsigned char d)
{
	comm_out(0xE0|d);			// Set Read Modify Write Mode
						//     Default => 0xE0
						//     0xE0 (0x00) => Enter Read Modify Write
						//     0xEE (0x0E) => Exit Read Modify Write
}
//--------------------------------------------------------------------------

void Set_NOP_12832()
{
	comm_out(0xE3);			// Command for No Operation
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
	comm_out(0x91);			// Define Look Up Table of Area Color
	comm_out(a);			//   Define Bank 0 Pulse Width
	comm_out(b);			//   Define Color A Pulse Width
	comm_out(c);			//   Define Color B Pulse Width
	comm_out(d);			//   Define Color C Pulse Width
}


void Set_Bank_Color_12832()
{
	comm_out(0x92);			// Define Area Color for Bank 1~16 (Page 0)
	comm_out(0x00);			//   Define Bank 1~4 as Color A
	comm_out(0x55);			//   Define Bank 5~8 as Color B
	comm_out(0xAA);			//   Define Bank 9~12 as Color C
	comm_out(0xFF);			//   Define Bank 13~16 as Color D

	comm_out(0x93);			// Define Area Color for Bank 17~32 (Page 1)
	comm_out(0xFF);			//   Define Bank 17~32 as Color D
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
	Set_Display_On_Off_12832(0x00);		      // Display Off (0x00/0x01) 
	Set_Display_Clock_12832(0x10);		      // Set Clock as 160 Frames/Sec
	Set_Multiplex_Ratio_12832(0x1F);		    // 1/32 Duty (0x0F~0x3F)
	Set_Display_Offset_12832(0x00);		      // Shift Mapping RAM Counter (0x00~0x3F)
	Set_Start_Line_12832(0x00);			        // Set Mapping RAM Display Start Line (0x00~0x3F)
	Set_Master_Config_12832(0x00);		      // Disable Embedded DC/DC Converter (0x00/0x01)
	Set_Area_Color_12832(0x05);			        // Set Monochrome & Low Power Save Mode
	Set_Addressing_Mode_12832(0x02);		    // Set Page Addressing Mode (0x00/0x01/0x02)
	Set_Segment_Remap_12832(0x01);		      // Set SEG/Column Mapping (0x00/0x01)
	Set_Common_Remap_12832(0x08);			      // Set COM/Row Scan Direction (0x00/0x08)
	Set_Common_Config_12832(0x10);		      // Set Alternative Configuration (0x00/0x10)
	Set_LUT_12832(0x3F,0x3F,0x3F,0x3F);		  // Define All Banks Pulse Width as 64 Clocks
	Set_Contrast_Control_12832(Brightness);	// Set SEG Output Current
	Set_Area_Brightness_12832(Brightness);	// Set Brightness for Area Color Banks  
	Set_Precharge_Period_12832(0xD2);		    // Set Pre-Charge as 13 Clocks & Discharge as 2 Clock
	Set_VCOMH_12832(0x08);			            // Set VCOM Deselect Level
	Set_Entire_Display_12832(0x00);		      // Disable Entire Display On (0x00/0x01)
	Set_Inverse_Display_12832(0x00);		    // Disable Inverse Display On (0x00/0x01)

	Fill_RAM_12832(0xff);				            // Clear Screen

	Set_Display_On_Off_12832(0x01);		      // Display On (0x00/0x01)
}

/*****************************************************
*           Setup Function, to run once              *
*****************************************************/

void setup()
{
  DDRB |= (1<<DDB5); //Enable CLK as Output
  DDRB |= (1<<DDB3); //Enable SDIN / SDA_IN as Output

  pinMode(OLED_RESET, OUTPUT);
  pinMode(BS1, OUTPUT);
  pinMode(BS2, OUTPUT);

  switch(mode)
  {
    case 1: pinMode(OLED_CS, OUTPUT);
            pinMode(OLED_DC, OUTPUT);
            pinMode(OLED_SDIN, OUTPUT);  
            digitalWrite(BS1, LOW);
            digitalWrite(BS2, LOW);
            break;
    case 2: pinMode(OLED_SA0, OUTPUT);
            pinMode(OLED_SDA_IN, OUTPUT);  
            digitalWrite(OLED_SA0, HIGH); //Slave Address = 0x7A (Write Mode) 
            digitalWrite(BS1, HIGH);
            digitalWrite(BS2, LOW);
            break;
  }

  digitalWrite(OLED_RESET, LOW);
  delay(150);
  digitalWrite(OLED_RESET, HIGH);
  delay(150);
  
  OLED_Init_12832(); //Initialization Sequence
  
  Set_Column_Address_12832(0x00,0x83); 

}

/*****************************************************
*           Loop Function, to run repeatedly         *
*****************************************************/

void loop() { 
  Checkerboard_12832();
  delay(750);
  Fill_RAM_12832(0x00);  
  delay(250);
  
  switch(mode)
  {
    case 1: ImageDisplay(NHD_Logo);
            delay(500);
            Show_Letter(0x03,0x32,0); //S
            Show_Letter(0x03,0x38,1); //E
            Show_Letter(0x03,0x3E,2); //R
            Show_Letter(0x03,0x44,3); //I
            Show_Letter(0x03,0x4A,4); //A
            Show_Letter(0x03,0x50,5); //L                        
            break;
            
    case 2: ImageDisplay(NHD_Logo);
            delay(500);
            Show_Letter(0x03,0x3B,6); //I
            Show_Letter(0x03,0x41,7); //2
            Show_Letter(0x03,0x47,8); //C
            break;
  }
  delay(1000);
    
  Fill_RAM_12832(0x00);
  delay(250);
}
