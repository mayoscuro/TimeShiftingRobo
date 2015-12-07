#include "Juego.h"
//#include "LectorPersonaje.h"

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

	auto edgeBody = PhysicsBody::createEdgeBox( Size(visibleSize.width * 20 ,visibleSize.height / 1.2), PhysicsMaterial(0,0,0) );
    
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
		auto personajeBody = PhysicsBody::createBox(personaje->personajeSprite->getContentSize(),PhysicsMaterial(0,0,0));
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
		enemigo2->setPosition( Point( visibleSize.width / 5 + origin.x/*+1000*/, visibleSize.height / 6.5 + origin.y) );
		auto enemigo2Body = PhysicsBody::createBox(enemigo2->enemigo->getContentSize(),PhysicsMaterial(0,0,0));
		enemigo2Body->setCollisionBitmask(2);
		enemigo2Body->setContactTestBitmask(true);
		enemigo2Body->setDynamic(true);
		enemigo2->setPhysicsBody( enemigo2Body );
		this->addChild( enemigo2);
	//Fin Prueba
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

    // Hacemos saber a cocos que tenemos una función update
    this->scheduleUpdate();

	//Para llamar al timer:

		this->schedule(schedule_selector(Juego::contador), 1.0f);
		this->schedule(schedule_selector(Juego::saltar), 0.009f);


	return true;

}
void Juego::saltar(float delta){
	if(personaje->getEnAire() && personaje->getMaxAltura() <= 20){
		personaje->setPosition(personaje->getPosition().x , personaje->getPosition().y +3);
		personaje->setMaxAltura(personaje->getMaxAltura() + 1);
	}else{
		personaje->setEnAire(false);
		personaje->setMaxAltura(0);
	}
}

bool Juego::onContactBegin(PhysicsContact &contact){
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();
	//Comprobar si los body han colisionado:
	if(3 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()|| 
		1 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask() ){
			label->setString("Colisiona, personaje, mina");
			
			//personaje->setPosition(personaje->getPosition().x , personaje->getPosition().y * 2/*personaje->getSalto()*/);
			//PUTA MINA QUE NO SE BORRA:
			//mina->removeFromPhysicsWorld();
			//mina->removeAllChildrenWithCleanup(true);
	}

	if(3 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask()|| 
		2 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask() ){
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
	
	return true;
}
//

 
void Juego::contador(float delta){
	if(personaje->isMina()){
		personaje->setTiempoMina(personaje->getTiempoMina() + 1);

		//Para que la mina desaparezca cuando explote:
		if(personaje->getTiempoMina() >= 3 && personaje->isMina()){
			personaje->setIsMina(false);
			personaje->setTiempoMina(0);	
			personaje->retornaMina();
			//explosionMina = mina->explotarMina();//Por ahora no hace nada, pero hara la animación
			//this->removeChild(mina, true);
			//mina->removeAllChildren();//[[[[¡¡¡¡¡¡ARREGLAAAAAAAR!!!!!]]]]
			//mina->setVisible(false);//Apaño por el momento...Que tampoco va...
			label->setString("borrado");
			//		
		}
	}

	
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
    }
	else if(isKeyPressed(EventKeyboard::KeyCode::KEY_D)){
		personaje->personajeAnim(2);
		personaje->setPosition(loc.x + 3,loc.y);
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
	case EventKeyboard::KeyCode::KEY_W:
		personaje->setEnAire(true);
		break;
	}
}

void Juego::lanzarMina(){	
	if((personaje->getNumMina()) < 2){
		Mina* mina = new Mina();
		Vec2 posmina = personaje->getPosition();
		auto minaBody = PhysicsBody::createCircle(mina->mina->getContentSize().width/2,PhysicsMaterial(0,0,0));
		minaBody->setCollisionBitmask(3);
		minaBody->setContactTestBitmask(true);
		minaBody->setDynamic(true);
		mina->setPhysicsBody( minaBody );
		this->addChild( mina);
		mina->setPosition(posmina.x + 100,posmina.y - 90);
		personaje->setIsMina(true);
		personaje->usarMina();

	}	
}

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