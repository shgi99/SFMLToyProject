#pragma once
template <typename T>
class ResourceMgr : public Singleton<ResourceMgr<T>>
{
	friend Singleton<ResourceMgr<T>>;
protected:
	std::unordered_map<std::string, T*> resources;

	ResourceMgr() = default;
	~ResourceMgr() {
		UnloadAll();
	}
	ResourceMgr(const ResourceMgr&) = delete;
	ResourceMgr& operator=(const ResourceMgr&) = delete;

public:
	static T Empty;
	void UnloadAll()
	{
		for (const auto& pair : resources)
		{
			delete pair.second;
		}
		resources.clear();
	}

	bool Load(const std::string& id)
	{
		if (resources.find(id) != resources.end())
		{
			std::cout << "Resource already loaded: " << id << std::endl;
			return false;  // 이미 로드된 경우
		}

		T* resource = new T();
		bool success = resource->loadFromFile(id);  // 파일에서 로드

		if (success)
		{
			std::cout << "Successfully loaded resource: " << id << std::endl;
			resources.insert({ id, resource });
		}
		else
		{
			std::cout << "Failed to load resource: " << id << std::endl;
			delete resource;
		}

		return success;
	}

	bool Unload(const std::string& id)
	{
		auto it = resources.find(id);

		if (it == resources.end())
		{
			return false;
		}
		delete it->second;
		resources.erase(it);
		return true;
	}

	T& Get(const std::string& id)
	{
		auto it = resources.find(id);
		if (it == resources.end())
		{
			std::cout << "Resource not found: " << id << std::endl;
			return Empty;
		}
		return *(it->second);
	}
};

template<typename T>
T ResourceMgr<T>::Empty;

#define TEXTURE_MGR ResourceMgr<sf::Texture>::Instance()
#define FONT_MGR ResourceMgr<sf::Font>::Instance()