#include "main.h"
#include "renderer.h"
#include "meshField.h"
#include "keylogger.h"

const static float testField[21][21] = {
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.5f,+1.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+1.0f,+2.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+1.0f,+2.0f,+3.0f,+1.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+1.0f,+2.0f,+3.0f,+2.0f,+0.0f,-1.0f,-2.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+1.0f,+2.0f,+3.0f,+2.0f,+1.0f,-1.0f,-2.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+1.0f,+2.0f,+3.0f,+2.0f,+1.0f,+0.0f,-2.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+1.0f,+0.0f,+0.0f,+1.0f,+2.0f,+3.0f,+2.0f,+1.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+1.5f,+0.0f,+0.0f,+1.0f,+2.0f,+3.0f,+2.0f,+1.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+2.0f,+0.0f,+0.0f,+1.0f,+2.0f,+3.0f,+2.0f,+1.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+1.5f,+0.0f,+0.0f,+1.0f,+2.0f,+3.0f,+2.0f,+1.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+2.0f,+0.0f,+0.0f,+1.0f,+2.0f,+3.0f,+2.0f,+1.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+1.5f,+0.0f,+0.0f,+1.0f,+2.0f,+3.0f,+2.0f,+1.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+1.0f,+0.0f,+0.0f,+1.0f,+2.0f,+3.0f,+2.0f,+1.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.5f,+0.0f,+0.0f,+1.0f,+2.0f,+3.0f,+2.0f,+1.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+1.0f,+0.0f,+0.0f,+1.0f,+2.0f,+3.0f,+2.0f,+1.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+1.5f,+0.0f,+0.0f,+1.0f,+2.0f,+3.0f,+2.0f,+1.0f,+0.0f,-2.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+1.0f,+2.0f,+3.0f,+2.0f,+1.0f,-1.0f,-2.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+1.0f,+2.0f,+3.0f,+1.0f,+0.0f,-1.0f,-2.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+1.0f,+2.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.5f,+1.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
};



