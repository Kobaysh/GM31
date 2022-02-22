#pragma once
#include "gameObject.h"

// �̊��o�[�N���X
class TrunkBar : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer;		// ���_�o�b�t�@
	class Enemy* m_Enemy;				// �G�|�C���^�[
public:
	void Init()override;
	void Init(class Enemy* pEnemy);
	void Uninit()override;
	void Update()override{}
	void Draw()override;

	// �o�[�`��
	void Draw_Bar(XMFLOAT4 color, float perHP);
};