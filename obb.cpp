#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "obb.h"

float LenSegOnSeparateAxis(XMFLOAT3 *Sep, XMFLOAT3* e1, XMFLOAT3* e2, XMFLOAT3* e3 = 0);


ID3D11VertexShader*		OBB::m_VertexShader = nullptr;
ID3D11PixelShader*		OBB::m_PixelShader = nullptr;
ID3D11InputLayout*		OBB::m_VertexLayout = nullptr;

bool OBB::ColOBBs(OBB & obb1, OBB & obb2)
{
	// 各方向ベクトルの確保
	XMVECTOR NAe1 = XMLoadFloat3(&obb1.GetDirect(OBB_DX)), Ae1 = NAe1 * obb1.GetLen_W(OBB_DX);
	XMVECTOR NAe2 = XMLoadFloat3(&obb1.GetDirect(OBB_DY)), Ae2 = NAe2 * obb1.GetLen_W(OBB_DY);
	XMVECTOR NAe3 = XMLoadFloat3(&obb1.GetDirect(OBB_DZ)), Ae3 = NAe3 * obb1.GetLen_W(OBB_DZ);
	XMVECTOR NBe1 = XMLoadFloat3(&obb2.GetDirect(OBB_DX)), Be1 = NBe1 * obb2.GetLen_W(OBB_DX);
	XMVECTOR NBe2 = XMLoadFloat3(&obb2.GetDirect(OBB_DY)), Be2 = NBe2 * obb2.GetLen_W(OBB_DY);
	XMVECTOR NBe3 = XMLoadFloat3(&obb2.GetDirect(OBB_DZ)), Be3 = NBe3 * obb2.GetLen_W(OBB_DZ);
	XMVECTOR Interval = XMLoadFloat3(&obb1.GetPos_W()) - XMLoadFloat3(&obb2.GetPos_W());

	

	XMVECTOR vLength, vDot, vCross;

	float rA, rB, L;

	XMFLOAT3 N, e1, e2, e3, fCross;

	// 分離軸Ae1
	vLength = XMVector3Length(Ae1);
	XMStoreFloat(&rA, vLength);
	XMStoreFloat3(&N, NAe1);
	XMStoreFloat3(&e1, Be1);
	XMStoreFloat3(&e2, Be2);
	XMStoreFloat3(&e3, Be3);
	rB = LenSegOnSeparateAxis(&N, &e1, &e2, &e3);
	vDot = XMVector3Dot(Interval, NAe1);
	XMStoreFloat(&L, vDot);
	L = fabsf(L);
	if (L > rA + rB) return false;

	// 分離軸Ae2
	vLength = XMVector3Length(Ae2);
	XMStoreFloat(&rA, vLength);
	XMStoreFloat3(&N, NAe2);
	XMStoreFloat3(&e1, Be1);
	XMStoreFloat3(&e2, Be2);
	XMStoreFloat3(&e3, Be3);
	rB = LenSegOnSeparateAxis(&N, &e1, &e2, &e3);
	vDot = XMVector3Dot(Interval, NAe2);
	XMStoreFloat(&L, vDot);
	L = fabsf(L);
	if (L > rA + rB) return false;

	
	// 分離軸Ae3
	vLength = XMVector3Length(Ae3);
	XMStoreFloat(&rA, vLength);
	XMStoreFloat3(&N, NAe3);
	XMStoreFloat3(&e1, Be1);
	XMStoreFloat3(&e2, Be2);
	XMStoreFloat3(&e3, Be3);
	rB = LenSegOnSeparateAxis(&N, &e1, &e2, &e3);
	vDot = XMVector3Dot(Interval, NAe3);
	XMStoreFloat(&L, vDot);
	L = fabsf(L);
	if (L > rA + rB) return false;


	// 分離軸Be1
	vLength = XMVector3Length(Be1);
	XMStoreFloat(&rB, vLength);
	XMStoreFloat3(&N, NBe1);
	XMStoreFloat3(&e1, Ae1);
	XMStoreFloat3(&e2, Ae2);
	XMStoreFloat3(&e3, Ae3);
	rA = LenSegOnSeparateAxis(&N, &e1, &e2, &e3);
	vDot = XMVector3Dot(Interval, NBe1);
	XMStoreFloat(&L, vDot);
	L = fabsf(L);
	if (L > rA + rB) return false;

	// 分離軸Be2
	vLength = XMVector3Length(Be2);
	XMStoreFloat(&rB, vLength);
	XMStoreFloat3(&N, NBe2);
	XMStoreFloat3(&e1, Ae1);
	XMStoreFloat3(&e2, Ae2);
	XMStoreFloat3(&e3, Ae3);
	rA = LenSegOnSeparateAxis(&N, &e1, &e2, &e3);
	vDot = XMVector3Dot(Interval, NBe2);
	XMStoreFloat(&L, vDot);
	L = fabsf(L);
	if (L > rA + rB) return false;


	// 分離軸Be3
	vLength = XMVector3Length(Be3);
	XMStoreFloat(&rB, vLength);
	XMStoreFloat3(&N, NBe3);
	XMStoreFloat3(&e1, Ae1);
	XMStoreFloat3(&e2, Ae2);
	XMStoreFloat3(&e3, Ae3);
	rA = LenSegOnSeparateAxis(&N, &e1, &e2, &e3);
	vDot = XMVector3Dot(Interval, NBe3);
	XMStoreFloat(&L, vDot);
	L = fabsf(L);
	if (L > rA + rB) return false;


	// 分離軸C11
	XMFLOAT3 ee1, ee2, ee3, ee4;
	vCross = XMVector3Cross(NAe1, NBe1);
	XMStoreFloat3(&fCross, vCross);
	XMStoreFloat3(&ee1, Ae2);
	XMStoreFloat3(&ee2, Ae3);
	XMStoreFloat3(&ee3, Be2);
	XMStoreFloat3(&ee4, Be3);
	rA = LenSegOnSeparateAxis(&fCross, &ee1, &ee2);
	rB = LenSegOnSeparateAxis(&fCross, &ee3, &ee4);
	vDot = XMVector3Dot(Interval, vCross);
	XMStoreFloat(&L, vDot);
	L = fabsf(L);
	if (L > rA + rB)
		return false;

	// 分離軸 : C12
	vCross = XMVector3Cross(NAe1, NBe1);
	XMStoreFloat3(&fCross, vCross);
	XMStoreFloat3(&ee1, Ae2);
	XMStoreFloat3(&ee2, Ae3);
	XMStoreFloat3(&ee3, Be1);
	XMStoreFloat3(&ee4, Be3);
	rA = LenSegOnSeparateAxis(&fCross, &ee1, &ee2);
	rB = LenSegOnSeparateAxis(&fCross, &ee3, &ee4);
	vDot = XMVector3Dot(Interval, vCross);
	XMStoreFloat(&L, vDot);
	L = fabsf(L);
	if (L > rA + rB)
		return false;

	// 分離軸 : C13
	vCross = XMVector3Cross(NAe1, NBe1);
	XMStoreFloat3(&fCross, vCross);
	XMStoreFloat3(&ee1, Ae2);
	XMStoreFloat3(&ee2, Ae3);
	XMStoreFloat3(&ee3, Be1);
	XMStoreFloat3(&ee4, Be2);
	rA = LenSegOnSeparateAxis(&fCross, &ee1, &ee2);
	rB = LenSegOnSeparateAxis(&fCross, &ee3, &ee4);
	vDot = XMVector3Dot(Interval, vCross);
	XMStoreFloat(&L, vDot);
	L = fabsf(L);
	if (L > rA + rB)
		return false;

	// 分離軸 : C21
	vCross = XMVector3Cross(NAe1, NBe1);
	XMStoreFloat3(&fCross, vCross);
	XMStoreFloat3(&ee1, Ae1);
	XMStoreFloat3(&ee2, Ae3);
	XMStoreFloat3(&ee3, Be2);
	XMStoreFloat3(&ee4, Be3);
	rA = LenSegOnSeparateAxis(&fCross, &ee1, &ee2);
	rB = LenSegOnSeparateAxis(&fCross, &ee3, &ee4);
	vDot = XMVector3Dot(Interval, vCross);
	XMStoreFloat(&L, vDot);
	L = fabsf(L);
	if (L > rA + rB)
		return false;

	// 分離軸 : C22
	vCross = XMVector3Cross(NAe1, NBe1);
	XMStoreFloat3(&fCross, vCross);
	XMStoreFloat3(&ee1, Ae1);
	XMStoreFloat3(&ee2, Ae3);
	XMStoreFloat3(&ee3, Be1);
	XMStoreFloat3(&ee4, Be3);
	rA = LenSegOnSeparateAxis(&fCross, &ee1, &ee2);
	rB = LenSegOnSeparateAxis(&fCross, &ee3, &ee4);
	vDot = XMVector3Dot(Interval, vCross);
	XMStoreFloat(&L, vDot);
	L = fabsf(L);
	if (L > rA + rB)
		return false;

	// 分離軸 : C23
	vCross = XMVector3Cross(NAe1, NBe1);
	XMStoreFloat3(&fCross, vCross);
	XMStoreFloat3(&ee1, Ae1);
	XMStoreFloat3(&ee2, Ae3);
	XMStoreFloat3(&ee3, Be1);
	XMStoreFloat3(&ee4, Be2);
	rA = LenSegOnSeparateAxis(&fCross, &ee1, &ee2);
	rB = LenSegOnSeparateAxis(&fCross, &ee3, &ee4);
	vDot = XMVector3Dot(Interval, vCross);
	XMStoreFloat(&L, vDot);
	L = fabsf(L);
	if (L > rA + rB)
		return false;

	// 分離軸 : C31
	vCross = XMVector3Cross(NAe1, NBe1);
	XMStoreFloat3(&fCross, vCross);
	XMStoreFloat3(&ee1, Ae1);
	XMStoreFloat3(&ee2, Ae2);
	XMStoreFloat3(&ee3, Be2);
	XMStoreFloat3(&ee4, Be3);
	rA = LenSegOnSeparateAxis(&fCross, &ee1, &ee2);
	rB = LenSegOnSeparateAxis(&fCross, &ee3, &ee4);
	vDot = XMVector3Dot(Interval, vCross);
	XMStoreFloat(&L, vDot);
	L = fabsf(L);
	if (L > rA + rB)
		return false;

	// 分離軸 : C32
	vCross = XMVector3Cross(NAe1, NBe1);
	XMStoreFloat3(&fCross, vCross);
	XMStoreFloat3(&ee1, Ae1);
	XMStoreFloat3(&ee2, Ae2);
	XMStoreFloat3(&ee3, Be1);
	XMStoreFloat3(&ee4, Be3);
	rA = LenSegOnSeparateAxis(&fCross, &ee1, &ee2);
	rB = LenSegOnSeparateAxis(&fCross, &ee3, &ee4);
	vDot = XMVector3Dot(Interval, vCross);
	XMStoreFloat(&L, vDot);
	L = fabsf(L);
	if (L > rA + rB)
		return false;

	// 分離軸 : C33
	vCross = XMVector3Cross(NAe1, NBe1);
	XMStoreFloat3(&fCross, vCross);
	XMStoreFloat3(&ee1, Ae1);
	XMStoreFloat3(&ee2, Ae2);
	XMStoreFloat3(&ee3, Be1);
	XMStoreFloat3(&ee4, Be2);
	rA = LenSegOnSeparateAxis(&fCross, &ee1, &ee2);
	rB = LenSegOnSeparateAxis(&fCross, &ee3, &ee4);
	vDot = XMVector3Dot(Interval, vCross);
	XMStoreFloat(&L, vDot);
	L = fabsf(L);
	if (L > rA + rB)
		return false;
	

	return true;
}

