#pragma once

class Trunk
{
public:
	Trunk();
	~Trunk();

	int GetNowTrunk() { return m_nowTrunk; }
	int GetMaxTrunk() { return m_maxTrunk; }

	void setNowTrunk(int trunk) { m_nowTrunk = trunk; }
	void setMaxTrunk(int maxTrunk) { m_maxTrunk = maxTrunk; }

private:
	int m_nowTrunk;					// �̊�
	int m_maxTrunk;					// Max�̊�
};

Trunk::Trunk()
{
}

Trunk::~Trunk()
{
}