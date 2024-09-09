#pragma once
#include "utils.h"
#include "CollisionAtrribute.h"
#include "Rendering.h"
class Camera
{

public:
	void Initialize();
	void Update(bool _isFalling, bool _isReturning, bool _endFall);
	void Draw(const sRendering& _rendring);

	//Vector2 GetScroll(){return scroll; };
	void SetParent(Vector2* _parent) { parent_ = _parent; }


	Vector2 GetShake() { return shake_; }
	sRendering GetRenderringMatrix() { return rendering_; }
	Rect GetRect() const { return screenRect_; };
	sLine GetLine() const { return downLine_; };

	CollisoinAttribute GetCollisoinAttribute() { return CollisoinAttribute::ScreenRect; }
private:
	void Shaking();

	Vector2						pos_;
	Vector2						size_;
	Vector2						scale_;

	Vector2						returnPos_;

	float						rotate_;

	float						moveSpeed_;

	Vector2*					parent_;

	Rect						screenRect_;
	sLine						downLine_;

	sRendering					rendering_;

	bool						isShake_;
	int							currentShakeCount_;
	int							baseShakeCount_;
	Vector2						shake_;


	float						kWindowHeight_;
	float						kWindowWidth_;

#ifdef _DEBUG
	void ShowImgui();
#endif // _DEBUG


};