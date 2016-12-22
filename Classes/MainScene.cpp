#include "MainScene.h"
#include "cocos2d.h"
#include "Stage.h"
#include "Player.h"
#include "SimpleAudioEngine.h"
#include "Enemy.h"

USING_NS_CC;
//重力を現すベクトル
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
	//物理エンジンを有効にしたシーンを作成する
	auto scene = Scene::createWithPhysics();
	//物理空間を取り出す
	auto world = scene->getPhysicsWorld();
	//重力の設定
	world->setGravity(GRAVITY_ACCELERATION);
	//物理空間のスピードを設定
	world->setSpeed(6.0);

	//デバッグ用の可視化
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	//レイヤーの設定
	auto layer = MainScene::create();
	scene->addChild(layer);

	return scene;
}

bool MainScene::init() {
	if (!Layer::init()) {
		return false;
	}
	//画面の大きさの取り出し
	auto winSize = Director::getInstance()->getWinSize();

	//ステージの追加
	auto stage = Stage::create();
	this->addChild(stage);
	this->setStage(stage);
	

	//Playerの作成
	player = Player::create();
	player->setPosition(Vec2(50, 80));
	this->addChild(player);
	//Enemyの追加
	auto enemy = Enemy::create();
	_enemy.pushBack(enemy);
	enemy->setPosition(Vec2(320, 80));
	this->addChild(enemy);

	//マップの幅の取得
	auto mapWidth = stage->getTiledMap()->getContentSize().width;
	auto mapHeight = stage->getTiledMap()->getContentSize().height;

	//カメラの追従
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
		//左の方向キーが押された場合
		if (keyState[(int)EventKeyboard::KeyCode::KEY_LEFT_ARROW]) {
			mv = -1.0f;
		}
		//右の方向キーが押された場合
		if (keyState[(int)EventKeyboard::KeyCode::KEY_RIGHT_ARROW]) {
			mv = 1.0f;
		}
		player->move(mv);

		//スペースキーが押された場合
		if (keyState[(int)EventKeyboard::KeyCode::KEY_SPACE]) {
			CCLOG("JUMP>.");
			player->jump();

		}
		//敵とぶつかったときの処理
		for (auto& enemy : _enemy) {
			Vec2 playerhitPos = player->getPosition();
			Rect boundingBox = enemy->getBoundingBox();
			bool isHit = boundingBox.containsPoint(playerhitPos);
			if (isHit) {
				player->removeFromParent();
				_state = GameState::ENDING;
			}
		}
		//敵が追いかけてくる
		
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
