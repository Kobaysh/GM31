#pragma once
#include "main.h"
#include <unordered_map>
#define INVALID_TEXURE_ID (-1)	// 無効なテクスチャ管理番号
#define TEXTURE_FILE_MAX (64)	// 最大テクスチャファイル名
class Texture
{
private:
//	static std::list<Texture*> m_TextureList;
	static std::unordered_map<std::string,ID3D11ShaderResourceView*> m_TextureList;

//	std::string m_fileName;
//	ID3D11ShaderResourceView*	m_texture = nullptr;
//	bool m_IsLoaded = false;
public:
	//static ID3D11ShaderResourceView*  GetTexture(int textureId);
	//static int SetTextureLoadFile(std::string pFileName);
	//static void Load(int textureId);
	//static void AllLoad();
	//static void Release(int textureId);
	//static void AllRelease();
	static ID3D11ShaderResourceView**  GetTexture(std::string fileName);
	static bool Load(std::string fileName);
	static void Release(std::string fileName);
	static void AllRelease();
};

