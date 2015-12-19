#include "Juego.h"

USING_NS_CC;

//Cosas de colisiones buscar contactManager

void Juego::setPhysicsWorld(PhysicsWorld *world){
	world->setGravity(Vec2::ZERO);
	//addChild(world);
}
Scene* Juego::createScene()
{
	auto scene = Scene::createWithPhysics();
    //auto scene = Scene::create();
	scene->getPhysicsWorld()->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL );
	scene->getPhysicsWorld()->setGravity(Vec2::ZERO);
    
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
	//Puntos de colisión del suelo:
	auto edgeBody = PhysicsBody::createEdgeBox( Size(visibleSize.width * 2.15 ,visibleSize.height / 1.1), PhysicsMaterial(0.0f,0.0f,1.0f) );
    edgeBody->setCollisionBitmask(100);
    edgeNode = Node::create();
    edgeNode ->setPosition( Point( 660,-280) );
    edgeNode->setPhysicsBody( edgeBody );
	this->addChild( edgeNode );

	auto edgeBody1 = PhysicsBody::createEdgeBox( Size(1150 ,visibleSize.height / 1.1), PhysicsMaterial(0.0f,0.0f,1.0f) );
 
    auto edgeNode1 = Node::create();
    edgeNode1 ->setPosition( Point( 3070,100) );
    edgeNode1->setPhysicsBody( edgeBody1 );
	this->addChild( edgeNode1 );

	auto edgeBody2 = PhysicsBody::createEdgeBox( Size(5400,visibleSize.height / 1.1), PhysicsMaterial(0.0f,0.0f,1.0f) );
    
    auto edgeNode2 = Node::create();
    edgeNode2 ->setPosition( Point( 7000,-280) );
    edgeNode2->setPhysicsBody( edgeBody2 );
	this->addChild( edgeNode2 );

	auto edgeBody3 = PhysicsBody::createEdgeBox( Size(100,300), PhysicsMaterial(0.0f,0.0f,1.0f) );
    
    auto edgeNode3 = Node::create();
    edgeNode3 ->setPosition( Point( 9635,250) );
    edgeNode3->setPhysicsBody( edgeBody3 );
	this->addChild( edgeNode3 );

	auto edgeBody4 = PhysicsBody::createEdgeBox( Size(5400, 380), PhysicsMaterial(0.0f,0.0f,1.0f) );
    
    auto edgeNode4 = Node::create();
    edgeNode4 ->setPosition( Point( 7000,630) );
    edgeNode4->setPhysicsBody( edgeBody4 );
	this->addChild( edgeNode4 );

	auto edgeBody5 = PhysicsBody::createEdgeBox( Size(100, 1000), PhysicsMaterial(0.0f,0.0f,1.0f) );
    
    auto edgeNode5 = Node::create();
    edgeNode5 ->setPosition( Point( 7545,1350) );
    edgeNode5->setPhysicsBody( edgeBody5 );
	this->addChild( edgeNode5 );
	
	//Colisión entrada:
	auto edgeBody6 = PhysicsBody::createEdgeBox( Size(10, 3000), PhysicsMaterial(0.0f,0.0f,1.0f) );
    
    auto edgeNode6 = Node::create();
    edgeNode6 ->setPosition( Point( -600,0) );
    edgeNode6->setPhysicsBody( edgeBody6 );
	this->addChild( edgeNode6 );
	//Fin colisión entrada.

	auto edgeBody8 = PhysicsBody::createEdgeBox( Size(500000, 200), PhysicsMaterial(0.0f,0.0f,1.0f) );

    auto edgeNode8 = Node::create();
    edgeNode8 ->setPosition( Point( -600,-500) );
    edgeNode8->setPhysicsBody( edgeBody8 );
	this->addChild( edgeNode8 );

	/*auto edgeBody7 = PhysicsBody::createEdgeBox( Size(1000, 300), PhysicsMaterial(0.0f,0.0f,1.0f) );
    
    auto edgeNode7 = Node::create();
    edgeNode7 ->setPosition( Point( 6045,1350) );
    edgeNode7->setPhysicsBody( edgeBody7 );
	this->addChild( edgeNode7 );*/

	//Fin de puntos de colisión del suelo
		{
		background = Sprite::create( "Escenario1.png" );
		background->setPosition( Point( 10250, 2000) );//Busacar sin numeros magicos
    
		this->addChild( background );

		//Pruebas de puerta1:
		puerta1 = new Puerta();
		puerta1->setPosition( Point( visibleSize.width / 5 + origin.x + 3850 , visibleSize.height / 4 + origin.y + 2820) );
		this->addChild(puerta1);
		//

		//Pruebas de puerta2:
		puerta2 = new Puerta();
		puerta2->setPosition( Point( visibleSize.width / 5 + origin.x + 3475 , visibleSize.height / 4 + origin.y + 2820) );
		this->addChild(puerta2);
		//

		//Pruebas laser:
		laser1 = new laser();
		laser1->setPosition(Point(visibleSize.width / 5 + origin.x + 4850 , visibleSize.height / 4 + origin.y + 1119));
		this->addChild(laser1);
		//

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
	//Prueba de visualización de enemigos:
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

		//Prueba visualización de llaves:

		llave1 = new llaves(1);
		llave1->setPosition( Point( visibleSize.width / 5 + origin.x + 19900, visibleSize.height / 4 + origin.y + 500));
		//llave1->setScale(llave1->getScale() / 2);
		auto llave1Body = PhysicsBody::createCircle(llave1->llave->getContentSize().height / 4,PhysicsMaterial(0,0,0));
		llave1Body->setCollisionBitmask(11);
		llave1Body->setContactTestBitmask(true);
		llave1Body->setDynamic(false);
		llave1->setPhysicsBody( llave1Body );
		this->addChild( llave1 );
		
		llave2 = new llaves(2);
		llave2->setPosition( Point( visibleSize.width / 5 + origin.x + 10200, visibleSize.height / 4 + origin.y + 1000));
		//llave2->setScale(llave2->getScale() / 2);
		auto llave2Body = PhysicsBody::createCircle(llave2->llave->getContentSize().height / 4,PhysicsMaterial(0,0,0));
		llave2Body->setCollisionBitmask(10);
		llave2Body->setContactTestBitmask(true);
		llave2Body->setDynamic(false);
		llave2->setPhysicsBody( llave2Body );
		this->addChild( llave2 );
		//Fin llaves

		//Aquí va a ir el tema plataformas:
		plataforma = new Plataforma();
		plataforma->setPosition(Point( visibleSize.width / 5 + origin.x + 3750 , visibleSize.height / 3 + origin.y + 100));
		auto plataformaBody = PhysicsBody::createBox(Size(plataforma->plataforma->getContentSize().width/ 2, plataforma->plataforma->getContentSize().height),PhysicsMaterial(0.0f,0.0f,1.0f));
		plataformaBody->setCollisionBitmask(7);
		plataformaBody->setContactTestBitmask(true);
		plataformaBody->setRotationEnable(false);
		plataformaBody->setDynamic(false);
		plataforma->setPhysicsBody( plataformaBody );
		this->addChild(plataforma);
		//Fin Plataformas.

		//Aquí las pruebas del interruptor:
		interruptor = new Interruptor();
		interruptor->setPosition( Point( visibleSize.width / 5 + origin.x + 6505 , visibleSize.height / 4 + origin.y + 3000));
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


	}
	//Colisiones:
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Juego::onContactBegin, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(Juego::onContactSeparate, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	//auto contactListener2 = EventListenerPhysicsContact::create();
	//this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);


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

    // Hacemos saber a cocos que tenemos una función update
    this->scheduleUpdate();

	//Para llamar al timer:

		this->schedule(schedule_selector(Juego::contador), 1.0f);
		this->schedule(schedule_selector(Juego::contadorLasers), 1.0f);


	return true;

}

