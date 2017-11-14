#ifndef __RENDER_RESOURCE_H__
#define __RENDER_RESOURCE_H__

#include "../ds_err.h"

namespace Dsim {

class RenderResource
{
	public:
		virtual ds_err PreContextSwitch()=0;
		virtual ds_err PostContextSwitch()=0;
	protected:
		//virtual ds_err Init()=0;

};

}
#endif //__RENDER_RESOURCE_H__
