// Trim Branch Command

#include "TrimBranchCommand.h"
#include "OctreeNode.h"

TrimBranchCommand::TrimBranchCommand(OctreeNode* branch)
	:pBranch(branch)
{

}

TrimBranchCommand::~TrimBranchCommand()
{

}

void TrimBranchCommand::Execute()
{
	delete pBranch;
}

OctreeNode* TrimBranchCommand::GetNode()
{
	return pBranch;
}