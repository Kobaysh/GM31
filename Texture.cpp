#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "texture.h"

//std::list<Texture*> Texture::m_TextureList;
std::unordered_map<std::string,ID3D11ShaderResourceView*> Texture::m_TextureList;


//ID3D11ShaderResourceView * Texture::GetTexture(int textureId)
//{
//	if (textureId <= INVALID_TEXURE_ID) return nullptr;
//	auto it = m_TextureList.begin();
//	for (int i = 0; i < textureId; i++) {
//		it++;
//	}
//	Texture* texture = *it;
//	return texture->m_texture;
//}
//
//int Texture::SetTextureLoadFile(std::string pFileName)
//{
//	int i = 0;
//	if (m_TextureList.empty()) {
//		Texture* newTexture = new Texture();
//		newTexture->m_fileName = pFileName;
//		m_TextureList.push_back(newTexture);
//		return i;
//	}
//	for (Texture* texture : m_TextureList) {
//		if (texture->m_fileName[0 == 0]) {
//			i++;
//			continue;
//		}
//		if (texture->m_fileName == pFileName) {
//			return i;
//		}
//		i++;
//	}
//	i = 0;
//	for (Texture* texture : m_TextureList) {
//		if (texture->m_fileName[0] != 0) {
//			i++;
//			continue;
//		}
//	}
//	Texture* newTexture = new Texture();
//	newTexture->m_fileName = pFileName;
//	m_TextureList.push_back(newTexture);
//	return i;
//}
//
//void Texture::Load(int textureId)
//{
//	if (textureId <= INVALID_TEXURE_ID) return;
//	auto it = m_TextureList.begin();
//	for (int i = 0; i < textureId; i++) {
//		it++;
//	}
//	Texture* _texture = *it;
//	if (_texture->m_fileName[0] == 0) return;
//	if (_texture->m_IsLoaded) return;
//
//
//	D3DX11CreateShaderResourceViewFromFile(
//		//	Renderer::GetDevice(),
//		Renderer::GetpDevice().Get(),
//		"asset/texture/grass02.jpg",
//		NULL,
//		NULL,
//		&_texture->m_texture,
//		NULL
//	);
//	assert(_texture->m_texture);
//	_texture->m_IsLoaded = true;
//}
//
//void Texture::AllLoad()
//{
//	for (Texture* texture : m_TextureList) {
//		if (texture->m_fileName[0] == 0) return;
//		if (texture->m_IsLoaded) return;
//
//
//		D3DX11CreateShaderResourceViewFromFile(
//			//	Renderer::GetDevice(),
//			Renderer::GetpDevice().Get(),
//			"asset/texture/grass02.jpg",
//			NULL,
//			NULL,
//			&texture->m_texture,
//			NULL
//		);
//		assert(texture->m_texture);
//		texture->m_IsLoaded = true;
//	}
//}
//
//void Texture::Release(int textureId)
//{
//	if (textureId == INVALID_TEXURE_ID) return;
//	auto it = m_TextureList.begin();
//	for (int i = 0; i < textureId; i++) {
//		it++;
//	}
//	Texture* texture = *it;
//	if (texture->m_texture) {
//		delete texture->m_texture;
//		texture->m_texture = nullptr;
//	}
//	m_TextureList.erase(std::next(m_TextureList.begin(), textureId));
//}
//
//void Texture::AllRelease()
//{
//	auto it = m_TextureList.begin();
//	for (unsigned int i = 0; i < m_TextureList.size(); i++) {
//		Texture* texture = *it;
//		if (texture->m_texture) {
//			delete texture->m_texture;
//			texture->m_texture = nullptr;
//		}
//		it++;
//	}
//	m_TextureList.clear();
//}


ID3D11ShaderResourceView** Texture::GetTexture(std::string fileName)
{
	auto it = m_TextureList.find(fileName);
	if (it != m_TextureList.end())
	{
		return &(*it).second;
	}
	return nullptr;
}


bool Texture::Load(std::string fileName)
{
	auto it = m_TextureList.find(fileName);
	if (it != m_TextureList.end())
	{
		return true;
	}
	ID3D11ShaderResourceView* texture;
		D3DX11CreateShaderResourceViewFromFile(
			//	Renderer::GetDevice(),
			Renderer::GetpDevice().Get(),
			fileName.data(), 
			NULL,
			NULL,
			&texture,
			NULL
		);
		if (!texture) return false;
		m_TextureList[fileName] = texture;
		return true;
}


void Texture::Release(std::string fileName)
{
	auto it = m_TextureList.find(fileName);
	if (it != m_TextureList.end())
	{
		(*it).second->Release();
		(*it).second = nullptr;
		m_TextureList.erase(fileName);
	}
}

void Texture::AllRelease()
{
	for (auto pair : m_TextureList)
	{
		pair.second->Release();
	//	pair.second = nullptr;
	}
	m_TextureList.clear();
}