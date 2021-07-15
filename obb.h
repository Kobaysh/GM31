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
	OBB(){
		m_normaDirect[0] = XMFLOAT3(1.0f,0.0f,0.0f);
		m_normaDirect[1] = XMFLOAT3(0.0f,1.0f,0.0f);
		m_normaDirect[2] = XMFLOAT3(0.0f,0.0f,1.0f);
		m_fLength[0] = 1.0f;
		m_fLength[1] = 1.0f;
		m_fLength[2] = 1.0f;
	}
	XMFLOAT3 GetDirect(OBB_Direction elem) { return m_normaDirect[elem]; }
	float GetLen_W(OBB_Direction elem) { return m_fLength[elem]; }
	XMFLOAT3 GetPos_W() { return m_pos; }

	static bool ColOBBs(OBB &obb1, OBB &obb2);
};