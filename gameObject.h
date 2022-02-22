#pragma once
#include "main.h"
#include "renderer.h"

#define GRAVITY (0.098f * 0.3f)

class GameObject
{
public:
	enum GameObject_State 
	{
		GOS_NONE = -1,
		GOS_ACTIVE,
		GOS_PAUSE,
		GOS_DEAD,
	};
	enum GameObject_Type 
	{
		GOT_NONE = -1,
		GOT_CAMERA,
		GOT_OBJECT3D,
		GOT_OBJECT2D,
		GOT_MAX,
	};
	struct GameObject_Direction
	{
		XMFLOAT3 Forward;
		XMFLOAT3 Right;
		XMFLOAT3 Up;
	};
protected:

	XMFLOAT3 m_Position;
	XMFLOAT3 m_Rotation;
	XMFLOAT3 m_Scale;
	GameObject_Direction m_Direction;

	GameObject_State m_GOState = GOS_ACTIVE;

	ID3D11VertexShader*		m_VertexShader = nullptr;
	ID3D11PixelShader*		m_PixelShader = nullptr;
	ID3D11InputLayout*		m_VertexLayout = nullptr;

public:
	
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	void SetPosition(XMFLOAT3 pos) { m_Position = pos; }
	virtual void SetRotation(XMFLOAT3 rot) { m_Rotation = rot; }
	virtual void SetScale(XMFLOAT3 scale) { m_Scale = scale; }
	XMFLOAT3 GetPosition() { return m_Position; }
	XMFLOAT3 GetRotation() { return m_Rotation; }
	GameObject_Direction* GetDirection() { return &m_Direction; }

	void SetDead() { m_GOState = GOS_DEAD; }
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
	void SetPShader(const char* pFileName){
		Renderer::CreatePixelShader(&m_PixelShader, pFileName);
	}
	void SetVShader(const char* pFileName) {
		Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, pFileName);
	}
};

