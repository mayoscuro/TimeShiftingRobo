#include "Juego.h"

USING_NS_CC;

//Cosas de colisiones buscar contactManager
Scene* Juego::createScene()
{
	auto scene = Scene::createWithPhysics();
    //auto scene = Scene::create();
	scene->getPhysicsWorld()->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL );
    
    Juego* layer = Juego::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());
	
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

	auto edgeBody = PhysicsBody::createEdgeBox( Size(visibleSize.width * 20 ,visibleSize.height / 1.2), PhysicsMaterial(0.0f,0.0f,1.0f) );
    
    auto edgeNode = Node::create();
    edgeNode ->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    edgeNode->setPhysicsBody( edgeBody );
	this->addChild( edgeNode );
		{
		background = Sprite::create( "Escenario1.jpg" );
		background->setPosition( Point( 6150,2750) );//Busacar sin numeros magicos
    
		this->addChild( background );

		personaje = new Personaje;
		personaje->setPosition( Point( visibleSize.width / 5 + origin.x, visibleSize.height / 4 + origin.y) );
		auto personajeBody = PhysicsBody::createBox(personaje->personajeSprite->getContentSize(),PhysicsMaterial(0.0f,0.0f,1.0f));
		personajeBody->setCollisionBitmask(1);
		personajeBody->setDynamic(true);
		personajeBody->setRotationEnable(false);
		personajeBody->setContactTestBitmask(true);
		personaje->setPhysicsBody( personajeBody );
		personaje->setPosition( Point( visibleSize.width / 5 + origin.x, visibleSize.height / 4 + origin.y) );
		this->addChild( personaje );
		
		
	}
	{
	//Prueba de visualizaci�n de enemigos:
		enemigo1 = new terrestres(1);
		enemigo1->setPosition( Point( visibleSize.width / 5 + origin.x +500, visibleSize.height / 4 + origin.y) );
		this->addChild( enemigo1 , 1 );
		enemigo2 = new terrestres(2);
		enemigo2->setPosition( Point( visibleSize.width / 5 + origin.x +1300, visibleSize.height / 6.5 + origin.y) );
		auto enemigo2Body = PhysicsBody::createBox(enemigo2->enemigo->getContentSize(),PhysicsMaterial(0,0,0));
		enemigo2Body->setCollisionBitmask(2);
		enemigo2Body->setContactTestBitmask(true);
		enemigo2Body->setRotationEnable(false);
		enemigo2Body->setDynamic(false);
		enemigo2->setPhysicsBody( enemigo2Body );
		this->addChild( enemigo2);
	//Fin Prueba

		//Prueba visualizaci�n de llaves:

		llave1 = new llaves(1);
		llave1->setPosition( Point( visibleSize.width / 5 + origin.x +1000, visibleSize.height / 4 + origin.y) );
		auto llave1Body = PhysicsBody::createBox(llave1->llave->getContentSize(),PhysicsMaterial(0,0,0));
		llave1Body->setCollisionBitmask(11);
		llave1Body->setContactTestBitmask(true);
		llave1Body->setDynamic(false);
		llave1->setPhysicsBody( llave1Body );
		this->addChild( llave1 );
		
		llave2 = new llaves(2);
		llave2->setPosition( Point( visibleSize.width / 5 + origin.x +2000, visibleSize.height / 4 + origin.y) );
		auto llave2Body = PhysicsBody::createBox(llave2->llave->getContentSize(),PhysicsMaterial(0,0,0));
		llave2Body->setCollisionBitmask(10);
		llave2Body->setContactTestBitmask(true);
		llave2Body->setDynamic(false);
		llave2->setPhysicsBody( llave2Body );
		this->addChild( llave2 );
		//Fin llaves

		//Aqu� va a ir el tema plataformas:
		plataforma = new Plataforma();
		plataforma->setPosition( Point( visibleSize.width / 5 + origin.x + 100 , visibleSize.height / 3 + origin.y) );
		auto plataformaBody = PhysicsBody::createBox(plataforma->plataforma->getContentSize(),PhysicsMaterial(0.0f,0.0f,1.0f));
		plataformaBody->setCollisionBitmask(7);
		plataformaBody->setContactTestBitmask(true);
		plataformaBody->setRotationEnable(false);
		plataformaBody->setDynamic(true);
		plataforma->setPhysicsBody( plataformaBody );
		this->addChild(plataforma);
		//Fin Plataformas.

		//Aqu� las pruebas del interruptor:
		interruptor = new Interruptor();
		interruptor->setPosition( Point( visibleSize.width / 5 + origin.x - 250 , visibleSize.height / 4 + origin.y) );
		auto interruptorBody = PhysicsBody::createBox(interruptor->interruptor->getContentSize(),PhysicsMaterial(0,0,0));
		interruptorBody->setCollisionBitmask(12);
		interruptorBody->setContactTestBitmask(true);
		interruptorBody->setRotationEnable(false);
		interruptorBody->setDynamic(false);
		interruptor->setPhysicsBody( interruptorBody );
		this->addChild(interruptor);
		//Fin de pruebas del interruptor

		mina = new Mina();
		mina->setPosition( personaje->getPosition() );
		this->addChild( mina);
		mina->setVisible(false);

		/*//Pruebas de puerta:
		puerta = new Puerta();
		puerta->setPosition( Point( visibleSize.width / 5 + origin.x - 250 , visibleSize.height / 4 + origin.y) );
		auto puertaBody = PhysicsBody::createBox(puerta->puerta->getContentSize(),PhysicsMaterial(0,0,0));
		puertaBody->setCollisionBitmask(13);
		puertaBody->setContactTestBitmask(true);
		puertaBody->setRotationEnable(false);
		puertaBody->setDynamic(false);
		puerta->setPhysicsBody( puertaBody );
		this->addChild(puerta);
		//*/

	}
	//Colisiones:
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Juego::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	//
	
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

    // Hacemos saber a cocos que tenemos una funci�n update
    this->scheduleUpdate();

	//Para llamar al timer:

		this->schedule(schedule_selector(Juego::contador), 1.0f);


	return true;

}

