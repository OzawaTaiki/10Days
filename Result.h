#pragma once

#include "Scene.h"

class Result :public Scene
{
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;


};