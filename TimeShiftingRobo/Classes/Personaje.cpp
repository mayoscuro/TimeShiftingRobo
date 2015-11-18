#include "Personaje.h"
#include "Mina.h"


Personaje::Personaje(void)
{
	personaje = Sprite::create("Personaje.jpg");
	this->addChild( personaje );
}

