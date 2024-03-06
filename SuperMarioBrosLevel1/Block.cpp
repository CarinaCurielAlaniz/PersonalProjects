#include "Block.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include "Game.h"
#include "WrappingMove.h"

Block::Block(class Game* game, char symbol, int idx, int line)
: Actor(game)
, mSpriteComp(new SpriteComponent(this))
, mCollision(new CollisionComponent(this))
{
	mGame = game;
	mGame->AddBlock(this);
	mCollision->SetSize(32.0f, 32.0f);

	Vector2 pos3(idx * 32 + 16, line * 32 - 16);
	this->SetPosition(pos3);
	std::string file = "Assets/Block";
	file += symbol;
	file += ".png";
	mSpriteComp->SetTexture(game->GetTexture(file));
}
Block::~Block()
{
	mGame->DeleteBlock(this);
}
CollisionComponent* Block::GetCol()
{
	return mCollision;
}
SpriteComponent* Block::GetSprite()
{
	return mSpriteComp;
}