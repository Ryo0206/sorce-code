#include "MainScene.h"
#include "cocos2d.h"
#include "Stage.h"
#include "Player.h"
#include "SimpleAudioEngine.h"
#include "Enemy.h"

USING_NS_CC;
//�d�͂������x�N�g��
const Vec2 GRAVITY_ACCELERATION = Vec2(0, -3);

MainScene::MainScene()
:_stage(nullptr)
,_state(GameState::PLAYING)
,player(nullptr)
{

}


MainScene::~MainScene()
{
	CC_SAFE_RELEASE_NULL(_stage);
	CC_SAFE_RELEASE_NULL(player);
}


Scene* MainScene::createScene() {
	//�����G���W����L���ɂ����V�[�����쐬����
	auto scene = Scene::createWithPhysics();
	//������Ԃ����o��
	auto world = scene->getPhysicsWorld();
	//�d�͂̐ݒ�
	world->setGravity(GRAVITY_ACCELERATION);
	//������Ԃ̃X�s�[�h��ݒ�
	world->setSpeed(6.0);

	//�f�o�b�O�p�̉���
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	//���C���[�̐ݒ�
	auto layer = MainScene::create();
	scene->addChild(layer);

	return scene;
}

bool MainScene::init() {
	if (!Layer::init()) {
		return false;
	}
	//��ʂ̑傫���̎��o��
	auto winSize = Director::getInstance()->getWinSize();

	//�X�e�[�W�̒ǉ�
	auto stage = Stage::create();
	this->addChild(stage);
	this->setStage(stage);
	

	//Player�̍쐬
	player = Player::create();
	player->setPosition(Vec2(50, 80));
	this->addChild(player);
	//Enemy�̒ǉ�
	auto enemy = Enemy::create();
	_enemy.pushBack(enemy);
	enemy->setPosition(Vec2(320, 80));
	this->addChild(enemy);

	//�}�b�v�̕��̎擾
	auto mapWidth = stage->getTiledMap()->getContentSize().width;
	auto mapHeight = stage->getTiledMap()->getContentSize().height;

	//�J�����̒Ǐ]
	this->runAction(Follow::create(player,Rect(0,0,mapWidth,mapHeight)));


	auto contactlistener = EventListenerPhysicsContact::create();
	contactlistener->onContactBegin = CC_CALLBACK_1(MainScene::ContactBegin,this);
	contactlistener->onContactSeparate = CC_CALLBACK_1(MainScene::ContactSeparate, this);

	auto dispatcher = getEventDispatcher();// Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerKeyboard::create();

	for (bool& b : keyState) {
		b = false;
	}
	listener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* keyevent) {
		this->keyState[(int)keyCode] = true;
		
	};
	listener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* keyevent) {
		this->keyState[(int)keyCode] = false;
	};
	dispatcher->addEventListenerWithFixedPriority(listener, 99);
	dispatcher->addEventListenerWithFixedPriority(contactlistener, 99);
	this->scheduleUpdate();

	return true;
}

void MainScene::update(float dt)
{
	if (_state == GameState::PLAYING) {
		Vec2 playerPos = player->getPosition();
		float mv = 0.0f;
		//���̕����L�[�������ꂽ�ꍇ
		if (keyState[(int)EventKeyboard::KeyCode::KEY_LEFT_ARROW]) {
			mv = -1.0f;
		}
		//�E�̕����L�[�������ꂽ�ꍇ
		if (keyState[(int)EventKeyboard::KeyCode::KEY_RIGHT_ARROW]) {
			mv = 1.0f;
		}
		player->move(mv);

		//�X�y�[�X�L�[�������ꂽ�ꍇ
		if (keyState[(int)EventKeyboard::KeyCode::KEY_SPACE]) {
			CCLOG("JUMP>.");
			player->jump();

		}
		//�G�ƂԂ������Ƃ��̏���
		for (auto& enemy : _enemy) {
			Vec2 playerhitPos = player->getPosition();
			Rect boundingBox = enemy->getBoundingBox();
			bool isHit = boundingBox.containsPoint(playerhitPos);
			if (isHit) {
				player->removeFromParent();
				_state = GameState::ENDING;
			}
		}
		//�G���ǂ������Ă���
		
	}
}

bool MainScene::ContactBegin(PhysicsContact& contact)
{
	CCLOG("ContactBegin");
	player->setOnGround(true);

	return true;
}
bool MainScene::ContactSeparate(PhysicsContact& contact)
{
	CCLOG("ContactSeparate");
	player->setOnGround(false);

	return true;
}
