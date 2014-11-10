#ifndef __CONNECTIONREPO_H__
#define __CONNECTIONREPO_H__

#include "global.h"

class ConnectionRepository {
public:
	ConnectionRepository(string dcFile);
private:
	Module* m_module;
	string m_dcFile;
};

#endif