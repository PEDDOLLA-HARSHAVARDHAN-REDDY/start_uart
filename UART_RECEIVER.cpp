
#include<avr/io.h>
#define FOSC 1843200// Clock Speed 1.8432MHz
#define BAUD 9600
#define MYUBRR (FOSC/16/BAUD-1)


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

int main() {
  // put your setup code here, to run once:
  USART_Init ( MYUBRR );
  while(1){
    lp();
  }
  return 0;
}

