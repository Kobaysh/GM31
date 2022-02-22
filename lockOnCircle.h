#pragma once
#include "gameObject.h"

class LockOnCircle : public GameObject
{
public:
	LockOnCircle(){}
	LockOnCircle(GameObject* obj):m_Object(obj){}
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
	GameObject* m_Object;
	ID3D11Buffer* m_VertexBuffer;
	static const std::string TEXTURE_FILE_NAME;
};