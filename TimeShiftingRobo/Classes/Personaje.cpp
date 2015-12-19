#include "Personaje.h"
#include "Mina.h"

int numMina;
int duracionMina;
Personaje::Personaje(void)
{

	state = Personaje::State::Quieto;
	facingRight = true;
	grounded = true;
	groundedPosition = this->getPositionY();
	stateTime = 0;
	velocity = Point(0,0);
	position = Point();

	vida = 3;
	numMina = 0;
	duracionMina = 0;
	minaApear = false;
	orientacion = 2;
	personajeSprite = Sprite::create("Robo.png");
	this->addChild( personajeSprite );
}

void Personaje::personajeAnim(int direccion){
	if(direccion == 1){
		//personajeSprite->setTexture("RoboIzq.png");//Si dirección = 1 personaje mira a la izquierda.
		personajeSprite->setFlippedX(true);
		orientacion = 1;
	}else if(direccion == 2){
		//personajeSprite->setTexture("Robo.png");//Didirección = 2 personaje mira derecha.
		personajeSprite->setFlippedX(false);
		orientacion = 2;
	}
}

int Personaje::getOrientacion(){
	return orientacion;
}

void Personaje::setOrientacion(int orientacion){
	this->orientacion = orientacion;
}

bool Personaje::isMina(){
	return minaApear;
}

//Geters y seters relacionados con las minas:
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





