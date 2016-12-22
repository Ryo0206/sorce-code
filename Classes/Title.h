#pragma once
#include "cocos2d.h"
class Title :
	public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init() override;
	void onEnterTransitionDidFinish() override;
	CREATE_FUNC(Title);
	Title();
	~Title();
};

