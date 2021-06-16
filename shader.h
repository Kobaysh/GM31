#pragma once
#include "main.h"
#include <string>
template<class T>
class Shader
{
protected:
	T* m_pShader;	// シェーダー

public:
	Shader():m_pShader(NULL){}
	virtual ~Shader() { Uninit(); }


	virtual bool Init(const std::string pFileName, const char* pEntryPoint) = 0;
	virtual void Uninit();

	// シェーダーの取得
	T* GetShader() { return m_pShader; }
protected:
	// シェーダーコンパイル
	bool ShaderCompile(const std::string pFileName, const char* pEntryPoint, std::string pShaderModel, ID3DBlob** ppBlob);

};


// VertexShaderクラス
class VertexShader : public Shader<ID3D11VertexShader>
{
public:
	VertexShader(void) : m_pShaderCode(NULL) {}
	// 初期化
	virtual bool Init(const std::string pFilename, const char* pEntryPoint);
	// 終了処理
	virtual void Uninit(void);
	// シェーダコードの取得
	ID3DBlob* GetShaderCode(void) { return m_pShaderCode; }

private:
	ID3DBlob* m_pShaderCode;
};

// PixelShaderクラス
class PixelShader : public Shader<ID3D11PixelShader >
{
public:
	// 初期化
	virtual bool Init( const std::string pFilename, const char* pEntryPoint);
};

