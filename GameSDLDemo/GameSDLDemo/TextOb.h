
#ifndef TEXTOB_H_
#define TEXTOB_H_
#include "BaseObject.h"
#include <string>
#include <SDL_ttf.h>

class TextObject : public BaseObject
{
public:
	enum TextColor
	{
		RED_TEXT = 0,
		WHITE_TEXT = 1,
		GREEN_TEXT = 2,
	};

	TextObject();
	~TextObject();

	void SetText(const std::string& text) {str_text_ = text;}
	void SetColor(const int& type);
	void CreateText(TTF_Font* font,SDL_Surface* des);
private:
	std::string str_text_;
	SDL_Color text_color_;
};



#endif