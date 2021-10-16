#include "shader.h"
// �V�F�[�_�R���p�C������̋@�\���C���N���[�h
#include <d3dcompiler.h>
#include <D3Dcompiler.h>
// �V�F�[�_�R���p�C���p�̐ÓI���C�u�����������N
#pragma comment(lib, "d3dcompiler.lib")

#include "renderer.h"

// �R���p�C��
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
		// �V�F�[�_�̃G���[���e��\��
		MessageBox(NULL, (char*)pErrorMsg->GetBufferPointer(), "Compile Error", MB_OK);

		if (pErrorMsg) {
			pErrorMsg->Release();
			pErrorMsg = nullptr;
		}
		return false;
	}
	return true;
}

// ������
bool VertexShader::Init(const std::string  pFilename, const char* pEntryPoint)
{
	ID3DBlob* pBlob;
	if (!ShaderCompile(pFilename, pEntryPoint, "vs_5_0", &pBlob))
	{
		return false;
	}

	auto pDevice = Renderer::GetpDevice();
	HRESULT hr;
	// ���_�V�F�[�_�̐���
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
// �I������
void VertexShader::Uninit(void)
{
	if (m_pShader) {
		m_pShader->Release();
		m_pShader = nullptr;
	}
	Shader::Uninit();
}

// ������
bool PixelShader::Init( const std::string  pFilename, const char* pEntryPoint)
{
	ID3DBlob* pBlob;
	if (!ShaderCompile(pFilename, pEntryPoint, "ps_5_0", &pBlob))
	{
		return false;
	}
	auto pDevice = Renderer::GetpDevice();
	HRESULT hr;
	// �s�N�Z���V�F�[�_�̐���
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