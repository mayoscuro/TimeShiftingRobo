#include "MenuInicio.h"

USING_NS_CC;

Scene* MenuInicio::createScene() {
	auto scene = Scene::create();

	auto layer = MenuInicio::create();

	scene->addChild(layer);

	return scene;
}

bool MenuInicio::init() 
{
	if (!Layer::init())
	{
		return false;
	}

	pos_menu_x = 0;
	pos_menu_y = 0;

	pos_boton_x = 10;
	pos_boton_y = 80;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	fondoMenu = Sprite::create("MPrincipal.png");
	fondoMenu->setPosition(Point(pos_menu_x, pos_menu_y));

	addChild(fondoMenu, 0);

	auto menuTitle = MenuItemImage::create("MPrincipal.png", "MPrincipal.png"); //hacer addchild en vez de boton
	menuTitle->setScale(menuTitle->getScale() / 2 + 0.1);
	menuTitle->setPosition(Point(pos_menu_x, pos_menu_y));
	
	
	auto boton = MenuItemImage::create("Engranaje.png", "Engranaje.png", CC_CALLBACK_1(MenuInicio::goToJuego, this));
	boton->setScale(boton->getScale() / 2 + 0.1);
	boton->setPosition(Point(-pos_boton_x, -pos_boton_y));
	

	auto menu = Menu::create(menuTitle, boton, NULL);
	
	//menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);


	addChild(menu, 1);
	return true;
}

void MenuInicio::goToJuego(Ref * pSender)
{
	auto scene = Juego::createScene();
	//Director::getInstance()->replaceScene(TransitionFade::create(0.5,scene));
	Director::getInstance()->replaceScene(scene);
}
;