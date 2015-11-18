#include "Juego.h"
//#include "LectorPersonaje.h"

USING_NS_CC;

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