void MeshField::Init(XMFLOAT3 pos, int horizonCnt, int verticalCnt, float horizonSize, float verticalSize)
{
	m_horizonCnt = horizonCnt;
	m_verticalCnt = verticalCnt;
	m_horizonSize = horizonSize;
	m_verticalSize = verticalSize;
	m_position = pos;
	m_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

	m_isWireFrame = false;

	// 縦横の比率で並べ方を変える場合
	int high, low;
	if (horizonCnt > verticalCnt) {
		// 横が多い場合
		high = horizonCnt;
		low = verticalCnt;
	}
	else {
		// 縦が多い、同数の場合
		high = verticalCnt;
		low = horizonCnt;
	}
	// 頂点数の計算
	int rowVertex = verticalCnt + 1;		// 行の頂点数
	int colVertex = horizonCnt + 1;			// 列の頂点数
	m_vertexCount = rowVertex * colVertex;	// 全体の頂点数
	// インデックス数とプリミティブ数の計算
	m_indexCount = (high + 1) * 2 * low + (low - 1) * 2;
	m_primitiveCount = high * low * 2 + (low - 1) * 4;

	// 開始座標
	float startX = m_position.x - horizonCnt * horizonSize * 0.5f;
	float startZ = m_position.z + verticalCnt * verticalSize * 0.5f;

	m_pVertex = new VERTEX_3DX[m_vertexCount];

	//VERTEX_3DX** m_ppVertex = new VERTEX_3DX*[colVertex];
	//for (int i = 0; i < colVertex; i++) {
	//	m_ppVertex[i] = new VERTEX_3DX[rowVertex];
	//}
	//for (int z = 0; z < rowVertex; z++) {
	//	for (int x = 0; x < colVertex; x++) {
	//		m_ppVertex[x][z].Position = XMFLOAT3(startX + x * horizonSize, sinf(x) * cosf(z), startZ - z * verticalSize);
	//		m_ppVertex[x][z].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	//		m_ppVertex[x][z].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//		m_ppVertex[x][z].TexCoord = XMFLOAT2((float)x, (float)z);
	//	}
	//}
	for (int z = 0, i = 0; z < rowVertex; z++) {
		for (int x = 0; x < colVertex; x++, i++) {
		//	m_pVertex[i].Position = XMFLOAT3(startX + x * horizonSize,x * 0.05f + z * 0.05f, startZ - z * verticalSize);
		//	m_pVertex[i].Position = XMFLOAT3(startX + x * horizonSize, cosf(x) * sinf(z) * 2.0f, startZ - z * verticalSize);
			m_pVertex[i].Position = XMFLOAT3(startX + x * horizonSize, testField[z][x], startZ - z * verticalSize);
			m_pVertex[i].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
			m_pVertex[i].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			m_pVertex[i].TexCoord = XMFLOAT2((float)x, (float)z);
		}
	}

	// 法線ベクトル算出
	for (int x = 1; x < horizonCnt; x++) {
		for (int z = 1; z < verticalCnt; z++) {
			XMVECTOR vx, vz, vn;
			vx = XMLoadFloat3(&m_pVertex[(x + 1) + z * (horizonCnt + 1)].Position) - XMLoadFloat3(&m_pVertex[(x - 1) + z * (horizonCnt + 1)].Position);
			vz = XMLoadFloat3(&m_pVertex[x + (z - 1) *(horizonCnt + 1)].Position) - XMLoadFloat3(&m_pVertex[x + (z+ 1) * (horizonCnt + 1)].Position);
			vn = XMVector3Cross(vz, vx);
		 	vn = XMVector3Normalize(vn);
			XMStoreFloat3(&m_pVertex[x + z * (horizonCnt + 1)].Normal, vn);
		}
	}
	//for (int x = 1; x <= horizonCnt - 1; x++) {
	//	for (int z = 1; z <= verticalCnt - 1; z++) {
	//		XMVECTOR vx, vz, vn;
	//		vx = DirectX::XMLoadFloat3(&m_ppVertex[x+1][z].Position) - DirectX::XMLoadFloat3(&m_ppVertex[x - 1][z].Position);
	//		vz = DirectX::XMLoadFloat3(&m_ppVertex[x][z-1].Position) - DirectX::XMLoadFloat3(&m_ppVertex[x][z + 1].Position);
	//		vn = XMVector3Cross(vz, vx);
	//		vn = XMVector3Normalize(vn);
	//		DirectX::XMStoreFloat3(&m_ppVertex[x][z].Normal, vn);
	//	}
	//}

	{
		// 頂点バッファ生成
		D3D11_BUFFER_DESC bd{};
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;	
		bd.ByteWidth = sizeof(VERTEX_3DX) * m_vertexCount;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;// バッファの種類
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd{};
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = m_pVertex;
//		sd.pSysMem = m_ppVertex;
		Renderer::GetpDevice()->CreateBuffer(&bd, &sd, &m_vertexBuffer);
	}

	{
		// インデックスバッファ生成
		unsigned int* pI = new unsigned int[m_indexCount];
	/*	int i = 0;
		for (int x = 0; x < colVertex; x++) {
			for (int z = 0; z < rowVertex; z++, i++) {
				pI[i] = x * colVertex + z;
				i++;

				pI[i] = (x + 1) * colVertex + z;
				i++;
			}
			if (x == colVertex - 1) break;

			pI[i] = (x + 1) * rowVertex + colVertex;

			i++;

			pI[i] = (x + 1)*rowVertex;
			i++;
		}*/
		
		if (high == horizonCnt) {	// 横に並べる場合
			for (int ZCnt = 0, i = 0, HVCnt = 0; ZCnt < verticalCnt; ZCnt++) {
				for (int XCnt = 0; XCnt < colVertex * 2; XCnt++) {

					if (i % 2 == 0) {
						// 偶数の場合
						pI[i] = (unsigned int)(colVertex + HVCnt);
					}
					else {
						// 奇数の場合
						pI[i] = (unsigned int)HVCnt;
						HVCnt++;
					}

					i++;
				}

				//改行時に縮退ポリゴン用のインデックスを追加する
				if (i < m_indexCount) {
					//始点
					pI[i] = pI[i - 1];
					i++;
					//終点
					pI[i] = (unsigned int)(colVertex + HVCnt);
					i++;
				}
			}
		}
		else if (high == verticalCnt) {	// 縦に並べる場合
			for (int XCnt = 0, i = 0, VVCnt = 0; XCnt < horizonCnt; XCnt++, VVCnt = 0) {
				for (int ZCnt = 0; ZCnt < rowVertex * 2; ZCnt++) {

					if (i % 2 == 0) {
						// 偶数の場合
						pI[i] = (unsigned int)(colVertex * VVCnt + XCnt);
					}
					else {
						// 奇数の場合
						pI[i] = pI[i - 1] + 1;
						VVCnt++;
					}

					i++;
				}

				//改行時に縮退ポリゴン用のインデックスを追加する
				if (i < m_indexCount) {
					//始点
					pI[i] = pI[i - 1];
					i++;

					//終点
					pI[i] = (unsigned int)(XCnt + 1);
					i++;
				}
			}
		}
		
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned int)* m_indexCount;
		bd.BindFlags = D3D10_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = pI;

		Renderer::GetpDevice()->CreateBuffer(&bd, &sd, &m_indexBuffer);

		delete[] pI;
	}


	// テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(
		Renderer::GetpDevice().Get(),
		"asset/texture/grass02.jpg",
		NULL,
		NULL,
		&m_texture,
		NULL
	);
	assert(m_texture);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

}

