#include "Application.h"
#include "ModuleLoadMeshes.h"
#include "GameObject.h"
#include "ModuleGameObjectManager.h"
#include "ModuleFileSystem.h"
#include "Component.h"
#include "ComponentTransform.h"
#include "ComponentMaterial.h"
#include "ComponentMesh.h"
#include "MathGeoLib\src/MathGeoLib.h"
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

using namespace std;


ModuleLoadMeshes::ModuleLoadMeshes(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleLoadMeshes::~ModuleLoadMeshes()
{}

bool ModuleLoadMeshes::Init()
{
	ilInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);
	
	return true;
}

bool ModuleLoadMeshes::CleanUp()
{
	return true;
}

vector<GameObject*> ModuleLoadMeshes::Load(const char* path)
{
	vector<GameObject*> gameObjects;
	char* buffer = nullptr;

	uint size = App->fs->Load(path, &buffer);
	const aiScene* scene = aiImportFileFromMemory(buffer,size, aiProcessPreset_TargetRealtime_MaxQuality,buffer);

	if (scene != nullptr && scene->HasMeshes())
	{
		aiNode* rootNode = scene->mRootNode;

		GameObject* parent = App->go->AddGameObject(nullptr);
		gameObjects.push_back(parent);

		for (int i = 0; i < rootNode->mNumChildren; ++i)
		{
			GameObject* child = LoadMesh(scene, rootNode->mChildren[i], path, parent);
			gameObjects.push_back(child);
		}

		aiReleaseImport(scene);
	}

	return gameObjects;
}

GameObject* ModuleLoadMeshes::LoadMesh(const aiScene* scene, aiNode* node, const char* path, GameObject* parent)
{
	GameObject* child = App->go->AddGameObject(parent);

	//Need to also create gameObjects for the ones that don't have mesh in order to Respect the hierarchy and the local Positions
	if (node->mNumMeshes <= 0)
	{
		aiVector3D translation;
		aiVector3D scaling;
		aiQuaternion rotation;

		node->mTransformation.Decompose(scaling, rotation, translation);

		float3 position(translation.x, translation.y, translation.z);
		float3 scale(scaling.x, scaling.y, scaling.z);
		Quat _rotation(rotation.x, rotation.y, rotation.z, rotation.w);

		ComponentTransform* Ctransform = (ComponentTransform*)child->AddComponent(Transform);
		Ctransform->SetPosition(position);
		Ctransform->SetRotationQuat(_rotation);
		Ctransform->SetScale(scale);
	}
	else
	{
		for (int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* aimesh = scene->mMeshes[node->mMeshes[i]];
			MeshT mesh = MeshT();

			mesh.numVertices = aimesh->mNumVertices;
			mesh.vertices = new uint[mesh.numVertices * 3];
			memcpy(mesh.vertices, aimesh->mVertices, sizeof(float)*mesh.numVertices * 3);

			glGenBuffers(1, (GLuint*)&(mesh.idVertices));
			glBindBuffer(GL_ARRAY_BUFFER, mesh.idVertices);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * mesh.numVertices, mesh.vertices, GL_STATIC_DRAW);

			if (aimesh->HasFaces())
			{
				mesh.numIndices = aimesh->mNumFaces * 3;
				mesh.indices = new uint[mesh.numIndices];
				for (uint j = 0; j < aimesh->mNumFaces; j++)
				{
					if (aimesh->mFaces[j].mNumIndices == 3)
					{
						memcpy(&mesh.indices[j * 3], aimesh->mFaces[j].mIndices, 3 * sizeof(uint));
					}
				}

				glGenBuffers(1, (GLuint*)&(mesh.idIndices));
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.idIndices);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * mesh.numIndices, mesh.indices, GL_STATIC_DRAW);
			}

			if (aimesh->HasTextureCoords(mesh.idUvs))
			{
				mesh.numUvs = aimesh->mNumVertices;
				mesh.uvs = new float[mesh.numUvs * 2];

				for (int i = 0; i < aimesh->mNumVertices; ++i)
				{
					memcpy(&mesh.uvs[i * 2], &aimesh->mTextureCoords[0][i].x, sizeof(float));
					memcpy(&mesh.uvs[(i * 2) + 1], &aimesh->mTextureCoords[0][i].y, sizeof(float));
				}

				glGenBuffers(1, (GLuint*)&(mesh.idUvs));
				glBindBuffer(GL_ARRAY_BUFFER, mesh.idUvs);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * mesh.numUvs, mesh.uvs, GL_STATIC_DRAW);
			}

			if (aimesh->HasNormals())
			{
				mesh.numNormals = aimesh->mNumVertices;
				mesh.normals = new float[mesh.numNormals * 3];
				memcpy(mesh.normals, aimesh->mNormals, sizeof(float) * mesh.numNormals * 3);

				glGenBuffers(1, (GLuint*)&(mesh.idNormals));
				glBindBuffer(GL_ARRAY_BUFFER, mesh.idNormals);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * mesh.numNormals, mesh.normals, GL_STATIC_DRAW);
			}

			aiVector3D translation;
			aiVector3D scaling;
			aiQuaternion rotation;

			node->mTransformation.Decompose(scaling, rotation, translation);

			float3 position(translation.x, translation.y, translation.z);
			float3 scale(scaling.x, scaling.y, scaling.z);
			Quat _rotation(rotation.x, rotation.y, rotation.z, rotation.w);

			ComponentTransform* Ctransform = (ComponentTransform*)child->AddComponent(Transform);
			Ctransform->SetPosition(position);
			Ctransform->SetRotationQuat(_rotation);
			Ctransform->SetScale(scale);

			ComponentMesh* Cmesh = (ComponentMesh*)child->AddComponent(Meshes);
			Cmesh->AddMesh(mesh);

			aiMaterial* material = scene->mMaterials[aimesh->mMaterialIndex];

			if (material)
			{
				aiString path;
				material->GetTexture(aiTextureType_DIFFUSE, 0, &path);

				if (path.length > 0)
				{
					std::string basePath = "../Game/Assets/Textures/";
					std::string finalpath = path.data;
					finalpath.erase(0, finalpath.find_last_of("\\") + 1);
					basePath += finalpath;

					ComponentMaterial* c_material = (ComponentMaterial*)child->AddComponent(Material);
					c_material->textureId = LoadTexture(basePath.c_str());

					finalpath.clear();
					basePath.clear();
				}
			}
		}
	}

	for (int i = 0; i < node->mNumChildren; i++)
	{
		LoadMesh(scene, node->mChildren[i], path, child);
	}

	return child;
}

uint ModuleLoadMeshes::LoadTexture(const char* path)
{
	ILuint id;
	ilGenImages(1, &id);
	ilBindImage(id);
	ilLoadImage(path);

	return ilutGLBindTexImage();
}