#pragma once

#include <json.hpp>
#include <vector>
#include <string>
#include <functional>
#include <glm/glm.hpp>

namespace math { class Ray; }
class Component;

class Node
{
public:
	std::vector<Component*> components;
	std::vector<Node*> children;
	Node* parent = nullptr;
	Node* root = this;
	std::string name;


	Node(const std::string& name = "", Node* parent = nullptr);
	void addComponent(Component* component);
	void setParent(Node* newParent);
	void removeChild(Node* child);



	void onRename();
	
	template<class T>
	T* getComponent()
	{
		for (auto c : components)
		{
			T* cc = dynamic_cast<T*>(c);
			if (cc)
				return cc;
		}
		return nullptr;
	}
	template<class T>
	std::vector<T*> removeComponent()
	{
		std::vector<T*> ret;
		for(auto it = components.begin(); it != components.end(); )
		{
			T* cc = dynamic_cast<T*>(*it);
			if (cc)
			{
				ret.push_back(cc);
				it = components.erase(it);
			}
			else
				it++;
		}
		return ret;
	}


	void traverse(const std::function<void(Node*)>& callBack);

	//TODO: move this somewhere else?
	std::vector<std::pair<Node*, std::vector<glm::vec3>>> getCollisions(const math::Ray& ray);
};


void to_json(nlohmann::json& j, const Node& n);
void from_json(const nlohmann::json& j, Node& p);