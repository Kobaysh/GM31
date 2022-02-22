#pragma once
#include "camera.h"

// デバッグ用カメラクラス
class DebugCamera : public Camera
{
private:
public:
	DebugCamera():Camera(){}
	DebugCamera(bool movable):Camera(movable){}
	DebugCamera(bool active, bool movable):Camera(active, movable){}
	void Update()override;
	void Draw()override;

};