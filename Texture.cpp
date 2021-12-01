#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "texture.h"

//std::list<Texture*> Texture::m_textureList;
std::unordered_map<std::string,ID3D11ShaderResourceView*> Texture::m_textureList;


//ID3D11ShaderResourceView * Texture::GetTexture(int textureId)
//{
//	if (textureId <= INVALID_TEXURE_ID) return nullptr;
//	auto it = m_textureList.begin();
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
//	if (m_textureList.empty()) {
//		Texture* newTexture = new Texture();
//		newTexture->m_fileName = pFileName;
//		m_textureList.push_back(newTexture);
//		return i;
//	}
//	for (Texture* texture : m_textureList) {
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
//	for (Texture* texture : m_textureList) {
//		if (texture->m_fileName[0] != 0) {
//			i++;
//			continue;
//		}
//	}
//	Texture* newTexture = new Texture();
//	newTexture->m_fileName = pFileName;
//	m_textureList.push_back(newTexture);
//	return i;
//}
//
//void Texture::Load(int textureId)
//{
//	if (textureId <= INVALID_TEXURE_ID) return;
//	auto it = m_textureList.begin();
//	for (int i = 0; i < textureId; i++) {
//		it++;
//	}
//	Texture* _texture = *it;
//	if (_texture->m_fileName[0] == 0) return;
//	if (_texture->m_isLoaded) return;
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
//	_texture->m_isLoaded = true;
//}
//
//void Texture::AllLoad()
//{
//	for (Texture* texture : m_textureList) {
//		if (texture->m_fileName[0] == 0) return;
//		if (texture->m_isLoaded) return;
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
//		texture->m_isLoaded = true;
//	}
//}
//
//void Texture::Release(int textureId)
//{
//	if (textureId == INVALID_TEXURE_ID) return;
//	auto it = m_textureList.begin();
//	for (int i = 0; i < textureId; i++) {
//		it++;
//	}
//	Texture* texture = *it;
//	if (texture->m_texture) {
//		delete texture->m_texture;
//		texture->m_texture = nullptr;
//	}
//	m_textureList.erase(std::next(m_textureList.begin(), textureId));
//}
//
//void Texture::AllRelease()
//{
//	auto it = m_textureList.begin();
//	for (unsigned int i = 0; i < m_textureList.size(); i++) {
//		Texture* texture = *it;
//		if (texture->m_texture) {
//			delete texture->m_texture;
//			texture->m_texture = nullptr;
//		}
//		it++;
//	}
//	m_textureList.clear();
//}


ID3D11ShaderResourceView** Texture::GetTexture(std::string fileName)
{
	auto it = m_textureList.find(fileName);
	if (it != m_textureList.end())
	{
		return &(*it).second;
	}
	return nullptr;
}


bool Texture::Load(std::string fileName)
{
	auto it = m_textureList.find(fileName);
	if (it != m_textureList.end())
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
		assert(texture);
		m_textureList[fileName] = texture;
		return true;
}


void Texture::Release(std::string fileName)
{
	auto it = m_textureList.find(fileName);
	if (it != m_textureList.end())
	{
		(*it).second->Release();
		(*it).second = nullptr;
		m_textureList.erase(fileName);
	}
}

void Texture::AllRelease()
{
	for (auto pair : m_textureList)
	{
		pair.second->Release();
		pair.second = nullptr;
	}
	m_textureList.clear();
}