#pragma once


class Polygon2D
{
public:
	/*Polygon2D();
	~Polygon2D();*/

	void Init();
	void Uninit();
	void Update();
	void Draw();
	


private:

	ComPtr<ID3D11Buffer>			 m_pVertexBuffer = NULL;
	ComPtr<ID3D11ShaderResourceView> m_pTexture		 = NULL;
	ID3D11VertexShader*				 m_pVertexShader = NULL;
	ID3D11PixelShader*				 m_pPixelShader	 = NULL;
	ID3D11InputLayout*				 m_pVertexLayout = NULL;


	/*ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_Texture = NULL;

	ID3D11VertexShader*		m_VertexShader = NULL;
	ID3D11PixelShader*		m_PixelShader = NULL;
	ID3D11InputLayout*		m_VertexLayout = NULL;*/


};

