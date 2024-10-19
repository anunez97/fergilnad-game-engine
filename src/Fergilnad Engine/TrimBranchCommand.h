// Trim Branch Command

#ifndef _TrimBranchCommand
#define _TrimBranchCommand

#include "CommandBase.h"

class OctreeNode;

class TrimBranchCommand : public CommandBase
{
public:
	TrimBranchCommand() {};
	TrimBranchCommand(const TrimBranchCommand& other) = delete;
	TrimBranchCommand& operator=(const TrimBranchCommand& other) = delete;
	~TrimBranchCommand();

	TrimBranchCommand(OctreeNode* branch);

	void Execute();
	OctreeNode* GetNode();

private:
	OctreeNode* pBranch;

};

#endif _TrimBranchCommand