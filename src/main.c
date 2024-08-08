#include <stdio.h>
#include <string.h>

#include "jakestering.h"

#define CLK 25
#define RW  24

int DATA[] = { 7, 6, 5, 4, 3, 2, 1, 0 };
int ADDR[] = { 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8 };

char* OPCODES[] = {
/*       0      1      2      3      4      5      6      7      8      9      A      B      C      D      E      F */
/*0*/  "BRK", "ORA", "NUL", "NUL", "TSB", "ORA", "ASL", "RMB", "PHP", "ORA", "ASL", "NUL", "TSB", "ORA", "ASL", "BBR",
/*1*/  "BPL", "ORA", "ORA", "NUL", "TRB", "ORA", "ASL", "RMB", "CLC", "ORA", "INC", "NUL", "TRB", "ORA", "ASL", "BBR",
/*2*/  "JSR", "AND", "NUL", "NUL", "BIT", "AND", "ROL", "RMB", "PLP", "AND", "ROL", "NUL", "BIT", "AND", "ROL", "BBR",
/*3*/  "BMI", "AND", "AND", "NUL", "BIT", "AND", "ROL", "RMB", "SEC", "AND", "DEC", "NUL", "BIT", "AND", "ROL", "BBR",
/*4*/  "RTI", "EOR", "NUL", "NUL", "NUL", "EOR", "LSR", "RMB", "PHA", "EOR", "LSR", "NUL", "JMP", "EOR", "LSR", "BBR",
/*5*/  "BVC", "EOR", "EOR", "NUL", "NUL", "EOR", "LSR", "RMB", "CLI", "EOR", "PHY", "NUL", "NUL", "EOR", "LSR", "BBR",
/*6*/  "RTS", "ADC", "NUL", "NUL", "STZ", "ADC", "ROR", "RMB", "PLA", "ADC", "ROR", "NUL", "JMP", "ADC", "ROR", "BBR",
/*7*/  "BVS", "ADC", "ADC", "NUL", "STZ", "ADC", "ROR", "RMB", "SEI", "ADC", "PLY", "NUL", "JMP", "ADC", "ROR", "BBR",
/*8*/  "BRA", "STA", "NUL", "NUL", "STY", "STA", "STX", "SMB", "DEY", "BIT", "TXA", "NUL", "STY", "STA", "STX", "BBS",
/*9*/  "BCC", "STA", "STA", "NUL", "STY", "STA", "STX", "SMB", "TYA", "STA", "TXS", "NUL", "STZ", "STA", "STZ", "BBS",
/*A*/  "LDY", "LDA", "LDX", "NUL", "LDY", "LDA", "LDX", "SMB", "TAY", "LDA", "TAX", "NUL", "LDY", "LDA", "LDX", "BBS",
/*B*/  "BCS", "LDA", "LDA", "NUL", "LDY", "LDA", "LDX", "SMB", "CLV", "LDA", "TSX", "NUL", "LDY", "LDA", "LDX", "BBS",
/*C*/  "CPY", "CMP", "NUL", "NUL", "CPY", "CMP", "DEC", "SMB", "INY", "CMP", "DEX", "WAI", "CPY", "CMP", "DEC", "BBS",
/*D*/  "BNE", "CMP", "CMP", "NUL", "NUL", "CMP", "DEC", "SMB", "CLD", "CMP", "PHX", "STP", "NUL", "CMP", "DEC", "BBS",
/*E*/  "CPX", "SBC", "NUL", "NUL", "CPX", "SBC", "INC", "SMB", "INX", "SBC", "NOP", "NUL", "CPX", "SBC", "INC", "BBS",
/*F*/  "BEQ", "SBC", "SBC", "NUL", "NUL", "SBC", "INC", "SMB", "SED", "SBC", "PLX", "NUL", "NUL", "SBC", "INC", "BBS",
};

