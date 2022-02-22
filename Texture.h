#pragma once
#include "main.h"
#include <unordered_map>
#define INVALID_TEXURE_ID (-1)	// �����ȃe�N�X�`���Ǘ��ԍ�
#define TEXTURE_FILE_MAX (64)	// �ő�e�N�X�`���t�@�C����

// �e�N�X�`���Ǘ��N���X
class Texture
{
private:
	static std::unordered_map<std::string,ID3D11ShaderResourceView*> m_TextureList;	// �e�N�X�`���Ǘ����X�g
public:
	// �e�N�X�`���Q�b�^�[
	static ID3D11ShaderResourceView**  GetTexture(std::string fileName);

	//�@�e�N�X�`���ǂݍ���
	static bool Load(std::string fileName);

	// ���
	static void Release(std::string fileName);

	// �S���
	static void AllRelease();
};

