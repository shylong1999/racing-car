#ifndef THREATES_OBJECT_H_
#define THREATES_OBJECT_H_

#include "Common_Function.h"
#include "BaseObject.h"
#include "AmoObject.h"
#include <vector>

#define WIDTH_THREAT 50
#define HEIGHT_THREAT 100

const int UNDER_LIMIT_THREAT = 50;
class ThreatObject : public BaseObject
{
public:
	ThreatObject();
	~ThreatObject();

	void HandleMove(const int& x_border,const int& y_border);
	void HandleInputAction(SDL_Event events);

	void set_x_val(const int& val) {x_val_ = val;}
	void set_y_val(const int& val) {y_val_ = val;}
	int get_x_val() {return x_val_;}
	int get_y_val() {return y_val_;}

	void SetAmoList(std::vector<AmoObject*> amo_list) {p_amo_list_ = amo_list;}
	std::vector<AmoObject*> GetAmoList() const {return p_amo_list_;}
	void InitAmo(AmoObject* p_amo);
	void MakeAmo(SDL_Surface* des, const int& x_limit, const int& y_limit);
	void Reset(const int& yboder);
	void ResetAmo(AmoObject* p_amo); //truyen dan vao
private:
	int x_val_;
	int y_val_;

	std::vector<AmoObject*> p_amo_list_;
};



#endif