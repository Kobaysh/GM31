#pragma once
#include "renderer.h"
#include <string>
#include <list>
#include <vector>
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





class Model
{
private:

	ID3D11Buffer*	m_VertexBuffer;
	ID3D11Buffer*	m_IndexBuffer;

	SUBSET*	m_SubsetArray;
	unsigned int	m_SubsetNum;
	void LoadObj( const char *FileName, MODEL *Model );
	void LoadMaterial( const char *FileName, MODEL_MATERIAL **MaterialArray, unsigned int *MaterialNum );

	int m_Index;
	std::string m_FileName;
//	static std::list<Model*> m_ModelList;
	static std::vector<Model> m_ModelList;

public:
	static void Init();
	void Draw();

	void Load( const char *FileName );
	void Unload();
	int SetModelLoadfile(std::string pFileName);
};