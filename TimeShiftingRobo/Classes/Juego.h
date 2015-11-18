#ifndef __JUEGO_H__
#define __JUEGO_H__

#include "cocos2d.h"
#include <map>
#include "Personaje.h"


USING_NS_CC;

class Juego : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();
    virtual bool init();

    bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
    double keyPressedDuration(cocos2d::EventKeyboard::KeyCode);

	
	cocos2d::Sprite *background;
	Personaje* personaje;

    CREATE_FUNC(Juego);

	
	 virtual void update(float delta) override;
private:
     static std::map<cocos2d::EventKeyboard::KeyCode,
        std::chrono::high_resolution_clock::time_point> keys;
   
};

#endif 