#include "SceneManager.h"
#include "InGame.h"
#include "Title.h"
#include "Result.h"
#include "ChangeSceneFromTitle.h"
#include "ImGuiManager.h"
#include "SoundManager.h"

void SceneManager::Initialize(sceneName _startScene, const Vector2& _windowSize)
{
	windowSize_ = _windowSize;
	rgb_ = 0x000000;
	alpha_ = 0x3f;

	previous_ = _startScene;
	current_ = _startScene;
	next_ = current_;

	switch (_startScene)
	{
	case sceneName::Title:
		currentScenePtr_ = new Title();
		break;
	case sceneName::FromTitle:
		currentScenePtr_ = new FromTitle();
		break;
	case sceneName::Game:
		currentScenePtr_ = new InGame();
		break;
	case sceneName::Result:
		currentScenePtr_ = new Result(0);
		break;
	default:
		break;
	}
	currentScenePtr_->Initialize();
}

void SceneManager::Update()
{
#ifdef _DEBUG
	//ImGui::Begin("sceneManager");
	//ImGui::End();
#endif // _DEBUG


	if (completeTransition_)
	{
		currentScenePtr_->Update();
		isReserve_ = currentScenePtr_->isChange_;
	}

	if (isReserve_)
	{
		StartTransition();

		switch (current_)
		{
		case sceneName::Title:
			ReserveScene(sceneName::FromTitle);
			break;
		case sceneName::FromTitle:
			ReserveScene(sceneName::Game);
			break;
		case sceneName::Game:
			score_ = dynamic_cast<InGame*>(currentScenePtr_)->GetScore();
			ReserveScene(sceneName::Result);
			break;
		case sceneName::Result:
			returnValue_ = dynamic_cast<Result*>(currentScenePtr_)->GetNextValue_();
			if (returnValue_ == 0)
				ReserveScene(sceneName::Game);
			else
				ReserveScene(sceneName::Title);
			break;
		default:
			break;
		}
	}
}

void SceneManager::Draw()
{
	currentScenePtr_->Draw();

	if (isSceneChange_)
		SceneTransition();
}

void SceneManager::ReserveScene(sceneName _nextScene)
{
	previous_ = current_;
	next_ = _nextScene;
}

void SceneManager::ChangeScene()
{
	current_ = next_;

	delete currentScenePtr_;
	currentScenePtr_ = nullptr;

	switch (current_)
	{
	case sceneName::Title:
		currentScenePtr_ = new Title();
		break;
	case sceneName::FromTitle:
		currentScenePtr_ = new FromTitle();
		break;
	case sceneName::Game:
		currentScenePtr_ = new InGame();
		break;
	case sceneName::Result:
		currentScenePtr_ = new Result(score_);
		break;
	default:
		break;
	}

	currentScenePtr_->Initialize();

}

void SceneManager::StartTransition()
{
	completeTransition_ = false;
	isSceneChange_ = true;
	fadeOut_ = true;
	fadeIn_ = false;
	isReserve_ = false;
}

void SceneManager::EndTransition()
{
	completeTransition_ = true;
	isSceneChange_ = false;
	fadeOut_ = false;
	fadeIn_ = true;
	isReserve_ = false;
}

void SceneManager::SceneTransition()
{
	if (current_ == sceneName::Title && next_ == sceneName::FromTitle)
	{
		EndTransition();
		ChangeScene();
		return;
	}

	if (fadeOut_)
	{
		alpha_ += 0x5;
		if (alpha_ >= 0xff - 0x5)
		{
			alpha_ = 0xff;
			fadeOut_ = false;
			fadeIn_ = true;
			ChangeScene();
		}
	}
	else if(fadeIn_)
	{
		{
			alpha_ -= 0x5;
			if (alpha_ <= 0x3f)
			{
				alpha_ = 0x3f;
				EndTransition();
			}
		}
	}

	uint32_t color;
	color = rgb_;
	color <<= 2;
	color += alpha_;

	Novice::DrawBox(0, 0, (int)windowSize_.x, (int)windowSize_.y, 0, color, kFillModeSolid);

}
