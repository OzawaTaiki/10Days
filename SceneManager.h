#pragma once
#include "Scene.h"
#include "utils.h"
#include <cstdint>

enum class sceneName
{
	Title,
	FromTitle,
	Game,
	Result
};

class SceneManager
{
public:
	static SceneManager*	GetInstance() { static SceneManager instance; return &instance; }

	void					Initialize(sceneName _startScene, const Vector2& _windowSize = { 1280,720 });
	void					Update();
	void					Draw();


private:
	SceneManager() = default;

	void					ReserveScene(sceneName _nextScene);
	void					ChangeScene();

	void					StartTransition();
	void					EndTransition();
	void					SceneTransition();

	sceneName						current_				= static_cast<sceneName>(1);
	sceneName						next_					= static_cast<sceneName>(1);
	sceneName						previous_				= static_cast<sceneName>(1);


	Scene*							currentScenePtr_			=nullptr;

	Vector2							windowSize_;
	uint32_t						rgb_						= 0;
	uint8_t							alpha_						= 0x3f;

	bool							fadeOut_					= false;
	bool							fadeIn_						= false;
	bool							isSceneChange_				= false;
	bool							isReserve_					= false;
	bool							completeTransition_			= true;

	uint32_t score_ = 0;
	int returnValue_ = 0;

	SceneManager(const SceneManager& _sceneManager) = delete;
	SceneManager& operator=(const SceneManager& _sceneManager) = delete;
};