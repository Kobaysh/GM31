#include "shaderManager.h"
#include "renderer.h"

std::list<ShaderManager*> 	ShaderManager::ms_ShaderList;

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
	AllRelease();
}

int ShaderManager::SetShaderLoadfile(Shader_Type type, std::string pFileName)
{
	int i = 0;
	if (type == Shader_Type::ST_VS) {
		if (ms_ShaderList.empty()) {
			
			return i;
		}


	}
	else if (type == Shader_Type::ST_PS) {

	}


	return 0;
}

bool ShaderManager::Load(Shader_Type type, int shaderId)
{
	return false;
}

int ShaderManager::AllLoad()
{
	return 0;
}

void ShaderManager::Release(Shader_Type type, int shaderId)
{
}

void ShaderManager::AllRelease()
{
}
