#include "SceneManager.h"
#include "InGame.h"
#include "Title.h"

void SceneManager::Initialize(sceneName _startScene)
{
	current_ = _startScene;
	next_ = current_;

	switch (_startScene)
	{
	case sceneName::Title:
		currentScenePtr_ = new Title();
		break;
	case sceneName::Game:
		currentScenePtr_ = new InGame();
		break;
	case sceneName::Result:
		break;
	default:
		break;
	}
	currentScenePtr_->Initialize();
}

void SceneManager::Update()
{
	currentScenePtr_->Update();

	if(currentScenePtr_->isChange_)
	{
		switch (current_)
		{
		case sceneName::Title:
			ReserveScene(sceneName::Game);
			break;
		case sceneName::Game:
			ReserveScene(sceneName::Title);
			break;
		case sceneName::Result:
			ReserveScene(sceneName::Game);
			break;
		default:
			break;
		}
	}
}

void SceneManager::Draw()
{
	currentScenePtr_->Draw();

	ChangeScene();
}

void SceneManager::ReserveScene(sceneName _nextScene)
{
	next_ = _nextScene;
}

void SceneManager::ChangeScene()
{
	if (current_ == next_)
		return;

	current_ = next_;

	delete currentScenePtr_;
	currentScenePtr_ = nullptr;

	switch (current_)
	{
	case sceneName::Title:
		currentScenePtr_ = new Title();
		break;
	case sceneName::Game:
		currentScenePtr_ = new InGame();
		break;
	case sceneName::Result:
		break;
	default:
		break;
	}

	currentScenePtr_->Initialize();
}
