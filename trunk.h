#pragma once

class Trunk
{
public:
	Trunk(){}
	~Trunk(){}

	int GetNowTrunk() { return m_nowTrunk; }
	int GetMaxTrunk() { return m_maxTrunk; }

	void SetNowTrunk(int trunk) { m_nowTrunk = trunk; }
	void SetMaxTrunk(int maxTrunk) { m_maxTrunk = maxTrunk; }

	void ChangeNowTrunk(int changeValue){
		if(m_nowTrunk + changeValue > m_maxTrunk){
			m_nowTrunk = m_maxTrunk;
		}
		else if(m_nowTrunk + changeValue < 0)
		{
			m_nowTrunk = 0;
		}
		else{
			m_nowTrunk += changeValue;
		}
	}
private:
	int m_nowTrunk;					// ‘ÌŠ²
	int m_maxTrunk;					// Max‘ÌŠ²
};