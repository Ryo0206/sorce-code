#pragma once
#include "cocos2d.h"
class TitleScene :
	public cocos2d::Layer
{
protected:
	TitleScene();
	~TitleScene();
	bool init() override;
public:
	static cocos2d::Scene* createScene();
	void onEnterTransitionDidFinish();
	CREATE_FUNC(TitleScene);
	};

