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
	* @brief モデル読み込み@n
	* モデルデータを読み込む
	* @return 作成の成否 成功(true)
	* @param[in] device デバイス
	* @param[in] vertex_shader モデルと関連付けるVertexShader
	*/
	bool Load(const char* file_name);

	/**
	* @brief モデル描画関数@n
	* 指定された情報でモデルを描画する
	* @return 作成の成否 成功(true)
	* @param[in] pos 描画座標
	* @param[in] scale 拡縮率
	* @param[in] degree 角度
	*/
	void Render(XMFLOAT3 pos, XMFLOAT3 scale, XMFLOAT3 degree);

private:
	/**
	* @brief メッシュ生成@n
	* ファイルからメッシュを生成する
	* @return 作成の成否 成功(true)
	* @param[in] file_name ファイル名
	*/
	bool LoadFbxFile(std::vector<std::string>& out_material_list, const char* file_path, const char* file_name);

	/**
	* @brief VertexBuffer作成@n
	* VertexBufferを作成する
	* @return 作成の成否 成功(true)
	*/
	bool CreateVertexBuffer();

	/**
	* @brief IndexBuffer作成@n
	* IndexBufferを作成する
	* @return 作成の成否 成功(true)
	*/
	bool CreateIndexBuffer();



	/**
	* @brief メッシュデータを作成する
	* @return 作成の成否 成功(true)
	* @param[in] node_name ノードの名前
	* @param[in] mesh Meshを作るためのNodeのMeshデータ
	*/
	bool CreateMesh(const char* node_name, FbxMesh* mesh);

	/**
	* @brief メッシュノードを集める
	* @param[in] node 検証対象のノード
	* @param[out] list 追加ノード保存用
	*/
	void CollectMeshNode(FbxNode* node, std::map<std::string, FbxNode*>& list);
private:
	std::map<std::string, ID3D11Buffer*> m_VertexBuffers;			//!< @brief 頂点バッファ(Shader送信用)
	std::map<std::string, ID3D11Buffer*> m_IndexBuffers;
	ID3D11InputLayout* m_InputLayout;
	std::map <std::string, std::vector<VERTEX_3DX>> m_Vertices;	//!< @brief 頂点バッファ
	std::map<std::string, std::vector<UINT>> m_Indices;				//!< @brief インデックスバッファ

};
