#ifndef RADIO_STATUS_H_
#define RADIO_STATUS_H_

enum Direction
{
    TRANSMIT, RECEIVE, UNKNOWNDIRECTION
};

void setRadioDirection(BYTE slot, enum Direction direction);
void setRadioFrequency(BYTE slot, BYTE frequency);
char* reportRadioStatus();
void setRadioActive(BYTE slot);
void setRadioInActive(BYTE slot);

#endif /* RADIO_STATUS_H_ */
