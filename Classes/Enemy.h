#pragma once
#include "cocos2d.h"
class Enemy :
	public cocos2d::Sprite
{
protected:
	bool init() override;
public:

	void update(float dt) override;
	CREATE_FUNC(Enemy);

	Enemy();
	~Enemy();
};

