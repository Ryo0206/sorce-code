#pragma once
#include "cocos2d.h"
class Player :
	public cocos2d::Sprite
{
protected:
	bool init() override;
	bool onGround;
public:
	void move(float m);
	void jump();
	void update(float dt) override;
	void setOnGround(bool sw);
	CREATE_FUNC(Player);
private:
	const float PLAYER_SPEED = 10.0f;
	const float JUMP_SPEED = 10.0f;
	cocos2d::PhysicsBody* body;
	Player();
	~Player();
};