void Juego::contadorLasers(float delta){
	if(laser1->isActive()){
		laser1->setActive(false);
	}else{
		laser1->setActive(true);
	}
}

bool Juego::onContactBegin(PhysicsContact &contact){
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();
	//Comprobar si los body han colisionado:
	
	if(3 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()|| 
		1 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask() ){
			label->setString("Colisiona, personaje, mina");
			eliminarMina();
			if(personaje->getOrientacion() == 2){
				accionSalto = JumpBy::create(3,Point(0, -20), 210, 1);//Para saltar, hay que generizarlo para cualquier colision de suelo(generalizar y)
				personaje->runAction(accionSalto);
			}else if(personaje->getOrientacion() == 1){
				accionSalto = JumpBy::create(3,Point(-500, -20), 210, 1);
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
		//Quitarle vida al personaje:
	}
	//Tema colisión con llaves:
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
	//Colisión personaje/Interruptor:
	if(12 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()|| 
		1 == a->getCollisionBitmask() && 12 == b->getCollisionBitmask() ){
		label->setString("tocando el interruptor");
		interruptor->setEsActivo(true);
	}else{
		interruptor->setEsActivo(false);//Pasar al update haber si se soluciona.
	}



	//COLISIÓN CON EL PRIMER SUELO:

	if(100 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()|| 
		1 == a->getCollisionBitmask() && 100 == b->getCollisionBitmask() ){
			personaje->grounded = true;
			personaje->velocity = Point(0,0);
			personaje->position.y = edgeNode->getBoundingBox().getMaxY();
	}
	return true;
}
void Juego::onContactSeparate(PhysicsContact &contact){
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

	//"Descolisión" personaje/Interruptor:
	if(12 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()|| 
		1 == a->getCollisionBitmask() && 12 == b->getCollisionBitmask() ){
		interruptor->setEsActivo(false);
	}

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
	CCSize	screenSize	=	CCDirector::sharedDirector()->getWinSize();
		float x =  screenSize.width/2.0;
		float y = screenSize.height/4.0;
	if(personaje->getPositionX() > personaje->getPositionX()/4.0f ){
		x	= screenSize.width/2.0	- personaje->getPosition().x;
	}
		y	= screenSize.height/4.0	- personaje->getPosition().y;					
	this->setPosition(ccp(x,	y));
}

void Juego::update(float delta) {
    Node::update(delta);

	Vec2 locEscenario = background->getPosition();
	Vec2 locEnemigo = enemigo1->getPosition();
	enemigo1->ruta();//Rutas de los enemigos.
	enemigo2->ruta();
	plataforma->rutaPlataforma();
	//moverEnemigos(locEnemigo);
	centerViewport();//Actualiza el movimiento de la camara.


	//Personaje esta delante de las puertas:
	if(personaje->getPosition() > Vec2(puerta1->getPositionX() -100 ,puerta1->getPositionY() -100) && personaje->getPosition() < Vec2(puerta1->getPositionX() + 100 ,puerta1->getPositionY() +100)){
		puerta1->personajeEnLaPuerta(true);
	}else{
		puerta1->personajeEnLaPuerta(false);
	}
	if(personaje->getPosition() > Vec2(puerta2->getPositionX() -100 ,puerta2->getPositionY() -100) && personaje->getPosition() < Vec2(puerta2->getPositionX() + 100 ,puerta2->getPositionY() +100)){
		puerta2->personajeEnLaPuerta(true);
	}else{
		puerta2->personajeEnLaPuerta(false);
	}
	//Fin personaje esta delante de las puertas.




	//Mina va con el personaje:
	if(!personaje->isMina()){
		if(personaje->getOrientacion()== 2){
			mina->setPosition(Vec2(personaje->getPositionX() + 130, personaje->getPositionY()));
		}else{
			mina->setPosition(Vec2(personaje->getPositionX() - 130, personaje->getPositionY()));
		}
	}



	//Abrir la puerta del jefe:
	/*if(llave1->esRecigida() && !llave2->esRecigida() ){

	}else if(llave2->esRecigida() && !llave1->esRecigida()){
	
	}else*/ if(llave1->esRecigida() && llave2->esRecigida()){
		//label->setString("Puerta abierta");//Esto funciona, pero a la hora del debug lo quito.
	}

	this->updatePersonaje(delta);

}

void Juego::updatePersonaje(float delta){
	//Controles de tecla mantenida pulsada:
	if(mina->isVisible()){//Por ahora isVisivle...Cambiar
		if(personaje->grounded){
			personaje->groundedPosition = personaje->getPositionY();
			personaje->velocity.y = PLAYER_JUMP_VELOCITY;
			personaje->state = Personaje::State::Saltando;
			personaje->grounded = false;
		}else{
			if(personaje->groundedPosition < personaje->getPositionY() + personaje->velocity.y){
				personaje->velocity -= Point(0, 0.5f);//Le resta a las y la fuerza de la gravedad
			}
		}
	}

		//personaje->velocity -= Point(0, 0.3f);//Le resta a las y la fuerza de la gravedad
	if(isKeyPressed(EventKeyboard::KeyCode::KEY_A)) {
		personaje->personajeAnim(1);//Para que el personaje mire a la izquierda, es su orientación, 1 izquierda
		personaje->velocity.x = -PLAYER_MAX_VELOCITY;
		if(personaje->grounded){
			personaje->state = Personaje::State::Corriendo;
		}

    }else if(isKeyPressed(EventKeyboard::KeyCode::KEY_D)){
		personaje->personajeAnim(2);// es su orientación, 2 derecha.
		personaje->velocity.x = PLAYER_MAX_VELOCITY;
			if(personaje->grounded){
				personaje->state = Personaje::State::Corriendo;
			}

	}

		if (std::abs(personaje->velocity.x) > PLAYER_MAX_VELOCITY) {
			personaje->velocity.x = signum(personaje->velocity.x) * PLAYER_MAX_VELOCITY;
		}
	
		if (std::abs(personaje->velocity.x) < 1) {
			personaje->velocity.x = 0;
			if (personaje->grounded) {
				personaje->state = Personaje::State::Quieto;
			}
		}
 
		// unscale the velocity by the inverse delta time and set
		// the latest position
		personaje->velocity = personaje->velocity * delta;
		personaje->position.x = personaje->position.x + personaje->velocity.x;
		personaje->position.y = personaje->position.y + personaje->velocity.y;
		personaje->velocity = personaje->velocity * 1/delta;
 
		personaje->velocity.x *= DAMPING;
		
		//personaje->setPositionX(personaje->getPositionX() + personaje->velocity.x);
		personaje->setPositionX( personaje->getPositionX() + personaje->velocity.x );
		personaje->setPositionY( personaje->getPositionY() + personaje->velocity.y );





	//Fin de controles de tecla mantenida pulsada.
}
// Cocos requiere que createScene sea estatico, Esto es para crear otro miembro statico.
std::map<cocos2d::EventKeyboard::KeyCode,
        std::chrono::high_resolution_clock::time_point> Juego::keys;

//Función magica que ya para más adelante mirare que hace, se usa para calcular la posicion del personaje cuando este esta en movimiento.
int Juego::signum(float x) 
{ 
  if (x > 0.0L) 
    return 1.0L; 
  else if (x < 0.0L)   
    return -1.0L; 
  else   
    return 0.0L; 
}

//Función que controla las teclas de un solo pulsado:
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
	case EventKeyboard::KeyCode::KEY_R:
		//na de na.
		/*personaje->setPosition(Vec2(personaje->getPositionX(), personaje->getPositionY() + 100));*/
		break;
	case EventKeyboard::KeyCode::KEY_C:
		/*personaje->setPosition(Vec2(personaje->getPositionX(), personaje->getPositionY() - 100));*/
		break;
	case EventKeyboard::KeyCode::KEY_W:
		lanzarMina(2);//lanzarMina modo dejar caer.
		break;
	case EventKeyboard::KeyCode::KEY_SPACE://Boton de acción
		if(interruptor->getEsActivo()){
			label->setString("Puente abierto");
			interruptor->removeFromPhysicsWorld();//Eliminar las fisica del interruptor, para que no pueda activar 10000000 puentes
			//FALTA:
			//crear el puente
			//Y creo que ya.
		}else if(puerta1->isPersoanje()){
			label->setString("abierta");
			accionSalto = JumpBy::create(2,Point(0, puerta1->getPositionY()), 50, 1);//Para mover la puerta desde aquí?Si
			puerta1->runAction(accionSalto);
			personaje->setPosition(Vec2(13355,200));
			personaje->personajeAnim(1);
			/*pause();
			resume();*/
			
			//Aqui va la animación de abrir puerta.
		}else if(puerta2->isPersoanje()){
			label->setString("abierta");
			accionSalto = JumpBy::create(2,Point(0, puerta2->getPositionY()), 50, 1);//Para mover la puerta desde aquí?Si
			puerta2->runAction(accionSalto);
			personaje->setPosition(Vec2(14555,350));
			personaje->personajeAnim(1);
			//Aqui va la animación de abrir puerta.
		}
		break;
	}
}

//Función que lleva el tema del lanzamiento de minas:
void Juego::lanzarMina(int tipo){	
	if((personaje->getNumMina()) < 1){
		personaje->setIsMina(true);
		if(personaje->getOrientacion()==2){	
			if(tipo == 1){
				lanzamientoDeMina = JumpBy::create(1,Point(300, 0), 40, 1);//Para saltar??
				mina->runAction(lanzamientoDeMina);
			}else{
				mina->setPosition(personaje->getPosition());
			}
		}else{
			if(tipo == 1){
				lanzamientoDeMina = JumpBy::create(1,Point(-300, 0), 40, 1);//Para saltar??
				mina->runAction(lanzamientoDeMina);
			}else{
				mina->setPosition(personaje->getPosition());
			}
		}
		auto minaBody = PhysicsBody::createBox(mina->mina->getContentSize()/6,PhysicsMaterial(0.0f,0.0f,1.0f));
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
			//explosionMina = mina->explotarMina();//Por ahora no hace nada, pero hara la animación
			mina->removeFromPhysicsWorld();
			mina->setVisible(false);
			label->setString("borrado");
			//		
		}
}



