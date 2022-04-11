#include "SoundPlayer.h"

ISoundEngine* SoundPlayer::s_SoundEngine =  createIrrKlangDevice();

void SoundPlayer::Play(const std::string& name, bool loop)
{
	s_SoundEngine->play2D(name.c_str(), loop);
}
