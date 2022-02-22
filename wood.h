#pragma once
#include "gameObject.h"

class Wood : public GameObject
{
private:

	ID3D11Buffer* m_VertexBuffer = nullptr;			// 頂点バッファ
	ID3D11ShaderResourceView* m_Texture = nullptr;	// テクスチャ
	XMFLOAT2 m_TextureOffset;						// テクスチャオフセット
	float m_OffsetY;								// 高さオフセット
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};

