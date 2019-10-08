#include "AmoObject.h"

AmoObject::AmoObject()
{
	rect_.x = 0;
	rect_.y = 0;
	x_val_ = 0;
	y_val_ = 0;
	is_move_ = false;
	amo_type_ = NONE;

}

AmoObject::~AmoObject()
{

}

void AmoObject::HandleMove(const int& x_border, const int& y_border)
{
	if (is_move_ == true)
	{
		rect_.y -= y_val_;
		if (rect_.y > y_border)
		{
			is_move_ = false;
		}
	}
}

void AmoObject::HandleMoveHighToShort()
{
	rect_.y += y_val_;
	if (rect_.y > SCREEN_HEIGHT)
	{
		is_move_ = false;
	}
}

void AmoObject::HandleInputAction(SDL_Event events)
{
	;
}
