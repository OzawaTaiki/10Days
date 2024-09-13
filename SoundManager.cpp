#include "SoundManager.h"
#include "Audio.h"
#include "ImGuiManager.h"

void SoundManager::Initilize()
{
	audio = Audio::GetInstance();
	sounds_.clear();
}

void SoundManager::Update()
{
#ifdef _DEBUG
	ImGui::Begin("Sound");
#endif // _DEBUG

	for (auto it = sounds_.begin(); it != sounds_.end(); ++it) 
	{
		it->second->ShowImgui();
		it->second->Update();
	}
#ifdef _DEBUG
	ImGui::End();
#endif // _DEBUG
}

void SoundManager::Play()
{
	for (auto it = sounds_.begin(); it != sounds_.end(); ++it)
	{
		it->second->Play();
	}
}

void SoundManager::RegisterSound(const std::string& _key, const std::string& _path, bool _loop, float _volume)
{
	uint32_t soundHandle = audio->LoadWave(_path);
	
	sounds_[_key] = std::make_unique<Sound>();
	sounds_[_key]->Initilize(_key, soundHandle,_volume, _loop);
}

void SoundManager::SetVolume(const std::string& _key, float _volume)
{
	sounds_[_key]->SetBaseVolume(_volume);
}

void SoundManager::StartFadeIn(const std::string& _key)
{
	sounds_[_key]->EnableFadeIn();
}

void SoundManager::StartFadeOut(const std::string& _key)
{
	sounds_[_key]->EnableFadeOut();
}

void SoundManager::EnableSound(const std::string& _key)
{
	sounds_[_key]->EnableSound();
}
