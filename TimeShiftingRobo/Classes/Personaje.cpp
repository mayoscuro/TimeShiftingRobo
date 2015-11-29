#include "Personaje.h"
#include "Mina.h"

int numMina;
int duracionMina;
Personaje::Personaje(void)
{
	numMina = 0;
	duracionMina = 0;
	personajeSprite = Sprite::create("Personaje.jpg");
	this->addChild( personajeSprite );
}

void Personaje::personajeAnim(int direccion){
	if(direccion == 1){
		personajeSprite->setTexture("personajeIzq.jpg");//Si dirección = 1 personaje mira a la izquierda.
	}else if(direccion == 2){
		personajeSprite->setTexture("personaje.jpg");//Didirección = 2 personaje mira derecha.
	}
}

int Personaje::getTiempoMina(){
	return duracionMina;
}

void Personaje::setTiempoMina(int tiempo){
	duracionMina = tiempo;
}

void Personaje::usarMina(){
	numMina++;
}

void Personaje::retornaMina(){
	numMina--;
}

int Personaje::getNumMina(){
	return numMina;
}






