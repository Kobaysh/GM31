#pragma once
#include <unordered_map>
#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/matrix4x4.h"
#pragma comment (lib, "assimp.lib")

// 修正済み頂点情報
struct DEFORM_VERTEX
{
	aiVector3D Position;
	aiVector3D Normal;
	int BoneNum;
	std::string BoneName[4];
	float BoneWeight[4];
};

// ボーン情報
struct BONE
{
	aiMatrix4x4 Matrix;
	aiMatrix4x4 OffsetMatrix;
	aiMatrix4x4 AnimationMatrix;
};

// アニメーション付きモデルクラス
class AnimationModel
{
private:
	const aiScene* m_AiScene = nullptr;										 // シーン
	std::unordered_map<std::string, const aiScene*>m_Animation;				 // アニメーション
	ID3D11Buffer** m_VertexBuffer;											 // 頂点バッファ
	ID3D11Buffer** m_IndexBuffer;											 // インデックスバッファ
	std::vector<DEFORM_VERTEX>* m_DeformVertex;								 // 修正済み頂点
	std::unordered_map<std::string, BONE> m_Bone;							 // ボーン
	std::unordered_map<std::string, ID3D11ShaderResourceView*> m_Texture;	 // テクスチャ
public:
	// 読み込み
	void Load(const char* fileName);

	// モデル解放
	void Unload();

	// アニメーション読み込み
	void LoadAnimaiton(const char* fileName, const char* name);

	// 更新
	void Update(int frame);
	void Update(const char* animationName, int frame);

	// アニメーションブレンド
	void Update(const char* animationName1, const char* animationName2, float blendRate, int frame);
	void Draw();
	
private:
	//  ボーン作成
	void CreateBone(aiNode* node);

	// ボーンマトリクス更新
	void UpdateBoneMatrix(aiNode* node, aiMatrix4x4 matrix);

	// ウェイト更新
	aiMatrix4x4 UpdateWeight(aiMatrix4x4* matrix4x4, DEFORM_VERTEX* deformVertex);
};



