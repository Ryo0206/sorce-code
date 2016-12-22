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
	//��ʃT�C�Y�̎��o��
	auto winSize = director->getWinSize();

	//�^�C�g���摜�̌Ăяo��
	auto title = Sprite::create("Title.png");
	//�^�C�g���̏ꏊ���w��
	title->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	//�^�C�g���̒ǉ�
	this->addChild(title);

	//�X�^�[�g��ʂ̒ǉ�
	auto touchToStart = Sprite::create("start.png");
	touchToStart->setPosition(Vec2(winSize.width / 2.0, 90));
	//�_�ł���A�N�V����
	auto blink = Sequence::create(FadeTo::create(0.5, 127),FadeTo::create(0.5,277),NULL);

	touchToStart->runAction(RepeatForever::create(blink));
	this->addChild(touchToStart);

	//��ʈڍs
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