void Juego::setPhysicsWorld(PhysicsWorld *world) {
	sceneWorld = world;
	sceneWorld->setGravity(Vec2(0,-98.0f));
}

bool Juego::onContactBegin(PhysicsContact &contact){
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();
	//Comprobar si los body han colisionado:
	
	if(7 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()|| 
		1 == a->getCollisionBitmask() && 7 == b->getCollisionBitmask() ){
			personaje->setPlataformCollision(true);
	}else{
			personaje->setPlataformCollision(false);
	}
	
	if(3 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()|| 
		1 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask() ){
			label->setString("Colisiona, personaje, mina");
			eliminarMina();
			if(personaje->getOrientacion() == 2){
				accionSalto = JumpBy::create(2,Point(500, personaje->getPositionY()), 100, 1);//Para saltar??
				personaje->runAction(accionSalto);
			}else if(personaje->getOrientacion() == 1){
				accionSalto = JumpBy::create(2,Point(-500, personaje->getPositionY()), 100, 1);
				personaje->runAction(accionSalto);
			}
			
	}

	if(3 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask()|| 
		2 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask() ){
			eliminarMina();
			label->setString("Colisiona, enemigo mina");
			enemigo2->removeFromPhysicsWorld();
			enemigo2->removeAllChildrenWithCleanup(true);
			
	}
	
	if(1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask() ||
		2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()){
		/*personaje->removeFromPhysicsWorld();*/
		//personaje->removeAllChildrenWithCleanup(true);	
		//label->setString("Colisiona, con enemigo");
	}
	//Tema colisi�n con llaves:
	if(1 == a->getCollisionBitmask() && 10 == b->getCollisionBitmask() ||
		10 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()){//Encontrar llave 2
		llave2->setVisible(false);
		llave2->setRecogida(true);
		label->setString("LLave 1 encontrada");
		llave2->removeFromPhysicsWorld();
	}else if(1 == a->getCollisionBitmask() && 11 == b->getCollisionBitmask() ||
		11 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()){//Encontrar llave 1
		llave1->setVisible(false);
		llave1->removeFromPhysicsWorld();
		label->setString("LLave 2 encontrada");
		llave1->setRecogida(true);
	}
	//Colisi�n personaje/Interruptor:
	if(12 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()|| 
		1 == a->getCollisionBitmask() && 12 == b->getCollisionBitmask() ){
		label->setString("tocando el interruptor");
		interruptor->setEsActivo(true);
	}else{
		interruptor->setEsActivo(false);//Pasar al update haber si se soluciona.
	}
	return true;
}
//

 
void Juego::contador(float delta){
	if(personaje->isMina()){
		personaje->setTiempoMina(personaje->getTiempoMina() + 1);
	}
	eliminarMina();
	
}

//Funciones de teclado:
bool Juego::isKeyPressed(EventKeyboard::KeyCode code) {
    if(keys.find(code) != keys.end())
        return true;
    return false;
}

//Para el scroll de la pantalla
void Juego::centerViewport()	{	
	if(personaje->getPositionX() > personaje->getPositionX()/4.0f ){//Esto funciona, pero...xD
		CCSize	screenSize	=	CCDirector::sharedDirector()->getWinSize();	
						
		float x	= screenSize.width/2.0	- personaje->getPosition().x;	
		float y	= screenSize.height/4.0	- personaje->getPosition().y;	
						
		this->setPosition(ccp(x,	y));
	}
}

