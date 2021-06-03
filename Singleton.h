#pragma once
#include <memory>
#include <wrl/client.h>

class Singleton
{
public:

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


	Singleton(const Singleton&){}	// �R�s�[�R���X�g���N�^�֎~
	Singleton& operator=(const Singleton&){}
	Singleton(Singleton&&){}
	Singleton& operator=(Singleton&&){}
};



template <class T>
class SingletonT
{
public:
	static T& singleton() {
		static typename T::singleton_pointer_type
			s_singleton(T::crateInstance());
	
		return getReference(s_singleton);
	}

private:
	typedef std::unique_ptr<T>
		singleton_pointer_type;
	inline static T * crateInstance() { return new T(); }

	inline static T &getReference(const singleton_pointer_type &ptr) { return *ptr; }

protected:
	SingletonT(){}
private:
	SingletonT(const SingletonT&){}
	SingletonT& operator=(const SingletonT&){}
	SingletonT(Singleton&&) {}
	SingletonT& operator=(Singleton&&){}

};