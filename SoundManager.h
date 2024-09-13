#pragma once
#include "Sound.h"
#include <list>
#include <memory>
#include <unordered_map>
#include <string>

class Audio;

class SoundManager
{
public:
	static SoundManager* GetInstance() { static SoundManager instance; return &instance; }

	void Initilize();
	void Update();
	void Play();

	void RegisterSound(const std::string& _key, const std::string& _path, bool _loop = false, float _volume = 0.99f);


	void SetVolume(const std::string& _key, float _volume);
	void StartFadeIn(const std::string& _key);
	void StartFadeOut(const std::string& _key);
	void EnableSound(const std::string& _key);
	void StopSound(const std::string& _key);
private:
	std::unordered_map<std::string, std::unique_ptr<Sound>> sounds_;
	Audio* audio = nullptr;

	SoundManager() = default;

	SoundManager(const SoundManager& _soundManager) = delete;
	SoundManager& operator=(const SoundManager& _soundManager) = delete;
};