void Juego::update(float delta) {
    // Funci�n que comprueba si las teclas A y D estan siendo pulsadas y mueven al personaje a derecha o izquierda.
    Node::update(delta);
	Vec2 loc = personaje->getPosition();
	Vec2 locEscenario = background->getPosition();
	Vec2 locEnemigo = enemigo1->getPosition();
	moverEnemigos(locEnemigo);
	centerViewport();
	if(isKeyPressed(EventKeyboard::KeyCode::KEY_A)) {
		personaje->personajeAnim(1);//Para que el personaje mire a la izquierda.
		personaje->setPosition(loc.x - 3,loc.y);
    }else if(isKeyPressed(EventKeyboard::KeyCode::KEY_D)){
		personaje->personajeAnim(2);
		personaje->setPosition(loc.x + 3,loc.y);
	}
	//Personaje en una plataforma//Esto hay que apa�arlo de alguna forma.
	/*if(personaje->getPlataformCollision()){
		personaje->setPosition(Vec2(personaje->getPositionX(), plataforma->getPositionY()*1.6));
	}*/

	//Mina va con el personaje:
	if(!personaje->isMina()){
		mina->setPosition(Vec2(personaje->getPositionX() + 130, personaje->getPositionY()));
	}
	//Abrir la puerta si:
	/*if(llave1->esRecigida() && !llave2->esRecigida() ){

	}else if(llave2->esRecigida() && !llave1->esRecigida()){
	
	}else*/ if(llave1->esRecigida() && llave2->esRecigida()){
		//label->setString("Puerta abierta");//Esto funciona, pero a la hora del debug lo quito.
	}

	plataforma->rutaPlataforma();

}
// Cocos requiere que createScene sea estatico, Esto es para crear otro miembro statico.
std::map<cocos2d::EventKeyboard::KeyCode,
        std::chrono::high_resolution_clock::time_point> Juego::keys;

//Funci�n que controla las teclas de un solo pulsado:
void Juego::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch(keyCode){
	case EventKeyboard::KeyCode::KEY_S:
		lanzarMina(1);//lanzarMina modo tirar lejos
		break;
	/*case EventKeyboard::KeyCode::KEY_D:
		personaje->setOrientacion(2);
		break;
	case EventKeyboard::KeyCode::KEY_A:
		personaje->setOrientacion(1);
		break;*/
	case EventKeyboard::KeyCode::KEY_W:
		lanzarMina(2);//lanzarMina modo dejar caer.
		break;
	case EventKeyboard::KeyCode::KEY_SPACE://Boton de acci�n
		if(interruptor->getEsActivo()){
			label->setString("Puente abierto");
			interruptor->removeFromPhysicsWorld();//Eliminar las fisica del interruptor, para que no pueda activar 10000000 puentes
			//FALTA:
			//crear el puente
			//Y creo que ya.
		}
		break;
	}
}

//Funci�n que lleva el tema del lanzamiento de minas:
void Juego::lanzarMina(int tipo){	
	if((personaje->getNumMina()) < 1){
		personaje->setIsMina(true);
		if(tipo == 1){
			lanzamientoDeMina = JumpBy::create(1,Point(400, 0), 50, 1);//Para saltar??
			mina->runAction(lanzamientoDeMina);
		}else{
			mina->setPosition(personaje->getPosition());
		}
		auto minaBody = PhysicsBody::createBox(mina->mina->getContentSize()/15,PhysicsMaterial(0.0f,0.0f,1.0f));
		minaBody->setCollisionBitmask(3);
		minaBody->setContactTestBitmask(true);
		minaBody->setDynamic(true);
		mina->setPhysicsBody( minaBody );
		mina->setVisible(true);
		personaje->usarMina();//numMina++

	}	
}

void Juego::eliminarMina(){
	//Para que la mina desaparezca cuando explote:
		if(personaje->getTiempoMina() >= 3 && personaje->isMina() && personaje->getNumMina() > 0){
			personaje->setIsMina(false);
			personaje->setTiempoMina(0);	
			personaje->retornaMina();//Resta 1 al numero de minas lanzadas.
			//explosionMina = mina->explotarMina();//Por ahora no hace nada, pero hara la animaci�n
			mina->removeFromPhysicsWorld();
			mina->setVisible(false);//Se aproxima a lo que quiero.
			label->setString("borrado");
			//		
		}
}



//Funci�n del movimiento del enemigo 1 (Abr�a que hacer que funcionar� para todos los enemigos(tal vez pasandola a la clase enemigos...))
void Juego::moverEnemigos(Vec2 locEnemigo){
	if(enemigo1->pasosDer < 100 ){
		enemigo1->setPosition(locEnemigo.x + 3,locEnemigo.y);
		enemigo1->pasosDer++;
		enemigo1->animEnemigo(1);
	}else if(enemigo1->pasosIzq > 0){
		enemigo1->setPosition(locEnemigo.x - 3,locEnemigo.y);
		enemigo1->pasosIzq--;
		enemigo1->animEnemigo(2);
	}else{
		enemigo1->pasosIzq = 100;
		enemigo1->pasosDer = 0;
	}
}