#pragma once
#include "gameObject.h"

class Bullet :public GameObject
{
public:
	Bullet();
	Bullet(XMFLOAT3 f3Position);
	void Init();
	void Uninit();
	void Update();
	void Draw();

	static void Load();
	static void UnLoad();

	static Bullet* Create(XMFLOAT3 f3Position, XMFLOAT3 f3Direction, float fSpeed);
	static void Destroy(Bullet* pBullet);
	class OBB& GetOBB() { return *m_obb; }

//	OBB& GetObb() { return *m_obb; }
private:
//	Model* m_model;
	XMFLOAT3 m_direction;
	float m_speed;
	static  int ms_modelId;
	class OBB* m_obb;

	static ID3D11VertexShader*		m_VertexShader;
	static ID3D11PixelShader*		m_PixelShader;
	static ID3D11InputLayout*		m_VertexLayout;
};