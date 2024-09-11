#pragma once
#include "utils.h"
#include <vector>
#include <sstream>


class Stage 
{
public:
	void Initialize();
	void Update();
	void Draw(const sRendering& _rendring);
	
	bool CollisionCheck(Rect& _rect, Vector2& _moveDir);

	float GetMapchipSize() { return kMapchipSize_; }
	Vector2 GetMapSize() { return {(float) maps_[0].size(),(float)maps_.size()}; }

private:
	void LoadFile();

	void Clamp(Rect& _rect, Vector2& _move);

	std::vector<std::vector<uint32_t>>	maps_;

	std::stringstream					mapchipData_;

	const float							kMapchipSize_					= 64.0f;

};