#pragma once

#include "cocos2d.h"
#include <map>

USING_NS_CC;

class Personaje : public Layer
{
public:
	cocos2d::Sprite *personajeSprite;
	int getNumMina(void);
	int getTiempoMina(void);
	void setTiempoMina(int);
	void usarMina(void);
	void retornaMina(void);
	void personajeAnim(int);//Encargado de cambiar el sprite del personaje.
 	Personaje(void);

private:
	int numMina;
	int duracionMina;
	
	
};
