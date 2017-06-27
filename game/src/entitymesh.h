#ifndef ENTITYMESH_H
#define ENTITYMESH_H

#include "entity.h"
#include "mesh.h"
#include "texture.h"
#include "camera.h"

class EntityMesh : public Entity
{
public:
	EntityMesh();
	virtual ~EntityMesh();

	Mesh* mesh;
	Texture* texture;
	Vector3 color;
	Shader* shader;

	void render();
	void update(float dt);
	void config(const char * text, const char * ase, const char * vs, const char* fs);
};

#endif