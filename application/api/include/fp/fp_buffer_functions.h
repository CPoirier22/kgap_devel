#ifndef FP_BUFFER_FUNCTIONHS_H_
#define FP_BUFFER_FUNCTIONHS_H_

/**
 * Returns a pointer to the byte array containing the data that is transmitted or received by the DECT radio.
 * For each connection established a byte array of 40 bytes (or 80 bytes if long slot mode is enabled) is allocated and
 * used by the DECT radio to hold bytes physically transmitted over the air. Each connection will have a transmit
 * buffer for outgoing data and a receive buffer for incoming data. Access to these buffer much be synchronized
 * with the DECT radio to avoid reading/writing to the buffer while the DECT radio is accessing it.
 *
 * If the DSP is enabled this may also access the byte buffers.
 *
 * To access these buffers at the right time use the DIP_RECV_INT interrupt. This interrupt is signaled once for
 * every open connection when the receive buffer has been updated by the DECT radio. Approx 5ms later the transmit
 * buffer will be read by the DECT radio, and approx 10 ms later the receive buffer will be updated with the next
 * frame received.
 *
 * @see set_interrupt_handler()
 *
 * @param Pmid            The connection ID.
 * @param rxtx            0 means the transmit buffer, 1 means the receive buffer.
 * @return UByte*         A pointer to the transmit or receive buffer for the named connection.
 */
extern UByte * fp_get_speech_buffer(PMIDType Pmid, UByte rxtx);

/**
 * If supplied a channel corresponding to an open connection the connection ID (the Pmid) is returned.
 *
 * This function is intended to be called from inside a DIP_RECV_INT interrupt handler. The channel
 * of the current connection on which the interrupt has been signaled is located in the global variable
 * currentReceiveChannel.
 *
 * The Pmid can be used as input to e.g. @see fp_get_speech_buffer().
 *
 * When a DIP_RECV_INT is signaled the interrupt handler itself does not know to which of the
 * up to 6 possible open connections the interrupt relates. Through the use of the currentReceiveChannel
 * and the fp_get_connection_id_from_channel function, an ID of the channel can be obtained.
 *
 * @param channel         The channel (a combination of timeslot and frequency)
 * @return UByte*         A 3 byte array containing the Pmid of the connected channel.
 */
extern UByte* fp_get_connection_id_from_channel(UByte channel);

/**
 * Translates between two forms of identifying a connection.
 *
 * The PPID is an integer often used as index into various tables.
 *
 * The Pmid is a 3 byte array, the first 12 bits of which will be the same as the PPID, but
 * then various flag bits may follow.
 *
 * @param Pmid         The connection ID in form of a Pmid.
 * @return PPIDType    The connection ID in form of a PPID.
 */
extern PPIDType PMID2PPID(PMIDType Pmid);

#endif /* FP_BUFFER_FUNCTIONHS_H_ */
