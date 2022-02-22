#pragma once
#include "gameObject.h"

// タイトルパーティクルクラス
class TitleParticle :public GameObject
{
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	// パーティクル作成
	static void Create(float offsetY);
	
	// テクスチャ解放
	static void Unload();


private:
	static ID3D11InputLayout* m_VertexLayout;		// 頂点レイアウト
	static ID3D11VertexShader* m_VertexShader;		// 頂点シェーダー
	static ID3D11PixelShader* m_PixelShader;		// ピクセルシェーダー
	static	ID3D11Buffer* m_VertexBuffer;			// 頂点バッファ
	static ID3D11ShaderResourceView* m_Texture;		// テクスチャ
};