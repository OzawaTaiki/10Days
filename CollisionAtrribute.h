#pragma once
#include <cstdint>

enum class CollisoinAttribute
{
	Thwomp					= 0b00000001,
	DefenceTarget			= 0b00000010,
	ScreenRect				= 0b00000011,
	CrushingWall			= 0b00000100,
	Enemy					= 0b00000101,
	Stage					= 0b00000110,
	KnockbacKRect			= 0b00000111
};

