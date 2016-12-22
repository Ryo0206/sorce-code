#include "Enemy.h"
#include "cocos2d.h"

USING_NS_CC;

const float ENEMY_SPEED = 2.0;

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

bool Enemy::init() {
	if (!Sprite::initWithFile("enemy.png")) {
		return false;
	}
	auto body = PhysicsBody::createCircle(this->getContentSize().width/5);
	this->setPhysicsBody(body);

	return true;
}

void Enemy::update(float dt) {

}