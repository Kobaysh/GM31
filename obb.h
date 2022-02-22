#pragma once
#include "main.h"
#include "gameObject.h"

// �����蔻��Ǘ��N���X
class OBB : public GameObject
{
private:
	static ID3D11VertexShader*		m_VertexShader;			// ���_�V�F�[�_�[
	static ID3D11PixelShader*		m_PixelShader;			// �s�N�Z���V�F�[�_�[
	static ID3D11InputLayout*		m_VertexLayout;			// ���_���C�A�E�g
															
	static const char* FILENAME_BLUE;						// �e�N�X�`������
	static const char* FILENAME_RED;						// �e�N�X�`������
															 
	ID3D11Buffer*				m_VertexBuffer = nullptr;	// ���_�o�b�t�@
	ID3D11Buffer*				m_Indexbuffer = nullptr;	// �C���f�b�N�X�o�b�t�@
	ID3D11RasterizerState* m_RasterrizerState = nullptr;	// ���X�^���C�U�X�e�[�g
																														
	bool m_IsDraw = false;									// �`�悷�邩
	bool m_IsCollide = false;								// �������Ă��邩
	bool m_WasCollide = false;								// ����������
protected:
	XMFLOAT3 m_NormalDirect[3];								// �����x�N�g��
	float m_Length[3];										// �e�������̒���

public:
	static bool m_IsDrawAll;					// �`�悷�邩(�S��)
	static bool m_IsDrawForwardRightUp;			// ����������`�悷�邩

	//�@����
	enum OBB_Direction {
		OBB_DX,		// X����
		OBB_DY,		// Y����
		OBB_DZ,		// Z����
	};
	OBB(){
		m_NormalDirect[0] = XMFLOAT3(1.0f,0.0f,0.0f);
		m_NormalDirect[1] = XMFLOAT3(0.0f,1.0f,0.0f);
		m_NormalDirect[2] = XMFLOAT3(0.0f,0.0f,1.0f);
		m_Length[0] = 0.5f;
		m_Length[1] = 0.5f;
		m_Length[2] = 0.5f;
	}

	OBB(XMFLOAT3 pos, XMFLOAT3 size) {
		m_NormalDirect[0] = XMFLOAT3(1.0f, 0.0f, 0.0f);
		m_NormalDirect[1] = XMFLOAT3(0.0f, 1.0f, 0.0f);
		m_NormalDirect[2] = XMFLOAT3(0.0f, 0.0f, 1.0f);
		m_Position = pos;
		m_Length[0] = size.x * 0.5f; 
		m_Length[1] = size.y * 0.5f;
		m_Length[2] = size.z * 0.5f;
		m_Scale = size;
	}
	OBB(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 size) {
		m_NormalDirect[0] = XMFLOAT3(1.0f, 0.0f, 0.0f);
		m_NormalDirect[1] = XMFLOAT3(0.0f, 1.0f, 0.0f);
		m_NormalDirect[2] = XMFLOAT3(0.0f, 0.0f, 1.0f);
		m_Position = pos;
		SetRotation(rot);
		m_Length[0] = size.x * 0.5f;
		m_Length[1] = size.y * 0.5f;
		m_Length[2] = size.z * 0.5f;
		m_Scale = size;
	}
	void SetScale(XMFLOAT3 size)override {
		m_Length[0] = size.x * 0.5f;
		m_Length[1] = size.y * 0.5f;
		m_Length[2] = size.z * 0.5f;
		m_Scale = size;
	}

	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	// �����Q�b�^�[
	XMFLOAT3 GetDirect(OBB_Direction elem) { return m_NormalDirect[elem]; }

	// �����Q�b�^�[
	float GetLen_W(OBB_Direction elem) { return m_Length[elem]; }

	// ���W�Q�b�^�[
	XMFLOAT3 GetPos_W() { return m_Position; }

	// ��]���Z�b�^�[
	void SetRotation(XMFLOAT3 rotationSpeed)override;
	void SetRotation(XMFLOAT3 rotation, XMFLOAT3 rotationSpeed);
	void SetRotationFromForwardRightVector(XMFLOAT3 forward, XMFLOAT3 right);
	void SetRotationFromForwardRightVector(XMFLOAT3 forward, XMFLOAT3 right, XMFLOAT3 rot);

	// �����蔻��֐�
	static bool ColOBBs(OBB &obb1, OBB &obb2);

	// �`�悷�邩(�S��)
	static bool GetIsColShow() { return m_IsDrawAll; }

	// �`���ԃZ�b�^�[(�S��)
	static void SetIsColShow(bool show) { m_IsDrawAll = show; }

	// �`���ԃZ�b�^�[(�P��)
	void SetisDraw(bool isDraw) { m_IsDraw = isDraw; }

	// �����蔻��Z�b�^�[
	void SetisCollide(bool isCollide) { m_IsCollide = isCollide; }
};