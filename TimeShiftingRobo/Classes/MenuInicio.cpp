#include "MenuInicio.h"

USING_NS_CC;

Scene* MenuInicio::createScene() {
	auto scene = Scene::create();

	MenuInicio* layer = MenuInicio::create();

	scene->addChild(layer);

	return scene;
}

bool MenuInicio::init() 
{
	if (!Layer::init())
	{
		return false;
	}

	pos_menu_x = 1000;
	pos_menu_y = 1000;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	fondoMenu = Sprite::create("MPrincipal.png");
	fondoMenu->setPosition(Point(pos_menu_x, pos_menu_y));

	this->addChild(fondoMenu);

	return true;
}

void MenuInicio::goToJuego(Ref * pSender)
{
	auto scene = Juego::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene));
	this->addChild(scene);
}
;