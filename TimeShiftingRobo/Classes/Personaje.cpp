#include "Personaje.h"


Personaje::Personaje(void)
{
	personaje = Sprite::create("Personaje.jpg");
	this->addChild( personaje );
}