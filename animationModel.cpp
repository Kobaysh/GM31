#include "main.h"
#include "renderer.h"
#include "animationModel.h"

void AnimationModel::Load(const char * fileName)
{
	const std::string modelPath(fileName);

	m_AiScene = aiImportFile(fileName, aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_ConvertToLeftHanded);
	assert(m_AiScene);
	m_VertexBuffer = new ID3D11Buffer*[m_AiScene->mNumMeshes];
	m_IndexBuffer = new ID3D11Buffer*[m_AiScene->mNumMeshes];

	m_DeformVertex = new std::vector<DEFORM_VERTEX>[m_AiScene->mNumMeshes];

	// 再帰的にボーン生成
	CreateBone(m_AiScene->mRootNode);
	
	for (unsigned int m = 0; m < m_AiScene->mNumMeshes; m++)
	{
		aiMesh* mesh = m_AiScene->mMeshes[m];
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

			Renderer::GetpDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer[m]);

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
			

			Renderer::GetpDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer[m]);

			delete[] index;
		}

		// 頂点データ初期化
		for (unsigned int v = 0; v < mesh->mNumVertices; v++) {
			DEFORM_VERTEX deformVertex;
			deformVertex.position = mesh->mVertices[v];
			deformVertex.normal = mesh->mNormals[v];
			deformVertex.boneNum = 0;
			for (unsigned int b = 0; b < 4; b++) {
				deformVertex.boneName[b] = "";
				deformVertex.boneWeight[b] = 0.0f;
			}
			m_DeformVertex[m].push_back(deformVertex);
		}

		// ボーンデータ初期化
		for (unsigned int b = 0; b < mesh->mNumBones; b++) {
			aiBone* bone = mesh->mBones[b];

			m_Bone[bone->mName.C_Str()].offsetMatrix = bone->mOffsetMatrix;

			for (unsigned int w = 0;w<bone->mNumWeights; w++) {
				aiVertexWeight weight = bone->mWeights[w];
				int num = m_DeformVertex[m][weight.mVertexId].boneNum;

				m_DeformVertex[m][weight.mVertexId].boneWeight[num] = weight.mWeight;
				m_DeformVertex[m][weight.mVertexId].boneName[num] = bone->mName.C_Str();
				m_DeformVertex[m][weight.mVertexId].boneNum++;

				assert(m_DeformVertex[m][weight.mVertexId].boneNum <= 4);
			}
		}
	}




	{
		for (unsigned int m = 0; m < m_AiScene->mNumMaterials; m++) {
			aiString path;
			if (m_AiScene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {
				if (path.data[0] == '*') {
					// FBXファイル内から読み込み
					if (m_Texture[path.data] == nullptr) {
						ID3D11ShaderResourceView* texture;
						int id = atoi(&path.data[1]);

						D3DX11CreateShaderResourceViewFromMemory(
							Renderer::GetpDevice().Get(),
							(const unsigned char*)m_AiScene->mTextures[id]->pcData,
							m_AiScene->mTextures[id]->mWidth,
							nullptr, nullptr, &texture, nullptr
						);

						m_Texture[path.data] = texture;
					}
					
				}
				else {
					// 外部ファイルから読み込み
				}
			}
			else {
				m_Texture[path.data] = nullptr;
			}
		}
	}
}

void AnimationModel::Unload()
{
	for (unsigned int m = 0; m < m_AiScene->mNumMeshes; m++) {
		m_VertexBuffer[m]->Release();
		m_IndexBuffer[m]->Release();
	}

	delete[] m_VertexBuffer;
	delete[] m_IndexBuffer;

	delete[] m_DeformVertex;

	for (auto pair : m_Texture) {
		pair.second->Release();
	}
	m_Texture.clear();

	aiReleaseImport(m_AiScene);

	for (auto pair : m_Animation) {
		aiReleaseImport(pair.second);
	}
}

void AnimationModel::LoadAnimaiton(const char * fileName, const char * animationName)
{
	m_Animation[animationName] = aiImportFile(fileName, aiProcess_ConvertToLeftHanded);
	assert(m_Animation[animationName]);
}

void AnimationModel::CreateBone(aiNode * node)
{
	BONE bone;
	m_Bone[node->mName.C_Str()] = bone;

	for (unsigned int n = 0; n < node->mNumChildren; n++) {
		CreateBone(node->mChildren[n]);
	}
}

