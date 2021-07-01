#pragma once
#include "main.h"
#include <list>
#define INVALID_TEXURE_ID (-1)	// �����ȃe�N�X�`���Ǘ��ԍ�
#define TEXTURE_FILE_MAX (64)	// �ő�e�N�X�`���t�@�C����
class Texture
{
private:
	static std::list<Texture*> m_textureList;

	std::string m_fileName;
	ID3D11ShaderResourceView*	m_Texture = nullptr;
	bool m_isLoaded = false;
public:
	static ID3D11ShaderResourceView*  GetTexture(int textureId);
	static int SetTextureLoadFile(std::string pFileName);
	static void Load(int textureId);
	static void AllLoad();
	static void Release(int textureId);
	static void AllRelease();

};

