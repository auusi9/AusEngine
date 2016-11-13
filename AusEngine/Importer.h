#ifndef __IMPORTER_H__
#define __IMPORTER_H__


#include "Globals.h"
#include <string>


class Importer
{
public:
	Importer()
	{
	
	}
	virtual ~Importer()
	{

	}

	virtual bool Import()
	{
		return true;
	}

	virtual void Save() const 
	{
		
	}

	virtual void Load() 
	{
		
	}

private:
	std::string file;
	std::string exported_file;
	uint loaded = 0;
};

#endif //!__IMPORTER_H__