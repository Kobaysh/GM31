#pragma once
#include "main.h"
#include "gameObject.h"

class OBB : public GameObject
{
private:
	static ID3D11VertexShader*		m_VertexShader;
	static ID3D11PixelShader*		m_PixelShader;
	static ID3D11InputLayout*		m_VertexLayout;

	static const char* FILENAME_BLUE;
	static const char* FILENAME_RED;

	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11Buffer*				m_Indexbuffer = NULL;
	ID3D11RasterizerState* m_pRasterrizerState = nullptr;


	bool m_isDraw = false;
	bool m_isCollide = false;
	bool m_wasCollide = false;
protected:
//	XMFLOAT3 m_pos;				// 位置
	XMFLOAT3 m_normaDirect[3];	// 方向ベクトル
	float m_fLength[3];			// 各軸方向の長さ

public:
	enum OBB_Direction {
		OBB_DX,
		OBB_DY,
		OBB_DZ,
	};
	OBB(){
		m_normaDirect[0] = XMFLOAT3(1.0f,0.0f,0.0f);
		m_normaDirect[1] = XMFLOAT3(0.0f,1.0f,0.0f);
		m_normaDirect[2] = XMFLOAT3(0.0f,0.0f,1.0f);
		m_fLength[0] = 0.5f;
		m_fLength[1] = 0.5f;
		m_fLength[2] = 0.5f;
	}

	OBB(XMFLOAT3 pos, XMFLOAT3 size) {
		m_normaDirect[0] = XMFLOAT3(1.0f, 0.0f, 0.0f);
		m_normaDirect[1] = XMFLOAT3(0.0f, 1.0f, 0.0f);
		m_normaDirect[2] = XMFLOAT3(0.0f, 0.0f, 1.0f);
		m_Position = pos;
		m_fLength[0] = size.x * 0.5f; 
		m_fLength[1] = size.y * 0.5f;
		m_fLength[2] = size.z * 0.5f;
		m_Scale = size;
	}
	OBB(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 size) {
		m_normaDirect[0] = XMFLOAT3(1.0f, 0.0f, 0.0f);
		m_normaDirect[1] = XMFLOAT3(0.0f, 1.0f, 0.0f);
		m_normaDirect[2] = XMFLOAT3(0.0f, 0.0f, 1.0f);
		m_Position = pos;
		SetRotation(rot);
		m_fLength[0] = size.x * 0.5f;
		m_fLength[1] = size.y * 0.5f;
		m_fLength[2] = size.z * 0.5f;
		m_Scale = size;
	}
	void SetScale(XMFLOAT3 size)override {
		m_fLength[0] = size.x * 0.5f;
		m_fLength[1] = size.y * 0.5f;
		m_fLength[2] = size.z * 0.5f;
		m_Scale = size;
	}

	XMFLOAT3 GetDirect(OBB_Direction elem) { return m_normaDirect[elem]; }
	float GetLen_W(OBB_Direction elem) { return m_fLength[elem]; }
	XMFLOAT3 GetPos_W() { return m_Position; }

	void SetRotation(XMFLOAT3 rotationSpeed)override;
	void SetRotation(XMFLOAT3 rotation, XMFLOAT3 rotationSpeed);


	void SetRotationFromForwardRightVector(XMFLOAT3 forward, XMFLOAT3 right);
	void SetRotationFromForwardRightVector(XMFLOAT3 forward, XMFLOAT3 right, XMFLOAT3 rot);

	static bool ColOBBs(OBB &obb1, OBB &obb2);
	static bool GetIsColShow() { return m_bIsDraw; }
	static void SetIsColShow(bool show) { m_bIsDraw = show; }
	void SetisDraw(bool isDraw) { m_isDraw = isDraw; }
	void SetisCollide(bool isCollide) { m_isCollide = isCollide; }

	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static bool m_bIsDraw;
	static bool m_bIsDrawForwardRightUp;
};