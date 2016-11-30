#ifndef __MATERIAL_IMPORTER_H__
#define __MATERIAL_IMPORTER_H__

#include "Importer.h"

class Texture;

class MaterialImporter : public Importer
{

public:
	MaterialImporter();
	~MaterialImporter();

	bool Import(const char* file, const char* path, std::string& output_file);

	bool Import(const void* buffer, uint size, std::string& output_file);

	bool Load(const char* exported_file, Texture* resource);

	bool LoadCheckers(Texture* resource);

};

#endif //!__MATERIAL_IMPORTER_H__