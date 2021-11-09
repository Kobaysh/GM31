#pragma once
#include "gameObject.h"
class Camera : public GameObject
{

private:
	XMFLOAT3 m_target;
	XMFLOAT3 m_front;
	XMFLOAT3 m_right;
	XMFLOAT3 m_up;
	bool m_isActive;
	bool m_movable;
	XMFLOAT4X4 m_viewMatrix;
	XMFLOAT4X4 m_projectionMatrix;
	XMFLOAT3 m_move;
public:
	Camera():m_movable(false){}
	Camera(bool movable):m_movable(movable){}
	void Init();
	void Uninit();
	void Update();
	void Draw();
	bool GetIsActive() { return m_isActive; }
	bool GetMovable() { return m_movable; }
	void SetMovale(bool movable) { m_movable = movable; }
	XMFLOAT3* GetFront() { return &m_front; }
	XMFLOAT3* GetRight() { return &m_right; }
	XMFLOAT3* GetUp() { return &m_up; }
	XMFLOAT4X4* GetView() { return &m_viewMatrix; }
	bool CheckView(XMFLOAT3 pos);
	XMFLOAT3* GetMove() { return &m_move; }
	float GetSpeed();

	void ChangeDir(float angle, bool isRight);
};

