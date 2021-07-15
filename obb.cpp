#include "obb.h"

float LenSegOnSeparateAxis(XMFLOAT3 *Sep, XMFLOAT3* e1, XMFLOAT3* e2, XMFLOAT3* e3);


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
	L = fabs(L);
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
	XMStoreFloat(&L, vDot);
	L = fabs(L);
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
	XMStoreFloat(&L, vDot);
	L = fabs(L);
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
	XMStoreFloat(&L, vDot);
	L = fabs(L);
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
	XMStoreFloat(&L, vDot);
	L = fabs(L);
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
	L = fabs(L);
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
	XMStoreFloat(&L, vDot);
	L = fabs(L);
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
	XMStoreFloat(&L, vDot);
	L = fabs(L);
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
	XMStoreFloat(&L, vDot);
	L = fabs(L);
	if (L > rA + rB)
		return false;
	

	return true;
}


float LenSegOnSeparateAxis(XMFLOAT3 *Sep, XMFLOAT3* e1, XMFLOAT3* e2, XMFLOAT3* e3 = 0) 
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
	vDot = XMVector3Dot(XMLoadFloat3(Sep), XMLoadFloat3(e3));
	XMStoreFloat(&fDot, vDot);
	r3 = e3 ? fabsf(fDot) : 0;

	return (r1 + r2 + r3);
}