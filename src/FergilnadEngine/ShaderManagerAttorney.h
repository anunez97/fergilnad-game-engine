// Shader Manager Attorney

#ifndef _ShaderManagerAttorney
#define _ShaderManagerAttorney

#include "ShaderManager.h"

class ShaderManagerAttorney
{
	friend class Fergilnad;

private:
	static void Delete() { ShaderManager::Delete(); }
};

#endif _ShaderManagerAttorney