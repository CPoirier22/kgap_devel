#ifndef _spi_h_
#define _spi_h_

extern uint8 *spi_voice_rx_buffer, *spi_voice_tx_buffer;
extern uint8 *spi_signal_rx_buffer, *spi_signal_tx_buffer;
extern uint8 SPI_Poll;

void SPI_Init();
void SPI_Transfer();

#endif
