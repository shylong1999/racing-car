#include "ExObject.h"


ExpObject::ExpObject()
{
	frame_ = 0;
}

ExpObject::~ExpObject()
{
	//	
}

void ExpObject::set_clip()
{
	clip_[0].x = 0;
	clip_[0].y = 0;
	clip_[0].w = EX_WIDTH;
	clip_[0].h = EX_HEIGHT;

	clip_[1].x = 0;
	clip_[1].y = EX_HEIGHT;
	clip_[1].w = EX_WIDTH;
	clip_[1].h = EX_HEIGHT;

	clip_[2].x = 0;
	clip_[2].y = 2*EX_HEIGHT;
	clip_[2].w = EX_WIDTH;
	clip_[2].h = EX_HEIGHT;

	clip_[3].x = 0;
	clip_[3].y = 3*EX_HEIGHT;
	clip_[3].w = EX_WIDTH;
	clip_[3].h = EX_HEIGHT;
}

void ExpObject::ShowEx(SDL_Surface* des)
{
	if (frame_ >=4)
	{
		frame_ = 0;
	}

	SDLCommonFunc::ApplySurfaceclip(this->p_object_, des, &clip_[frame_], rect_.x, rect_.y);
}