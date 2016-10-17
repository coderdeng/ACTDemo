﻿#pragma once

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "shana.h"
#include "monster.h"

class gameScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(gameScene);
protected:
	virtual void onEnter();

private:
	Role *shana;
	AIRole *monster;
	void hurtCompute();
	bool checkCrash();
	void addPhysicsListener();
	void addBackgroundMusic();

};
