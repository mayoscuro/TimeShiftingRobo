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
		int tipo;
		int pasosIzq;
		int pasosDer;

};  

class terrestres : public Enemigos{
public:
	terrestres(int tipo){
		pasosIzq = 50;
		pasosDer = 0;
		cocos2d::Sprite *enemigo;
		if(tipo== 1){
			this->tipo = 1;
			enemigo = Sprite::create("Mina.png");
		}else{
			this->tipo = 2;
			enemigo = Sprite::create("CloseNormal.png");
		}
		this->addChild( enemigo );
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