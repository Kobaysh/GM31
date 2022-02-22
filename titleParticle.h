#pragma once
#include "gameObject.h"

// �^�C�g���p�[�e�B�N���N���X
class TitleParticle :public GameObject
{
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	// �p�[�e�B�N���쐬
	static void Create(float offsetY);
	
	// �e�N�X�`�����
	static void Unload();


private:
	static ID3D11InputLayout* m_VertexLayout;		// ���_���C�A�E�g
	static ID3D11VertexShader* m_VertexShader;		// ���_�V�F�[�_�[
	static ID3D11PixelShader* m_PixelShader;		// �s�N�Z���V�F�[�_�[
	static	ID3D11Buffer* m_VertexBuffer;			// ���_�o�b�t�@
	static ID3D11ShaderResourceView* m_Texture;		// �e�N�X�`��
};