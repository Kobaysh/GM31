#pragma once
#include "main.h"
#include "renderer.h"

#define GRAVITY (0.098f * 0.3f)

// �Q�[���I�u�W�F�N�g�C���^�[�t�F�[�X
class GameObject
{
public:
	// �I�u�W�F�N�g�̏��
	enum GameObject_State 
	{
		GOS_NONE = -1,
		GOS_ACTIVE,
		GOS_PAUSE,
		GOS_DEAD,
	};
	// �I�u�W�F�N�g�̎��
	enum GameObject_Type 
	{
		GOT_NONE = -1,
		GOT_CAMERA,
		GOT_OBJECT3D,
		GOT_OBJECT2D,
		GOT_MAX,
	};
	// ����
	struct GameObject_Direction
	{
		XMFLOAT3 Forward;
		XMFLOAT3 Right;
		XMFLOAT3 Up;
	};
protected:

	XMFLOAT3 m_Position;								// ���W
	XMFLOAT3 m_Rotation;								// ��]
	XMFLOAT3 m_Scale;									// �g�嗦
	GameObject_Direction m_Direction;					// ����
														
	GameObject_State m_GOState = GOS_ACTIVE;			// ���
														 
	ID3D11VertexShader*		m_VertexShader = nullptr;	// ���_�V�F�[�_�[
	ID3D11PixelShader*		m_PixelShader = nullptr;	// �s�N�Z���V�F�[�_�[
	ID3D11InputLayout*		m_VertexLayout = nullptr;	// ���_���C�A�E�g	

public:
	
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// ���W�Z�b�^�[
	void SetPosition(XMFLOAT3 pos) { m_Position = pos; }

	// ��]���Z�b�^�[
	virtual void SetRotation(XMFLOAT3 rot) { m_Rotation = rot; }

	// �g�嗦�Z�b�^�[
	virtual void SetScale(XMFLOAT3 scale) { m_Scale = scale; }

	// ���W�Q�b�^�[
	XMFLOAT3 GetPosition() { return m_Position; }

	// ��]���Q�b�^�[
	XMFLOAT3 GetRotation() { return m_Rotation; }
	
	// �����Q�b�^�[
	GameObject_Direction* GetDirection() { return &m_Direction; }

	// ���S��ԂɃZ�b�g
	void SetDead() { m_GOState = GOS_DEAD; }

	// ���S��ԂȂ�I�u�W�F�N�g�폜
	bool Destroy() {
		if (m_GOState == GOS_DEAD) {
			Uninit();
			delete this;
			return true;
		}
		else {
			return false;
		}
	}

	// �s�N�Z���V�F�[�_�[�쐬
	void SetPShader(const char* pFileName){
		Renderer::CreatePixelShader(&m_PixelShader, pFileName);
	}

	// ���_�V�F�[�_�[�쐬
	void SetVShader(const char* pFileName) {
		Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, pFileName);
	}
};