void OBB::Init()
{
	XMVECTOR vPosition = XMLoadFloat3(&m_Position);
	XMVECTOR vSizeX = XMLoadFloat3(&XMFLOAT3(m_fLength[0] * 0.5f, 0.0f, 0.0f));
	XMVECTOR vSizeY = XMLoadFloat3(&XMFLOAT3(0.0f, m_fLength[1] * 0.5f, 0.0f));
	XMVECTOR vSizeZ = XMLoadFloat3(&XMFLOAT3(0.0f, 0.0f, m_fLength[2] * 0.5f));

	VERTEX_3DX vertex[8];
	XMStoreFloat3(&vertex[0].Position, vPosition - vSizeX + vSizeY - vSizeZ);
	XMStoreFloat3(&vertex[1].Position, vPosition + vSizeX + vSizeY - vSizeZ);
	XMStoreFloat3(&vertex[2].Position, vPosition + vSizeX + vSizeY + vSizeZ);
	XMStoreFloat3(&vertex[3].Position, vPosition - vSizeX + vSizeY + vSizeZ);
	XMStoreFloat3(&vertex[4].Position, vPosition - vSizeX - vSizeY - vSizeZ);
	XMStoreFloat3(&vertex[5].Position, vPosition + vSizeX - vSizeY - vSizeZ);
	XMStoreFloat3(&vertex[6].Position, vPosition + vSizeX - vSizeY + vSizeZ);
	XMStoreFloat3(&vertex[7].Position, vPosition - vSizeX - vSizeY + vSizeZ);

	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd{};

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3DX) * 8;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;// バッファの種類
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;
	Renderer::GetpDevice()->CreateBuffer(&bd, &sd, &m_vertexBuffer);


	UWORD index[36] = {
		0,1,4,
		1,4,5,
		1,2,5,
		2,5,6,
		2,3,6,
		3,6,7,
		3,0,7,
		0,7,4,
		3,2,0,
		2,0,1,
		4,5,7,
		5,7,6
	};

	// インデックスバッファ生成
	D3D11_BUFFER_DESC ibd{};
	ibd.ByteWidth = sizeof(UWORD) * 36;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA isd{};
	isd.pSysMem = index;
	isd.SysMemPitch = 0;
	isd.SysMemSlicePitch = 0;
	Renderer::GetpDevice()->CreateBuffer(&ibd, &isd, &m_Indexbuffer);

	D3D11_RASTERIZER_DESC rdc{};
	rdc.FillMode = D3D11_FILL_WIREFRAME;
	rdc.CullMode = D3D11_CULL_NONE;
	rdc.FrontCounterClockwise = true;
	Renderer::GetpDevice()->CreateRasterizerState(&rdc, &m_pRasterrizerState);
}

