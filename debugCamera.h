#pragma once
#include "camera.h"

// �f�o�b�O�p�J�����N���X
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