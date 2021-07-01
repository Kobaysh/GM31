#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "texture.h"

std::list<Texture*> Texture::m_textureList;

ID3D11ShaderResourceView * Texture::GetTexture(int textureId)
{
	if (textureId <= INVALID_TEXURE_ID) return nullptr;
	auto it = m_textureList.begin();
	for (int i = 0; i < textureId; i++) {
		it++;
	}
	Texture* texture = *it;
	return texture->m_Texture;
}

int Texture::SetTextureLoadFile(std::string pFileName)
{
	int i = 0;
	if (m_textureList.empty()) {
		Texture* newTexture = new Texture();
		newTexture->m_fileName = pFileName;
		m_textureList.push_back(newTexture);
		return i;
	}
	for (Texture* texture : m_textureList) {
		if (texture->m_fileName[0 == 0]) {
			i++;
			continue;
		}
		if (texture->m_fileName == pFileName) {
			return i;
		}
		i++;
	}
	i = 0;
	for (Texture* texture : m_textureList) {
		if (texture->m_fileName[0] != 0) {
			i++;
			continue;
		}
	}
	Texture* newTexture = new Texture();
	newTexture->m_fileName = pFileName;
	m_textureList.push_back(newTexture);
	return i;
}

void Texture::Load(int textureId)
{
	if (textureId <= INVALID_TEXURE_ID) return;
	auto it = m_textureList.begin();
	for (int i = 0; i < textureId; i++) {
		it++;
	}
	Texture* _texture = *it;
	if (_texture->m_fileName[0] == 0) return;
	if (_texture->m_isLoaded) return;


	D3DX11CreateShaderResourceViewFromFile(
		//	Renderer::GetDevice(),
		Renderer::GetpDevice().Get(),
		"asset/texture/grass02.jpg",
		NULL,
		NULL,
		&_texture->m_Texture,
		NULL
	);
	assert(_texture->m_Texture);
	_texture->m_isLoaded = true;
}

void Texture::AllLoad()
{
	for (Texture* texture : m_textureList) {
		if (texture->m_fileName[0] == 0) return;
		if (texture->m_isLoaded) return;


		D3DX11CreateShaderResourceViewFromFile(
			//	Renderer::GetDevice(),
			Renderer::GetpDevice().Get(),
			"asset/texture/grass02.jpg",
			NULL,
			NULL,
			&texture->m_Texture,
			NULL
		);
		assert(texture->m_Texture);
		texture->m_isLoaded = true;
	}
}

void Texture::Release(int textureId)
{
	if (textureId == INVALID_TEXURE_ID) return;
	auto it = m_textureList.begin();
	for (int i = 0; i < textureId; i++) {
		it++;
	}
	Texture* texture = *it;
	if (texture->m_Texture) {
		delete texture->m_Texture;
		texture->m_Texture = nullptr;
	}
	m_textureList.erase(std::next(m_textureList.begin(), textureId));
}

void Texture::AllRelease()
{
	auto it = m_textureList.begin();
	for (unsigned int i = 0; i < m_textureList.size(); i++) {
		Texture* texture = *it;
		if (texture->m_Texture) {
			delete texture->m_Texture;
			texture->m_Texture = nullptr;
		}
		it++;
	}
	m_textureList.clear();
}
