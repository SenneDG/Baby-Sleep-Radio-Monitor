#include "stm8s.h"
#include "stm8s_spi.h"
#include "rf24l01.h"
#include "ntc.h"
#include "hall.h"
#include "stm8s_it.h"

/*
RF24L01 connector pinout:
	GND    VCC
	CE     CSN
	SCK    MOSI
	MISO   IRQ
	
Connections:
  PC3 -> CE
  PC4 -> CSN
	PC5 -> SCK
	PC6 -> MOSI
  PC7 -> MISO
*/

float temp = 0;

uint8_t raddr[5];
uint8_t taddr[5];

uint16_t temp_int = 0;

int statusHALL = 0;

uint8_t value[3];

/*
this function adds a delay on sending packets
int ms: time in miliseconds that the delay will take
*/
void delay_ms (int ms){
		int i = 0;
		int j = 0;
	
		for ( i=0; i<=ms; i++)
			for ( j=0; j<120; j++) // nop = Fosc/4
				_asm("nop"); //assembly code nop (no operation)
	}
	
main()
{
	// setup SPI and GPIO pins
	RF24L01_init(); 
	
	raddr[0] = 0x41;
	raddr[1] = 0x42;
	raddr[2] = 0x43;
	raddr[3] = 0x44;
	raddr[4] = 0x45;
	
	taddr[0] = 0x41;
	taddr[1] = 0x42;
	taddr[2] = 0x43;
	taddr[3] = 0x44;
	taddr[4] = 0x45;
	
	// set all registers of the nrf24
  setup2(raddr, taddr);
	
	// set config register as receiver (uncomment for RX)
	//NRF_MODE_RX(); 
	
	// set config register as transmitter (uncomment for TX)
	NRF_MODE_TX();
	
	
	while(1)
	{
		
		// read temperature and hall from sensors
		temp = read_temp();
		statusHALL = read_hall();
		
		// convert temp to integer
		temp_int = (int16_t)(temp * 10.0);
		
		//delay_ms(10000);
		

		// copy temp and status to values array
		value[0] = (uint8_t)(temp_int & 0xFF); // lower byte
		value[1] = (uint8_t)((temp_int >> 8) & 0xFF); // upper byte
		//value[2] = statusHALL;
		
		//value[0] = 237;
		//value[1] = 0;
		value[2] = statusHALL;
		
		// sent packet 
		RF24L01_write_payload(value, 3);
	
		
		delay_ms(10000);
		
	}
}


#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif