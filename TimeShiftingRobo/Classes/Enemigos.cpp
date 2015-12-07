#include "cocos2d.h"
USING_NS_CC;
class Enemigos : public cocos2d::Layer {  
    public:  
		 Enemigos(int){};
		 Enemigos(){};
        //virtual ~Enemigos(){};  
		int movimiento;
		virtual void ruta(){};
		virtual void perseguir(){};
		virtual void atacar(){};
		virtual void movNoMov(){};
		virtual void animEnemigo(int){};
		int tipo;
		int pasosIzq;
		int pasosDer;

};  

class terrestres : public Enemigos{
public:
	cocos2d::Sprite *enemigo;
	terrestres(int tipo){
		pasosIzq = 100;
		pasosDer = 0;
		if(tipo== 1){
			this->tipo = 1;
			enemigo = Sprite::create("E_BipedoDer.png");
		}else{
			this->tipo = 2;
			enemigo = Sprite::create("la.png");

		}
		this->addChild( enemigo);
	}

	void animEnemigo(int direccion){
		if(direccion == 1){
			enemigo->setTexture("E_BipedoDer.png");
		}else{
			enemigo->setTexture("E_Bipedo.png");
		}
	}

	void terrestres::ruta(){
		

	}
};

/*  ejemplos clases que implementan custom interfaces xD
class ClassA : public Interface{  
    public:  
        int method(int param) const{return param+1;};  
};  
  
class ClassB : public Interface{  
    public:  
        int method(int param) const{return param+2;};  
};  
*/