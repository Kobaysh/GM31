#pragma once
#include <unordered_map>
#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/matrix4x4.h"
#pragma comment (lib, "assimp.lib")

struct DEFORM_VERTEX
{
	aiVector3D position;
	aiVector3D normal;
	int boneNum;
	std::string boneName[4];
	float boneWeight[4];
};


struct BONE
{
	aiMatrix4x4 matrix;
	aiMatrix4x4 offsetMatrix;
	aiMatrix4x4 animationMatrix;
};


class AnimationModel
{
public:
	
	void Load(const char* fileName);
	void Unload();
	void LoadAnimaiton(const char* fileName, const char* name);


	void Update(int frame);
	void Update(const char* animationName, int frame);
	void Update(const char* animationName1, const char* animationName2, float blendRate, int frame);
	void Draw();
	

private:
	const aiScene* m_AiScene = nullptr;
	std::unordered_map<std::string, const aiScene*>m_Animation;
	ID3D11Buffer** m_VertexBuffer;
	ID3D11Buffer** m_IndexBuffer;
	std::vector<DEFORM_VERTEX>* m_DeformVertex;
	std::unordered_map<std::string, BONE> m_Bone;

	std::unordered_map<std::string, ID3D11ShaderResourceView*> m_Texture;

	void CreateBone(aiNode* node);
	void UpdateBoneMatrix(aiNode* node, aiMatrix4x4 matrix);
	aiMatrix4x4 UpdateWeight(aiMatrix4x4* matrix4x4, DEFORM_VERTEX* deformVertex);
};



