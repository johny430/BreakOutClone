#pragma once
#include <string>
#include <irrKlang.h>
using namespace irrklang;

class SoundPlayer
{
public:
	static void Play(const std::string& name, bool loop = false);
private:
	static ISoundEngine* s_SoundEngine;
};