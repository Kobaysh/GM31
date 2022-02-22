#pragma once
#include "main.h"
#include <unordered_map>

// ���_���
struct VertexShaderLayout
{
	ID3D11VertexShader* m_VertexShader;
	ID3D11InputLayout* m_VertexLayout;
};

// �V�F�[�_�[�Ǘ��N���X
class ShaderManager
{
public:
	enum Shader_Type {
		ST_VS,
		ST_PS,
	};
	ShaderManager();
	~ShaderManager();

	// �ǂݍ���
	static void Load(Shader_Type type,  std::string pFileName);

	// ���
	static void Release(Shader_Type type,  std::string pFileName);

	// �S���
	static void AllRelease();

	// ���_�V�F�[�_�[�Q�b�^�[
	static VertexShaderLayout* GetVertexShader(std::string pFileName) { return m_VertexInfo[pFileName]; }

	// �s�N�Z���V�F�[�_�[�Q�b�^�[
	static ID3D11PixelShader* GetPixelShader(std::string pFileName) { return m_PixelShaders[pFileName]; }

private:
	static std::unordered_map<std::string, VertexShaderLayout*> m_VertexInfo;	// ���_���
	static std::unordered_map<std::string, ID3D11PixelShader*> m_PixelShaders;	// �s�N�Z���V�F�[�_�[
};

