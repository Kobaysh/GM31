#pragma once
#include "main.h"
#include <unordered_map>
#define INVALID_TEXURE_ID (-1)	// 無効なテクスチャ管理番号
#define TEXTURE_FILE_MAX (64)	// 最大テクスチャファイル名

// テクスチャ管理クラス
class Texture
{
private:
	static std::unordered_map<std::string,ID3D11ShaderResourceView*> m_TextureList;	// テクスチャ管理リスト
public:
	// テクスチャゲッター
	static ID3D11ShaderResourceView**  GetTexture(std::string fileName);

	//　テクスチャ読み込み
	static bool Load(std::string fileName);

	// 解放
	static void Release(std::string fileName);

	// 全解放
	static void AllRelease();
};

