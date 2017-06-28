#include "scene.h"
#include <math.h>

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
	barco = NULL;
	aircar = NULL;
	bomber1 = NULL;
	bomber2 = NULL;
	root = new Entity();
}


Scene::~Scene()
{
}

void Scene::createScene() {

	plane = new AirPlane();
	plane->setDynamic();
	plane->setName("ourplane");
	plane->config("data/meshes/spitfire/spitfire_color_spec.tga", "data/meshes/spitfire/spitfire.ASE", "data/shaders/texture.vs", "data/shaders/simple.fs");
	plane->model.setTranslation(-2214, 200, 7000);
	plane->model.rotateLocal(M_PI ,  Vector3(0.f,1.f,0.f));
	plane->setPosition(plane->model * Vector3(0,0,0));
	plane->setLastPosition(plane->getPosition());
	plane->setHp(100);
	plane->setScore(0);
	root->addChild(plane);

	//for (int i = -1; i <= 1; i++) {
		//for (int j = -1; j <= 1; j++) {
			suelo = new EntityCollider();
			//bool terrain = rand() % 2 == 0;
			suelo->setName("floor");
			suelo->setStatic();
			suelo->config("data/meshes/island/island_color.tga", "data/meshes/island/island.ASE", "data/shaders/texture.vs", "data/shaders/simple.fs");
			suelo->model.setTranslation( 0, 0, 0);
			root->addChild(suelo);
		//}
	//}


		
	cielo = new EntityMesh();
	cielo->setName("cielo");
	cielo->config("data/meshes/cielo.tga", "data/meshes/cielo.ASE", "data/shaders/texture.vs", "data/shaders/simple.fs");
	//root->addChild(cielo);

	for (int i = -2; i < 3; i++) {
		for (int j = -2; j < 2; j++) {
			bomber = new AirPlane(true);
			bomber->setDynamic();
			bomber->config("data/meshes/bomber_axis/bomber_axis.tga", "data/meshes/bomber_axis/bomber_axis.ASE", "data/shaders/texture.vs", "data/shaders/simple.fs");
			bomber->model.setTranslation(i*2200, 1000, j*750);
			bomber->setHp(50);
			bomber->setScore(50);
			bomber->setPosition(bomber->model * Vector3(0, 0, 0));
			bomber->setLastPosition(bomber->getPosition());
			root->addChild(bomber);

			p38 = new AirPlane(true);
			p38->setDynamic();
			p38->config("data/meshes/p38/p38.tga", "data/meshes/p38/p38.ASE", "data/shaders/texture.vs", "data/shaders/simple.fs");
			p38->model.setTranslation(i*2240, 750, j*740);
			p38->setPosition(p38->model * Vector3(0, 0, 0));
			p38->setLastPosition(p38->getPosition());
			p38->setHp(25);
			p38->setScore(25);
			root->addChild(p38);

			p38a = new AirPlane(true);
			p38a->setDynamic();
			p38a->config("data/meshes/p38/p38_axis.tga", "data/meshes/p38/p38.ASE", "data/shaders/texture.vs", "data/shaders/simple.fs");
			p38a->model.setTranslation(i*2160, 1250,j*740);
			p38a->setPosition(p38a->model * Vector3(0, 0, 0));
			p38a->setLastPosition(p38a->getPosition());
			p38a->setHp(25);
			p38a->setScore(25);
			root->addChild(p38a);
		}
	}


	

	/*cannon->config("data/meshes/antiaircraft/antiaircraft_cannon.tga", "data/meshes/antiaircraft/antiaircraft_cannon.ASE", "data/shaders/texture.vs", "data/shaders/simple.fs");
	cannon->model.setScale(15.0f, 15.0f, 15.0f);
	cannon->model.traslate(0, 1010, 1300);
	plane->addChild(cannon);*/
	
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			water = new EntityMesh();
			water->config("data/meshes/island/agua.tga", "data/meshes/island/agua.ASE", "data/shaders/water.vs", "data/shaders/water.fs");
			water->model.traslate(i*10000, -15,j *10000);
			root->addChild(water);
		}
	}

	barco = new Boat();
	barco->setDynamic();
	barco->setName("BarcoEnemigo");
	barco->setHp(400);
	barco->config("data/meshes/barcos/barco.tga", "data/meshes/barcos/barco.ASE", "data/shaders/texture.vs", "data/shaders/simple.fs");
	barco->model.setTranslation(-1094, -15, -2887);
	barco->setPosition(barco->model * Vector3(0, 0, 0));
	barco->setLastPosition(barco->getPosition());
	root->addChild(barco);
	

	aircar = new AircraftCarrier();
	aircar->setDynamic();
	aircar->setName("BarcoAliado");
	aircar->setHp(5000);
	aircar->config("data/meshes/barcos/aircarrier_metal.tga", "data/meshes/barcos/aircarrier.ASE", "data/shaders/texture.vs", "data/shaders/simple.fs");
	aircar->model.setTranslation(-2214, -15, 5420);
	aircar->model.rotateLocal(M_PI, Vector3(0.f, 1.f, 0.f));
	aircar->setPosition(barco->model * Vector3(0, 0, 0));
	aircar->setLastPosition(barco->getPosition());
	root->addChild(aircar);

	bomber1 = new AirPlane(true);
	bomber1->setDynamic();
	bomber1->isFB = true;
	bomber1->config("data/meshes/bomber_axis/bomber_axis.tga", "data/meshes/bomber_axis/bomber_axis.ASE", "data/shaders/texture.vs", "data/shaders/simple.fs");
	bomber1->model.setTranslation(-1074, 150, -2913);
	bomber1->setHp(100);
	bomber1->setScore(200);
	bomber1->setPosition(bomber1->model * Vector3(0, 0, 0));
	bomber1->setLastPosition(bomber1->getPosition());
	root->addChild(bomber1);

	bomber2 = new AirPlane(true);
	bomber2->setDynamic();
	bomber2->isFB = true;
	bomber2->config("data/meshes/bomber_axis/bomber_axis.tga", "data/meshes/bomber_axis/bomber_axis.ASE", "data/shaders/texture.vs", "data/shaders/simple.fs");
	bomber2->model.setTranslation(-1114, 150, -2850);
	bomber2->setHp(100);
	bomber1->setScore(200);
	bomber2->setPosition(bomber2->model * Vector3(0, 0, 0));
	bomber2->setLastPosition(bomber2->getPosition());
	root->addChild(bomber2);

	
}
