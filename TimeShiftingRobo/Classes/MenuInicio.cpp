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

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	fondoMenu = Sprite::create("MPrincipal.png");
	fondoMenu->setPosition(Point(pos_menu_x, pos_menu_y));

	this->addChild(fondoMenu);

	auto menuTitle = MenuItemImage::create("MPrincipal.png", "MPrincipal.png");
	menuTitle->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(menuTitle);

	auto playItem = MenuItemImage::create("Engranaje.png", "Engranaje.png", CC_CALLBACK_1(MenuInicio::goToJuego, this));
	playItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(playItem);

	auto menu = Menu::create(menuTitle, playItem, NULL);
	menu->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);
	addChild(menu, 1);
}

void MenuInicio::goToJuego(Ref * pSender)
{
	auto scene = Juego::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene));
	this->addChild(scene);
}
;