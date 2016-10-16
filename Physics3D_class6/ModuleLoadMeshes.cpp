#include "Application.h"
#include "ModuleLoadMeshes.h"
#include "GameObject.h"
#include "ModuleGameObjectManager.h"
#include "Component.h"

#include "Glew\include\glew.h"

#include "Assimp\include\cimport.h"
#include "Assimp\include\scene.h"
#include "Assimp\include\postprocess.h"
#include "Assimp\include\cfileio.h"
#pragma comment (lib, "Assimp/libx86/assimp.lib")

#include "Devil/include/il.h"
#include "Devil/include/ilut.h"
#pragma comment ( lib, "Devil/libx86/DevIL.lib" )
#pragma comment ( lib, "Devil/libx86/ILU.lib" )
#pragma comment ( lib, "Devil/libx86/ILUT.lib" )

#pragma comment (lib, "Assimp/libx86/assimp.lib")
#pragma comment (lib, "Glew/libx86/glew32.lib")
#include "ComponentTransform.h"
#include "ComponentMaterial.h"
#include "ComponentMesh.h"
#include "MathGeoLib\src/MathGeoLib.h"
using namespace std;


ModuleLoadMeshes::ModuleLoadMeshes(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleLoadMeshes::~ModuleLoadMeshes()
{}

bool ModuleLoadMeshes::Init()
{
	//Use console to LOG debug stuff from assimp
	//struct aiLogStrem stream;
	//stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullprt);
	//aiAttachLogStream(&stream);

	//Initialize DevIL
	ilInit();
	iluInit();
	ilutInit();

	ilutRenderer(ILUT_OPENGL);

	return true;
}

bool ModuleLoadMeshes::CleanUp()
{
	//Stop debbuging through the console
	//aiDetachAllLogStreams();

	return true;
}

vector<MeshT> ModuleLoadMeshes::LoadMesh(const char* path)
{
	vector<MeshT> full_mesh;

	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes())
	{
		aiNode* root_node = scene->mRootNode;

		GameObject* g_object = App->go->AddGameObject(nullptr);

		//USE NODES TO ITERATE ALL THE SCENE
		for (int i = 0; i < root_node->mNumChildren; i++)
		{
			LoadCurrentNode(scene, root_node->mChildren[i], g_object, path);
		}

		aiReleaseImport(scene);
	}
	else
		LOG("Error loading scene %s", path);

	return full_mesh;
}

