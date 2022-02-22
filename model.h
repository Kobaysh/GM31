#pragma once
#include "renderer.h"
#include <string>
#include <list>
#include <vector>


#define INVALID_MODEL_ID (-1)
// �}�e���A���\����
struct MODEL_MATERIAL
{
	char						Name[256];
	MATERIAL					Material;
	char						TextureName[256];
	ID3D11ShaderResourceView*	Texture;

};


// �`��T�u�Z�b�g�\����
struct SUBSET
{
	unsigned int	StartIndex;
	unsigned int	IndexNum;
	MODEL_MATERIAL	Material;
};


// ���f���\����
struct MODEL
{
	VERTEX_3DX		*VertexArray;
	unsigned int	VertexNum;

	unsigned int	*IndexArray;
	unsigned int	IndexNum;

	SUBSET			*SubsetArray;
	unsigned int	SubsetNum;
};


// ���f���Ǘ��N���X
class Model
{
private:

	ID3D11Buffer*	m_VertexBuffer;			 // ���_�o�b�t�@
	ID3D11Buffer*	m_IndexBuffer;			 // �C���f�b�N�X�o�b�t�@
	SUBSET*	m_SubsetArray;					 // �T�u�Z�b�g�z��
	unsigned int	m_SubsetNum;			 // �T�u�Z�b�g��
	bool m_IsLoaded;						 // ���[�h�ς݂�
	std::string m_FileName;					 // �t�@�C����
	static std::list<Model*> m_ModelList;	 // ���f���Ǘ����X�g
	int m_TextureId;						 // �e�N�X�`��ID
//	static std::vector<Model> m_ModelList;

public:
	static void Init(){}
	static void Uninit();
	void Draw();
	static void Draw(int modelId);

	// �ǂݍ���
	void Load( const char *FileName );
	static void Load(int modelId);

	// �\��ς݂�S���ǂݍ���
	static void AllLoad();

	// ���
	void Unload();
	static void Release(int modelId);
	static void AllRelease();

	// �ǂݍ��ݗ\��
	static int SetModelLoadfile(std::string pFileName);

private:
	// OBJ�t�@�C����ǂݍ���
	void LoadObj( const char *FileName, MODEL *Model );

	// �}�e���A������ǂݍ���
	void LoadMaterial( const char *FileName, MODEL_MATERIAL **MaterialArray, unsigned int *MaterialNum );

	// OBJ�t�@�C����ǂݍ���
	static void SLoadObj(std::string FileName, MODEL *Model);

	// �}�e���A������ǂݍ���
	static void SLoadMaterial(std::string FileName, MODEL_MATERIAL **MaterialArray, unsigned int *MaterialNum);
};