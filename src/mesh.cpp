#include "mesh.h"
#include <cassert>
#include "includes.h"
#include "shader.h"
#include "utils.h"

#include "extra/textparser.h"

std::map<std::string, Mesh*> Mesh::s_Meshes;

Mesh::Mesh()
{
	//init all values
	vertices_vbo_id = 0;
	normals_vbo_id = 0;
	uvs_vbo_id = 0;
	colors_vbo_id = 0;

	modelc = NULL;

	//itsfloor = true;
}

Mesh::Mesh(const Mesh& m)
{
	vertices = m.vertices;
	normals = m.normals;
	uvs = m.uvs;
	colors = m.colors;

	modelc = NULL;
}

Mesh::~Mesh()
{
	if (vertices_vbo_id) glDeleteBuffersARB(1, &vertices_vbo_id);
	if (normals_vbo_id) glDeleteBuffersARB(1, &normals_vbo_id);
	if (uvs_vbo_id) glDeleteBuffersARB(1, &uvs_vbo_id);
	if (colors_vbo_id) glDeleteBuffersARB(1, &colors_vbo_id);
}

void Mesh::clear()
{
	vertices.clear();
	normals.clear();
	uvs.clear();
	colors.clear();
}


void Mesh::render(int primitive)
{
	assert(vertices.size() && "No vertices in this mesh");

	glEnableClientState(GL_VERTEX_ARRAY);

	if (vertices_vbo_id)
	{
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, vertices_vbo_id);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
	}
	else
		glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);

	if (normals.size())
	{
		glEnableClientState(GL_NORMAL_ARRAY);
		if (normals_vbo_id)
		{
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, normals_vbo_id);
			glNormalPointer(GL_FLOAT, 0, NULL);
		}
		else
			glNormalPointer(GL_FLOAT, 0, &normals[0]);
	}

	if (uvs.size())
	{
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		if (uvs_vbo_id)
		{
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, uvs_vbo_id);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);
		}
		else
			glTexCoordPointer(2, GL_FLOAT, 0, &uvs[0]);
	}

	if (colors.size())
	{
		glEnableClientState(GL_COLOR_ARRAY);
		if (colors_vbo_id)
		{
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, colors_vbo_id);
			glColorPointer(4, GL_FLOAT, 0, NULL);
		}
		else
			glColorPointer(4, GL_FLOAT, 0, &colors[0]);
	}

	glDrawArrays(primitive, 0, (GLsizei)vertices.size());
	glDisableClientState(GL_VERTEX_ARRAY);

	if (normals.size())
		glDisableClientState(GL_NORMAL_ARRAY);
	if (uvs.size())
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	if (colors.size())
		glDisableClientState(GL_COLOR_ARRAY);
	//glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );
}

void Mesh::render(int primitive, Shader* sh)
{
	if (!sh || !sh->compiled)
		return render(primitive);

	assert(vertices.size() && "No vertices in this mesh");

	int vertex_location = sh->getAttribLocation("a_vertex");
	assert(vertex_location != -1 && "No a_vertex found in shader");

	if (vertex_location == -1)
		return;

	glEnableVertexAttribArray(vertex_location);
	if (vertices_vbo_id)
	{
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, vertices_vbo_id);
		glVertexAttribPointer(vertex_location, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	}
	else
		glVertexAttribPointer(vertex_location, 3, GL_FLOAT, GL_FALSE, 0, &vertices[0]);

	int normal_location = -1;
	if (normals.size())
	{
		normal_location = sh->getAttribLocation("a_normal");
		if (normal_location != -1)
		{
			glEnableVertexAttribArray(normal_location);
			if (normals_vbo_id)
			{
				glBindBufferARB(GL_ARRAY_BUFFER_ARB, normals_vbo_id);
				glVertexAttribPointer(normal_location, 3, GL_FLOAT, GL_FALSE, 0, NULL);
			}
			else
				glVertexAttribPointer(normal_location, 3, GL_FLOAT, GL_FALSE, 0, &normals[0]);
		}
	}

	int uv_location = -1;
	if (uvs.size())
	{
		uv_location = sh->getAttribLocation("a_uv");
		if (uv_location != -1)
		{
			glEnableVertexAttribArray(uv_location);
			if (uvs_vbo_id)
			{
				glBindBufferARB(GL_ARRAY_BUFFER_ARB, uvs_vbo_id);
				glVertexAttribPointer(uv_location, 2, GL_FLOAT, GL_FALSE, 0, NULL);
			}
			else
				glVertexAttribPointer(uv_location, 2, GL_FLOAT, GL_FALSE, 0, &uvs[0]);
		}
	}

	int color_location = -1;
	if (colors.size())
	{
		color_location = sh->getAttribLocation("a_color");
		if (color_location != -1)
		{
			glEnableVertexAttribArray(color_location);
			if (colors_vbo_id)
			{
				glBindBufferARB(GL_ARRAY_BUFFER_ARB, colors_vbo_id);
				glVertexAttribPointer(color_location, 4, GL_FLOAT, GL_FALSE, 0, NULL);
			}
			else
				glVertexAttribPointer(color_location, 4, GL_FLOAT, GL_FALSE, 0, &colors[0]);
		}
	}

	glDrawArrays(primitive, 0, (GLsizei)vertices.size());

	glDisableVertexAttribArray(vertex_location);
	if (normal_location != -1) glDisableVertexAttribArray(normal_location);
	if (uv_location != -1) glDisableVertexAttribArray(uv_location);
	if (color_location != -1) glDisableVertexAttribArray(color_location);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
}

