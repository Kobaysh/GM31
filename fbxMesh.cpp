//#include "fbxMesh.h"
//
//bool FbxMeshFile::Load(const char* file_name)
//{
//	char file_path[256];
//	std::vector<std::string> out_material_list;
//	int len = strlen(file_name);
//	int path_tail_point = 0;
//
//	for (int i = len - 1; i >= 0; i--)
//	{
//		if (file_name[i] == '/')
//		{
//			path_tail_point = i;
//			break;
//		}
//	}
//
//	strncpy_s(file_path, file_name, path_tail_point + 1);
//
//	// XFile読み込み
//	if (LoadFbxFile(out_material_list, file_path, file_name) == false)
//	{
//		return false;
//	}
//
//	// VertexBuffer作成
//	if (CreateVertexBuffer() == false)
//	{
//		return false;
//	}
//
//	// IndexBuffer作成
//	if (CreateIndexBuffer() == false)
//	{
//		return false;
//	}
//
//	return true;
//}
//
//void FbxMeshFile::Render(XMFLOAT3 pos, XMFLOAT3 scale, XMFLOAT3 degree)
//{
//	UINT strides = sizeof(VERTEX_3DX);
//	UINT offsets = 0;
//
//	XMMATRIX matrix;
//	XMMATRIX translate_matrix = XMMatrixTranslation(pos.x, pos.y, pos.z);
//	XMMATRIX scale_matrix = XMMatrixScaling(scale.x, scale.y, scale.z);
//	XMMATRIX rotateX_matrix = XMMatrixRotationX(XMConvertToRadians(degree.x));
//	XMMATRIX rotateY_matrix = XMMatrixRotationY(XMConvertToRadians(degree.y));
//	XMMATRIX rotateZ_matrix = XMMatrixRotationZ(XMConvertToRadians(degree.z));
//	matrix = scale_matrix * rotateX_matrix* rotateY_matrix * rotateZ_matrix * translate_matrix;
//
//	Renderer::SetWorldMatrixX(&matrix);
//	
//
//	Renderer::GetpDeviceContext()->SetTransform(D3DTS_WORLD, &matrix);
//
//	for (auto index : m_Indices)
//	{
//		// FVF設定(XYZ座標、法線)
//		Renderer::GetpDevice()->SetFVF(MESH_FVF);
//		// 頂点バッファの登録
//		Renderer::GetpDevice()->SetStreamSource(0, m_VertexBuffers[index.first], 0, strides);
//		// インデックスバッファの登録
//		Renderer::GetpDevice()->SetIndices(m_IndexBuffers[index.first]);
//		// 描画
//		Renderer::GetpDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_Vertices[index.first].size(), 0, index.second.size() / 3);
//	}
//}
//
//bool FbxMeshFile::CreateMesh(const char* node_name, FbxMesh* mesh)
//{
//	// 頂点バッファの取得
//	FbxVector4* vertices = mesh->GetControlPoints();
//	// インデックスバッファの取得
//	int* indices = mesh->GetPolygonVertices();
//	// 頂点座標の数の取得
//	int polygon_vertex_count = mesh->GetPolygonVertexCount();
//
//	// GetPolygonVertexCount => 頂点数
//	for (int i = 0; i < polygon_vertex_count; i++)
//	{
//		VERTEX_3DX vertex;
//		// インデックスバッファから頂点番号を取得
//		int index = indices[i];
//
//		// 頂点座標リストから座標を取得する
//		vertex.Position.x = (float)-vertices[index][0];
//		vertex.Position.y = (float)vertices[index][1];
//		vertex.Position.z = (float)vertices[index][2];
//
//		// 追加
//		m_Vertices[node_name].push_back(vertex);
//	}
//
//	FbxArray<FbxVector4> normals;
//	// 法線リストの取得
//	mesh->GetPolygonVertexNormals(normals);
//
//	// 法線設定
//	for (int i = 0; i < normals.Size(); i++)
//	{
//		m_Vertices[node_name][i].Normal.x = (float)-normals[i][0];
//		m_Vertices[node_name][i].Normal.y = (float)normals[i][1];
//		m_Vertices[node_name][i].Normal.z = (float)normals[i][2];
//	}
//
//	// ポリゴン数の取得
//	int polygon_count = mesh->GetPolygonCount();
//
//	// ポリゴンの数だけ連番として保存する
//	for (int i = 0; i < polygon_count; i++)
//	{
//		m_Indices[node_name].push_back(i * 3 + 2);
//		m_Indices[node_name].push_back(i * 3 + 1);
//		m_Indices[node_name].push_back(i * 3 + 0);
//	}
//
//	return true;
//}
//
//
//bool FbxMeshFile::LoadFbxFile(std::vector<std::string>& out_material_list, const char* file_path, const char* file_name)
//{
//	// FbxManager作成
//	FbxManager* fbx_manager = fbxsdk::FbxManager::Create();
//	if (fbx_manager == nullptr)
//	{
//		return false;
//	}
//
//	// FbxImporter作成
//	FbxImporter* fbx_importer = FbxImporter::Create(fbx_manager, "");
//	if (fbx_importer == nullptr)
//	{
//		fbx_manager->Destroy();
//		return false;
//	}
//
//	// FbxScene作成
//	FbxScene* fbx_scene = FbxScene::Create(fbx_manager, "");
//	if (fbx_scene == nullptr)
//	{
//		fbx_importer->Destroy();
//		fbx_manager->Destroy();
//		return false;
//	}
//
//	// Fileを初期化
//	fbx_importer->Initialize(file_name);
//	// sceneにインポート
//	fbx_importer->Import(fbx_scene);
//
//	FbxGeometryConverter converter(fbx_manager);
//	// ポリゴンを三角形にする
//	converter.Triangulate(fbx_scene, true);
//
//	std::map<std::string, FbxNode*> mesh_node_list;
//	// メッシュNodeを探す
//	CollectMeshNode(fbx_scene->GetRootNode(), mesh_node_list);
//
//	for (auto data : mesh_node_list)
//	{
//		// mesh作成
//		CreateMesh(data.first.c_str(), data.second->GetMesh());
//	}
//
//	fbx_importer->Destroy();
//	fbx_scene->Destroy();
//	fbx_manager->Destroy();
//
//	return true;
//}
//
//bool FbxMeshFile::CreateVertexBuffer()
//{
//	for (auto vertex_buffer : m_Vertices)
//	{
//		if (FAILED(Renderer::GetpDevice()->CreateVertexBuffer(
//			// 作成するバッファのサイズ(頂点バッファの数 * 頂点構造体のサイズ)
//			sizeof(CustomVertex) * vertex_buffer.second.size(),
//			// 使用方法
//			0,
//			// FVF設定(SetFVF設定できるので0でも可)
//			MESH_FVF,
//			// メモリの指定
//			D3DPOOL_MANAGED,
//			// 生成したVertexBufferの格納先の指定
//			&m_VertexBuffers[vertex_buffer.first],
//			// nullptr固定
//			nullptr)))
//		{
//			return false;
//		}
//
//		// 頂点バッファにデータをコピーする
//		VERTEX_3DX* list;
//		if (SUCCEEDED(m_VertexBuffers[vertex_buffer.first]->Lock(
//			// Lockする領域のオフセット値
//			0,
//			// Lockする領域のサイズ(0なら全体)
//			0,
//			// ロックされたポインタ変数を受け取る変数
//			(void**)&list,
//			// ロックの種類
//			0
//		)))
//		{
//			// 頂点データをコピー
//			for (int i = 0; i < vertex_buffer.second.size(); i++)
//			{
//				list[i] = vertex_buffer.second[i];
//			}
//
//			m_VertexBuffers[vertex_buffer.first]->Unlock();
//		}
//	}
//
//	return true;
//}
//
//bool FbxMeshFile::CreateIndexBuffer()
//{
//	for (auto index : m_Indices)
//	{
//		_D3DFORMAT format = _D3DFORMAT::D3DFMT_INDEX32;
//
//		if (FAILED(Renderer::GetpDevice()->CreateIndexBuffer(
//			// インデックスバッファのサイズ
//			sizeof(UINT) * index.second.size(),
//			// 使用方法
//			D3DUSAGE_WRITEONLY,
//			// インデックスバッファのフォーマット
//			format,
//			// メモリの指定
//			D3DPOOL_MANAGED,
//			// 生成したIndexBufferの格納先の指定
//			&m_IndexBuffers[index.first],
//			// nullptr固定
//			nullptr)))
//		{
//			return false;
//		}
//
//		// インデックスバッファにコピーする
//		UINT* index_buffer;
//		if (SUCCEEDED(m_IndexBuffers[index.first]->Lock(
//			// Lockする領域のオフセット値
//			0,
//			// Lockする領域のサイズ(0なら全体)
//			0,
//			// ロックされたポインタ変数を受け取る変数
//			(void**)&index_buffer,
//			// ロックの種類
//			0
//		)))
//		{
//			// インデックスデータをコピー
//			for (int i = 0; i < index.second.size() / 3; i++)
//			{
//				for (int j = 0; j < 3; j++)
//				{
//					index_buffer[i * 3 + j] = index.second[i * 3 + j];
//				}
//			}
//
//			m_IndexBuffers[index.first]->Unlock();
//
//		}
//	}
//
//	return true;
//}
//
//void FbxMeshFile::CollectMeshNode(FbxNode* node, std::map<std::string, FbxNode*>& list)
//{
//	for (int i = 0; i < node->GetNodeAttributeCount(); i++)
//	{
//		FbxNodeAttribute* attribute = node->GetNodeAttributeByIndex(i);
//
//		// Attributeがメッシュなら追加
//		if (attribute->GetAttributeType() == FbxNodeAttribute::EType::eMesh)
//		{
//			list[node->GetName()] = node;
//			break;
//		}
//	}
//
//	for (int i = 0; i < node->GetChildCount(); i++)
//	{
//		CollectMeshNode(node->GetChild(i), list);
//	}
//}
