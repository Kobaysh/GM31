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
	XMFLOAT4X4 m_viewMatrix;
	XMFLOAT3 m_move;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	bool GetIsActive() { return m_isActive; }
	XMFLOAT3* GetFront() { return &m_front; }
	XMFLOAT3* GetRight() { return &m_right; }
	XMFLOAT3* GetUp() { return &m_up; }
	XMFLOAT4X4* GetView() { return &m_viewMatrix; }
	XMFLOAT3* GetMove() { return &m_move; }
	float GetSpeed();
};