char* ASCII[] = {
  "NUL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", "BEL",
  "BS" , "HT" , "LF" , "VT" , "FF" , "CR" , "SO" , "SI" ,
  "DLE", "DC1", "DC2", "DC3", "DC4", "NAK", "SYN", "ETB",
  "CAN", "EM" , "SUB", "ESC", "FS" , "GS" , "RS" , "US" ,
  "SP" , "!"  , """" , "#"  , "$"  , "%"  , "&"  , "'"  ,
  "("  , ")"  , "*"  , "+"  , ","  , "-"  , "."  , "/"  ,
  "0"  , "1"  , "2"  , "3"  , "4"  , "5"  , "6"  , "7"  ,
  "8"  , "9"  , ":"  , ";"  , "<"  , "="  , ">"  , "?"  ,
  "@"  , "A"  , "B"  , "C"  , "D"  , "E"  , "F"  , "G"  ,
  "H"  , "I"  , "J"  , "K"  , "L"  , "M"  , "N"  , "O"  ,
  "P"  , "Q"  , "R"  , "S"  , "T"  , "U"  , "V"  , "W"  ,
  "X"  , "Y"  , "Z"  , "["  , "\\" , "]"  , "^"  , "_"  ,
  "`"  , "a"  , "b"  , "c"  , "d"  , "e"  , "f"  , "g"  ,
  "h"  , "i"  , "j"  , "k"  , "l"  , "m"  , "n"  , "o"  ,
  "p"  , "q"  , "r"  , "s"  , "t"  , "u"  , "v"  , "w"  ,
  "x"  , "y"  , "z"  , "{"  , "|"  , "}"  , "~"  , "DEL", 
  ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   ,
  ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   ,
  ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   ,
  ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   ,
  ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   ,
  ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   ,
  ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   ,
  ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   ,
  ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   ,
  ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   ,
  ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   ,
  ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   ,
  ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   ,
  ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   ,
  ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   ,
  ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   ,
};

typedef struct _pinData
{
  unsigned int data;
  unsigned int addr;
  int r_w;
  int clk;
}Pin_data_t;

void logic_analyzer_handler(void);
void fillPinData( Pin_data_t *data );

int pressed = 0;

int main( int argc, char *argv[] )
{
  setupIO();
  
  pinMode(  RW, OUTPUT );
  digitalWrite( RW, LOW );
  pinMode( CLK, OUTPUT );
  digitalWrite( CLK, LOW );

  for ( int i = 0; i < 8; i++ )
  {
    pinMode( DATA[i], OUTPUT );
    digitalWrite( DATA[i], LOW );
  }
  
  for ( int i = 0; i < 16; i++ )
  {
    pinMode( ADDR[i], OUTPUT );
    digitalWrite( ADDR[i], LOW );
  }
  
  pinMode(  RW, INPUT );
  pudController( RW, PUD_DOWN );
  pinMode( CLK, INPUT );
  pudController( CLK, PUD_DOWN );

  for ( int i = 0; i < 8; i++ )
  {
    pinMode( DATA[i], INPUT );
    pudController( DATA[i], PUD_DOWN );
  }
  
  for ( int i = 0; i < 16; i++ )
  {
    pinMode( ADDR[i], INPUT );
    pudController( ADDR[i], PUD_DOWN );
  }

  jakestering_ISR( CLK, RISING_EDGE, &logic_analyzer_handler );
  
  while (1)
  {
    delay( 1000 );
  }
  
  return 0;
}

void logic_analyzer_handler(void)
{
  Pin_data_t current;
  fillPinData( &current );
  printf("[%04d] R/W: %c | ADDR: %04x | DATA: %02x | %s | %s \n", pressed, current.r_w ? 'r' : 'W', current.addr, current.data, OPCODES[current.data], ASCII[current.data] );
  pressed++;
}

void fillPinData( Pin_data_t *data )
{
  data->data = 0;
  for ( int i = 0; i < 8; i++ )
  {
    int bit = digitalRead( DATA[i] ) ? 1 : 0;
//    printf( "%d", bit );
    data->data = ( data->data << 1 ) + bit;
  }
  
  data->addr = 0;
//  printf(" | ");
  for ( int i = 0; i < 16; i++ )
  {
    int bit = digitalRead( ADDR[i] ) ? 1 : 0;
//    printf( "%d", bit );
    data->addr = ( data->addr << 1 ) + bit;
  }

  data->r_w = digitalRead( RW );
  data->clk = digitalRead( CLK );
}

