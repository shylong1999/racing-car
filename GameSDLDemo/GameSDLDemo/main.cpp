#include "Common_Function.h"
#include "MainObject.h"
#include "ThreateObject.h"
#include "ExObject.h"
#include "PlayerPower.h"
#include "TextOb.h"

TTF_Font* g_font_text = NULL;
TTF_Font* g_font_menu = NULL;
bool Init()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
  {
    return false;
  }
  g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

  if (g_screen == NULL)
  {
    return false;
  }

  if(TTF_Init() == -1) return false;

  g_font_text = TTF_OpenFont("Penny Script Demo.ttf",24);
  g_font_menu = TTF_OpenFont("Penny Script Demo.ttf",50);
  if (g_font_text == NULL||g_font_menu == NULL) return false;

  return true;
}


int main(int arc, char* argv[])
{
	int bkgn_y=0;
    bool is_quit = false;
    if (Init() == false)
    return 0;
 

  g_bkground = SDLCommonFunc::LoadImage("Road.png");
  if (g_bkground == NULL)
  {
    return 0;
  }
 
  //Make Player Power
  PlayerPower player_power;
  player_power.Init();
  
  //TEXT
  TextObject Point;
  Point.SetColor(TextObject::GREEN_TEXT);

  
 //Make MainOb
  MainObject human_object;
  human_object.SetRect(125,400);
  bool ret = human_object.LoadImg("Car_4.png");
  if(!ret)
  {
	  return 0;
  }


  //Init ExObject
  ExpObject exp_main;
  ExpObject exp_threats;

  ret = exp_main.LoadImg("exp_main.png");
  exp_main.set_clip();
  if (ret == false) return 0;

  ret = exp_threats.LoadImg("exp.png");
  exp_threats.set_clip();
  if (ret == false) return 0;
  //Make ThreatOb
  ThreatObject* p_threats = new ThreatObject[NUM_THREATS];

  for(int i=0; i< NUM_THREATS;i++)
  {
	    ThreatObject* p_threat = (p_threats + i);
		if (p_threat)
		{
			ret = p_threat->LoadImg("Car_1.png");
			if (ret == false)
			{
				return 0;
			}

  
			int rand_x = rand()%400;
			if (rand_x > SCREEN_WIDTH - UNDER_LIMIT_THREAT)
			{
				rand_x = SCREEN_WIDTH*0.7;
			}


			p_threat->SetRect(rand_x,SCREEN_HEIGHT - i*150);
			p_threat->set_y_val(2);


			AmoObject* p_amo = new AmoObject();
			p_threat->InitAmo(p_amo);
		}
  }

  unsigned int die_number = 0;
  unsigned int Point_value = 0;

  int ret_menu = SDLCommonFunc::ShowMenu(g_screen, g_font_menu);
  if (ret_menu == 1)
  {
	  is_quit = true;
  }

  while (!is_quit) 
  {
    while (SDL_PollEvent(&g_even)) 
    {
      if (g_even.type == SDL_QUIT)
      {
        is_quit = true;
        break;
      }
	  human_object.HandleInputAction(g_even);
    }
	
	//Apply Background
	bkgn_y +=2;
	SDLCommonFunc::ApplySurface(g_bkground, g_screen, 0, bkgn_y);
	SDLCommonFunc::ApplySurface(g_bkground,g_screen, 0, bkgn_y - SCREEN_HEIGHT); // di chuyen man hinh
	if (bkgn_y >= SCREEN_HEIGHT)
	{
		bkgn_y = 0;
	}
	

	//Show Player Power
	player_power.Render(g_screen);


	//Implement main object
	human_object.HandleMove();
	human_object.Show(g_screen);
	human_object.MakeAmo(g_screen);
	//Implement Threats object
	for (int j=0;j<NUM_THREATS;j++)
	{
		ThreatObject* p_threat = (p_threats+j); 
		if (p_threat)
		{
			p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
			p_threat->Show(g_screen);
			p_threat->MakeAmo(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);

			if ( SDL_Flip(g_screen) == -1) return 0;


			//

			bool is_col1 = false;
			std::vector<AmoObject*> amo_arr = p_threat->GetAmoList();
			for (int am = 0; am < amo_arr.size(); am++)
			{
			  AmoObject* p_amo = amo_arr.at(am);
			  if (p_amo)
			  {
				  is_col1 = SDLCommonFunc::CheckCollision(p_amo->GetRect(), human_object.GetRect());
				if (is_col1 == true)
				{
				  p_threat->ResetAmo(p_amo);
				  break;
				}
			  }
			}

			//check collision main and threats

			bool is_coll = SDLCommonFunc::CheckCollision(human_object.GetRect(), p_threat->GetRect());
			if (is_coll||is_col1)
			{
				for (int ex = 0 ; ex < 4; ex++)
				{
					int x_pos = (human_object.GetRect().x + human_object.GetRect().w*0.5) - EX_WIDTH*0.5;
					int y_pos = (human_object.GetRect().y + human_object.GetRect().h*0.5) - EX_HEIGHT*0.5;
					exp_main.set_frame(ex);
					exp_main.SetRect(x_pos,y_pos);
					exp_main.ShowEx(g_screen);
					

					int x_threat = (p_threat->GetRect().x + p_threat->GetRect().w*0.5) - EX_WIDTH*0.5;
					int y_threat = (p_threat->GetRect().y + p_threat->GetRect().h*0.5) - EX_HEIGHT*0.5;
					exp_threats.set_frame(ex);
					exp_threats.SetRect(x_threat,y_threat);
					exp_threats.ShowEx(g_screen);
					if ( SDL_Flip(g_screen) == -1)
					{
						delete [] p_threats;
						SDLCommonFunc::CleanUp();
						SDL_Quit();
						return 0;
					}
				}

				die_number ++;
				if(die_number <= 2)
				{
					SDL_Delay(500);
					human_object.SetRect(125,400);
					int rand_x = rand()%400;
					if (rand_x > SCREEN_WIDTH - UNDER_LIMIT_THREAT)
					{
						rand_x = SCREEN_WIDTH*0.7;
					}
					p_threat->SetRect(rand_x,0);
					player_power.Decrease();
					player_power.Render(g_screen);

					if (SDL_Flip(g_screen) == -1)
					{
						delete [] p_threats;
						delete [] p_threat;
						SDLCommonFunc::CleanUp();
						SDL_Quit();
						return 0;
					}
				}
				else 
				{
					if (MessageBox(NULL, L"GAME OVER", L"Infomation", MB_OK) == IDOK)
					{
						delete [] p_threats;
						SDLCommonFunc::CleanUp();
						SDL_Quit();
						return 1;
					}

				}

			}
			//check collision main amo and threats
			std::vector<AmoObject*> amo_list = human_object.GetAmoList();
			for (int im = 0 ; im < amo_list.size(); im++)
			{
				AmoObject* p_amo = amo_list.at(im);
				if (p_amo != NULL)
				{
					bool ret_coll = SDLCommonFunc::CheckCollision(p_amo->GetRect(), p_threat->GetRect());
					if (ret_coll)
					{
						Point_value++;
						for (int tx = 0; tx < 4;tx++)
						{
							int x_threat = p_amo->GetRect().x - EX_WIDTH*0.5;
							int y_threat = p_amo->GetRect().y - EX_HEIGHT*0.5;
							exp_threats.set_frame(tx);
							exp_threats.SetRect(x_threat,y_threat);
							exp_threats.ShowEx(g_screen);
						}
						if ( SDL_Flip(g_screen) == -1)
						{
							delete [] p_threats;
							SDLCommonFunc::CleanUp();
							SDL_Quit();
							return 0;
						}
						p_threat->Reset(SCREEN_HEIGHT - j*150);
						human_object.RemoveAmo(im);
					}
				}
			}

			//check threat amo vs main
		/*	std::vector<AmoObject*> p_amo_list_ = p_threats->GetAmoList();
			for (int ip = 0 ; ip < p_amo_list_.size(); ip++)
			{
				AmoObject* p_threats = p_amo_list_.at(ip);
				if (p_threats != NULL)
				{
					bool ret_coll1 = SDLCommonFunc::CheckCollision(human_object.GetRect(), p_threats->GetRect());
					if (ret_coll1)
					{
						for (int tx = 0; tx < 4;tx++)
						{
							int x_pos = (human_object.GetRect().x + human_object.GetRect().w*0.5) - EX_WIDTH*0.5;
							int y_pos = (human_obje``ct.GetRect().y + human_object.GetRect().h*0.5) - EX_HEIGHT*0.5;
							exp_main.set_frame(tx);
							exp_main.SetRect(x_pos,y_pos);
							exp_main.ShowEx(g_screen);
						}
						if ( SDL_Flip(g_screen) == -1)
						{
							delete [] p_threats;
							SDLCommonFunc::CleanUp();
							SDL_Quit();
							return 0;
						}
						p_threat->ResetAmo(p_threats);

						die_number ++;
						if(die_number <= 2)
						{
							SDL_Delay(500);
							human_object.SetRect(20,400);
							player_power.Decrease();
							player_power.Render(g_screen);

							if (SDL_Flip(g_screen) == -1)
							{
								delete [] p_threats;
								SDLCommonFunc::CleanUp();
								SDL_Quit();
								return 0;
							}
						}
						else 
						{
							if (MessageBox(NULL, L"GAME OVER", L"Infomation", MB_OK) == IDOK)
							{
								delete [] p_threats;
								SDLCommonFunc::CleanUp();
								SDL_Quit();
								return 1;
							}

						}
					}
				} 

			}  */

		}
	}




	//Show Point
	std::string val_str_point = std::to_string(Point_value);  //chuyen diem thanh so
	std::string strPoint("Point : ");
	strPoint += val_str_point;
	Point.SetText(strPoint);
	Point.CreateText(g_font_text, g_screen);


	//Update Screen
    if ( SDL_Flip(g_screen) == -1)
    return 0;
	}

    delete [] p_threats;
	SDLCommonFunc::CleanUp();
	SDL_Quit();

	return 1;
}