#pragma once
#include "gameObject.h"
class Camera : public GameObject
{

private:
	XMFLOAT3 m_target;
	XMFLOAT3 m_front;
	XMFLOAT3 m_right;
	XMFLOAT3 m_up;
	
//	D3DXVECTOR3 m_Position;
//	D3DXVECTOR3 m_target;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};

