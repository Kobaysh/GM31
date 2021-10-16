#pragma once
#include "main.h"
#include <list>

class C_VertexShader :public ID3D11VertexShader
{
private:
	ID3D11VertexShader* m_VertexShader;
	std::string m_FileName;
};


class C_PixelShader :public ID3D11PixelShader
{
private:
	ID3D11PixelShader* m_PixelShader;
	std::string m_FileName;
};

class ShaderManager
{
public:
	enum Shader_Type {
		ST_NONE = -1,
		ST_VS,
		ST_PS,
		ST_MAX
	};
	ShaderManager();
	~ShaderManager();

	static int SetShaderLoadfile(Shader_Type type, std::string pFileName);
	static bool Load(Shader_Type type, int shaderId);
	static int AllLoad();
	static void Release(Shader_Type type, int shaderId);
	static void AllRelease();

private:
	static std::list<ShaderManager*> ms_ShaderList;
//	static std::list<C_VertexShader>	ms_VSList;
//	static std::list<C_PixelShader>		ms_PSList;

	std::string m_VSFileName = NULL;
	std::string m_PSFileName = NULL;
	ID3D11VertexShader*		m_VertexShader = NULL;
	ID3D11PixelShader*		m_PixelShader = NULL;
	ID3D11InputLayout*		m_VertexLayout = NULL;
};

