#pragma once
#include <fbxsdk.h>
#include "main.h"
#include "renderer.h"
#include <vector>
#include <map>

class FbxMeshFile
{
public:
	/** Constructor */
	FbxMeshFile()
	{
		m_VertexBuffers.clear();
		m_Vertices.clear();
	}

	/** Destructor */
	~FbxMeshFile()
	{
		for (auto buffer : m_VertexBuffers)
		{
			buffer.second->Release();
		}
		m_VertexBuffers.clear();

		for (auto buffer : m_IndexBuffers)
		{
			buffer.second->Release();
		}
		m_IndexBuffers.clear();
	}

	/**
	* @brief ���f���ǂݍ���@n
	* ���f���f�[�^��ǂݍ���
	* @return �쐬�̐��� ����(true)
	* @param[in] device �f�o�C�X
	* @param[in] vertex_shader ���f���Ɗ֘A�t����VertexShader
	*/
	bool Load(const char* file_name);

	/**
	* @brief ���f���`��֐�@n
	* �w�肳�ꂽ���Ń��f����`�悷��
	* @return �쐬�̐��� ����(true)
	* @param[in] pos �`����W
	* @param[in] scale �g�k��
	* @param[in] degree �p�x
	*/
	void Render(XMFLOAT3 pos, XMFLOAT3 scale, XMFLOAT3 degree);

private:
	/**
	* @brief ���b�V������@n
	* �t�@�C�����烁�b�V���𐶐�����
	* @return �쐬�̐��� ����(true)
	* @param[in] file_name �t�@�C����
	*/
	bool LoadFbxFile(std::vector<std::string>& out_material_list, const char* file_path, const char* file_name);

	/**
	* @brief VertexBuffer�쐬@n
	* VertexBuffer���쐬����
	* @return �쐬�̐��� ����(true)
	*/
	bool CreateVertexBuffer();

	/**
	* @brief IndexBuffer�쐬@n
	* IndexBuffer���쐬����
	* @return �쐬�̐��� ����(true)
	*/
	bool CreateIndexBuffer();



	/**
	* @brief ���b�V���f�[�^���쐬����
	* @return �쐬�̐��� ����(true)
	* @param[in] node_name �m�[�h�̖��O
	* @param[in] mesh Mesh����邽�߂�Node��Mesh�f�[�^
	*/
	bool CreateMesh(const char* node_name, FbxMesh* mesh);

	/**
	* @brief ���b�V���m�[�h���W�߂�
	* @param[in] node ���ؑΏۂ̃m�[�h
	* @param[out] list �ǉ��m�[�h�ۑ��p
	*/
	void CollectMeshNode(FbxNode* node, std::map<std::string, FbxNode*>& list);
private:
	std::map<std::string, ID3D11Buffer*> m_VertexBuffers;			//!< @brief ���_�o�b�t�@(Shader���M�p)
	std::map<std::string, ID3D11Buffer*> m_IndexBuffers;
	ID3D11InputLayout* m_InputLayout;
	std::map <std::string, std::vector<VERTEX_3DX>> m_Vertices;	//!< @brief ���_�o�b�t�@
	std::map<std::string, std::vector<UINT>> m_Indices;				//!< @brief �C���f�b�N�X�o�b�t�@

};
