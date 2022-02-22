#pragma once
#include "gameObject.h"

class TitleParticle :public GameObject
{
public:


	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static void Create(float offsetY);
	static void Unload();


private:
	static ID3D11InputLayout* m_sVertexLayout;
	static ID3D11VertexShader* m_sVertexShader;
	static ID3D11PixelShader* m_sPixelShader;
	static	ID3D11Buffer*			m_VertexBuffer;
	static ID3D11ShaderResourceView* m_Texture;
};