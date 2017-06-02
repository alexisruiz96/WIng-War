#include "entitymesh.h"
#include "shader.h"

EntityMesh::EntityMesh()
{
	texture = NULL;
	mesh = NULL;
	shader = NULL;
}

EntityMesh::~EntityMesh()
{
}


void EntityMesh::render(Camera* camera, Shader* s)
{
	//model.rotate((float)(angle * DEG2RAD), Vector3(0.0f, 1.0f, 0.0f)); //build a rotation matrix

	Matrix44 mvp = model * camera->viewprojection_matrix;
	shader->enable();
	shader->setMatrix44("u_model", model);
	shader->setMatrix44("u_mvp", mvp);
	shader->setTexture("u_texture", texture);
	//if (!camera->testSphereInFrustum(this->mesh->header.center, this->mesh->header.radius))
	mesh->render(GL_TRIANGLES, shader);
	
	
	shader->disable();

	for (int i = 0; i < children.size(); i++) {
		children[i]->render(camera, shader);
	}

}

void EntityMesh::update(float dt)
{
}

void EntityMesh::config(const char * text, const char * ase, const char * vs, const char* fs )
{
	//call to the managers to load it all

	mesh = Mesh::Load(ase);

	texture = Texture::Load(text);
	
	shader = Shader::Load(vs, fs);
	
	
}
