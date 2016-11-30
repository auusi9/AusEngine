#include "Globals.h"
#include "Application.h"
#include "OpenGL.h"
#include "MaterialImporter.h"
#include "ModuleFileSystem.h"
#include "Devil/include/il.h"
#include "Devil/include/ilut.h"



#pragma comment( lib, "Devil/libx86/DevIL.lib" )
#pragma comment( lib, "Devil/libx86/ILU.lib" )
#pragma comment( lib, "Devil/libx86/ILUT.lib" )

using namespace std;

MaterialImporter::MaterialImporter()
{
	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);
}

// Destructor
MaterialImporter::~MaterialImporter()
{
	ilShutDown();
}

// Import new texture from file path
bool MaterialImporter::Import(const char* file, const char* path, string& output_file)
{
	bool ret = false;

	std::string sPath(path);
	std::string sFile(file);

	char* buffer = nullptr;
	uint size = App->fs->Load((char*)(sPath + sFile).c_str(), &buffer);

	if (buffer)
		ret = Import(buffer, size, output_file);

	RELEASE(buffer);

	if (ret == false)
		LOG("Cannot load texture %s from path %s", file, path);

	return ret;
}

bool MaterialImporter::Import(const void* buffer, uint size, string& output_file)
{
	bool ret = false;

	if (buffer)
	{
		ILuint ImageName;
		ilGenImages(1, &ImageName);
		ilBindImage(ImageName);

		if (ilLoadL(IL_TYPE_UNKNOWN, (const void*)buffer, size))
		{
			ilEnable(IL_FILE_OVERWRITE);

			ILuint   size;
			ILubyte *data;
			
			ilSetInteger(IL_DXTC_FORMAT, IL_DXT5);// To pick a specific DXT compression use 
			size = ilSaveL(IL_DDS, NULL, 0); // Get the size of the data buffer
			if (size > 0)
			{
				data = new ILubyte[size]; // allocate data buffer
				if (ilSaveL(IL_DDS, data, size) > 0) // Save with the ilSaveIL function
					ret = App->fs->SaveUnique(output_file, (const char*)data, size, "Library/Textures", "texture", "dds");

				RELEASE(data);
			}
			ilDeleteImages(1, &ImageName);
		}
	}

	if (ret == false)
		LOG("Cannot load texture from buffer of size %u", size);

	return ret;
}