void MeshField::Uninit()
{
	if (m_pVertex) {
		delete[] m_pVertex;
	}
//	delete[] m_ppVertex;

	m_vertexBuffer->Release();
	m_indexBuffer->Release();
	m_texture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void MeshField::Update()
{
	if (KeyLogger_Trigger(KL_WIRE)) {
		m_isWireFrame = m_isWireFrame == true ? false : true;
	}
}

void MeshField::Draw()
{
	// 入力レイアウト
	Renderer::GetpDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダー設定
	Renderer::GetpDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetpDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// マトリクス

	XMMATRIX scaleX = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	XMMATRIX rotX = XMMatrixRotationRollPitchYaw(m_rotation.x,m_rotation.y,m_rotation.z);
	XMMATRIX transX = XMMatrixTranslation(m_position.x, m_position.y, m_position.z);
	XMMATRIX worldX = scaleX * rotX * transX;
	Renderer::SetWorldMatrixX(&worldX);



	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3DX);
	UINT offset = 0;
	Renderer::GetpDeviceContext()->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// インデックスバッファ設定
	Renderer::GetpDeviceContext()->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	
	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.Emission = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	Renderer::SetMaterial(material);
	

	// テクスチャ設定
	Renderer::GetpDeviceContext()->PSSetShaderResources(0, 1, &m_texture);

	// プリミティブトポロジ設定
	Renderer::GetpDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	if (m_isWireFrame) {
		D3D11_RASTERIZER_DESC rdc{};
		rdc.FillMode = D3D11_FILL_WIREFRAME;
		rdc.CullMode = D3D11_CULL_NONE;
		rdc.FrontCounterClockwise = true;
		Renderer::GetpDevice()->CreateRasterizerState(&rdc, &m_pRasterrizerState);
		Renderer::GetpDeviceContext()->RSSetState(m_pRasterrizerState);
		//Renderer::GetpDeviceContext()->RSSetState(Renderer::GetpRS_FillWireFrame().Get());
	}

	// ポリゴン描画
	Renderer::GetpDeviceContext()->DrawIndexed(m_indexCount, 0, 0);
	if (m_isWireFrame) {
		D3D11_RASTERIZER_DESC rdc{};
		rdc.FillMode = D3D11_FILL_SOLID;
		rdc.CullMode = D3D11_CULL_NONE;
		rdc.FrontCounterClockwise = true;
		Renderer::GetpDevice()->CreateRasterizerState(&rdc, &m_pRasterrizerState);
		Renderer::GetpDeviceContext()->RSSetState(m_pRasterrizerState);
		//Renderer::GetpDeviceContext()->RSSetState(Renderer::GetpRS_FillSolid().Get());
	}
}

float MeshField::GetHeight(XMFLOAT3 position)
{
	int x, z;
	x = position.x / (float)m_horizonSize * 1.0f + m_horizonCnt* 0.5f;
	z = m_verticalCnt - (position.z / (float)m_verticalSize * 1.0f + m_verticalCnt * 0.5f);

	if (x > m_horizonCnt + 1 || z > m_verticalCnt + 1) {
		return position.y - 0.5f;
	}

	XMFLOAT3 pos0, pos1, pos2, pos3,vecc;
	pos0 = m_pVertex[(x + 0) + (z + 0) * (m_horizonCnt + 1)].Position;
	pos1 = m_pVertex[(x + 1) + (z + 0) * (m_horizonCnt + 1)].Position;
	pos2 = m_pVertex[(x + 0) + (z + 1) * (m_horizonCnt + 1)].Position;
	pos3 = m_pVertex[(x + 1) + (z + 1) * (m_horizonCnt + 1)].Position;
	//pos0 = m_vertex[x + 0][z + 0].Position;
	//pos1 = m_vertex[x + 1][z + 0].Position;
	//pos2 = m_vertex[x + 0][z + 1].Position;
	//pos3 = m_vertex[x + 1][z + 1].Position;

	XMVECTOR v12, v1p, c;
	v12 = XMLoadFloat3(&pos2) - XMLoadFloat3(&pos1);
	v1p = XMLoadFloat3(&position) - XMLoadFloat3(&pos1);

	c = XMVector3Cross(v12, v1p);

	XMStoreFloat3(&vecc, c);

	float py;
	XMVECTOR n;

	if (vecc.y > 0.0f) {
		XMVECTOR v10;
		v10 = XMLoadFloat3(&pos0) - XMLoadFloat3(&pos1);
		n = XMVector3Cross(v10, v12);
	}
	else
	{
		XMVECTOR v13;
		v13 = XMLoadFloat3(&pos3) - XMLoadFloat3(&pos1);
		n = XMVector3Cross(v12, v13);
	}

	XMFLOAT3 nn;
	XMStoreFloat3(&nn, n);

	py = -((position.x - pos1.x) * nn.x + (position.z - pos1.z) * nn.z) / nn.y + pos1.y;


	return py;
}
