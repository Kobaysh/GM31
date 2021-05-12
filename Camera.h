#pragma once
class Camera
{

private:
	XMVECTOR m_vPosition;
	XMVECTOR m_vTarget;
	XMVECTOR m_vUp;
	
	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Target;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};

