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

private:
	void LoadFile();

	std::vector<std::vector<uint32_t>>	maps_;

	std::stringstream					mapchipData_;

	const float							kMapchipSize_					= 64.0f;

};