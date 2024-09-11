#pragma once
#include "Matrix3x3.h"

/// matrix3x3>world
/// matrix3x3>view
/// matrix3x3>ortho
/// matrix3x3>viewport
/// matrix3x3>wvpVp
struct sRendering
{
	Matrix3x3 worldMatrix;
	Matrix3x3 viewMatrix;
	Matrix3x3 orthoMatrix;
	Matrix3x3 viewportMatrix;
	Matrix3x3 wvpVpMatrix;

	Matrix3x3 GetwvpVpMat(const Matrix3x3& _worldMat)const;
	Matrix3x3 GetvpVpMat()const;
	Matrix3x3 GetvpVpMat(float _scale)const;
};