void Mesh::uploadToVRAM()
{
	if (glGenBuffersARB == 0)
	{
		std::cout << "Error: your graphics cards dont support VBOs. Sorry." << std::endl;
		exit(0);
	}

	//delete old
	if (vertices_vbo_id) glDeleteBuffersARB(1, &vertices_vbo_id);
	if (normals_vbo_id) glDeleteBuffersARB(1, &normals_vbo_id);
	if (uvs_vbo_id) glDeleteBuffersARB(1, &uvs_vbo_id);
	if (colors_vbo_id) glDeleteBuffersARB(1, &colors_vbo_id);

	glGenBuffersARB(1, &vertices_vbo_id); //generate one handler (id)
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vertices_vbo_id); //bind the handler
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, vertices.size() * 3 * sizeof(float), &vertices[0], GL_STATIC_DRAW_ARB); //upload data

	if (normals.size())
	{
		glGenBuffersARB(1, &normals_vbo_id); //generate one handler (id)
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, normals_vbo_id); //bind the handler
		glBufferDataARB(GL_ARRAY_BUFFER_ARB, normals.size() * 3 * sizeof(float), &normals[0], GL_STATIC_DRAW_ARB); //upload data
	}

	if (uvs.size())
	{
		glGenBuffersARB(1, &uvs_vbo_id); //generate one handler (id)
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, uvs_vbo_id); //bind the handler
		glBufferDataARB(GL_ARRAY_BUFFER_ARB, uvs.size() * 2 * sizeof(float), &uvs[0], GL_STATIC_DRAW_ARB); //upload data
	}

	if (colors.size())
	{
		glGenBuffersARB(1, &colors_vbo_id); //generate one handler (id)
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, colors_vbo_id); //bind the handler
		glBufferDataARB(GL_ARRAY_BUFFER_ARB, colors.size() * 4 * sizeof(float), &colors[0], GL_STATIC_DRAW_ARB); //upload data
	}

}

void Mesh::createQuad(float center_x, float center_y, float w, float h, bool flip_uvs)
{
	vertices.clear();
	normals.clear();
	uvs.clear();
	colors.clear();

	//create six vertices (3 for upperleft triangle and 3 for lowerright)

	vertices.push_back(Vector3(center_x + w*0.5f, center_y + h*0.5f, 0.0f));
	vertices.push_back(Vector3(center_x - w*0.5f, center_y - h*0.5f, 0.0f));
	vertices.push_back(Vector3(center_x + w*0.5f, center_y - h*0.5f, 0.0f));
	vertices.push_back(Vector3(center_x - w*0.5f, center_y + h*0.5f, 0.0f));
	vertices.push_back(Vector3(center_x - w*0.5f, center_y - h*0.5f, 0.0f));
	vertices.push_back(Vector3(center_x + w*0.5f, center_y + h*0.5f, 0.0f));


	//texture coordinates
	uvs.push_back(Vector2(1.0f, flip_uvs ? 0.0f : 1.0f));
	uvs.push_back(Vector2(0.0f, flip_uvs ? 1.0f : 0.0f));
	uvs.push_back(Vector2(1.0f, flip_uvs ? 1.0f : 0.0f));
	uvs.push_back(Vector2(0.0f, flip_uvs ? 0.0f : 1.0f));
	uvs.push_back(Vector2(0.0f, flip_uvs ? 1.0f : 0.0f));
	uvs.push_back(Vector2(1.0f, flip_uvs ? 0.0f : 1.0f));

	//all of them have the same normal
	normals.push_back(Vector3(0.0f, 0.0f, 1.0f));
	normals.push_back(Vector3(0.0f, 0.0f, 1.0f));
	normals.push_back(Vector3(0.0f, 0.0f, 1.0f));
	normals.push_back(Vector3(0.0f, 0.0f, 1.0f));
	normals.push_back(Vector3(0.0f, 0.0f, 1.0f));
	normals.push_back(Vector3(0.0f, 0.0f, 1.0f));
}



