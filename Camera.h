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
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	bool GetIsActive() { return m_isActive; }
	XMFLOAT3 GetFront()const { return m_front; }
	XMFLOAT4X4 GetView()const { return m_viewMatrix; }
	
};