void ModuleLoadMeshes::LoadCurrentNode(const aiScene* scene, aiNode* node, GameObject* parent, const char* path)
{
	GameObject* g_object = App->go->AddGameObject(parent);

	if (node->mNumMeshes > 0)
	{
		for (int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh_to_load = scene->mMeshes[node->mMeshes[i]];
			MeshT mesh = MeshT();

			//VERTICES
			mesh.num_vertices = mesh_to_load->mNumVertices;
			mesh.vertices = new uint[mesh.num_vertices * 3];
			memcpy(mesh.vertices, mesh_to_load->mVertices, sizeof(float)*mesh.num_vertices * 3);

			//Vertices buffer
			glGenBuffers(1, (GLuint*)&(mesh.id_vertices));
			glBindBuffer(GL_ARRAY_BUFFER, mesh.id_vertices);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * mesh.num_vertices, mesh.vertices, GL_STATIC_DRAW);

			//INDICES
			if (mesh_to_load->HasFaces())
			{
				mesh.num_indices = mesh_to_load->mNumFaces * 3;
				mesh.indices = new uint[mesh.num_indices];
				for (uint j = 0; j < mesh_to_load->mNumFaces; j++)
				{
					if (mesh_to_load->mFaces[j].mNumIndices != 3)
					{
						LOG("WARNING: geometry with indices != 3 found");
					}
					else
					{
						memcpy(&mesh.indices[j * 3], mesh_to_load->mFaces[j].mIndices, 3 * sizeof(uint));
					}
				}
				//Indices buffer
				glGenBuffers(1, (GLuint*)&(mesh.id_indices));
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.id_indices);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * mesh.num_indices, mesh.indices, GL_STATIC_DRAW);
			}

			//NORMALS
			if (mesh_to_load->HasNormals())
			{
				mesh.num_normals = mesh_to_load->mNumVertices;
				mesh.normals = new float[mesh.num_normals * 3];
				memcpy(mesh.normals, mesh_to_load->mNormals, sizeof(float) * mesh.num_normals * 3);

				//Normals buffer
				glGenBuffers(1, (GLuint*)&(mesh.id_normals));
				glBindBuffer(GL_ARRAY_BUFFER, mesh.id_normals);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * mesh.num_normals, mesh.normals, GL_STATIC_DRAW);
			}

			//UVS
			if (mesh_to_load->HasTextureCoords(mesh.id_uvs))
			{
				mesh.num_uvs = mesh_to_load->mNumVertices;
				mesh.uvs = new float[mesh.num_uvs * 2];
				for (int i = 0; i < mesh_to_load->mNumVertices; ++i)
				{
					memcpy(&mesh.uvs[i * 2], &mesh_to_load->mTextureCoords[0][i].x, sizeof(float));
					memcpy(&mesh.uvs[(i * 2) + 1], &mesh_to_load->mTextureCoords[0][i].y, sizeof(float));
				}

				//UVs buffer
				glGenBuffers(1, (GLuint*)&(mesh.id_uvs));
				glBindBuffer(GL_ARRAY_BUFFER, mesh.id_uvs);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * mesh.num_uvs, mesh.uvs, GL_STATIC_DRAW);
			}

			//Transformation
			aiVector3D translation;
			aiVector3D scaling;
			aiQuaternion rotation;

			node->mTransformation.Decompose(scaling, rotation, translation);

			float3 pos(translation.x, translation.y, translation.z);
			float3 scale(scaling.x, scaling.y, scaling.z);
			Quat rot(rotation.x, rotation.y, rotation.z, rotation.w);

			ComponentTransform* c_transform = (ComponentTransform*)g_object->AddComponent(Transform);
			c_transform->SetPosition(pos);
			c_transform->SetRotationQuat(rot);
			c_transform->SetScale(scale);

			ComponentMesh* c_mesh = (ComponentMesh*)g_object->AddComponent(Meshes);
			c_mesh->AddMesh(mesh);

			if (scene->HasMaterials())
			{
				aiMaterial* material = scene->mMaterials[mesh_to_load->mMaterialIndex];
				//uint numTextures = material->GetTextureCount(aiTextureType_DIFFUSE);
				if (material)
				{
					aiString path;
					material->GetTexture(aiTextureType_DIFFUSE, 0, &path);

					if (path.length > 0)
					{
						std::string str1 = path.data;
						str1.erase(0, str1.find_last_of("\\") + 1);

						std::string str2 = "../Game/Assets/Textures/";
						str2 += str1;

					
						ComponentMaterial* c_material = (ComponentMaterial*)g_object->AddComponent(Material);

						c_material->textureId = LoadTexture(str2.c_str());
						LOG(str2.c_str());
						str1.clear();
						str2.clear();
					}

				}
			}
		}
	}

	else
	{
		aiVector3D translation;
		aiVector3D scaling;
		aiQuaternion rotation;

		node->mTransformation.Decompose(scaling, rotation, translation);

		float3 pos(translation.x, translation.y, translation.z);
		float3 scale(scaling.x, scaling.y, scaling.z);
		Quat rot(rotation.x, rotation.y, rotation.z, rotation.w);


		ComponentTransform* c_transform = (ComponentTransform*)g_object->AddComponent(Transform);
		c_transform->SetPosition(pos);
		c_transform->SetRotationQuat(rot);
		c_transform->SetScale(scale);
	}

	for (int i = 0; i < node->mNumChildren; i++)
	{
		LoadCurrentNode(scene, node->mChildren[i], g_object, path);
	}
}

uint ModuleLoadMeshes::LoadTexture(const char* path)
{
	ILuint id;
	ilGenImages(1, &id);
	ilBindImage(id);
	ilLoadImage(path);

	return ilutGLBindTexImage();
}