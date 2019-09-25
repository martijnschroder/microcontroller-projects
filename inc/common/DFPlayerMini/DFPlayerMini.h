/*
 * Library for using DFPlayer Mini chip.
 */

#ifndef DFPLAYER_MINI_H
#define DFPLAYER_MINI_H

#include <stdlib.h>
#include <math.h>
#include <dctypes.h>
#include <dcutil/delay.h>
#include <Stream/Stream.h>

#define DFPLAYER_COMMAND_NEXT			0x01
#define DFPLAYER_COMMAND_PREVIOUS		0x02
#define DFPLAYER_COMMAND_TRACK			0x03
#define DFPLAYER_COMMAND_VOL_UP			0x04
#define DFPLAYER_COMMAND_VOL_DOWN		0x05
#define DFPLAYER_COMMAND_VOL_SET		0x06
#define DFPLAYER_COMMAND_EQ_SET			0x07
#define DFPLAYER_COMMAND_MODE_SET		0x08
#define DFPLAYER_COMMAND_SOURCE_SET		0x09
#define DFPLAYER_COMMAND_STANDBY_ON		0x0A
#define DFPLAYER_COMMAND_STANDBY_OFF	0x0B
#define DFPLAYER_COMMAND_RESET			0x0C
#define DFPLAYER_COMMAND_PLAY			0x0D
#define DFPLAYER_COMMAND_PAUSE			0x0E
#define DFPLAYER_COMMAND_FOLDER_SET		0x0F
#define DFPLAYER_COMMAND_GAIN_SET		0x0A
#define DFPLAYER_COMMAND_REPEAT_SET		0x0B

#define DFPLAYER_COMMAND_GET_STATUS		0x42
#define DFPLAYER_COMMAND_GET_VOLUME		0x43
#define DFPLAYER_COMMAND_GET_EQ			0x44
#define DFPLAYER_COMMAND_GET_MODE		0x45
#define DFPLAYER_COMMAND_GET_SW_VER		0x46
#define DFPLAYER_COMMAND_GET_FILE_COUNT	0x47


namespace digitalcave {

	class DFPlayerMini{
		public:
			//Inits the DFPlayer Mini chip
			DFPlayerMini(Stream* serial);
			//
			// void playRandom();
			// void playNext();
			// void playPrevious();
			// void setPlaybackMode(uint8_t playback_mode);
			// void setEqMode(uint8_t eq_mode);
			// void setVolume(uint8_t volume);
			// void setStandby(uint8_t standby);

			//Resets the module and
			void init();

			uint8_t* getResponse();
			uint8_t sendCommand(uint8_t command, uint16_t arg = 0);
			uint8_t poll();

		private:
			Stream* serial;

			uint8_t request[10];
			uint8_t response[10];

	};
}
#endif
