
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

void USART_Transmit( unsigned char data )
{
/* Wait for empty transmit buffer */
while ( !( UCSR0A & (1<<UDRE0)) )
;
/* Put data into buffer, sends the data */
UDR0 = data;
}

void lp() {
  // put your main code here, to run repeatedly:
  USART_Transmit('P');
}

int main() {
  // put your setup code here, to run once:
  USART_Init ( MYUBRR );
  while(1){
    lp();
  }

  return 0;
}

