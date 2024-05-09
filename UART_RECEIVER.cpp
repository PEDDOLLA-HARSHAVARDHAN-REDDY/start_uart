
#include<avr/io.h>
#define FOSC 1843200// Clock Speed 1.8432MHz
#define BAUD 9600
#define MYUBRR (FOSC/16/BAUD-1)

volatile uint8_t *opData = (volatile uint8_t*)0x31,*opCntrl = (volatile uint8_t*)0x108;

void del(){
  volatile int i=0;
  for(i=0;i<100;i++);
}

void writeCntrl(unsigned char cmd){
  *opCntrl = (0x00);// enable low, RS is low
  *opData = cmd;
  del();
  *opCntrl = (*opCntrl | (0x02)); //enable is high
  del();
  *opCntrl = (0x00);// enable low, RS low
  del();
}

void writeData(unsigned char data){
  *opCntrl = (0x01);// enable low, RS is high
  *opData = data;
  del();
  *opCntrl = (*opCntrl | (0x02)); //enable is high
  del();
  *opCntrl = (0x01); // enable low
  del();
  *opCntrl = (0x00);// enable low, RS low
  del();
}

void setUpDisplay(){
  writeCntrl(0x01); // clear display
  writeCntrl(0x0F); // display on, cursor, cursor blink
  writeCntrl(0x06); // move cursor right
}

void USART_Init(unsigned int ubrr){
/* Set baud rate */
UBRR0L = (unsigned char)(ubrr>>8);
UBRR0H = (unsigned char)ubrr;
/* Enable receiver and transmitter */
UCSR0B = (1<<RXEN0)|(1<<TXEN0);
/* Set frame format: 8data, 2stop bit */
UCSR0C = (1<<USBS0)|(3<<UCSZ00);
} // USART_Init

unsigned char USART_Receive( void )
{
/* Wait for data to be received */
while ( !(UCSR0A & (1<<RXC0)) );
/* Get and return received data from buffer */
return UDR0;
}

unsigned char lp() {
  // put your main code here, to run repeatedly:
  return USART_Receive();
}

void setup() {
  // put your setup code here, to run once:
  volatile uint8_t *ddrData = (volatile uint8_t*)0x30,*ddrCntrl = (volatile uint8_t*)0x107;
  *ddrData = 0xFF;
  *ddrCntrl = 0xFF;

  //setUpDisplay();
  USART_Init ( MYUBRR );
}

int main() {
  // put your setup code here, to run once:
  setup();
  while(1){
    char temp=lp();
    //writeData(temp);
  }
  return 0;
}

