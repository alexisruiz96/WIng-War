#include "bulletmanager.h"


BulletManager* BulletManager::instance = NULL;


BulletManager::BulletManager()
{
	for (int i = 0; i <1000; i++)
	{
		bullets[i] = Bullet();
	}

	last_pos = 0;
	
}


BulletManager::~BulletManager(){}

void BulletManager::render()
{ //recorrer el vector i ignorar las posiciones que estan libres
	if (last_pos == 0)
		return;

	Mesh mesh;
	for (int i = 0; i < last_pos; i++)
	{
		Bullet &bull = bullets[i];
		mesh.vertices.push_back(bull.last_position);
		mesh.vertices.push_back(bull.position);

	}
		mesh.render(GL_LINES);
}

void BulletManager::update(float elapsed_time)
{
	
	for (int i = 0; i < last_pos; i++)
	{
		//mover bala : P' = P + V*dt
		//bullets[i]->last_position = bullets[i]->position;
		Bullet &bull = bullets[i];


		//mesh.vertices.push_back(bullets[i]->position);
		//eliminar balas con ttl<0
		if (bull.ttl <= 0.0) {
			bull = bullets[last_pos];
			last_pos -= 1;
			i--;
		}

		bull.last_position = bull.position;
		bull.position = bull.position + bull.velocity * elapsed_time;
		bull.ttl -= elapsed_time;
	}
	
	//comprobar colisiones 

	std::vector<EntityCollider *> colliders;
	colliders = EntityCollider::static_colliders;
	colliders.insert(colliders.end(), EntityCollider::dynamic_colliders.begin(), EntityCollider::dynamic_colliders.end());

	
	for (int i = 0; i < last_pos; i++)
	{
		Bullet &bull = bullets[i];
		for (int j = 0; j < colliders.size();j++)
		{
			if (colliders[j]->isDynamic()) {
				Vector3 center = colliders[j]->getCenter();
				Matrix44 model = colliders[j]->model;
				float radius = colliders[j]->getRadius();
				if ((model*center).distance(bull.position) <= radius) //distance between bullet and center less than the sphereCollision
				{
					std::cout << "bullet collision" << std::endl;
				}
			}
			/*else if (colliders[i]->isStatic()) {
				Vector3 or = bull.position;
				Vector3 dir = (bull.last_position - bull.position).normalize();
				Vector3 coll;
				float max = dir.length();

				if (colliders[j]->colVSStatics(or, dir, coll, 0, max)) {
					std::cout << "Colision con statico" << std::endl;
				}
				
				
			}*/
			
		}

	}
}

void BulletManager::shoot(Vector3 pos,  Vector3 vel, float tl, float pow, Entity* author, int type)
{
	
	

	Bullet &bull = bullets[last_pos];

	bull.position = pos;
	bull.last_position = pos;
	bull.velocity = vel;
	bull.ttl = tl;
	bull.power = pow;
	bull.author = author;
	bull.type = type;

	last_pos += 1;
}
