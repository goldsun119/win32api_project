#pragma once
#include "Header.h"

class SoundPlay
{
public:
	SoundPlay();
	~SoundPlay();

private:
	System* pSystem;
	Sound* pSound;
	Channel* pChannel;

public:
	void Set(const char* file, int type);
	void Stop();
	void Play();
};