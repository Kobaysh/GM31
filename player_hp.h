#pragma once
#include "gameObject.h"

// �v���C���[HP�o�[�N���X
class HpPlayer : public GameObject
{
private:	
	int m_NowHP;					// ����HP
	int m_MaxHP;					// �ő�HP
	ID3D11Buffer* m_VertexBuffer;	// ���_�o�b�t�@
public:
	void Init()override;
	void Init(XMFLOAT3 pos, XMFLOAT3 scale, int nowHP, int maxHP);
	void Uninit()override;
	void Update()override{}
	void Draw()override;

	// �o�[�\��
	void Draw_Bar(XMFLOAT4 color, float perHP);

	// �o�[�O�g�\��
	void Draw_OutLine(XMFLOAT4 color);

	// HP�Z�b�^�[
	void SetHP(int nowHp, int maxHP) { m_NowHP = nowHp, m_MaxHP = maxHP; }
};