void AnimationModel::Update(int frame)
{
	if (!m_AiScene->HasAnimations()) return;

	// アニメーションデータからボーンマトリクス算出
	aiAnimation* animation = m_AiScene->mAnimations[0];

	for (unsigned int c = 0; c < animation->mNumChannels; c++) {
		aiNodeAnim* nodeAnim = animation->mChannels[c];
		BONE* bone = &m_Bone[nodeAnim->mNodeName.C_Str()];

		int f;
		f = frame % nodeAnim->mNumRotationKeys;	// 簡易実装
		aiQuaternion rot = nodeAnim->mRotationKeys[f].mValue;

		f = frame % nodeAnim->mNumPositionKeys;
		aiVector3D pos = nodeAnim->mPositionKeys[f].mValue;

		bone->animationMatrix = aiMatrix4x4(aiVector3D(1.0f, 1.0f, 1.0f), rot, pos);

	}
	// 再帰的にボーンマトリクスを更新
	UpdateBoneMatrix(m_AiScene->mRootNode, aiMatrix4x4());

	// 頂点変換
	for (unsigned int m = 0; m < m_AiScene->mNumMeshes; m++) {
		aiMesh* mesh = m_AiScene->mMeshes[m];

		D3D11_MAPPED_SUBRESOURCE ms;
		Renderer::GetpDeviceContext()->Map(m_VertexBuffer[m], 0,
			D3D11_MAP_WRITE_DISCARD, 0, &ms);
		VERTEX_3DX * vertex = (VERTEX_3DX*)ms.pData;
		for (unsigned int v = 0; v < mesh->mNumVertices; v++) {
			DEFORM_VERTEX* deformVertex = &m_DeformVertex[m][v];

			aiMatrix4x4 matrix[4];
			aiMatrix4x4 outMatrix;

			matrix[0] = m_Bone[deformVertex->boneName[0]].matrix;
			matrix[1] = m_Bone[deformVertex->boneName[1]].matrix;
			matrix[2] = m_Bone[deformVertex->boneName[2]].matrix;
			matrix[3] = m_Bone[deformVertex->boneName[3]].matrix;

			// ウェイトを考慮してマトリクス算出
		/*	outMatrix   = matrix[0] * deformVertex->boneWeight[0]
						+ matrix[1] * deformVertex->boneWeight[1]
						+ matrix[2] * deformVertex->boneWeight[2]
						+ matrix[3] * deformVertex->boneWeight[3];
		*/
			{
				outMatrix.a1 = matrix[0].a1 * deformVertex->boneWeight[0]
					+ matrix[1].a1 * deformVertex->boneWeight[1]
					+ matrix[2].a1 * deformVertex->boneWeight[2]
					+ matrix[3].a1 * deformVertex->boneWeight[3];

				outMatrix.a2 = matrix[0].a2 * deformVertex->boneWeight[0]
					+ matrix[1].a2 * deformVertex->boneWeight[1]
					+ matrix[2].a2 * deformVertex->boneWeight[2]
					+ matrix[3].a2 * deformVertex->boneWeight[3];


				outMatrix.a3 = matrix[0].a3 * deformVertex->boneWeight[0]
					+ matrix[1].a3 * deformVertex->boneWeight[1]
					+ matrix[2].a3 * deformVertex->boneWeight[2]
					+ matrix[3].a3 * deformVertex->boneWeight[3];

				outMatrix.a4 = matrix[0].a4 * deformVertex->boneWeight[0]
					+ matrix[1].a4 * deformVertex->boneWeight[1]
					+ matrix[2].a4 * deformVertex->boneWeight[2]
					+ matrix[3].a4 * deformVertex->boneWeight[3];

				outMatrix.b1 = matrix[0].b1 * deformVertex->boneWeight[0]
					+ matrix[1].b1 * deformVertex->boneWeight[1]
					+ matrix[2].b1 * deformVertex->boneWeight[2]
					+ matrix[3].b1 * deformVertex->boneWeight[3];

				outMatrix.b2 = matrix[0].b2 * deformVertex->boneWeight[0]
					+ matrix[1].b2 * deformVertex->boneWeight[1]
					+ matrix[2].b2 * deformVertex->boneWeight[2]
					+ matrix[3].b2 * deformVertex->boneWeight[3];


				outMatrix.b3 = matrix[0].b3 * deformVertex->boneWeight[0]
					+ matrix[1].b3 * deformVertex->boneWeight[1]
					+ matrix[2].b3 * deformVertex->boneWeight[2]
					+ matrix[3].b3 * deformVertex->boneWeight[3];

				outMatrix.b4 = matrix[0].b4 * deformVertex->boneWeight[0]
					+ matrix[1].b4 * deformVertex->boneWeight[1]
					+ matrix[2].b4 * deformVertex->boneWeight[2]
					+ matrix[3].b4 * deformVertex->boneWeight[3];

				outMatrix.c1 = matrix[0].c1 * deformVertex->boneWeight[0]
					+ matrix[1].c1 * deformVertex->boneWeight[1]
					+ matrix[2].c1 * deformVertex->boneWeight[2]
					+ matrix[3].c1 * deformVertex->boneWeight[3];

				outMatrix.c2 = matrix[0].c2 * deformVertex->boneWeight[0]
					+ matrix[1].c2 * deformVertex->boneWeight[1]
					+ matrix[2].c2 * deformVertex->boneWeight[2]
					+ matrix[3].c2 * deformVertex->boneWeight[3];


				outMatrix.c3 = matrix[0].c3 * deformVertex->boneWeight[0]
					+ matrix[1].c3 * deformVertex->boneWeight[1]
					+ matrix[2].c3 * deformVertex->boneWeight[2]
					+ matrix[3].c3 * deformVertex->boneWeight[3];

				outMatrix.c4 = matrix[0].c4 * deformVertex->boneWeight[0]
					+ matrix[1].c4 * deformVertex->boneWeight[1]
					+ matrix[2].c4 * deformVertex->boneWeight[2]
					+ matrix[3].c4 * deformVertex->boneWeight[3];

				outMatrix.d1 = matrix[0].d1 * deformVertex->boneWeight[0]
					+ matrix[1].d1 * deformVertex->boneWeight[1]
					+ matrix[2].d1 * deformVertex->boneWeight[2]
					+ matrix[3].d1 * deformVertex->boneWeight[3];

				outMatrix.d2 = matrix[0].d2 * deformVertex->boneWeight[0]
					+ matrix[1].d2 * deformVertex->boneWeight[1]
					+ matrix[2].d2 * deformVertex->boneWeight[2]
					+ matrix[3].d2 * deformVertex->boneWeight[3];


				outMatrix.d3 = matrix[0].d3 * deformVertex->boneWeight[0]
					+ matrix[1].d3 * deformVertex->boneWeight[1]
					+ matrix[2].d3 * deformVertex->boneWeight[2]
					+ matrix[3].d3 * deformVertex->boneWeight[3];

				outMatrix.d4 = matrix[0].d4 * deformVertex->boneWeight[0]
					+ matrix[1].d4 * deformVertex->boneWeight[1]
					+ matrix[2].d4 * deformVertex->boneWeight[2]
					+ matrix[3].d4 * deformVertex->boneWeight[3];
			}

			deformVertex->position = mesh->mVertices[v];
			deformVertex->position *= outMatrix;

			// 法線変換用に移動成分を削除
			outMatrix.a4 = 0.0f;
			outMatrix.b4 = 0.0f;
			outMatrix.c4 = 0.0f;

			deformVertex->normal = mesh->mNormals[v];
			deformVertex->normal *= outMatrix;

			// 頂点バッファへ書き込み
			vertex[v].Position.x = deformVertex->position.x;
			vertex[v].Position.y = deformVertex->position.y;
			vertex[v].Position.z = deformVertex->position.z;

			vertex[v].Normal.x = deformVertex->normal.x;
			vertex[v].Normal.y = deformVertex->normal.y;
			vertex[v].Normal.z = deformVertex->normal.z;

			vertex[v].TexCoord.x = mesh->mTextureCoords[0][v].x;
			vertex[v].TexCoord.y = mesh->mTextureCoords[0][v].y;

			vertex[v].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		}
		Renderer::GetpDeviceContext()->Unmap(m_VertexBuffer[m], 0);
	}

}

