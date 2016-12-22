#pragma once
#include "cocos2d.h"
#include "Stage.h"

class MainScene :
	public cocos2d::Layer
{
	bool keyState[256];
	Player* player;
public:
	bool init() override;
	static cocos2d::Scene* createScene();
	void update(float dt) override;

	bool ContactBegin(cocos2d::PhysicsContact& contact);
	bool ContactSeparate(cocos2d::PhysicsContact& contact);
	enum class GameState {
		READY,
		PLAYING,
		RESULT,
		GAMEOVER,
		ENDING,
		COUNT,
	};
	//ステージを呼び出し
	CC_SYNTHESIZE_RETAIN(Stage *, _stage, Stage);
	CC_SYNTHESIZE(GameState, _state, State);
	CC_SYNTHESIZE(cocos2d::Vector<cocos2d::Sprite *>, _enemy, Enemy);
	CC_SYNTHESIZE_RETAIN(cocos2d::TMXTiledMap *, _tiledMap, TiledMap);
	CREATE_FUNC(MainScene);
protected:
	
	MainScene();
	virtual ~MainScene();
private:
	cocos2d::Sprite* addPhysicsBody(cocos2d::TMXLayer *layer, cocos2d::Vec2&coordinate);
};

