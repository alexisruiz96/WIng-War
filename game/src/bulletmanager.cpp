#include "bulletmanager.h"
#include "bass.h"
#include "scene.h"

BulletManager* BulletManager::instance = NULL;

//El handler para un sample
HSAMPLE hSample, hSample3;

//El handler para un canal
HCHANNEL hSampleChannel, hSampleChannel3;

BulletManager::BulletManager()
{
	for (int i = 0; i <500; i++)
	{
		bullets[i] = Bullet();
	}

	last_pos = 0;
	
	BASS_Init(1, 44100, 0, 0, NULL);
	//Cargamos un sample (memoria, filename, offset, length, max, flags)
	hSample = BASS_SampleLoad(false, "data/sounds/shot.wav", 0, 0, 3, 0);
	hSample3 = BASS_SampleLoad(false, "data/sounds/hitmarker.wav", 0, 0, 3, 0);
	//Creamos un canal para el sample
	hSampleChannel = BASS_SampleGetChannel(hSample, false);
	hSampleChannel3 = BASS_SampleGetChannel(hSample3, false);
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
					if (!bull.hittedYet) {
						if ((bull.author != colliders[j]) && ((bull.author == Scene::instance->plane) || (colliders[j] == Scene::instance->plane))) {
							colliders[j]->hp = colliders[j]->hp - 5;
							bull.hittedYet = true;
							if (bull.author == Scene::instance->plane)
								BASS_ChannelPlay(hSampleChannel3, false);
						}
					}
				}

			}
			/*else if (colliders[i]->isStatic()) {
				Vector3 or = bull.position;
				Vector3 dir = (bull.last_position - bull.position).normalize();
				Vector3 coll;
				float max = dir.length();

				if (colliders[j]->colVSStatics(or, dir, coll, 0, max)) {
					std::cout << "Bala Con Statico" << std::endl;
				}
				
				
			}*/
			
		}

	}
}

void BulletManager::shoot(Vector3 pos,  Vector3 vel, float tl, float pow, Entity* author, int type)
{
	if (last_pos >= 500) {
		return;
	}
	

	Bullet &bull = bullets[last_pos];

	bull.position = pos;
	bull.last_position = pos;
	bull.velocity = vel;
	bull.ttl = tl;
	bull.power = pow;
	bull.author = author;
	bull.type = type;
	bull.hittedYet = false;

	last_pos++;

	//Lanzamos un sample
	BASS_ChannelPlay(hSampleChannel, true);
}
