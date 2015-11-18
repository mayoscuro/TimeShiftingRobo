#include "Juego.h"
//#include "LectorPersonaje.h"

USING_NS_CC;

int maxMina = 0;
Scene* Juego::createScene()
{
    auto scene = Scene::create();
    
    Juego* layer = Juego::create();
	
    scene->addChild(layer);
    return scene;
}

bool Juego::init()
{
    if ( !Layer::init() )
    {
        return false;
    }



	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    background = Sprite::create( "Escenario1.jpg" );
    background->setPosition( Point( 5800,2600) );
    
    this->addChild( background );
	
	personaje = new Personaje;
	personaje->setPosition( Point( visibleSize.width / 5 + origin.x, visibleSize.height / 4 + origin.y) );
	this->addChild( personaje );
	//Prueba de visualización de enemigos:
	enemigo1 = new terrestres(1);
	enemigo1->setPosition( Point( visibleSize.width / 5 + origin.x +500, visibleSize.height / 4 + origin.y) );
	this->addChild( enemigo1 );
	enemigo2 = new terrestres(2);
	enemigo2->setPosition( Point( visibleSize.width / 5 + origin.x+1000, visibleSize.height / 4 + origin.y) );
	this->addChild( enemigo2 );
	//Fin Prueba

	//Teclado Mantener pulsado:
	auto eventListener = EventListenerKeyboard::create();
	Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);
    eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event){

        if(keys.find(keyCode) == keys.end()){
            keys[keyCode] = std::chrono::high_resolution_clock::now();
        }
    };
    eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event){
        // remove the key.  std::map.erase() doesn't care if the key doesnt exist
        keys.erase(keyCode);
    };

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener,this);

    // Hacemos saber a cocos que tenemos una función update
    this->scheduleUpdate();
	
	return true;

}

//Funciones de teclado:
bool Juego::isKeyPressed(EventKeyboard::KeyCode code) {
    //Devuelve true si la tecla esta siendo pulsada:
    if(keys.find(code) != keys.end())
        return true;
    return false;
}

double Juego::keyPressedDuration(EventKeyboard::KeyCode code) {
    if(!isKeyPressed(EventKeyboard::KeyCode::KEY_A) || !isKeyPressed(EventKeyboard::KeyCode::KEY_D))
        return 0;  // SI LAS TECLAS NO SE PULSAN NO TIENE DURACIÓN.

    // Devuelve el tiempo transcurrido de pulsado de las teclas.
    return std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::high_resolution_clock::now() - keys[code]).count();
}

void Juego::update(float delta) {
    // Función que comprueba si las teclas A y D estan siendo pulsadas y mueven al personaje a derecha o izquierda.
    Node::update(delta);
	Vec2 loc = personaje->getPosition();
	Vec2 locEscenario = background->getPosition();
	if(isKeyPressed(EventKeyboard::KeyCode::KEY_A)) {
		//personaje->setTexture("Personajeizq.png");
		personaje->setPosition(loc.x - 3,loc.y);
		background->setPosition(locEscenario.x,locEscenario.y);
		lanzarMina();//Lo pongo aquí por probar...
    }
	else if(isKeyPressed(EventKeyboard::KeyCode::KEY_D)){
		//personaje->setTexture("Personaje.jpg");
		personaje->setPosition(loc.x + 3,loc.y);
		background->setPosition(locEscenario.x ,locEscenario.y);
	}
}
// Cocos requiere que createScene sea estatico, Esto es para crear otro miembro statico.
std::map<cocos2d::EventKeyboard::KeyCode,
        std::chrono::high_resolution_clock::time_point> Juego::keys;
void::Juego::lanzarMina(){
	if(maxMina <= 1){
		Vec2 posmina = personaje->getPosition();
		Mina* mina = new Mina();
		this->addChild( mina );
		maxMina++;
		mina->setPosition(posmina.x + 100,posmina.y - 90);
		explosionMina = mina->explotarMina();
		//if(explosionMina = true)delete mina;//El else es un petardazo brutal por razónes que pueden surgir xD
	}
}