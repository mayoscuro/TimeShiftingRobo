#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Mina : public Layer
{
public:
	cocos2d::Sprite *mina;
	Mina(void);
	bool explotarMina(void);//Explota la mina y devuelve true si lo ha hecho correctamente;
private:
	
	
	
};
