#pragma once
#include "renderer.h"
#include <string>
#include <list>
#include <vector>


#define INVALID_MODEL_ID (-1)
// マテリアル構造体
struct MODEL_MATERIAL
{
	char						Name[256];
	MATERIAL					Material;
	char						TextureName[256];
	ID3D11ShaderResourceView*	Texture;

};


// 描画サブセット構造体
struct SUBSET
{
	unsigned int	StartIndex;
	unsigned int	IndexNum;
	MODEL_MATERIAL	Material;
};


// モデル構造体
struct MODEL
{
	VERTEX_3DX		*VertexArray;
	unsigned int	VertexNum;

	unsigned int	*IndexArray;
	unsigned int	IndexNum;

	SUBSET			*SubsetArray;
	unsigned int	SubsetNum;
};


// モデル管理クラス
class Model
{
private:

	ID3D11Buffer*	m_VertexBuffer;			 // 頂点バッファ
	ID3D11Buffer*	m_IndexBuffer;			 // インデックスバッファ
	SUBSET*	m_SubsetArray;					 // サブセット配列
	unsigned int	m_SubsetNum;			 // サブセット数
	bool m_IsLoaded;						 // ロード済みか
	std::string m_FileName;					 // ファイル名
	static std::list<Model*> m_ModelList;	 // モデル管理リスト
	int m_TextureId;						 // テクスチャID
//	static std::vector<Model> m_ModelList;

public:
	static void Init(){}
	static void Uninit();
	void Draw();
	static void Draw(int modelId);

	// 読み込み
	void Load( const char *FileName );
	static void Load(int modelId);

	// 予約済みを全部読み込み
	static void AllLoad();

	// 解放
	void Unload();
	static void Release(int modelId);
	static void AllRelease();

	// 読み込み予約
	static int SetModelLoadfile(std::string pFileName);

private:
	// OBJファイルを読み込む
	void LoadObj( const char *FileName, MODEL *Model );

	// マテリアル情報を読み込む
	void LoadMaterial( const char *FileName, MODEL_MATERIAL **MaterialArray, unsigned int *MaterialNum );

	// OBJファイルを読み込む
	static void SLoadObj(std::string FileName, MODEL *Model);

	// マテリアル情報を読み込む
	static void SLoadMaterial(std::string FileName, MODEL_MATERIAL **MaterialArray, unsigned int *MaterialNum);
};