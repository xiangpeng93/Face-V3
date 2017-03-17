#pragma once
#include "FacePlusPlusInterface.h"
class CGroupManger :public CFacePlusPlusInterface
{
public:
	virtual int _createGroup(char *dspName);
	virtual int _deleteGroup(char *outId);

public:
	std::string m_groupName;
};