void AnimationModel::Update(const char * animationName, int frame)
{
#if defined(_DEBUG) || defined(DEBUG)
	return;
#endif // ! (DEBUG | _DEBUG)
	if (m_Animation.count(animationName) <= 0) return;
	if (!m_Animation[animationName]->HasAnimations()) return;

	// アニメーションデータからボーンマトリクス算出
	aiAnimation* animation = m_Animation[animationName]->mAnimations[0];
	for (unsigned int c = 0; c < animation->mNumChannels; c++) {
		aiNodeAnim* nodeAnim = animation->mChannels[c];
		BONE* bone = &m_Bone[nodeAnim->mNodeName.C_Str()];
		int f;
		f = frame % nodeAnim->mNumRotationKeys;	// 簡易実装
		aiQuaternion rot = nodeAnim->mRotationKeys[f].mValue;

	//	f = frame % nodeAnim->mNumPositionKeys;
	//	aiVector3D pos = nodeAnim->mPositionKeys[f].mValue;
		aiVector3D pos = aiVector3D(0.0f,0.0f,0.0f);


		bone->animationMatrix = aiMatrix4x4(aiVector3D(1.0f, 1.0f, 1.0f), rot, pos);

	}
	// 再帰的にボーンマトリクスを更新
	UpdateBoneMatrix(m_AiScene->mRootNode, aiMatrix4x4());

	// 頂点変換
	for (unsigned int m = 0; m < m_AiScene->mNumMeshes; m++) {
		aiMesh* mesh = m_AiScene->mMeshes[m];

		D3D11_MAPPED_SUBRESOURCE ms;
		Renderer::GetpDeviceContext()->Map(m_VertexBuffer[m], 0,
			D3D11_MAP_WRITE_DISCARD, 0, &ms);
		VERTEX_3DX * vertex = (VERTEX_3DX*)ms.pData;
		for (unsigned int v = 0; v < mesh->mNumVertices; v++) {
			DEFORM_VERTEX* deformVertex = &m_DeformVertex[m][v];

			aiMatrix4x4 matrix[4];
			aiMatrix4x4 outMatrix;

			matrix[0] = m_Bone[deformVertex->boneName[0]].matrix;
			matrix[1] = m_Bone[deformVertex->boneName[1]].matrix;
			matrix[2] = m_Bone[deformVertex->boneName[2]].matrix;
			matrix[3] = m_Bone[deformVertex->boneName[3]].matrix;

			// ウェイトを考慮してマトリクス算出
			outMatrix =	UpdateWeight(matrix, deformVertex);

			deformVertex->position = mesh->mVertices[v];
			deformVertex->position *= outMatrix;

			// 法線変換用に移動成分を削除
			outMatrix.a4 = 0.0f;
			outMatrix.b4 = 0.0f;
			outMatrix.c4 = 0.0f;

			deformVertex->normal = mesh->mNormals[v];
			deformVertex->normal *= outMatrix;

			// 頂点バッファへ書き込み
			vertex[v].Position.x = deformVertex->position.x;
			vertex[v].Position.y = deformVertex->position.y;
			vertex[v].Position.z = deformVertex->position.z;

			vertex[v].Normal.x = deformVertex->normal.x;
			vertex[v].Normal.y = deformVertex->normal.y;
			vertex[v].Normal.z = deformVertex->normal.z;

			vertex[v].TexCoord.x = mesh->mTextureCoords[0][v].x;
			vertex[v].TexCoord.y = mesh->mTextureCoords[0][v].y;

			vertex[v].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		}
		Renderer::GetpDeviceContext()->Unmap(m_VertexBuffer[m], 0);
	}

}

