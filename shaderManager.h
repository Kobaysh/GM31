#pragma once
#include "main.h"
#include <unordered_map>

// 頂点情報
struct VertexShaderLayout
{
	ID3D11VertexShader* m_VertexShader;
	ID3D11InputLayout* m_VertexLayout;
};

// シェーダー管理クラス
class ShaderManager
{
public:
	enum Shader_Type {
		ST_VS,
		ST_PS,
	};
	ShaderManager();
	~ShaderManager();

	// 読み込み
	static void Load(Shader_Type type,  std::string pFileName);

	// 解放
	static void Release(Shader_Type type,  std::string pFileName);

	// 全解放
	static void AllRelease();

	// 頂点シェーダーゲッター
	static VertexShaderLayout* GetVertexShader(std::string pFileName) { return m_VertexInfo[pFileName]; }

	// ピクセルシェーダーゲッター
	static ID3D11PixelShader* GetPixelShader(std::string pFileName) { return m_PixelShaders[pFileName]; }

private:
	static std::unordered_map<std::string, VertexShaderLayout*> m_VertexInfo;	// 頂点情報
	static std::unordered_map<std::string, ID3D11PixelShader*> m_PixelShaders;	// ピクセルシェーダー
};

