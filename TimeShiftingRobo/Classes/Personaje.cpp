#include "Personaje.h"
#include "Mina.h"

int numMina;
int duracionMina;
Personaje::Personaje(void)
{
	numMina = 0;
	duracionMina = 0;
	salto = 0;
	maxAltura = 0;
	//salto = false;
	enAire = false;
	minaApear = false;
	personajeSprite = Sprite::create("Robo.png");
	this->addChild( personajeSprite );
}

void Personaje::personajeAnim(int direccion){
	if(direccion == 1){
		personajeSprite->setTexture("RoboIzq.png");//Si dirección = 1 personaje mira a la izquierda.
	}else if(direccion == 2){
		personajeSprite->setTexture("Robo.png");//Didirección = 2 personaje mira derecha.
	}
}

void Personaje::setMaxAltura(int alturaMaxima){
	this->maxAltura = alturaMaxima;
}

int Personaje::getMaxAltura(){
	return maxAltura;
}

bool Personaje::getEnAire(){
	return enAire;
}

void Personaje::setEnAire(bool esEnAire){
	this->enAire = esEnAire;
}

bool Personaje::isMina(){
	return minaApear;
}

/*int Personaje::getSalto(){
	return salto;
}

void Personaje::setSalto(int salto){
	this->salto = salto;
}*/

void Personaje::setIsMina(bool isMina){
	minaApear = isMina;
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






