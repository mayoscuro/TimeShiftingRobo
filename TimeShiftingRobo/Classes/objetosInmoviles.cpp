#include "cocos2d.h"
USING_NS_CC;
class ObjetosInmoviles : public cocos2d::Layer {  
    public:  
		ObjetosInmoviles(int){};
		ObjetosInmoviles(){};
		float posicionX;
		float posicionY;

};  

class llaves : public ObjetosInmoviles{
private:
	bool recogida;
public:
	cocos2d::Sprite *llave;

	llaves(int numero){
		llave = Sprite::create("E_BipedoDer.png");//Sustituir por el dibujo de llave
		recogida = false;
		if(numero == 1){
			//posicionX = ;
			//posicionY = ;
		}else{
			//posicionX = ;
			//posicionY = ;
		}
		this->addChild(llave);
	}
	
	bool esRecigida(){
		return recogida;
	}

	void setRecogida(bool estaRecogida){
		this->recogida = estaRecogida;
	}

	
};
//Pasar a objetosMoviles
class Plataforma : public ObjetosInmoviles{
private:
	int alturasum;
	int alturarest;
public:
	cocos2d::Sprite *plataforma;
	Plataforma(){
		alturasum = 0;
		alturarest = 70;
		plataforma = Sprite::create("Plataforma.png");//Sustituir por el dibujo de la plataforma
		this->addChild(plataforma);
	}

	void rutaPlataforma(){
		if(alturasum < 70){
			this->setPosition(this->getPositionX(), this->getPositionY() + 2);
			alturasum++;
		}else if(alturarest > 0){
			this->setPosition(this->getPositionX(), this->getPositionY() - 2);
			alturarest--;
		}else{
			alturasum = 0;
			alturarest = 70;
		}
	}
};

class Interruptor : public ObjetosInmoviles{
private:
	bool activo;
public:
	cocos2d::Sprite *interruptor;

	Interruptor(){
		interruptor = Sprite::create("Boton_Desactivado.png");//Cambiar por la imagen que sea.
		activo = false;
		interruptor->isFlipX();
		this->addChild(interruptor);
	}
	bool getEsActivo(){
		return activo;
	}
	void setEsActivo(bool activado){
		this->activo = activado;
	}

};
//Pasar a Objetosmoviles
class Puerta : public ObjetosInmoviles{
private:
	bool personajeEnPuerta;
public:
	cocos2d::Sprite *puerta;

	Puerta(){
		puerta = Sprite::create("Puerta_Amarilla.png");//Cambiar por la imagen que sea.
		this->addChild(puerta);
	}

	void personajeEnLaPuerta(bool personajeEnPuerta){
		this->personajeEnPuerta = personajeEnPuerta; 
	}

	bool isPersoanje(){
		return personajeEnPuerta;
	}
};

class laser : public ObjetosInmoviles{
private:
	bool activo;
public:
	cocos2d::Sprite *laserSprite;
	laser(){
		laserSprite = Sprite::create("Laser_Apagado.png");
		this->addChild(laserSprite);
	}
	void setActive(bool activar){
		this->activo = activar; 
		activarLaser(this->activo);
	}

	bool isActive(){
		return activo;
	}

	void activarLaser(bool isActive){
		if(isActive){
			laserSprite->setTexture("Laser_Normal_2.png");
		}else{
			laserSprite->setTexture("Laser_Apagado.png");
		}
	}


};