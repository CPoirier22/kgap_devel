#ifndef PP_BUFFER_FUNCTIONS_H_
#define PP_BUFFER_FUNCTIONS_H_

/**
 * Returns a pointer to the byte array containing the data that is transmitted or received by the DECT radio.
 * A PP will have at most one open connection and a byte array of 40 bytes (or 80 bytes if long slot
 * mode is enabled) is allocated and used by the DECT radio to hold bytes physically transmitted over the air.
 * This connection will have a transmit buffer for outgoing data and a receive buffer for incoming data.
 * Access to these buffer much be synchronized with the DECT radio to avoid reading/writing to the
 * buffer while the DECT radio is accessing it.
 *
 * If the DSP is enabled this may also access the byte buffers.
 *
 * To access these buffers at the right time use the DIP_RECV_INT interrupt. This interrupt is signaled when
 * the receive buffer has been updated by the DECT radio. Approx 5ms later the transmit
 * buffer will be read by the DECT radio, and approx 10 ms later the receive buffer will be updated with the next
 * frame received.
 *
 * @see set_interrupt_handler()
 *
 * @param rxtx            0 means the transmit buffer, 1 means the receive buffer.
 * @return UByte*         A pointer to the transmit or receive buffer for the named connection.
 */
extern UByte* pp_get_speech_buffer(UByte rxtx);

#endif /* PP_BUFFER_FUNCTIONS_H_ */
