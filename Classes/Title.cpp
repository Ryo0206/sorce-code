#include "Title.h"
#include "SimpleAudioEngine.h"
#include "MainScene.h"

USING_NS_CC;

Title::Title()
{
}


Title::~Title()
{
}

Scene *Title::createScene() {
	auto scene = Scene::create();
	auto layer = Title::create();
	scene->addChild(layer);
	return scene;
}

bool Title::init() {
	if (!Title::init()) {
		return false;
	}
	
	auto director = Director::getInstance()->getInstance();
	//画面サイズの取り出し
	auto winSize = director->getWinSize();

	//タイトル画像の呼び出し
	auto title = Sprite::create("Title.png");
	//タイトルの場所を指定
	title->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	//タイトルの追加
	this->addChild(title);

	//スタート画面の追加
	auto touchToStart = Sprite::create("start.png");
	touchToStart->setPosition(Vec2(winSize.width / 2.0, 90));
	//点滅するアクション
	auto blink = Sequence::create(FadeTo::create(0.5, 127),FadeTo::create(0.5,277),NULL);

	touchToStart->runAction(RepeatForever::create(blink));
	this->addChild(touchToStart);

	//画面移行
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		this->getEventDispatcher()->removeAllEventListeners();
		auto delay = DelayTime::create(0.5);

		auto StartGame = CallFunc::create([] {
			auto scene = MainScene::createScene();
			auto transition = TransitionPageTurn::create(0.5, scene, true);
			Director::getInstance()->replaceScene(transition);
		});
		this->runAction(Sequence::create(delay, StartGame, NULL));

		return true;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void Title::onEnterTransitionDidFinish() {

}