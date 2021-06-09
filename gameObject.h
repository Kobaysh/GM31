#pragma once
#include "main.h"
class GameObject
{
public:
	enum GameObject_State {
		NONE = -1,
		ACTIVE,
		PAUSE,
		DEAD,
	};
protected:
//	bool m_Destroy = false;
	XMFLOAT3 m_Position;
	XMFLOAT3 m_Rotation;
	XMFLOAT3 m_Scale;
	GameObject_State m_state = ACTIVE;

	ID3D11VertexShader*		m_VertexShader = NULL;
	ID3D11PixelShader*		m_PixelShader = NULL;
	ID3D11InputLayout*		m_VertexLayout = NULL;

public:
	
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	void SetPosition(XMFLOAT3 pos) { m_Position = pos; }
	XMFLOAT3 GetPosition() { return m_Position; }
//	void SetDestroy() { m_Destroy = true; }

	void SetDead() { m_state = DEAD; }
	bool Destroy() {
		if (m_state == DEAD) {
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
};

