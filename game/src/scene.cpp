#include "scene.h"

Scene* Scene::instance = NULL;

Scene::Scene()
{
	instance = this;
	plane = NULL;
	suelo = NULL;
	cielo = NULL;
	bomber = NULL;
	p38 = NULL;
	p38a = NULL;
	water = NULL;
	cannon = NULL;
	root = new Entity();
}


Scene::~Scene()
{
}

void Scene::createScene() {

	plane = new AirPlane();
	//plane->setDynamic();
	plane->config("data/meshes/spitfire/spitfire_color_spec.tga", "data/meshes/spitfire/spitfire.ASE", "data/shaders/texture.vs", "data/shaders/simple.fs");
	plane->model.setTranslation(0, 750, 130);
	plane->setPosition(plane->model * Vector3(0,0,0));
	plane->setLastPosition(plane->getPosition());
	root->addChild(plane);

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			suelo = new EntityCollider();
			//bool terrain = rand() % 2 == 0;

			suelo->setStatic();
			suelo->config("data/meshes/island/island_color.tga", "data/meshes/island/island.ASE", "data/shaders/texture.vs", "data/shaders/simple.fs");
			suelo->model.setTranslation(i * 14000, 0, j * 14000);
			root->addChild(suelo);
		}
	}


		
	cielo = new EntityMesh();
	cielo->config("data/meshes/cielo.tga", "data/meshes/cielo.ASE", "data/shaders/texture.vs", "data/shaders/simple.fs");
	//root->addChild(cielo);
	int e = 0;
	for (int i = 1; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			bomber = new AirPlane(true);
			bomber->setDynamic();
			bomber->config("data/meshes/bomber_axis/bomber_axis.tga", "data/meshes/bomber_axis/bomber_axis.ASE", "data/shaders/texture.vs", "data/shaders/simple.fs");
			bomber->model.setTranslation(0, i*750, j*300);
			bomber->setPosition(bomber->model * Vector3(0, 0, 0));
			bomber->setLastPosition(bomber->getPosition());
			root->addChild(bomber);

			p38 = new AirPlane(true);
			p38->setDynamic();
			p38->config("data/meshes/p38/p38.tga", "data/meshes/p38/p38.ASE", "data/shaders/texture.vs", "data/shaders/simple.fs");
			p38->model.setTranslation(40, i*750, j*290);
			p38->setPosition(p38->model * Vector3(0, 0, 0));
			p38->setLastPosition(p38->getPosition());
			root->addChild(p38);

			p38a = new AirPlane(true);
			p38a->setDynamic();
			p38a->config("data/meshes/p38/p38_axis.tga", "data/meshes/p38/p38.ASE", "data/shaders/texture.vs", "data/shaders/simple.fs");
			p38a->model.setTranslation(-40, i*750,j*290);
			p38a->setPosition(p38a->model * Vector3(0, 0, 0));
			p38a->setLastPosition(p38a->getPosition());
			root->addChild(p38a);
		}
	}


	

	/*cannon->config("data/meshes/antiaircraft/antiaircraft_cannon.tga", "data/meshes/antiaircraft/antiaircraft_cannon.ASE", "data/shaders/texture.vs", "data/shaders/simple.fs");
	cannon->model.setScale(15.0f, 15.0f, 15.0f);
	cannon->model.traslate(0, 1010, 1300);
	plane->addChild(cannon);*/
	
	water = new EntityMesh();
	water->config("data/meshes/island/agua.tga", "data/meshes/island/agua.ASE", "data/shaders/texture.vs", "data/shaders/texture.fs");
	water->model.traslate(0, 0, 0);
	root->addChild(water);



	


	
}