void AnimationModel::Update(const char * animationName1, const char * animationName2, float blendRate, int frame)
{
#if defined(_DEBUG) || defined(DEBUG)
	return;
#endif // ! (DEBUG | _DEBUG)

	if (!m_Animation[animationName1]->HasAnimations()) return;
	if (!m_Animation[animationName2]->HasAnimations()) return;

	// アニメーションデータからボーンマトリクス算出
	aiAnimation* animation1 = m_Animation[animationName1]->mAnimations[0];
	aiAnimation* animation2 = m_Animation[animationName2]->mAnimations[0];

	for (unsigned int c = 0; c < animation1->mNumChannels; c++) {
		aiNodeAnim* nodeAnim1 = animation1->mChannels[c];
		aiNodeAnim* nodeAnim2 = animation2->mChannels[c];
		BONE* bone = &m_Bone[nodeAnim1->mNodeName.C_Str()];

		int f;
		f = frame % nodeAnim1->mNumRotationKeys;	// 簡易実装
		aiQuaternion rot1 = nodeAnim1->mRotationKeys[f].mValue;

		f = frame % nodeAnim2->mNumRotationKeys;	// 簡易実装
		aiQuaternion rot2 = nodeAnim2->mRotationKeys[f].mValue;

		//	f = frame % nodeAnim->mNumPositionKeys;
		//	aiVector3D pos = nodeAnim->mPositionKeys[f].mValue;
		aiVector3D pos1 = aiVector3D(0.0f, 0.0f, 0.0f);
		aiVector3D pos2 = aiVector3D(0.0f, 0.0f, 0.0f);
		aiVector3D pos = pos1 * (1.0f - blendRate) + pos2 * blendRate;
		aiQuaternion rot;
		aiQuaternion::Interpolate(rot, rot1, rot2, blendRate); // 球面線形補間




		bone->animationMatrix = aiMatrix4x4(aiVector3D(1.0f, 1.0f, 1.0f), rot, pos);

	}
	// 再帰的にボーンマトリクスを更新
	UpdateBoneMatrix(m_AiScene->mRootNode, aiMatrix4x4());

	// 頂点変換
	for (unsigned int m = 0; m < m_AiScene->mNumMeshes; m++) {
		aiMesh* mesh = m_AiScene->mMeshes[m];

		D3D11_MAPPED_SUBRESOURCE ms;
		Renderer::GetpDeviceContext()->Map(m_VertexBuffer[m], 0,
			D3D11_MAP_WRITE_DISCARD, 0, &ms);
		VERTEX_3DX * vertex = (VERTEX_3DX*)ms.pData;
		for (unsigned int v = 0; v < mesh->mNumVertices; v++) {
			DEFORM_VERTEX* deformVertex = &m_DeformVertex[m][v];

			aiMatrix4x4 matrix[4];
			aiMatrix4x4 outMatrix;

			matrix[0] = m_Bone[deformVertex->boneName[0]].matrix;
			matrix[1] = m_Bone[deformVertex->boneName[1]].matrix;
			matrix[2] = m_Bone[deformVertex->boneName[2]].matrix;
			matrix[3] = m_Bone[deformVertex->boneName[3]].matrix;

			// ウェイトを考慮してマトリクス算出
			outMatrix = UpdateWeight(matrix, deformVertex);

			deformVertex->position = mesh->mVertices[v];
			deformVertex->position *= outMatrix;

			// 法線変換用に移動成分を削除
			outMatrix.a4 = 0.0f;
			outMatrix.b4 = 0.0f;
			outMatrix.c4 = 0.0f;

			deformVertex->normal = mesh->mNormals[v];
			deformVertex->normal *= outMatrix;

			// 頂点バッファへ書き込み
			vertex[v].Position.x = deformVertex->position.x;
			vertex[v].Position.y = deformVertex->position.y;
			vertex[v].Position.z = deformVertex->position.z;

			vertex[v].Normal.x = deformVertex->normal.x;
			vertex[v].Normal.y = deformVertex->normal.y;
			vertex[v].Normal.z = deformVertex->normal.z;

			vertex[v].TexCoord.x = mesh->mTextureCoords[0][v].x;
			vertex[v].TexCoord.y = mesh->mTextureCoords[0][v].y;

			vertex[v].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		}
		Renderer::GetpDeviceContext()->Unmap(m_VertexBuffer[m], 0);
	}


}

