#include "TitleScene.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* TitleScene::createScene() {
	auto scene = Scene::create();
	auto layer = TitleScene::create();
	scene->addChild(layer);
	return scene;
}

TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}



bool TitleScene::init() {
	if (!Layer::init()) {
		return false;
	}
	auto director = Director::getInstance();
	auto winSize = director->getWinSize();

	//タイトル画面の追加
	auto background = Sprite::create("Title.png");
	background->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(background);
	//スタートボタンの追加
	auto touchToStart = Sprite::create("start.png");
	touchToStart->setPosition(Vec2(winSize.width / 2 , 90));
	this->addChild(touchToStart);
	//点滅アクションの追加
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		this->getEventDispatcher()->removeAllEventListeners();
		auto delay = DelayTime::create(0.5);
		//ゲームを始めるアクション
		auto startGame = CallFunc::create([] {
			auto scene = MainScene::createScene();
			auto transition = TransitionPageTurn::create(0.5, scene, true);
			Director::getInstance()->replaceScene(transition);
		});
		this->runAction(Sequence::create(delay, startGame, NULL));

		return true;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void TitleScene::onEnterTransitionDidFinish() {

}