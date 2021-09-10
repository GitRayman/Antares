//SPI driver for P2, Raymond Allen 2021, MIT license
//Adapted from - Propeller SPI Engine  ... Spin Version  v1.0 * Author: Beau Schwabe
//But, only using modes needed for EVE, MSBPRE and MSBFIRST
//User needs to control Chip select pin seperately

//Note:  This version does not need it's own cog, but not as fast as the assembly version that uses it's own cog

//With clockdelay==0, get bitrate ~6.25 MHz with 297 MHz P2 clock (although clock pulse is narrow, other usages may need larger clockdelay value).

#include "propeller2.h"


typedef struct spi {//Note:  This version does not need it's own cog, but not as fast as the assembly version that uses it's own cog
	//With clockdelay==0, get bitrate ~6.25 MHz with 297 MHz P2 clock (although clock pulse is narrow, other usages may need larger clockdelay value).

	int ClockDelay, ClockState;
	void Start(int _ClockDelay, int _ClockState)
	{//save input values
		ClockState = _ClockState;
		ClockDelay = _ClockDelay;
	}

	void Write8(int Dpin, int Cpin, uint8_t Value)
	{//Write 8 bits
		_pinh(Dpin);
		_pinw(Cpin, ClockState);
		uint32_t _Value = Value;//need more bits for shifting
		for (int i=0;i<8;i++)
		{
			_Value=_Value<<1;
			if ((_Value&0x100)>0)
				_pinw(Dpin,1);   // output data bit
			else
				_pinw(Dpin, 0);   // output data bit
			PostClock(Cpin);  // toggle clock pin
		}
		
	}

	void WriteN(int Dpin, int Cpin, uint8_t* buff, int TransferSize)
	{//Write N bits
		for (int j=0;j<TransferSize;j++)
		{//send bytes one at at time
			_pinh(Dpin);
			_pinw(Cpin, ClockState);			
			uint32_t _Value = buff[j];//need more bits for shifting
			for (int i = 0; i < 8; i++)
			{
				_Value = _Value << 1;
				if ((_Value & 0x100) > 0)
					_pinw(Dpin, 1);   // output data bit
				else
					_pinw(Dpin, 0);   // output data bit
				PostClock(Cpin);  // toggle clock pin
			}
		}
	}

	uint8_t Read8(int Dpin, int Cpin)
	{//Read 8 bits
		_pinf(Dpin);
		_pinw(Cpin, ClockState);

		int Value=0;
		for (int i = 0; i < 8; i++)
		{
			Value = Value << 1;
			Value = Value |_pinr(Dpin);   // input data bit
			PostClock(Cpin);  // toggle clock pin	
		}
			
		return Value;
	}

	void PostClock(_Cpin)
	{//Toggle the clock
		_pinnot(_Cpin);
		_waitx(ClockDelay);
		_pinnot(_Cpin);
	}

} Spi;






