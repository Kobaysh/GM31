#pragma once
#include <unordered_map>
#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/matrix4x4.h"
#pragma comment (lib, "assimp.lib")

// �C���ςݒ��_���
struct DEFORM_VERTEX
{
	aiVector3D Position;
	aiVector3D Normal;
	int BoneNum;
	std::string BoneName[4];
	float BoneWeight[4];
};

// �{�[�����
struct BONE
{
	aiMatrix4x4 Matrix;
	aiMatrix4x4 OffsetMatrix;
	aiMatrix4x4 AnimationMatrix;
};

// �A�j���[�V�����t�����f���N���X
class AnimationModel
{
private:
	const aiScene* m_AiScene = nullptr;										 // �V�[��
	std::unordered_map<std::string, const aiScene*>m_Animation;				 // �A�j���[�V����
	ID3D11Buffer** m_VertexBuffer;											 // ���_�o�b�t�@
	ID3D11Buffer** m_IndexBuffer;											 // �C���f�b�N�X�o�b�t�@
	std::vector<DEFORM_VERTEX>* m_DeformVertex;								 // �C���ςݒ��_
	std::unordered_map<std::string, BONE> m_Bone;							 // �{�[��
	std::unordered_map<std::string, ID3D11ShaderResourceView*> m_Texture;	 // �e�N�X�`��
public:
	// �ǂݍ���
	void Load(const char* fileName);

	// ���f�����
	void Unload();

	// �A�j���[�V�����ǂݍ���
	void LoadAnimaiton(const char* fileName, const char* name);

	// �X�V
	void Update(int frame);
	void Update(const char* animationName, int frame);

	// �A�j���[�V�����u�����h
	void Update(const char* animationName1, const char* animationName2, float blendRate, int frame);
	void Draw();
	
private:
	//  �{�[���쐬
	void CreateBone(aiNode* node);

	// �{�[���}�g���N�X�X�V
	void UpdateBoneMatrix(aiNode* node, aiMatrix4x4 matrix);

	// �E�F�C�g�X�V
	aiMatrix4x4 UpdateWeight(aiMatrix4x4* matrix4x4, DEFORM_VERTEX* deformVertex);
};



