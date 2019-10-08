#include "ThreateObject.h"

ThreatObject::ThreatObject()
{
	rect_.x = SCREEN_WIDTH*0.5;
	rect_.y = SCREEN_HEIGHT;
	rect_.w = WIDTH_THREAT;
	rect_.h = HEIGHT_THREAT;

	x_val_ = 0;
	y_val_ = 0;

}

ThreatObject::~ThreatObject()
{
	if (p_amo_list_.size()>0)
	{
		for (int i=0;i<p_amo_list_.size();i++)
		{
			AmoObject* p_amo = p_amo_list_.at(i);
			if (p_amo != NULL)
			{
				delete p_amo;
				p_amo = NULL;
			}
		}
		p_amo_list_.clear();
	}
}

void ThreatObject::InitAmo(AmoObject* p_amo)
{
	if(p_amo)
	{
		bool ret = p_amo->LoadImg("sphere2.png");
		if(ret)
		{
			p_amo->set_is_move(true);
			p_amo->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
			p_amo->set_type(AmoObject::SPHERE);
			p_amo->SetRect(rect_.x + rect_.w*0.5, rect_.y);
			p_amo->set_y_val(4);
			p_amo_list_.push_back(p_amo);
		}
	}
}

void ThreatObject::MakeAmo(SDL_Surface* des, const int& x_limit, const int& y_limit)
{
	for (int i=0; i<p_amo_list_.size();i++)
	{
		AmoObject* p_amo = p_amo_list_.at(i);
		if(p_amo)
		{
			if (p_amo->get_is_move())
			{
				p_amo->Show(des);
				p_amo->HandleMoveHighToShort();
			}
			else 
			{
				p_amo->set_is_move(true);
				p_amo->SetRect(rect_.x + rect_.w*0.42, rect_.y + 100);
			}
		}
	}
}

void ThreatObject::HandleMove(const int& x_border, const int& y_border)
{
	rect_.y += y_val_;
	if (rect_.y > SCREEN_HEIGHT) 
	{
		rect_.y = 0;
		int rand_x = rand()%400;
		if (rand_x > SCREEN_WIDTH - UNDER_LIMIT_THREAT)
		{
			rand_x = SCREEN_WIDTH*0.82;
		}
		rect_.x = rand_x;
	}
}

void ThreatObject::HandleInputAction(SDL_Event events)
{
	//todo
}

void ThreatObject::Reset(const int& yboder)
{
	rect_.y = yboder;
	int rand_x = rand()%400;
	rect_.y = 0;
	if (rand_x > SCREEN_WIDTH - UNDER_LIMIT_THREAT)
	{
		rand_x = SCREEN_WIDTH*0.72;
	}
	rect_.x = rand_x;
	for (int i = 0 ;i < p_amo_list_.size(); i++)
	{
		AmoObject* p_amo = p_amo_list_.at(i);
		if (p_amo)
		{
			ResetAmo(p_amo);
		}
	}
}

void ThreatObject::ResetAmo(AmoObject* p_amo)
{
	p_amo->SetRect(rect_.x + rect_.w*0.5, rect_.y);
}
