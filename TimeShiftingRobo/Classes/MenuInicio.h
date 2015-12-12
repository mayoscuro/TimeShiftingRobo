#ifndef __MENU_INICIO_H__
#define __MENU_INICIO_H__

#include "cocos2d.h"
#include "Juego.h"
#include <map>

#define COCOS2D_DEBUG 1;

USING_NS_CC;

class MenuInicio : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	cocos2d::Sprite *fondoMenu;

	cocos2d::Label *label;

	CREATE_FUNC(MenuInicio);

	void MenuInicio::goToJuego(Ref *pSender);

private:
	static std::map<cocos2d::EventKeyboard::KeyCode,
		std::chrono::high_resolution_clock::time_point> keys;

	double pos_menu_x = 1000;
	double pos_menu_y = 1000;
};
#endif
