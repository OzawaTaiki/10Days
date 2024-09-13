#pragma once
#include "utils.h"
#include <vector>
#include <sstream>

class DefenceTarget;

class Stage 
{
public:
	void Initialize();
	void Update();
	void Draw(const sRendering& _rendring);
	
	bool CollisionCheck(Rect& _rect, Vector2& _move);

	float GetMapchipSize() { return kMapchipSize_; }
	Vector2 GetMapSize() { 
		return { (float)(maps_[nowMapNum_][0].size() * mapCount_),(float)maps_[nowMapNum_].size() };
	}
	bool CollisionWithPrincess(DefenceTarget* _target);

private:
	void LoadFile(uint32_t _num);

	void Clamp(Rect& _rect, Vector2& _move);

	void DrawNumber(const sRendering& _rendring);
	float mapSegmentWidth_;
	uint32_t nowMapNum_;
	std::vector<uint32_t>drawMapNum_;
	uint32_t mapCount_ = 10;

	std::vector<std::vector<std::vector<uint32_t>>>	maps_;

	std::stringstream					mapchipData_;

	const float							kMapchipSize_					= 64.0f;
	int textureHandle_[2];

};