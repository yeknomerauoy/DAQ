# include <SPI.h>
# include <avr/interrupt.h>
char str[100];
volatile byte i;
volatile bool pin;

void setup()
 {
  Serial.begin (9600);   // set baud rate to 115200 for usart
  Serial.println("Done");
  Serial.println("Hello I'm SPI UNO_SLAVE");
  pinMode(MISO, OUTPUT); // have to send on Master in so it set as output
  SPCR |= _BV(SPE); // turn on SPI in slave mode
  i = 0; // buffer empty
  pin = false;
  SPI.attachInterrupt();     // turn on interrupt
}

void loop(){
  if (pin)
  {
    pin = false;   //reset the pin
    i=0;
  }
}

// Interrupt function
ISR (SPI_STC_vect) 
{
  uint16_t c = SPDR; // read byte from SPI Data Register           
  Serial.println(c>>4);
  Serial.println(c%16);
  pin = true;
}