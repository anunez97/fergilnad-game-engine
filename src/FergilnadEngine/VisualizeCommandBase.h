// Visualize Command Base

#ifndef _VisualizeCommandBase
#define _VisualizeCommandBase

#include "AzulCore.h"

class VisualizeCommandBase
{
public:
	VisualizeCommandBase() {};
	VisualizeCommandBase(const VisualizeCommandBase& other) = delete;
	VisualizeCommandBase& operator=(const VisualizeCommandBase& other) = delete;
	virtual ~VisualizeCommandBase() {};

	virtual void Execute() = 0;
	virtual void Return() = 0;
};

#endif _VisualizeCommandBase