#ifndef __JUEGO_H__
#define __JUEGO_H__

#include "cocos2d.h"
#include <map>
#include "Personaje.h"
#include "Mina.h"
#include "Enemigos.cpp"
#include "ObjetosInmoviles.cpp"

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
	cocos2d::Sprite *personajeSprite;
	Mina* mina;
	terrestres* enemigo1;
	terrestres* enemigo2;
	cocos2d::Sprite *enemigo2Sprite;
	JumpBy* accionSalto;
	JumpBy* lanzamientoDeMina;
	
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
	 void lanzarMina(int);
	 void eliminarMina();
	 void contador(float);
	 void saltar(float);
	 llaves* llave1;
	 llaves* llave2;
	 Plataforma* plataforma;
	 Interruptor* interruptor;
	 Puerta* puerta;

	 void centerViewport(void);
	 
	 //Colisiones:
	 private:
		 //PhysicsJointFixed* jointPlataform;
		PhysicsWorld *sceneWorld;
		/*PhysicsBody  *body;
		PhysicsBody  *body2;*/
	public:
		void setPhysicsWorld(PhysicsWorld *world);
		bool onContactBegin(PhysicsContact &contact);
		void onContactSeparate(PhysicsContact &contact);
	//
};

#endif 