#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>

namespace util
{
	template<class T>
	class ResourceManager
	{
		static inline std::vector<T*> resources;
		static inline std::map<std::string, T*> resmap;
	public:
		template<class R = T>
		static R* load()
		{
			for (auto r : resources)
			{
				R* rr = dynamic_cast<R*>(r);
				if (rr)
					return rr;
			}
			R* rr = new R();
			resources.push_back(rr);
			return rr;
		}
		template<class R = T>
		static R* load(const std::string &str)
		{
			auto it = resmap.find(str);
			if(it != resmap.end())
				return dynamic_cast<R*>(it->second);
			R* r = new R(str);
			resmap[str] = r;
			return r;
		}
		static void unload(T*)
		{
			std::cout << "Unloading resource, but not really :P this is a memory leak, and will be fixed later" << std::endl;
		}
	};

//	template<class T>
//	std::vector<T*> ResourceManager<T>::resources;
}

