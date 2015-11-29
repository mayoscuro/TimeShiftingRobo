#include "Juego.h"
//#include "LectorPersonaje.h"

USING_NS_CC;
//Cosas para las colisiones:
/*Juego::~Juego()//Destructor
{
  if (_colPersonaje)
  {
    _colPersonaje->release();
    _colPersonaje = NULL;
  }

  if (_colMina)
  {
    _colMina->release();
    _colMina = NULL;
  }

  // cpp don't need to call super dealloc
  // virtual destructor will do this
}

Juego::Juego()//Constructor
:_colPersonaje(NULL)
,_colMina(NULL)
{
}   
//Fin de cosas para las colisiones.*/

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


	/*//prueba de colisiones:
	_colPersonaje = new CCArray;
	_colMina = new CCArray;
	//Fin de prueba de colisiones.*/


	//intento de añadir fisicas(solo colisionadores y poco más xD)
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0,0));
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	//FIN


	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    background = Sprite::create( "Escenario1.jpg" );
    background->setPosition( Point( 5800,2600) );
    
    this->addChild( background );
	
	personaje = new Personaje;
	personaje->setPosition( Point( visibleSize.width / 5 + origin.x, visibleSize.height / 4 + origin.y) );
	this->addChild( personaje );
	
	/*//Cosas de colisiones:
	personaje->setTag(1);
	_colPersonaje->addObject(personaje);
	//Fin de cosas de colisiones.*/

	//Prueba de visualización de enemigos:
	enemigo1 = new terrestres(1);
	enemigo1->setPosition( Point( visibleSize.width / 5 + origin.x +500, visibleSize.height / 4 + origin.y) );
	this->addChild( enemigo1 );
	enemigo2 = new terrestres(2);
	enemigo2->setPosition( Point( visibleSize.width / 5 + origin.x+1000, visibleSize.height / 4 + origin.y) );
	this->addChild( enemigo2 );
	//Fin Prueba

	/*//COSA DE CAMARA(PRUEBA):
	auto s = Director::getInstance()->getWinSize();
	auto camera = Camera::createPerspective(60, (GLfloat)s.width/s.height, 1, 1000);*/

	/*// set parameters for camera
	camera->setPosition3D(Vec3(0, 100, 100));
	camera->lookAt(Vec3(0, 0, 0), Vec3(0, 0, 0));

	addChild(camera); //add camera to the scene	
	FIN DE COSAS DE CAMARA(PRUEBA)*/

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

	//Botones de un solo pulsado
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Juego::onKeyPressed ,this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	//

	label = Label::create("timer","\fonts\Arial.ttf",20);
	label->setPosition( Point( visibleSize.width / 5 + origin.x, visibleSize.height / 4 + origin.y) );
	label->setColor(Color3B(255,0,0));
	this->addChild(label);

	//TIMMER FALLIDO:
	//this->schedule(schedule_selector(Juego::lanzarMina),1.0f);

	//Cosa para lanzar mina:
	//auto keyboardListener = EventListenerKeyboard::create();
	//keyboardListener->onKeyPressed = CC_CALLBACK_2(Juego::lanzarMina, this);

    // Hacemos saber a cocos que tenemos una función update
    this->scheduleUpdate();

	//Para llamar al timer:
	this->schedule(schedule_selector(Juego::contador), 10.0f);//Contador que aun no va    [[[[¡¡¡¡¡¡ARREGLAAAAAAAR!!!!!]]]]



	return true;

}

//Contador que aun no va    [[[[¡¡¡¡¡¡ARREGLAAAAAAAR!!!!!]]]]
void Juego::contador(float delta){
	personaje->setTiempoMina(personaje->getTiempoMina() + 1);
}

//Funciones de teclado:
bool Juego::isKeyPressed(EventKeyboard::KeyCode code) {
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

//Para el scroll de la pantalla
void Juego::centerViewport()	{	
	CCSize	screenSize	=	CCDirector::sharedDirector()->getWinSize();	
						
	float	x	=	screenSize.width/2.0	-	personaje->getPosition().x;	
	float	y	=	screenSize.height/4.0	-	personaje->getPosition().y;	
						
	this->setPosition(ccp(x,	y));	
}

void Juego::update(float delta) {
    // Función que comprueba si las teclas A y D estan siendo pulsadas y mueven al personaje a derecha o izquierda.
    Node::update(delta);
	Vec2 loc = personaje->getPosition();
	Vec2 locEscenario = background->getPosition();
	Vec2 locEnemigo = enemigo1->getPosition();
	moverEnemigos(locEnemigo);
	centerViewport();
	if(isKeyPressed(EventKeyboard::KeyCode::KEY_A)) {
		personaje->personajeAnim(1);//Para que el personaje mire a la izquierda.
		personaje->setPosition(loc.x - 3,loc.y);
		background->setPosition(locEscenario.x,locEscenario.y);
    }
	else if(isKeyPressed(EventKeyboard::KeyCode::KEY_D)){
		personaje->personajeAnim(2);
		personaje->setPosition(loc.x + 3,loc.y);
		background->setPosition(locEscenario.x ,locEscenario.y);
	}
}
// Cocos requiere que createScene sea estatico, Esto es para crear otro miembro statico.
std::map<cocos2d::EventKeyboard::KeyCode,
        std::chrono::high_resolution_clock::time_point> Juego::keys;

void Juego::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch(keyCode){
	case EventKeyboard::KeyCode::KEY_S:
		lanzarMina();
		break;
	}
}

void Juego::lanzarMina(){	
	if((personaje->getNumMina()) < 2){
		Mina* mina = new Mina();
		Vec2 posmina = personaje->getPosition();
		this->addChild( mina );
		mina->setPosition(posmina.x + 100,posmina.y - 90);
		personaje->usarMina();
		
		/*//Cosas de colisiones:
		mina->setTag(2);
		_colMina->addObject(mina);
		//Fin de cosas de colisiones.*/

		if(personaje->getTiempoMina() >= 5){
			personaje->retornaMina();
			explosionMina = mina->explotarMina();
			removeChild(mina);
			personaje->setTiempoMina(0);
		}	
	}
}

void Juego::moverEnemigos(Vec2 locEnemigo){
	if(enemigo1->pasosDer < 50 ){
		enemigo1->setPosition(locEnemigo.x + 3,locEnemigo.y);
		enemigo1->pasosDer++;
	}else if(enemigo1->pasosIzq > 0){
		enemigo1->setPosition(locEnemigo.x - 3,locEnemigo.y);
		enemigo1->pasosIzq--;
	}else{
		enemigo1->pasosIzq = 50;
		enemigo1->pasosDer = 0;
	}
}