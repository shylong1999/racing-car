
#ifndef EXOBJECT_H_
#define EXOBJECT_H_

#include "BaseObject.h"
#include "Common_Function.h"


const int EX_WIDTH = 165;
const int EX_HEIGHT = 165;


class ExpObject : public BaseObject
{
public:
	ExpObject();
	~ExpObject();
	void set_clip();
	void set_frame(int fr) {frame_ = fr;}
	void ShowEx(SDL_Surface* des);


private:
	int frame_;
	SDL_Rect clip_[4];

};


#endif 