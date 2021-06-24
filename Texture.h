#pragma once
#include <list>
#define TEXTURE_INVALID_ID (-1)	// 無効なテクスチャ管理番号
#define TEXTURE_FILE_MAX (64)	// 最大テクスチャファイル名
class Texture
{
	static std::list<Texture*> m_ModelList;
};

