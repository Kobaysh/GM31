#pragma once
#include "main.h"

class OBB
{
protected:
	XMFLOAT3 m_pos;				// 位置
	XMFLOAT3 m_normaDirect[3];	// 方向ベクトル
	float m_fLength[3];			// 各軸方向の長さ

public:
	enum OBB_Direction {
		OBB_DX,
		OBB_DY,
		OBB_DZ,
	};
	XMFLOAT3 GetDirect(OBB_Direction elem) { return m_normaDirect[elem]; }
	float GetLen_W(OBB_Direction elem) { return m_fLength[elem]; }
	XMFLOAT3 GetPos_W() { return m_pos; }

	static bool ColOBBs(OBB &obb1, OBB &obb2);
};