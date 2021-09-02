#pragma once
#include <unordered_map>
#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/matrix4x4.h"
#pragma comment (lib, "assimp.lib")

class AnimationModel
{
public:
	
	void Load(const char* fileName);
	void Unload();
	void Update();
	void Draw();

private:
	const aiScene* m_aiScene = nullptr;
	ID3D11Buffer** m_vertexBuffer;
	ID3D11Buffer** m_indexBuffer;

	std::unordered_map<std::string, ID3D11ShaderResourceView*> m_texture;

};