void AnimationModel::UpdateBoneMatrix(aiNode * node, aiMatrix4x4 matrix)
{
	BONE* bone = &m_Bone[node->mName.C_Str()];

	aiMatrix4x4 worldMatrix;

	worldMatrix = matrix;
	worldMatrix *= node->mTransformation;
	worldMatrix *= bone->animationMatrix;

	bone->matrix = worldMatrix;
	bone->matrix *= bone->offsetMatrix;

	for (unsigned int n = 0; n < node->mNumChildren; n++) {
		UpdateBoneMatrix(node->mChildren[n], worldMatrix);
	}

}

aiMatrix4x4  AnimationModel::UpdateWeight(aiMatrix4x4*  matrix4x4, DEFORM_VERTEX* deformVertex)
{
	aiMatrix4x4 outMatrix;

	outMatrix.a1 = matrix4x4[0].a1 * deformVertex->boneWeight[0];
	outMatrix.a2 = matrix4x4[0].a2 * deformVertex->boneWeight[0];
	outMatrix.a3 = matrix4x4[0].a3 * deformVertex->boneWeight[0];
	outMatrix.a4 = matrix4x4[0].a4 * deformVertex->boneWeight[0];

	outMatrix.b1 = matrix4x4[0].b1 * deformVertex->boneWeight[0];
	outMatrix.b2 = matrix4x4[0].b2 * deformVertex->boneWeight[0];
	outMatrix.b3 = matrix4x4[0].b3 * deformVertex->boneWeight[0];
	outMatrix.b4 = matrix4x4[0].b4 * deformVertex->boneWeight[0];

	outMatrix.c1 = matrix4x4[0].c1 * deformVertex->boneWeight[0];
	outMatrix.c2 = matrix4x4[0].c2 * deformVertex->boneWeight[0];
	outMatrix.c3 = matrix4x4[0].c3 * deformVertex->boneWeight[0];
	outMatrix.c4 = matrix4x4[0].c4 * deformVertex->boneWeight[0];

	outMatrix.d1 = matrix4x4[0].d1 * deformVertex->boneWeight[0];
	outMatrix.d2 = matrix4x4[0].d2 * deformVertex->boneWeight[0];
	outMatrix.d3 = matrix4x4[0].d3 * deformVertex->boneWeight[0];
	outMatrix.d4 = matrix4x4[0].d4 * deformVertex->boneWeight[0];
		
	for (int i = 1; i < 4; i++) {
		outMatrix.a1 += matrix4x4[i].a1 * deformVertex->boneWeight[i];
		outMatrix.a2 += matrix4x4[i].a2 * deformVertex->boneWeight[i];
		outMatrix.a3 += matrix4x4[i].a3 * deformVertex->boneWeight[i];
		outMatrix.a4 += matrix4x4[i].a4 * deformVertex->boneWeight[i];

		outMatrix.b1 += matrix4x4[i].b1 * deformVertex->boneWeight[i];
		outMatrix.b2 += matrix4x4[i].b2 * deformVertex->boneWeight[i];
		outMatrix.b3 += matrix4x4[i].b3 * deformVertex->boneWeight[i];
		outMatrix.b4 += matrix4x4[i].b4 * deformVertex->boneWeight[i];

		outMatrix.c1 += matrix4x4[i].c1 * deformVertex->boneWeight[i];
		outMatrix.c2 += matrix4x4[i].c2 * deformVertex->boneWeight[i];
		outMatrix.c3 += matrix4x4[i].c3 * deformVertex->boneWeight[i];
		outMatrix.c4 += matrix4x4[i].c4 * deformVertex->boneWeight[i];

		outMatrix.d1 += matrix4x4[i].d1 * deformVertex->boneWeight[i];
		outMatrix.d2 += matrix4x4[i].d2 * deformVertex->boneWeight[i];
		outMatrix.d3 += matrix4x4[i].d3 * deformVertex->boneWeight[i];
		outMatrix.d4 += matrix4x4[i].d4 * deformVertex->boneWeight[i];
	}
	return outMatrix;
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

	for (unsigned int m = 0; m < m_AiScene->mNumMeshes; m++) {
		aiMesh* mesh = m_AiScene->mMeshes[m];

		aiMaterial* aiMaterial = m_AiScene->mMaterials[mesh->mMaterialIndex];
		
		// テクスチャ設定
		aiString path;
		aiMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &path);
		Renderer::GetpDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[path.data]);


		// 頂点バッファ
		UINT stride = sizeof(VERTEX_3DX);
		UINT offset = 0;
		Renderer::GetpDeviceContext()->IASetVertexBuffers(
			0, 1, &m_VertexBuffer[m], &stride, &offset
		);

		// インデックスバッファ
		Renderer::GetpDeviceContext()->IASetIndexBuffer(
			m_IndexBuffer[m], DXGI_FORMAT_R32_UINT, 0
		);



		Renderer::GetpDeviceContext()->DrawIndexed(mesh->mNumFaces * 3, 0, 0);
			
	}

}
