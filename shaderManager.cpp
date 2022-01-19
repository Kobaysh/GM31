#include "shaderManager.h"
#include "renderer.h"

std::unordered_map<std::string, VertexShaderLayout*> ShaderManager::m_vertexInfo;
std::unordered_map<std::string, ID3D11PixelShader*> ShaderManager::m_pixelShaders;
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

		Renderer::CreateVertexShader(&shaderLayout->m_vertexShader, &shaderLayout->m_vertexLayout, pFileName.c_str());
		m_vertexInfo[pFileName] = shaderLayout;
	}
	else if(type == Shader_Type::ST_PS)
	{
		ID3D11PixelShader* pixelShader;
		Renderer::CreatePixelShader(&pixelShader, pFileName.c_str());
		m_pixelShaders[pFileName] = pixelShader;
	}

	//switch (type)
	//{
	//case ShaderManager::ST_VS:
	//	VertexShaderLayout* shaderLayout = new VertexShaderLayout;
	//	
	//	Renderer::CreateVertexShader(&shaderLayout->m_vertexShader, &shaderLayout->m_vertexLayout, pFileName.c_str());
	//	m_vertexInfo[pFileName] = shaderLayout;
	//	break;
	//case ShaderManager::ST_PS:
	//	ID3D11PixelShader* pixelShader;
	//	Renderer::CreatePixelShader(&pixelShader, pFileName.c_str());
	//	m_pixelShaders[pFileName] = pixelShader;
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
		if (m_vertexInfo.find(pFileName) != m_vertexInfo.end())
		{
			m_vertexInfo[pFileName]->m_vertexShader->Release();
			m_vertexInfo[pFileName]->m_vertexLayout->Release();
			m_vertexInfo.erase(pFileName);
		}

		break;
	case ShaderManager::ST_PS:
		if (m_pixelShaders.find(pFileName) != m_pixelShaders.end())
		{
			m_pixelShaders[pFileName]->Release();
			m_pixelShaders.erase(pFileName);
		}
		break;
	default:
		break;
	}
}

void ShaderManager::AllRelease()
{
	for (auto vertexInfo : m_vertexInfo)
	{
		vertexInfo.second->m_vertexLayout->Release();
		vertexInfo.second->m_vertexShader->Release();
	}
	m_vertexInfo.clear();

	for (auto pixelShader : m_pixelShaders)
	{
		pixelShader.second->Release();
	}
	m_pixelShaders.clear();
}
