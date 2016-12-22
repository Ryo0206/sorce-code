#pragma once
#include "cocos2d.h"
#include "Player.h"

class Stage :
	public cocos2d::Layer
{
public:
	
	void update(float dt)override;
	//タイルマップ
	CC_SYNTHESIZE_RETAIN(cocos2d::TMXTiledMap *, _tiledMap, TiledMap);
	
	CREATE_FUNC(Stage);
protected:
	Stage();
	~Stage();
	bool init() override;
private:
	cocos2d::Sprite* addPhysicsBody(cocos2d::TMXLayer *layer, cocos2d::Vec2&coordinate);
};

