#pragma once
#include <list>
#define TEXTURE_INVALID_ID (-1)	// �����ȃe�N�X�`���Ǘ��ԍ�
#define TEXTURE_FILE_MAX (64)	// �ő�e�N�X�`���t�@�C����
class Texture
{
	static std::list<Texture*> m_ModelList;
};

