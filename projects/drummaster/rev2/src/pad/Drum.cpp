#include "Drum.h"

using namespace digitalcave;

Drum::Drum(const char* filenamePrefix, uint8_t piezoMuxIndex, uint8_t doubleHitThreshold) : Pad(filenamePrefix, doubleHitThreshold), piezoMuxIndex(piezoMuxIndex){
}

void Drum::poll(){
	uint8_t volume = readPiezo(piezoMuxIndex);
	if (volume){
		play(volume);
	}
}