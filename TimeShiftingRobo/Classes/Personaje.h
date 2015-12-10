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
	bool isMina();
	void setIsMina(bool);
	bool getEnAire();
	void setEnAire(bool);
	void setMaxAltura(int);
	int getMaxAltura();
 	Personaje(void);

private:
	int numMina;
	int duracionMina;
	bool minaApear;
	bool enAire;
	int maxAltura;
	int salto;
	
	
	
};