void OBB::Uninit()
{
}

void OBB::Update()
{
}

void OBB::Draw()
{
	Renderer::GetpDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダー設定
	Renderer::GetpDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetpDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// マトリクス設定

	XMMATRIX scaleX = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	XMMATRIX rotX = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	XMMATRIX transX = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	XMMATRIX worldX = scaleX * rotX * transX;
	Renderer::SetWorldMatrixX(&worldX);



	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3DX);
	UINT offset = 0;
	Renderer::GetpDeviceContext()->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// インデックスバッファ設定
	Renderer::GetpDeviceContext()->IASetIndexBuffer(m_Indexbuffer, DXGI_FORMAT_R16_UINT, 0);

	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.Emission = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	Renderer::SetMaterial(material);
	D3D11_RASTERIZER_DESC rdc{};
	rdc.FillMode = D3D11_FILL_WIREFRAME;
	rdc.CullMode = D3D11_CULL_NONE;
	rdc.FrontCounterClockwise = true;
	Renderer::GetpDevice()->CreateRasterizerState(&rdc, &m_pRasterrizerState);

	// ラスタライザ設定
	Renderer::GetpDeviceContext()->RSSetState(m_pRasterrizerState);

	// テクスチャ設定

//	Renderer::GetpDeviceContext()->PSSetShaderResources(0, 1, nullptr);


	// プリミティブトポロジ設定
	Renderer::GetpDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// ポリゴン描画
	Renderer::GetpDeviceContext()->DrawIndexed(36, 0, 0);


	rdc.FillMode = D3D11_FILL_SOLID;
	rdc.CullMode = D3D11_CULL_NONE;
	rdc.FrontCounterClockwise = true;
	Renderer::GetpDevice()->CreateRasterizerState(&rdc, &m_pRasterrizerState);
	// ラスタライザ設定
	Renderer::GetpDeviceContext()->RSSetState(m_pRasterrizerState);
	
}



float LenSegOnSeparateAxis(XMFLOAT3 *Sep, XMFLOAT3* e1, XMFLOAT3* e2, XMFLOAT3* e3) 
{
	XMVECTOR vDot;
	float fDot;
	float r1;
	vDot = XMVector3Dot(XMLoadFloat3(Sep), XMLoadFloat3(e1));
	XMStoreFloat(&fDot, vDot);
	r1 = fabsf(fDot);
	float r2;
	vDot = XMVector3Dot(XMLoadFloat3(Sep), XMLoadFloat3(e2));
	XMStoreFloat(&fDot, vDot);
	r2 = fabsf(fDot);

	float r3;
	if (e3) {
		vDot = XMVector3Dot(XMLoadFloat3(Sep), XMLoadFloat3(e3));
		XMStoreFloat(&fDot, vDot);
	}
	r3 = e3 ? fabsf(fDot) : 0;

	return (r1 + r2 + r3);
}