#ifndef __MESH_IMPORTER_H__
#define __MESH_IMPORTER_H__

#include "Importer.h"

class aiMesh;
class ResourceMesh;

class MeshImporter : public Importer
{

public:

	bool Import(const aiMesh* mesh, std::string & output_file);

	bool Load(const char* exported_file, ResourceMesh* resource);


};

#endif //!__MESH_IMPORTER_H__