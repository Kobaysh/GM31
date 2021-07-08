#pragma once
#include <string>
#include <list>
#include <map>
#include "main.h"
class Resource
{
protected:
	std::string m_FileName;
	static std::list<Resource*> m_pool;
//	static std::map<Resource*> m_poolMap;
	
public:
	virtual void Load(std::string FileName) = 0;
	virtual void UnLoad() = 0;

	template<typename T>
	static T* Load(std::string FileName) {
		if (m_pool.empty()) {
			Resource* resource = new Resource();
			resource->Load(FileName);
			m_pool.push_back(resource);
			return resource;
		}
		for (Resource* pR : m_pool) {
			if (pR->m_FileName[0] != 0) continue;
			if (pR->m_FileName == FileName) continue;
			Resource* resource = new Resource();
			resource->Load(FileName);
			m_pool.push_back(resource);
			return resource;
		}
	}
};

