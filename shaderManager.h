#pragma once
#include "main.h"
#include <unordered_map>

struct VertexShaderLayout
{
	ID3D11VertexShader* m_VertexShader;
	ID3D11InputLayout* m_VertexLayout;
};

class ShaderManager
{
public:
	enum Shader_Type {
		ST_VS,
		ST_PS,
	};
	ShaderManager();
	~ShaderManager();

	static void Load(Shader_Type type,  std::string pFileName);
	static void Release(Shader_Type type,  std::string pFileName);
	static void AllRelease();

	static VertexShaderLayout* GetVertexShader(std::string pFileName) { return m_VertexInfo[pFileName]; }
	static ID3D11PixelShader* GetPixelShader(std::string pFileName) { return m_PixelShaders[pFileName]; }

private:
	static std::unordered_map<std::string, VertexShaderLayout*> m_VertexInfo;
	static std::unordered_map<std::string, ID3D11PixelShader*> m_PixelShaders;
};

