#pragma once
class Camera
{

private:
	XMFLOAT3 m_vPosition;
	XMFLOAT3 m_vTarget;
	XMFLOAT3 m_vUp;
	
	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Target;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};

