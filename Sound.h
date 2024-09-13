#pragma once
#include <cstdint>
#include <string>

class Audio;
class Sound
{
public:
	void Initilize(const std::string& _key, uint32_t _soundHandle, float _volume, bool _loop = false);
	void Update();
	void Play();

	void EnableFadeIn()		{ isFadeInEnabled_ = true; }
	void EnableFadeOut()	{ isFadeIOutnabled_ = true; }
	void EnableSound()		{ isPlay_= true; }

	void SetBaseVolume(float _volume);

	void ShowImgui();

private:
	void FadeIn();
	void FadeOut();
	void SetVolume();

	Audio* audio_ = nullptr;

	std::string				key_;

	uint32_t				soundHandle_					= 0;
	uint32_t				voiceHandle_					= 0;

	float					volume_;
	float					baseVolume_;
	bool					loop_							= false;

	// 処理中か否か
	bool					isFadingIn_						= false;
	// 処理中か否か
	bool					isFadingOut_					= false;

	// 行うか否か
	bool					isFadeInEnabled_				= false;
	// 行うか否か
	bool					isFadeIOutnabled_				= false;

	bool					isPlay_							= false;

	// フェード用の媒介変数
	float					t_;
	// ｔの変化量
	float					deltaT_;

};