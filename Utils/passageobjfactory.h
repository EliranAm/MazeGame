#ifndef __PASSAGE_OBJ_FACTORY_H__
#define __PASSAGE_OBJ_FACTORY_H__

#include <tr1/memory>
#include <map>

#include "../Objects/passage.h"
#include "../Objects/passageobj.h"
#include "uncopyable.h"

#define ROOM_ID unsigned int

namespace advcpp
{

class IpassageObj;

class passageObjFactory : private Uncopyable
{

public:

	static Passage::PassageObjCon CreateAllObj();
	
	
private:
	
	passageObjFactory();
	~passageObjFactory();
	const passageObjFactory& operator = (const passageObjFactory&);
	passageObjFactory(const passageObjFactory&);
	


};



}	//namespace advcpp

#endif /* __PASSAGE_OBJ_FACTORY_H__*/

