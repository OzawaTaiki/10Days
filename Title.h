#pragma once
#include "Scene.h"

class Title :public Scene
{
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	

};