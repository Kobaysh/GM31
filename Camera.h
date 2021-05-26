#pragma once
#include "gameObject.h"
class Camera : public GameObject
{

private:
	XMFLOAT3 m_vTarget;
	XMFLOAT3 m_vUp;
	
//	D3DXVECTOR3 m_Position;
//	D3DXVECTOR3 m_Target;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};

