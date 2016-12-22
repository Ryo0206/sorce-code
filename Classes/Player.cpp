#include "Player.h"
#include "Stage.h"

USING_NS_CC;

//アニメーションが何フレームあるか
const int FRAME_COUNT = 3;

Player::Player()
{
}


Player::~Player()
{
}

bool Player::init() {
	if (!Sprite::initWithFile("player.png")) {
		return false;
	}
	//キャラクタのサイズを取り出し
	auto frameSize = Size(this->getContentSize().width / FRAME_COUNT, this->getContentSize().height);
	//左下のポイントからサイズを取り出す(1フレーム分)
	this->setTextureRect(Rect(0, 0, frameSize.width, frameSize.height));
	//1コマずつのアニメーションを指定
	Vector<SpriteFrame *>frames;
	for (int i = 0; i < FRAME_COUNT; i++) {
		auto frame = SpriteFrame::create("player.png", Rect(frameSize.width * i, 0,
			frameSize.width, frameSize.height));
		frames.pushBack(frame);
	}
	//アニメーション用のフレームの作成
	auto animation = Animation::createWithSpriteFrames(frames);
	animation->setDelayPerUnit(0.05);
	this->runAction(RepeatForever::create(Animate::create(animation)));

	body = PhysicsBody::createCircle(this->getContentSize().width / 2.0);
	body->setCategoryBitmask(1);
	body->setContactTestBitmask(2);
	//剛体の回転を無効にする
	body->setRotationEnable(false);
	this->setPhysicsBody(body);
	

	this->scheduleUpdate();

	return true;
}

void Player::move(float m) {
	auto v = body->getVelocity();
	v.x = PLAYER_SPEED * m;
	body->setVelocity(v);
}

void Player::jump() {
	if (onGround) {
		auto v = body->getVelocity();
		v.y = JUMP_SPEED;
		body->setVelocity(v);
	}
}

void Player::update(float dt)
{
}

void Player::setOnGround(bool sw) {
	onGround = sw;
}