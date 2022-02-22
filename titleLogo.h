#pragma once
#include "gameObject.h"

// タイトルロゴクラス
class TitleLogo : public GameObject
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
private:
	ID3D11Buffer*				m_VertexBuffer = nullptr;	// 頂点バッファ
	ID3D11ShaderResourceView*	m_Texture = nullptr;		// テクスチャ


	ID3D11Buffer*				m_VertexBuffer2 = nullptr;	// 頂点バッファ2
	ID3D11ShaderResourceView*	m_Texture2 = nullptr;		// テクスチャ2
};

