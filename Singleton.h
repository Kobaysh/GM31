#pragma once

//template<class T>
class Singleton
{
public:
	/*static inline T& GetInstance() {
		static T instance;
		return instance;
	}*/

	static Singleton* GetInstance() {
		return m_pInstance;
	}

	static void Create() {
		if (!m_pInstance) {
			m_pInstance = new Singleton;
		}
	}

	static void Destory() {
		delete m_pInstance;
		m_pInstance = nullptr;
	}


protected:
	static Singleton* m_pInstance;
	Singleton(){}	// �O���ł̃C���X�^���X�쐬�͋֎~
	virtual ~Singleton(){}


private:
	void operator=(const Singleton& obj){}	// ������Z�q�֎~
	Singleton(const Singleton& obj){}	// �R�s�[�R���X�g���N�^�֎~
};

