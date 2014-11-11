#ifndef __DISTRIBUTED_OBJECT_H_
#define __DISTRIBUTED_OBJECT_H_

#include "ConnectionRepository.h"
#include "ChannelWatcher.h"
#include "msgtypes.h"

#include "AIRepository.h"

class DistributedObject : public ChannelWatcher {
public:
	DistributedObject(uint32_t do_id);
	DistributedObject();

	void message(ConnectionRepository* cr, DatagramIterator* dg, uint64_t sender, uint16_t msgtype);
	virtual bool fieldUpdate(string fieldName, vector<Value*> arguments) {
		return false;
	};

	void setCR(ConnectionRepository* cr) {
		m_cr = cr;
	};

	void setDoId(uint32_t doId) {
		m_do_id = doId;
	}

	void sendUpdate(string fieldName, vector<Value*> arguments);

	void generateWithRequiredAndId(uint32_t doId, uint32_t parentId, uint32_t zoneId) {
		AIRepository* cr = (AIRepository*) m_cr;
		cr->generateWithRequiredAndId(this, doId, parentId, zoneId, vector<Method*> {});
	};
protected:
	ConnectionRepository* m_cr;
	uint32_t m_do_id;
};

#endif