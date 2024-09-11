#pragma once
#include "Scene.h"
#include "Thwomp.h"
#include "utils.h"
#include <memory>

class Title :public Scene
{
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	
private:

	int							backGround_;		//背景
	int							title_;				//ロゴ

	Vector2 pos_;
	Vector2 size_;
	float scale_;

	std::unique_ptr<Thwomp>		thwomp_;

};