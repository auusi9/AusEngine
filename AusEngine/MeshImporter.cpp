#include "Globals.h"
#include "Application.h"
#include "MeshImporter.h"
#include "ModuleFileSystem.h"
#include "Assimp\include\cimport.h"
#include "Assimp\include\scene.h"
#include "Assimp\include\postprocess.h"
#include "Assimp\include\cfileio.h"
#include "Mesh.h"
#pragma comment (lib, "Assimp/libx86/assimp.lib")
#pragma comment (lib, "Glew/libx86/glew32.lib")


bool MeshImporter::Import(const aiMesh* nmesh, std::string & output_file)
{
	bool ret = false;

	ResourceMesh m;
	if (nmesh != nullptr)
	{
		// copy vertices
		m.num_vertices = nmesh->mNumVertices;
		m.vertices = new float[m.num_vertices * 3];
		memcpy(m.vertices, nmesh->mVertices, sizeof(float) * m.num_vertices * 3);
		LOG("New nmesh with %d vertices", m.num_vertices);

		// copy faces
		if (nmesh->HasFaces())
		{
			m.num_indices = nmesh->mNumFaces * 3;
			m.indices = new uint[m.num_indices]; // assume each face is a triangle
			for (uint i = 0; i < nmesh->mNumFaces; ++i)
			{
				if (nmesh->mFaces[i].mNumIndices != 3)
					LOG("WARNING, geometry face with %d indices, all should be have 3!", nmesh->mFaces[i].mNumIndices);

				memcpy(&m.indices[i * 3], nmesh->mFaces[i].mIndices, 3 * sizeof(uint));
			}
		}

		// normals
		if (nmesh->HasNormals())
		{
			m.normals = new float[m.num_vertices * 3];
			memcpy(m.normals, nmesh->mNormals, sizeof(float) * m.num_vertices * 3);
		}

		// colors
		if (nmesh->HasVertexColors(0))
		{
			m.colors = new float[m.num_vertices * 3];
			memcpy(m.colors, nmesh->mColors, sizeof(float) * m.num_vertices * 3);
		}

		// texture coords
		if (nmesh->HasTextureCoords(0))
		{
			m.texture_coords = new float[m.num_vertices * 3];
			memcpy(m.texture_coords, nmesh->mTextureCoords[0], sizeof(float) * m.num_vertices * 3);
		}


	// amount of indices / vertices / colors / normals / texture_coords / AABB

	uint ranges[5] = { m.num_indices, m.num_vertices, (m.colors) ? m.num_vertices : 0,

		(m.normals) ? m.num_vertices : 0, (m.texture_coords) ? m.num_vertices : 0 };

	uint size = sizeof(ranges) + sizeof(uint) * m.num_indices + sizeof(float) * m.num_vertices * 3;

	if (m.colors != nullptr) size += sizeof(float) * m.num_vertices * 3;

	if (m.normals != nullptr) size += sizeof(float) * m.num_vertices * 3;

	if (m.texture_coords != nullptr) size += sizeof(float) * m.num_vertices * 3;

	char* data = new char[size]; // Allocate

	char* cursor = data;

	uint bytes = sizeof(ranges); // First store ranges

	memcpy(cursor, ranges, bytes);

	cursor += bytes; // Store indices

	bytes = sizeof(uint) * m.num_indices;

	memcpy(cursor, m.indices, bytes);

	ret = App->fs->SaveUnique(output_file, (const char*)cursor, size, "Library/Meshes", "mesh", "m");

	}

	return ret;
}

bool MeshImporter::Load(const char* exported_file, ResourceMesh* resource)
{

	return false;
}

