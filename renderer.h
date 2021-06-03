#pragma once

#include "Singleton.h"

using Microsoft::WRL::ComPtr;

struct VERTEX_3D
{
    D3DXVECTOR3 Position;
    D3DXVECTOR3 Normal;
    D3DXVECTOR4 Diffuse;
    D3DXVECTOR2 TexCoord;
};

struct VERTEX_3DX
{
	XMFLOAT3	Position;
	XMFLOAT3	Normal;
	XMFLOAT4	Diffuse;
	XMFLOAT2	TexCoord;
};


struct MATERIAL
{
	D3DXCOLOR	Ambient;
	D3DXCOLOR	Diffuse;
	D3DXCOLOR	Specular;
	D3DXCOLOR	Emission;
	float		Shininess;
	float		Dummy[3];
};

struct MATERIALX
{
	XMFLOAT4	Ambient;
	XMFLOAT4	Diffuse;
	XMFLOAT4	Specular;
	XMFLOAT4	Emission;
	float		Shininess;
	float		Dummy[3];
};


struct LIGHT
{
	BOOL		Enable;
	BOOL		Dummy[3];
	D3DXVECTOR4	Direction;
	D3DXCOLOR	Diffuse;
	D3DXCOLOR	Ambient;
};



class Renderer : public SingletonT<Renderer>
{
private:

	static D3D_FEATURE_LEVEL       m_FeatureLevel;

	static ID3D11Device*           m_Device;
	static ComPtr<ID3D11Device>			m_pDevice;
	static ID3D11DeviceContext*    m_DeviceContext;
	static ComPtr<ID3D11DeviceContext>	m_pDeviceContext;
	static IDXGISwapChain*         m_SwapChain;
	static ComPtr<IDXGISwapChain>         m_pSwapChain;
	static ID3D11RenderTargetView* m_RenderTargetView;
	static ComPtr<ID3D11RenderTargetView> m_pRenderTargetView;
	static ID3D11DepthStencilView* m_DepthStencilView;
	static ComPtr<ID3D11DepthStencilView> m_pDepthStencilView;

	static ID3D11Buffer*			m_WorldBuffer;
	static ID3D11Buffer*			m_ViewBuffer;
	static ID3D11Buffer*			m_ProjectionBuffer;
	static ID3D11Buffer*			m_MaterialBuffer;
	static ID3D11Buffer*			m_LightBuffer;


	static ComPtr<ID3D11Buffer>		m_pWorldBuffer;
	static ComPtr<ID3D11Buffer>		m_pViewBuffer;
	static ComPtr<ID3D11Buffer>		m_pProjectionBuffer;
	static ComPtr<ID3D11Buffer>		m_pMaterialBuffer;
	static ComPtr<ID3D11Buffer>		m_pLightBuffer;

	static ID3D11DepthStencilState* m_DepthStateEnable;
	static ID3D11DepthStencilState* m_DepthStateDisable;




public:
	static void Init();
	static void Uninit();
	static void Begin();
	static void End();

	static void SetDepthEnable(bool Enable);
	static void SetWorldViewProjection2D();
	static void SetWorldMatrix(D3DXMATRIX* WorldMatrix);
	static void SetViewMatrix(D3DXMATRIX* ViewMatrix);
	static void SetProjectionMatrix(D3DXMATRIX* ProjectionMatrix);
	static void SetWorldMatrixX(XMMATRIX* WorldMatrix);
	static void SetViewMatrixX(XMMATRIX* ViewMatrix);
	static void SetProjectionMatrixX(XMMATRIX* ProjectionMatrix);
	static void SetMaterial(MATERIAL Material);
	static void SetLight(LIGHT Light);

	static ID3D11Device* GetDevice( void ){ return m_Device; }
	static ComPtr<ID3D11Device> GetpDevice( void ){ return m_pDevice; }
	static ID3D11DeviceContext* GetDeviceContext( void ){ return m_DeviceContext; }
	static ComPtr<ID3D11DeviceContext> GetpDeviceContext( void ){ return m_pDeviceContext; }



	static void CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName);
	static void CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName);


};

//class RendererT : public SingletonT<RendererT>
//{
//private:
//
//	static D3D_FEATURE_LEVEL       m_FeatureLevel;
//
//	static ID3D11Device*           m_Device;
//	static ID3D11DeviceContext*    m_DeviceContext;
//	static IDXGISwapChain*         m_SwapChain;
//	static ID3D11RenderTargetView* m_RenderTargetView;
//	static ID3D11DepthStencilView* m_DepthStencilView;
//
//	static ID3D11Buffer*			m_WorldBuffer;
//	static ID3D11Buffer*			m_ViewBuffer;
//	static ID3D11Buffer*			m_ProjectionBuffer;
//	static ID3D11Buffer*			m_MaterialBuffer;
//	static ID3D11Buffer*			m_LightBuffer;
//
//
//	static ID3D11DepthStencilState* m_DepthStateEnable;
//	static ID3D11DepthStencilState* m_DepthStateDisable;
//
//
//
//
//public:
//	static void Init();
//	static void Uninit();
//	static void Begin();
//	static void End();
//
//	static void SetDepthEnable(bool Enable);
//	static void SetWorldViewProjection2D();
//	static void SetWorldMatrix(D3DXMATRIX* WorldMatrix);
//	static void SetViewMatrix(D3DXMATRIX* ViewMatrix);
//	static void SetProjectionMatrix(D3DXMATRIX* ProjectionMatrix);
//	static void SetMaterial(MATERIAL Material);
//	static void SetLight(LIGHT Light);
//
//	static ID3D11Device* GetDevice(void) { return m_Device; }
//	static ID3D11DeviceContext* GetDeviceContext(void) { return m_DeviceContext; }
//
//
//
//	static void CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName);
//	static void CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName);
//
//
//};