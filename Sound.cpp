#include "Sound.h"
#include "utils.h"
#include "Audio.h"
#include "ImGuiManager.h" 

void Sound::Initilize(const std::string& _key, uint32_t _soundHandle, float _volume, bool _loop)
{
	key_ = _key;

	soundHandle_ = _soundHandle;
	voiceHandle_ = 512;

	volume_ = _volume;
	baseVolume_ = volume_;

	loop_ = _loop;

	t_ = 1.0f;
	deltaT_ = 0.01f;
	audio_ = Audio::GetInstance();

}
void Sound::Update()
{
	if (isFadeInEnabled_)
	{
		isFadeInEnabled_ = false;
		isFadingIn_ = true;
		volume_ = 0;
		t_ = 0.5f;
	}

	if (isFadeIOutnabled_)
	{
		isFadeIOutnabled_ = false;
		isFadingOut_ = true;
		volume_ = 1.0f;
		t_ = 1.0f;
	}

	if (isFadingIn_)
		FadeIn();
	if (isFadingOut_)
		FadeOut();
}

void Sound::Play()
{
	if (!isPlay_)
		return;

	if (loop_ && !audio_->IsPlaying(voiceHandle_) && voiceHandle_ == 512)
		voiceHandle_ = audio_->PlayWave(soundHandle_, loop_, volume_);
	else if (!loop_ )
		voiceHandle_ = audio_->PlayWave(soundHandle_, loop_, volume_);
	isPlay_ = false;
}

void Sound::SetBaseVolume(float _volume)
{
	baseVolume_ = _volume;
	volume_ = baseVolume_;
	SetVolume();
}

void Sound::StopSound()
{
	audio_->StopWave(voiceHandle_);
}

void Sound::FadeIn()
{
	// でかくなる
	t_ += deltaT_;
	if (t_ >= 1.0f)
	{
		t_ = 1.0f;
		isFadingIn_ = false;
	}

	volume_ = baseVolume_ * t_;
	SetVolume();
}

void Sound::FadeOut()
{
	// 小さくなる
	t_ -= deltaT_;
	if (t_ <= 0)
	{
		t_ = 0;
		isFadingOut_ = false;
	}

	volume_ = baseVolume_ * t_;
	SetVolume();
}

void Sound::SetVolume()
{
	audio_->SetVolume(voiceHandle_, volume_);
}

void Sound::ShowImgui()
{
#ifdef _DEBUG

	ImGui::BeginTabBar("Sound");
	if (ImGui::BeginTabItem(key_.c_str()))
	{
		ImGui::Text("%s", key_.c_str());
		ImGui::Text("handle %d", soundHandle_);
		ImGui::Text("vhandle %d", voiceHandle_);
		if (ImGui::DragFloat("volume", &volume_, 0.001f))
			SetVolume();
		ImGui::Checkbox("play", &isPlay_);
		ImGui::EndTabItem();
	}
	ImGui::EndTabBar();

#endif // _DEBUG

}
