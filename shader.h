#pragma once
#include "main.h"
#include <string>
template<class T>
class Shader
{
protected:
	T* m_pShader;	// �V�F�[�_�[

public:
	Shader():m_pShader(NULL){}
	virtual ~Shader() { Uninit(); }


	virtual bool Init(const std::string pFileName, const char* pEntryPoint) = 0;
	virtual void Uninit();

	// �V�F�[�_�[�̎擾
	T* GetShader() { return m_pShader; }
protected:
	// �V�F�[�_�[�R���p�C��
	bool ShaderCompile(const std::string pFileName, const char* pEntryPoint, std::string pShaderModel, ID3DBlob** ppBlob);

};


// VertexShader�N���X
class VertexShader : public Shader<ID3D11VertexShader>
{
public:
	VertexShader(void) : m_pShaderCode(NULL) {}
	// ������
	virtual bool Init(const std::string pFilename, const char* pEntryPoint);
	// �I������
	virtual void Uninit(void);
	// �V�F�[�_�R�[�h�̎擾
	ID3DBlob* GetShaderCode(void) { return m_pShaderCode; }

private:
	ID3DBlob* m_pShaderCode;
};

// PixelShader�N���X
class PixelShader : public Shader<ID3D11PixelShader >
{
public:
	// ������
	virtual bool Init( const std::string pFilename, const char* pEntryPoint);
};

