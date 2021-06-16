#include "shader.h"
// シェーダコンパイル周りの機能をインクルード
#include <d3dcompiler.h>
#include <D3Dcompiler.h>
// シェーダコンパイル用の静的ライブラリをリンク
#pragma comment(lib, "d3dcompiler.lib")

#include "renderer.h"

// コンパイル
template<class T>
bool Shader<T>::ShaderCompile(const std::string pFileName, const char * pEntryPoint, std::string pShaderModel, ID3DBlob** ppBlob)
{
	WCHAR path[256];
	size_t len = 0;
	mbstowcs_s(&len, path, 256, pFileName, _TRUNCATE);

	ID3DBlob* pErrorMsg;
	HRESULT hr = D3DX11CompileFromFile(
		path,
		NULL,
		LPD3D10INCLUDE,
		pEntryPoint,
		pShaderModel,
		0,
		0,
		ppBlob,
		&pErrorMsg
	);
	if (FAILED(hr))
	{
		// シェーダのエラー内容を表示
		MessageBox(NULL, (char*)pErrorMsg->GetBufferPointer(), "Compile Error", MB_OK);

		if (pErrorMsg) {
			pErrorMsg->Release();
			pErrorMsg = nullptr;
		}
		return false;
	}
	return true;
}

// 初期化
bool VertexShader::Init(const std::string  pFilename, const char* pEntryPoint)
{
	ID3DBlob* pBlob;
	if (!ShaderCompile(pFilename, pEntryPoint, "vs_5_0", &pBlob))
	{
		return false;
	}

	auto pDevice = Renderer::GetpDevice();
	HRESULT hr;
	// 頂点シェーダの生成
	hr = pDevice->CreateVertexShader(
		pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(),
		NULL,
		&m_pShader
	);
	if (FAILED(hr)) {
		if (pBlob) {
			pBlob->Release();
			pBlob = nullptr;
		}
		return false;
	}
	m_pShaderCode = pBlob;

	return true;
}
// 終了処理
void VertexShader::Uninit(void)
{
	if (m_pShader) {
		m_pShader->Release();
		m_pShader = nullptr;
	}
	Shader::Uninit();
}

// 初期化
bool PixelShader::Init( const std::string  pFilename, const char* pEntryPoint)
{
	ID3DBlob* pBlob;
	if (!ShaderCompile(pFilename, pEntryPoint, "ps_5_0", &pBlob))
	{
		return false;
	}
	auto pDevice = Renderer::GetpDevice();
	HRESULT hr;
	// ピクセルシェーダの生成
	hr = pDevice->CreatePixelShader(
		pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(),
		NULL,
		&m_pShader
	);
	if (pBlob) {
		pBlob->Release();
		pBlob = nullptr;
	}

	return SUCCEEDED(hr);
}