void Mesh::createPlane(float size)
{
	vertices.clear();
	normals.clear();
	uvs.clear();
	colors.clear();

	//create six vertices (3 for upperleft triangle and 3 for lowerright)

	vertices.push_back(Vector3(size, 0, size));
	vertices.push_back(Vector3(size, 0, -size));
	vertices.push_back(Vector3(-size, 0, -size));
	vertices.push_back(Vector3(-size, 0, size));
	vertices.push_back(Vector3(size, 0, size));
	vertices.push_back(Vector3(-size, 0, -size));

	//all of them have the same normal
	normals.push_back(Vector3(0, 1, 0));
	normals.push_back(Vector3(0, 1, 0));
	normals.push_back(Vector3(0, 1, 0));
	normals.push_back(Vector3(0, 1, 0));
	normals.push_back(Vector3(0, 1, 0));
	normals.push_back(Vector3(0, 1, 0));

	//texture coordinates
	uvs.push_back(Vector2(1, 1));
	uvs.push_back(Vector2(1, 0));
	uvs.push_back(Vector2(0, 0));
	uvs.push_back(Vector2(0, 1));
	uvs.push_back(Vector2(1, 1));
	uvs.push_back(Vector2(0, 0));


}


/*******************PARSER**********************/

bool Mesh::parseASE(const char* filename)
{
	long time = getTime();

	std::string filename_bin(filename); 
	filename_bin += ".bin"; //create .bin file


	FILE* file = fopen(filename_bin.c_str(), "rb");
	if (file != NULL)
	{
		fread(&header, sizeof(sMeshInfo), 1, file); 
		vertices.resize(header.num_faces * 3); //reserve the needed space
		normals.resize(header.num_faces * 3);
		uvs.resize(header.num_uvs * 3);
		fread(&vertices[0], sizeof(Vector3), header.num_faces * 3, file);
		fread(&normals[0], sizeof(Vector3), header.num_faces * 3, file);
		fread(&uvs[0], sizeof(Vector2), header.num_uvs * 3, file);

		fclose(file);
		uploadToVRAM();
		long time2 = getTime();
		std::cout << "parsing time: " << (time2 - time) << "ms" << std::endl;

		return true;
	}

	TextParser t;

	if (t.create(filename) == false)
	{
		std::cout << "File not found: " << filename << std::endl;
		return false;
	}

	std::vector < Vector3> unique_vertices;

	t.seek("*MESH_NUMVERTEX");
	int num_vertices = t.getint();

	t.seek("*MESH_NUMFACES");
	int num_faces = t.getint();

	unique_vertices.resize(num_vertices);

	for (int i = 0; i < num_vertices; ++i)
	{
		t.seek("*MESH_VERTEX");
		t.getint();
		float x = t.getfloat();
		float z = -t.getfloat();
		float y = t.getfloat();
		Vector3 v(x, y, z);
		unique_vertices[i] = v;

		//calculamos en min
		if (header.min_v.x < v.x)
			header.min_v.x = v.x;
		if (header.min_v.y < v.y)
			header.min_v.y = v.y;
		if (header.min_v.z < v.z)
			header.min_v.z = v.z;

		//calculamos el max
		if (header.max_v.x > v.x)
			header.max_v.x = v.x;
		if (header.max_v.y > v.y)
			header.max_v.y = v.y;
		if (header.max_v.z > v.z)
			header.max_v.z = v.z;
	}


	for (int i = 0; i < num_faces; ++i) {
		t.seek("*MESH_FACE");
		t.getword();
		t.getword();
		int A = t.getint();
		t.getword();
		int B = t.getint();
		t.getword();
		int C = t.getint();

		vertices.push_back(unique_vertices[A]);
		vertices.push_back(unique_vertices[B]);
		vertices.push_back(unique_vertices[C]);

		//colors.push_back(Vector4(unique_vertices[C], 1.0));
		//colors.push_back(Vector4(unique_vertices[B], 1.0));
		//colors.push_back(Vector4(unique_vertices[A], 1.0));
	}



	std::vector <Vector2> unique_tvertices;

	t.seek("*MESH_NUMTVERTEX");
	int num_textures = t.getint();

	unique_tvertices.resize(num_textures);

	for (int i = 0; i < num_textures; i++)
	{
		t.seek("*MESH_TVERT");
		t.getint();
		float x = t.getfloat();
		float y = t.getfloat();

		Vector2 vt(x, y);
		unique_tvertices[i] = vt;
	}

	//MESH_TFACES
	t.seek("*MESH_NUMTVFACES");
	int num_tfaces = t.getint();

	for (int i = 0; i < num_tfaces; i++)
	{
		t.seek("*MESH_TFACE");
		t.getint();
		int A = t.getint();
		int B = t.getint();
		int C = t.getint();

		uvs.push_back(unique_tvertices[A]);
		uvs.push_back(unique_tvertices[B]);
		uvs.push_back(unique_tvertices[C]);
	}


	//in normals we use num_vertices to make the for loop because each vertex has a normal
	//number of normals it is equal to the number of vertexs

	for (int i = 0; i < num_faces * 3; i++)
	{
		t.seek("*MESH_VERTEXNORMAL");
		t.getint();
		float x = t.getfloat();
		float y = t.getfloat();
		float z = t.getfloat();

		Vector3 v(x, z, -y);

		normals.push_back(v);

	}

	//calculate center, halfsize and radius for the bounding box
	header.num_faces = num_faces;
	header.num_uvs = num_tfaces;

	header.center = Vector3((header.min_v.x + header.max_v.x) / 2, (header.min_v.y + header.max_v.y) / 2, (header.min_v.z + header.max_v.z) / 2);
	header.halfsize = header.max_v - header.center;
	header.radius = header.center.distance(header.max_v);

	FILE* file1 = fopen(filename_bin.c_str(), "wb");
	fwrite(&header, sizeof(header), 1, file1);
	fwrite(&vertices[0], sizeof(Vector3), vertices.size(), file1);
	fwrite(&normals[0], sizeof(Vector3), normals.size(), file1);
	fwrite(&uvs[0], sizeof(Vector2), uvs.size(), file1);
	fclose(file1);

	//numero de:
	std::cout << "Vertexs: " << num_vertices << std::endl;
	std::cout << "Faces: " << num_faces << std::endl;


	uploadToVRAM();

	long time2 = getTime();
	std::cout << "parsing time: " << (time2 - time) << "ms" << std::endl;


	return true;

}

/*static Mesh* s_instance;
static Mesh* getInstance() {
return s_instance;
}*/

/*******************************MESH MANAGER***************************************/

Mesh* Mesh::Load(const char* filename) {
	std::map<std::string, Mesh*>::iterator it = s_Meshes.find(filename);
	if (it != s_Meshes.end())
		return it->second;

	Mesh* m = new Mesh();
	if (!m->parseASE(filename))
		return NULL;
	s_Meshes[filename] = m;
	return m;
}

CollisionModel3D* Mesh::getCollisionModel3D() {	//fill the collisionModel3D with all the triangles

	if (modelc)
		return modelc;

	modelc = newCollisionModel3D();
	modelc->setTriangleNumber(header.num_faces);

	for (int i = 0; i < vertices.size(); i++) {
		modelc->addTriangle(vertices[i].x, vertices[i].y, vertices[i].z,
		vertices[i + 1].x, vertices[i + 1].y, vertices[i + 1].z,
		vertices[i + 2].x, vertices[i + 2].y, vertices[i + 2].z);

		i += 2;
	}
	modelc->finalize();


	return modelc;
}