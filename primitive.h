#pragma once
#include "main.h"
#include <math.h>

#define _OX_EPSILION_ 0.00001f // 浮動小数点誤差


typedef XMFLOAT3 Point;

struct Line {
	Point m_p;
	XMFLOAT3 m_v;
	Line(){}
	Line(const Point &p, const XMFLOAT3 &v):m_p(p),m_v(v){}
	Line(const Point &p, const Point &p1, const Point &p2){
		m_p = p;
		XMStoreFloat3(&m_v, XMLoadFloat3(&p2) - XMLoadFloat3(&p1));
	}
	XMFLOAT3 GetPoint(float t)const {
		XMFLOAT3 newV;
		XMStoreFloat3(&newV, XMLoadFloat3(&m_v) * t + XMLoadFloat3(&m_p));
		return newV;
	}
};

struct Segment : public Line
{
	Segment(){}
	Segment(const Point &p, const XMFLOAT3 &v):Line(p, v){}
	Segment(const Point &p, const Point &p1, const Point &p2):Line(p, p1, p2){}

	XMFLOAT3 GetEndPoint() const {
		XMFLOAT3 newV;
		XMStoreFloat3(&newV, (XMLoadFloat3(&m_p) + XMLoadFloat3(&m_v)));
		return newV;
	}
};


struct Sphere {
	Point m_p;
	float m_rad;	// 半径
	Sphere():m_p(0.0f,0.0f,0.0f), m_rad(0.5f){}
	Sphere(const Point &p, float r):m_p(p), m_rad(r){}
	~Sphere(){}
};

struct Capsule
{
	Segment m_s;	// 線分
	float m_rad;	// 半径
	Capsule() : m_rad(0.5f){}
	Capsule(const Segment &s, float r):m_s(s), m_rad(r){}
	Capsule(const Point &p1, const Point&p2, float r) : m_s(p1, p1, p2){}
	~Capsule(){}
};

struct AABB
{
	Point m_p;	// 中心点
	XMFLOAT3 m_hl;	// 各軸の辺の長さの半分
	AABB() {}
	AABB(const Point &p, const XMFLOAT3 &hl): m_p(p), m_hl(hl){}
	float GetLenX()const { return m_hl.x * 2.0f; }
	float GetLenX()const { return m_hl.y * 2.0f; }
	float GetLenX()const { return m_hl.z * 2.0f; }
	float GetLen(int i)const { return *((&m_hl.x) + i) * 2.0f; }
};

