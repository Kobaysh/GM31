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

	ID3D11Buffer*				m_VertexBuffer = nullptr;
	ID3D11Buffer*				m_Indexbuffer = nullptr;
	ID3D11RasterizerState* m_RasterrizerState = nullptr;


	bool m_IsDraw = false;
	bool m_IsCollide = false;
	bool m_WasCollide = false;
protected:
//	XMFLOAT3 m_pos;				// 位置
	XMFLOAT3 m_NormalDirect[3];	// 方向ベクトル
	float m_Length[3];			// 各軸方向の長さ

public:
	enum OBB_Direction {
		OBB_DX,
		OBB_DY,
		OBB_DZ,
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

	XMFLOAT3 GetDirect(OBB_Direction elem) { return m_NormalDirect[elem]; }
	float GetLen_W(OBB_Direction elem) { return m_Length[elem]; }
	XMFLOAT3 GetPos_W() { return m_Position; }

	void SetRotation(XMFLOAT3 rotationSpeed)override;
	void SetRotation(XMFLOAT3 rotation, XMFLOAT3 rotationSpeed);


	void SetRotationFromForwardRightVector(XMFLOAT3 forward, XMFLOAT3 right);
	void SetRotationFromForwardRightVector(XMFLOAT3 forward, XMFLOAT3 right, XMFLOAT3 rot);

	static bool ColOBBs(OBB &obb1, OBB &obb2);
	static bool GetIsColShow() { return m_SIsDraw; }
	static void SetIsColShow(bool show) { m_SIsDraw = show; }
	void SetisDraw(bool isDraw) { m_IsDraw = isDraw; }
	void SetisCollide(bool isCollide) { m_IsCollide = isCollide; }

	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static bool m_SIsDraw;
	static bool m_SIsDrawForwardRightUp;
};