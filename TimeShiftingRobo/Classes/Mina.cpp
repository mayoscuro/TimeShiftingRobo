#include "Mina.h"

Mina::Mina(void)
{
	mina = Sprite::create("Mina.png");
	this->addChild( mina );

}

bool Mina::explotarMina(){
	//Animación de explotar la mina;
	//this->removeAllChildren();
	return true;
}

