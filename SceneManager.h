#pragma once
#include "Scene.h"

enum class sceneName
{
	Title,
	Game,
	Result
};

class SceneManager
{
public:
	static SceneManager*	GetInstance() { static SceneManager instance; return &instance; }

	void					Initialize(sceneName _startScene);
	void					Update();
	void					Draw();


private:
	SceneManager() = default;

	void					ReserveScene(sceneName _nextScene);
	void					ChangeScene();

	sceneName						current_				= static_cast<sceneName>(1);
	sceneName						next_					= static_cast<sceneName>(1);

	Scene*							currentScenePtr_			=nullptr;


	SceneManager(const SceneManager& _sceneManager) = delete;
	SceneManager& operator=(const SceneManager& _sceneManager) = delete;
};