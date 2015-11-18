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

};  

class terrestres : public Enemigos{
public:
	terrestres(int tipo){
		cocos2d::Sprite *enemigo;
		if(tipo== 1){
			enemigo = Sprite::create("Mina.png");
		}else{
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