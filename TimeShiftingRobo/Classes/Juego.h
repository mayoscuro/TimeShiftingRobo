#ifndef __JUEGO_H__
#define __JUEGO_H__

#include "cocos2d.h"
#include <map>
#include "Personaje.h"
#include "Mina.h"
#include "Enemigos.cpp"
#define COCOS2D_DEBUG 1;//COSAS PARA DEBUG DE COCOS...


USING_NS_CC;

class Juego : public cocos2d::Layer
{
public:
	
    static cocos2d::Scene* createScene();
	
    virtual bool init();

    bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
    double keyPressedDuration(cocos2d::EventKeyboard::KeyCode);
	void moverEnemigos(Vec2);
	
	cocos2d::Sprite *background;
	Personaje* personaje;
	Mina* mina;
	terrestres* enemigo1;
	terrestres* enemigo2;
	
	//Prueba debug info
	cocos2d::Label *label;
	//Prueba debug info

	CCRect	bbPersonaje;
	CCRect	bbMina;

	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

    CREATE_FUNC(Juego);

	
	 virtual void update(float delta) override;
private:
     static std::map<cocos2d::EventKeyboard::KeyCode,
        std::chrono::high_resolution_clock::time_point> keys;
	

	 bool explosionMina;
	 void lanzarMina();
	 void contador(float);
};

#endif 