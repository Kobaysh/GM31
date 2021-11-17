#pragma once
#include "main.h"
#include "renderer.h"

#define GRAVITY (0.098f * 0.3f)

class GameObject
{
public:
	enum GameObject_State {
		GOS_NONE = -1,
		GOS_ACTIVE,
		GOS_PAUSE,
		GOS_DEAD,
	};
	enum GameObject_Type {
		GOT_NONE = -1,
		GOT_CAMERA,
		GOT_OBJECT3D,
		GOT_OBJECT2D,
		GOT_MAX,
	};
protected:
//	bool m_Destroy = false;
	XMFLOAT3 m_position;
	XMFLOAT3 m_rotation;
	XMFLOAT3 m_scale;
	GameObject_State m_state = GOS_ACTIVE;

	ID3D11VertexShader*		m_VertexShader = NULL;
	ID3D11PixelShader*		m_PixelShader = NULL;
	ID3D11InputLayout*		m_VertexLayout = NULL;

	static bool ms_IsVoidPS;
public:
	
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	void SetPosition(XMFLOAT3 pos) { m_position = pos; }
	virtual void SetRotation(XMFLOAT3 rot) { m_rotation = rot; }
	virtual void SetScale(XMFLOAT3 scale) { m_scale = scale; }
	XMFLOAT3 GetPosition() { return m_position; }
//	void SetDestroy() { m_Destroy = true; }

	void SetDead() { m_state = GOS_DEAD; }
	bool Destroy() {
		if (m_state == GOS_DEAD) {
			Uninit();
			delete this;
			return true;
		}
		else {
			return false;
		}
		/*if (m_Destroy) {
			Uninit();
			delete this;
			return true;
		}
		else{
			return false;
		}*/
	}
	void SetPShader(const char* pFileName){
		Renderer::CreatePixelShader(&m_PixelShader, pFileName);
	}
	void SetVShader(const char* pFileName) {
		Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, pFileName);
	}

	XMFLOAT3 GetObbX()
	{
		XMMATRIX rot, scale, world;
		scale = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
		rot = XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z);
		world = scale * rot;
		XMFLOAT4X4 worldx4;
		XMStoreFloat4x4(&worldx4, world);
		XMFLOAT3 vx = XMFLOAT3(worldx4._11 * 0.5f, worldx4._12 * 0.5f, worldx4._13 * 0.5f);
		return vx;
	}
	XMFLOAT3 GetObbZ()
	{
		XMMATRIX rot, scale, world;
		scale = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
		rot = XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z);
		world = scale * rot;
		XMFLOAT4X4 worldx4;
		XMStoreFloat4x4(&worldx4, world);
		XMFLOAT3 vx = XMFLOAT3(worldx4._31 * 0.5f, worldx4._32 * 0.5f, worldx4._32 * 0.5f);
		return vx;
	}

};

