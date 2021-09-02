#include "main.h"
#include "renderer.h"
#include "animationModel.h"

void AnimationModel::Load(const char * fileName)
{
	const std::string modelPath(fileName);

	m_aiScene = aiImportFile(fileName, aiProcessPreset_TargetRealtime_MaxQuality);
	assert(m_aiScene);
	m_vertexBuffer = new ID3D11Buffer*[m_aiScene->mNumMeshes];
	m_indexBuffer = new ID3D11Buffer*[m_aiScene->mNumMeshes];
	
	for (unsigned int m = 0; m < m_aiScene->mNumMeshes; m++)
	{
		aiMesh* mesh = m_aiScene->mMeshes[m];
		// 頂点バッファ設定
		{
			VERTEX_3DX* vertex = new VERTEX_3DX[mesh->mNumVertices];

			for (unsigned int v = 0; v < mesh->mNumVertices; v++)
			{
				vertex[v].Position = XMFLOAT3(mesh->mVertices[v].x, mesh->mVertices[v].y, mesh->mVertices[v].z);
				vertex[v].Normal = XMFLOAT3(mesh->mNormals[v].x, mesh->mNormals[v].y, mesh->mNormals[v].z);
				vertex[v].TexCoord = XMFLOAT2(mesh->mTextureCoords[0][v].x, mesh->mTextureCoords[0][v].y);
				vertex[v].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			}


			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DYNAMIC;	// 動的
			bd.ByteWidth = sizeof(VERTEX_3DX)* mesh->mNumVertices;
			bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	// 上書き可能

			D3D11_SUBRESOURCE_DATA sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.pSysMem = vertex;

			Renderer::GetpDevice()->CreateBuffer(&bd, &sd, &m_vertexBuffer[m]);

			delete[] vertex;
		}


		// インデックスバッファ設定
		{
			unsigned int* index = new unsigned int[mesh->mNumFaces * 3];
			for (unsigned int f = 0; f < mesh->mNumFaces; f++) {
				const aiFace* face = &mesh->mFaces[f];

				assert(face->mNumIndices == 3);

				index[f * 3 + 0] = face->mIndices[0];
				index[f * 3 + 1] = face->mIndices[1];
				index[f * 3 + 2] = face->mIndices[2];
			}

			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DEFAULT;	
			bd.ByteWidth = sizeof(unsigned int)* mesh->mNumFaces * 3;
			bd.BindFlags = D3D10_BIND_INDEX_BUFFER;
			bd.CPUAccessFlags = 0;

			D3D11_SUBRESOURCE_DATA sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.pSysMem = index;
			

			Renderer::GetpDevice()->CreateBuffer(&bd, &sd, &m_indexBuffer[m]);

			delete[] index;
		}
	}
}

void AnimationModel::Unload()
{
	for (unsigned int m = 0; m < m_aiScene->mNumMeshes; m++) {
		m_vertexBuffer[m]->Release();
		m_indexBuffer[m]->Release();
	}

	delete[] m_vertexBuffer;
	delete[] m_indexBuffer;

	aiReleaseImport(m_aiScene);
}

void AnimationModel::Update()
{

}

void AnimationModel::Draw()
{
	// プリミティブトポロジ設定
	Renderer::GetpDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// マテリアル設定
	MATERIALX material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.Ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	Renderer::SetMaterialX(material);

	for (unsigned int m = 0; m < m_aiScene->mNumMeshes; m++) {
		aiMesh* mesh = m_aiScene->mMeshes[m];

		// 頂点バッファ
		UINT stride = sizeof(VERTEX_3DX);
		UINT offset = 0;
		Renderer::GetpDeviceContext()->IASetVertexBuffers(
			0, 1, &m_vertexBuffer[m], &stride, &offset
		);

		// インデックスバッファ
		Renderer::GetpDeviceContext()->IASetIndexBuffer(
			m_indexBuffer[m], DXGI_FORMAT_R32_UINT, 0
		);
		Renderer::GetpDeviceContext()->DrawIndexed(mesh->mNumFaces * 3, 0, 0);
			
	}

}
