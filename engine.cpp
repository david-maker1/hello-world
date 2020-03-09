#include <iostream>
#include <map>
#include <vector>
#include <string>



class GameObject;
class Component;



class DataStorage{
public:
	bool createObject(GameObject game_object);
	bool deleteObject(std::string object_name);
	GameObject* getObject(std::string object_name);
private:
	std::vector<GameObject> objects;
};



class GameObject{
public:
	std::string name;
	template<typename T>
	void addComponent();
	template<typename T>
	void removeComponent();
	template<typename T>
	T* getComponent();
private:
	std::map<std::string, Component*> components;
};

template<typename T>
void GameObject:: addComponent(){
	if (this->components.find(typeid(T).name()) == this->components.end()){
		T* new_component = new T;
		this->components[typeid(T).name()] = new_component;
	}
}

template<typename T>
void GameObject:: removeComponent(){
	if (this->components.find(typeid(T).name()) != this->components.end()){
		delete this->components[typeid(T).name()];
		this->components.erase(typeid(T).name());
	}
}	
	
template<typename T>
T* GameObject::getComponent(){
	std::map<std::string, Component*>::iterator it;
	for (it = components.begin(); it != components.end(); it++)
		if (it->first == typeid(T).name())
			return static_cast<T*>(it->second);
	return nullptr;
}



class Component{
private:
	std::string name;
public:
	virtual ~Component() = 0;
};


class Collider :public Component{
public:
	~Collider() override{};
};



class Renderer :public Component{
public:
	~Renderer() override{};
};



int main(){
	GameObject obj;
	obj.addComponent<Renderer>();
	obj.removeComponent<Renderer>();
return 0;
}
