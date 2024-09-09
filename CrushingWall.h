#pragma once
#include "utils.h"

class CrushingWall
{
public:
	void Initialize();
	void Update();
	void Draw(const sRendering& _rendring);

	void OnCollision(size_t _charge);

	Rect GetRect() { return rect_; }

private:
	void Move();

	Rect					rect_;
	Vector2					scale_;
	float					rotate_;

	float					moveSpeed_;

	float					returnValue_[3];

	int						textureHandle_;
	unsigned int			color_;

	bool im_isMove_;
#ifdef _DEBUG
	void ShowImgui();
#endif // _DEBUG
};