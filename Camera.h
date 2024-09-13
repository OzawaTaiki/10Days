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
	void SetParent(Vector2* _parent);
	void SetMovableRange(const Vector2& _min, const Vector2& _max) { minMovableRange_ = _min; maxMovableRange_ = _max; };

	Vector2 GetShake() { return shake_; }
	Vector2 GetMove() { return move_; }
	sRendering GetRenderringMatrix() { return rendering_; }
	Rect GetRect() const { return screenRect_; };
	sLine GetLine() const { return downLine_; };

	CollisoinAttribute GetCollisoinAttribute() { return CollisoinAttribute::ScreenRect; }

	void				StartStagingFromTitle(bool _endFall);
private:
	void Shaking();
	void Clamp();

	Vector2						pos_;
	Vector2						size_;
	Vector2						scale_;
	Vector2 move_;

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

	Vector2						minMovableRange_;
	Vector2						maxMovableRange_;

	float						kWindowHeight_;
	float						kWindowWidth_;

	void ShowImgui();


};