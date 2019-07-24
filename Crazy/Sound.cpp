#include "Sound.h"

SoundPlay::SoundPlay()
{

}
SoundPlay::~SoundPlay()
{
	pSystem->release();
	pSystem->close();
}

void SoundPlay::Set(const char* file, int type)
{
	System_Create(&pSystem);
	pSystem->init(1, FMOD_INIT_NORMAL, NULL);

	if (type == 1)	// 배경음
		pSystem->createSound(file, FMOD_LOOP_NORMAL, NULL, &pSound);
	else if (type == 2)// 효과음
		pSystem->createSound(file, FMOD_DEFAULT, NULL, &pSound);
}

void SoundPlay::Stop()
{
	pChannel->stop();
}

void SoundPlay::Play()
{
	pSystem->playSound(FMOD_CHANNEL_REUSE, pSound, false, &pChannel);
}