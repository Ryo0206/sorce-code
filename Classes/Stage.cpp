#include "Stage.h"
#include "cocos2d.h"
#include "MainScene.h"

USING_NS_CC;

Stage::Stage()
:_tiledMap(nullptr)
{
}

Stage::~Stage()
{
	CC_SAFE_RELEASE_NULL(_tiledMap);
	
}

bool Stage::init() {
	if (!Layer::init()) {
		return false;
	}

	//マップファイルからノードを作成
	auto map = TMXTiledMap::create("map/Stage.tmx");
	this->addChild(map);
	this->setTiledMap(map);
	//マップのレイヤーを取得する
	auto terrainLayer = map->getLayer("Terrain");
	auto yukaLayer = map->getLayer("yuka");
	auto doorLayer = map->getLayer("door");
	auto kaidanLayer = map->getLayer("kaidan");

	//マップのサイズ
	auto mapSize = map->getMapSize();
	for (int x = 0; x < mapSize.width; x++) {
		for (int y = 0; y < mapSize.height; y++) {
			auto coordinate = Vec2(x, y);

			this->addPhysicsBody(terrainLayer, coordinate);
			this->addPhysicsBody(yukaLayer, coordinate);
			this->addPhysicsBody(kaidanLayer, coordinate);
		}
	}

	this->scheduleUpdate();

	return true;
}

Sprite* Stage::addPhysicsBody(cocos2d::TMXLayer *layer, cocos2d::Vec2 &coordinate) {
	auto sprite = layer->getTileAt(coordinate);
	if (sprite){
		auto material = PhysicsMaterial();
		material.friction = 0.5;
		auto physicsBody = PhysicsBody::createBox(sprite->getContentSize(), material);
		physicsBody->setCategoryBitmask(2);
		physicsBody->setContactTestBitmask(1);
		physicsBody->setDynamic(false);
		sprite->setPhysicsBody(physicsBody);

		return sprite;
	}
	return nullptr;
}

void Stage::update(float dt) {

}