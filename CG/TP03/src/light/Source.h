#ifndef _SOURCE_H
#define _SOURCE_H

#include "../util/Vect.h"
#include "../color/Color.h"

class Source {
	public:
	
	Source();
	
	virtual Vect getLightPosition();
	virtual Color getLightColor();
	
};


#endif
