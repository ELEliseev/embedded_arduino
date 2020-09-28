/*
 *  MLRC5 Arduino Library
 *  Guy Carpenter, Clearwater Software - 2013
 *
 *  Licensed under the BSD2 license, see LICENSE for details.
 *
 *  All text above must be included in any redistribution.
 */

#ifndef MLRC5_h
#define MLRC5_h

#include <Arduino.h>

class MLRC5
{
 public:
   

    MLRC5(bool TxRx, unsigned char Writepin);
    bool write(unsigned int WriteValue);
    bool read(unsigned int *message);
    bool read(unsigned char *toggle, unsigned char *address, unsigned char *command);
    
  private:
     unsigned char Readpin;
    unsigned char Writepin;
    unsigned long WriteValue;
    unsigned char state;
    unsigned long time0;
    unsigned long lastValue;
    unsigned int bits;
    unsigned int command;
    void reset();
    void decodeEvent(unsigned char event);
    void decodePulse(unsigned char signal, unsigned long period);
    void emit( bool bit);  
};

#endif // MLRC5_h
