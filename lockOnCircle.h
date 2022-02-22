#pragma once
#include "gameObject.h"

// ���b�N�I���\���N���X
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
	GameObject* m_Object;						// ���b�N�I���I�u�W�F�N�g
	ID3D11Buffer* m_VertexBuffer;				// ���_�o�b�t�@
	static const std::string TEXTURE_FILE_NAME;	// �e�N�X�`����
};