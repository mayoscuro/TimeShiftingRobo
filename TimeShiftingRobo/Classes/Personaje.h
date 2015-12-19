#pragma once

#include "cocos2d.h"
#include <map>

USING_NS_CC;

class Personaje : public Layer
{
public:
	enum State {
        Quieto, Corriendo, Saltando
    };
	cocos2d::Sprite *personajeSprite;
	int getNumMina(void);
	int getTiempoMina(void);
	void setTiempoMina(int);
	void usarMina(void);
	void retornaMina(void);
	void personajeAnim(int);//Encargado de cambiar el sprite del personaje.
	bool isMina();
	void setIsMina(bool);
	void setOrientacion(int);
	int getOrientacion();

	//Cosas de fisicas del jugador:
	State state;
 
	bool facingRight;
	bool grounded;
	float stateTime;
	float groundedPosition;
 
	Point position;
	Point velocity;
	//

 	Personaje(void);

private:
	int vida;
	int numMina;
	int duracionMina;
	bool minaApear;
	int orientacion;
	
};
