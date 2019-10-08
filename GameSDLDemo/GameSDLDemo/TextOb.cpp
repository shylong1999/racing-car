#include "TextOb.h"

TextObject::TextObject()
{
	rect_.x = 142;
	rect_.y = 0;
}

TextObject::~TextObject()
{

}

void TextObject::SetColor(const int& type)
{
	if (type == RED_TEXT)
	{
		SDL_Color color = {255,0,0};
		text_color_ = color;
	}
	else if (type == WHITE_TEXT)
	{
		SDL_Color color = {255,255,0};
		text_color_ = color;
	}
	else if (type == GREEN_TEXT)
	{
		SDL_Color color = {0,255,0};
		text_color_ = color;
	}
	else
	{
		SDL_Color color = {0,0,0};
		text_color_ = color;
	}

}

void TextObject::CreateText(TTF_Font* font,SDL_Surface* des)
{
	p_object_ = TTF_RenderText_Solid(font, str_text_.c_str(), text_color_);
	Show(des);
}