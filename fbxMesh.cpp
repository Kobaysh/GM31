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
//	// XFile�ǂݍ���
//	if (LoadFbxFile(out_material_list, file_path, file_name) == false)
//	{
//		return false;
//	}
//
//	// VertexBuffer�쐬
//	if (CreateVertexBuffer() == false)
//	{
//		return false;
//	}
//
//	// IndexBuffer�쐬
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
//		// FVF�ݒ�(XYZ���W�A�@��)
//		Renderer::GetpDevice()->SetFVF(MESH_FVF);
//		// ���_�o�b�t�@�̓o�^
//		Renderer::GetpDevice()->SetStreamSource(0, m_VertexBuffers[index.first], 0, strides);
//		// �C���f�b�N�X�o�b�t�@�̓o�^
//		Renderer::GetpDevice()->SetIndices(m_IndexBuffers[index.first]);
//		// �`��
//		Renderer::GetpDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_Vertices[index.first].size(), 0, index.second.size() / 3);
//	}
//}
//
//bool FbxMeshFile::CreateMesh(const char* node_name, FbxMesh* mesh)
//{
//	// ���_�o�b�t�@�̎擾
//	FbxVector4* vertices = mesh->GetControlPoints();
//	// �C���f�b�N�X�o�b�t�@�̎擾
//	int* indices = mesh->GetPolygonVertices();
//	// ���_���W�̐��̎擾
//	int polygon_vertex_count = mesh->GetPolygonVertexCount();
//
//	// GetPolygonVertexCount => ���_��
//	for (int i = 0; i < polygon_vertex_count; i++)
//	{
//		VERTEX_3DX vertex;
//		// �C���f�b�N�X�o�b�t�@���璸�_�ԍ����擾
//		int index = indices[i];
//
//		// ���_���W���X�g������W���擾����
//		vertex.Position.x = (float)-vertices[index][0];
//		vertex.Position.y = (float)vertices[index][1];
//		vertex.Position.z = (float)vertices[index][2];
//
//		// �ǉ�
//		m_Vertices[node_name].push_back(vertex);
//	}
//
//	FbxArray<FbxVector4> normals;
//	// �@�����X�g�̎擾
//	mesh->GetPolygonVertexNormals(normals);
//
//	// �@���ݒ�
//	for (int i = 0; i < normals.Size(); i++)
//	{
//		m_Vertices[node_name][i].Normal.x = (float)-normals[i][0];
//		m_Vertices[node_name][i].Normal.y = (float)normals[i][1];
//		m_Vertices[node_name][i].Normal.z = (float)normals[i][2];
//	}
//
//	// �|���S�����̎擾
//	int polygon_count = mesh->GetPolygonCount();
//
//	// �|���S���̐������A�ԂƂ��ĕۑ�����
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
//	// FbxManager�쐬
//	FbxManager* fbx_manager = fbxsdk::FbxManager::Create();
//	if (fbx_manager == nullptr)
//	{
//		return false;
//	}
//
//	// FbxImporter�쐬
//	FbxImporter* fbx_importer = FbxImporter::Create(fbx_manager, "");
//	if (fbx_importer == nullptr)
//	{
//		fbx_manager->Destroy();
//		return false;
//	}
//
//	// FbxScene�쐬
//	FbxScene* fbx_scene = FbxScene::Create(fbx_manager, "");
//	if (fbx_scene == nullptr)
//	{
//		fbx_importer->Destroy();
//		fbx_manager->Destroy();
//		return false;
//	}
//
//	// File��������
//	fbx_importer->Initialize(file_name);
//	// scene�ɃC���|�[�g
//	fbx_importer->Import(fbx_scene);
//
//	FbxGeometryConverter converter(fbx_manager);
//	// �|���S�����O�p�`�ɂ���
//	converter.Triangulate(fbx_scene, true);
//
//	std::map<std::string, FbxNode*> mesh_node_list;
//	// ���b�V��Node��T��
//	CollectMeshNode(fbx_scene->GetRootNode(), mesh_node_list);
//
//	for (auto data : mesh_node_list)
//	{
//		// mesh�쐬
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
//			// �쐬����o�b�t�@�̃T�C�Y(���_�o�b�t�@�̐� * ���_�\���̂̃T�C�Y)
//			sizeof(CustomVertex) * vertex_buffer.second.size(),
//			// �g�p���@
//			0,
//			// FVF�ݒ�(SetFVF�ݒ�ł���̂�0�ł���)
//			MESH_FVF,
//			// �������̎w��
//			D3DPOOL_MANAGED,
//			// ��������VertexBuffer�̊i�[��̎w��
//			&m_VertexBuffers[vertex_buffer.first],
//			// nullptr�Œ�
//			nullptr)))
//		{
//			return false;
//		}
//
//		// ���_�o�b�t�@�Ƀf�[�^���R�s�[����
//		VERTEX_3DX* list;
//		if (SUCCEEDED(m_VertexBuffers[vertex_buffer.first]->Lock(
//			// Lock����̈�̃I�t�Z�b�g�l
//			0,
//			// Lock����̈�̃T�C�Y(0�Ȃ�S��)
//			0,
//			// ���b�N���ꂽ�|�C���^�ϐ����󂯎��ϐ�
//			(void**)&list,
//			// ���b�N�̎��
//			0
//		)))
//		{
//			// ���_�f�[�^���R�s�[
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
//			// �C���f�b�N�X�o�b�t�@�̃T�C�Y
//			sizeof(UINT) * index.second.size(),
//			// �g�p���@
//			D3DUSAGE_WRITEONLY,
//			// �C���f�b�N�X�o�b�t�@�̃t�H�[�}�b�g
//			format,
//			// �������̎w��
//			D3DPOOL_MANAGED,
//			// ��������IndexBuffer�̊i�[��̎w��
//			&m_IndexBuffers[index.first],
//			// nullptr�Œ�
//			nullptr)))
//		{
//			return false;
//		}
//
//		// �C���f�b�N�X�o�b�t�@�ɃR�s�[����
//		UINT* index_buffer;
//		if (SUCCEEDED(m_IndexBuffers[index.first]->Lock(
//			// Lock����̈�̃I�t�Z�b�g�l
//			0,
//			// Lock����̈�̃T�C�Y(0�Ȃ�S��)
//			0,
//			// ���b�N���ꂽ�|�C���^�ϐ����󂯎��ϐ�
//			(void**)&index_buffer,
//			// ���b�N�̎��
//			0
//		)))
//		{
//			// �C���f�b�N�X�f�[�^���R�s�[
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
//		// Attribute�����b�V���Ȃ�ǉ�
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
