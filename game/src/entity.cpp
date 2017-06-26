#include "entity.h"
#include "framework.h"
#include "utils.h"
#include "camera.h"
#include "shader.h"
#include "scene.h"

std::vector<Entity*> Entity::toDestroy;

Entity::Entity()
{
	parent = NULL;
}

Entity::~Entity()
{
}

void Entity::render(Shader* shader)
{
	for (int i = 0; i < children.size(); i++) {
		children[i]->render(shader);
	}

}

void Entity::update(float elapsed_time)
{
	if (!this->children.empty()) {
		for (int i = 0; i < children.size(); i++)
			children[i]->update(elapsed_time);
	}
}

std::string Entity::getName() {
	return name;
}

void Entity::setName(std::string name) {
	this->name = name;
}
Vector3 Entity::getPosition()
{
	return Vector3();
}

Matrix44 Entity::getGlobalMatrix()
{
	if (parent)
		return model*parent->getGlobalMatrix();
	return model;
}

void Entity::addChild(Entity* ent)
{
	ent->parent = this;
	children.push_back(ent);
}

void Entity::removeChild(Entity* ent)
{
	auto it = std::find(children.begin(), children.end(), ent);
	if (it == children.end())
		return;
	children.erase(it);

	ent->parent = NULL;

	//para actualizar la posicion de la entity cuando se quita como hijo
	ent->model = ent->model * getGlobalMatrix();

}

void Entity::deleteEntity()
{
	//Scene::instance->root->addChild(Scene::instance->cielo);
	Entity* tod;
	for (int i = 0; i < toDestroy.size(); i++) {
		tod = toDestroy[i];
	}
	if (tod->parent != NULL) {
		tod->parent->removeChild(tod);
	}

	if (!tod->children.empty()) {
		for (int j = 0; j < tod->children.size(); j++)
			delete(tod->children[j]);
	}
	delete(tod);

	toDestroy.clear();

}