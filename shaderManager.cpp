#include "shaderManager.h"
#include "renderer.h"

std::unordered_map<std::string, VertexShaderLayout*> ShaderManager::m_VertexInfo;
std::unordered_map<std::string, ID3D11PixelShader*> ShaderManager::m_PixelShaders;
ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
	AllRelease();
}


void ShaderManager::Load(Shader_Type type,  std::string pFileName)
{

	if (type == Shader_Type::ST_VS)
	{
		VertexShaderLayout* shaderLayout = new VertexShaderLayout;

		Renderer::CreateVertexShader(&shaderLayout->m_VertexShader, &shaderLayout->m_VertexLayout, pFileName.c_str());
		m_VertexInfo[pFileName] = shaderLayout;
	}
	else if(type == Shader_Type::ST_PS)
	{
		ID3D11PixelShader* pixelShader;
		Renderer::CreatePixelShader(&pixelShader, pFileName.c_str());
		m_PixelShaders[pFileName] = pixelShader;
	}

	//switch (type)
	//{
	//case ShaderManager::ST_VS:
	//	VertexShaderLayout* shaderLayout = new VertexShaderLayout;
	//	
	//	Renderer::CreateVertexShader(&shaderLayout->m_VertexShader, &shaderLayout->m_VertexLayout, pFileName.c_str());
	//	m_VertexInfo[pFileName] = shaderLayout;
	//	break;
	//case ShaderManager::ST_PS:
	//	ID3D11PixelShader* pixelShader;
	//	Renderer::CreatePixelShader(&pixelShader, pFileName.c_str());
	//	m_PixelShaders[pFileName] = pixelShader;
	//	break;
	//default:
	//	break;
	//}

	return;
}


void ShaderManager::Release(Shader_Type type,  std::string pFileName)
{
	switch (type)
	{
	case ShaderManager::ST_VS:
		if (m_VertexInfo.find(pFileName) != m_VertexInfo.end())
		{
			m_VertexInfo[pFileName]->m_VertexShader->Release();
			m_VertexInfo[pFileName]->m_VertexLayout->Release();
			m_VertexInfo.erase(pFileName);
		}

		break;
	case ShaderManager::ST_PS:
		if (m_PixelShaders.find(pFileName) != m_PixelShaders.end())
		{
			m_PixelShaders[pFileName]->Release();
			m_PixelShaders.erase(pFileName);
		}
		break;
	default:
		break;
	}
}

void ShaderManager::AllRelease()
{
	for (auto vertexInfo : m_VertexInfo)
	{
		vertexInfo.second->m_VertexLayout->Release();
		vertexInfo.second->m_VertexShader->Release();
	}
	m_VertexInfo.clear();

	for (auto pixelShader : m_PixelShaders)
	{
		pixelShader.second->Release();
	}
	m_PixelShaders.clear();
}
