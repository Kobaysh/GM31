#pragma once
#include "main.h"
#include "renderer.h"

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
	XMFLOAT3 m_Position;
	XMFLOAT3 m_Rotation;
	XMFLOAT3 m_Scale;
	GameObject_State m_state = GOS_ACTIVE;

	ID3D11VertexShader*		m_VertexShader = NULL;
	ID3D11PixelShader*		m_PixelShader = NULL;
	ID3D11InputLayout*		m_VertexLayout = NULL;

	bool m_isVoidPS = false;
	static bool m_sIsVoidPS;
public:
	
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	void SetPosition(XMFLOAT3 pos) { m_Position = pos; }
	XMFLOAT3 GetPosition() { return m_Position; }
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
};

