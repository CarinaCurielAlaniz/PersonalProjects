#include "GoombaMove.h"
#include "PlayerMove.h"
#include "SpriteComponent.h"
#include "AnimatedSprite.h"
#include "Goomba.h"
#include "Actor.h"
#include "Game.h"
#include "Player.h"
#include "Block.h"
#include "CollisionComponent.h"

GoombaMove::GoombaMove(class Goomba* owner)
: MoveComponent(owner)

{
	mGomb = owner;
	mYSpeed = 0.0f;
}
void GoombaMove::Update(float deltaTime)
{
	Vector2 offset;
	Game* mGame = mGomb->GetGame();
	Vector2 pos = mGomb->GetPosition();
	pos.x += mForwardSpeed * deltaTime;
	pos.y += mYSpeed * deltaTime;
	mOwner->SetPosition(pos);
	std::vector<class Block*> blockCop = mGame->GetBlock();
	std::vector<class Goomba*> gombaVec = mGame->GetEnemies();
	mInAir = true;
	for (size_t i = 0; i < gombaVec.size(); i++)
	{
		CollSide collideGoomba = mGomb->GetCol()->GetMinOverlap(gombaVec[i]->GetCol(), offset);
		if (collideGoomba == CollSide::Right && mForwardSpeed < 0)
		{
			mForwardSpeed *= -1;
		}
		if (collideGoomba == CollSide::Left && mForwardSpeed > 0)
		{
			mForwardSpeed *= -1;
		}
	}
	mYSpeed += 2000.0f * deltaTime;
	bool tocuhesTop = false;
	for (size_t i = 0; i < blockCop.size(); i++)
	{
		CollSide collideBlock = mGomb->GetCol()->GetMinOverlap(blockCop[i]->GetCol(), offset);
		if (collideBlock == CollSide::Top)
		{
			if (mInAir)
			{
				mYSpeed = 0.0f;
				pos.y = blockCop[i]->GetPosition().y - 32;
				mOwner->SetPosition(pos);
			}
			mInAir = false;
			tocuhesTop = true;
		}
		if (collideBlock == CollSide::Right && mForwardSpeed < 0)
		{
			mForwardSpeed *= -1;
		}
		if (collideBlock == CollSide::Left && mForwardSpeed > 0)
		{
			mForwardSpeed *= -1;
		}
	}
	if (!tocuhesTop)
	{
		mYSpeed += 2000.0f * deltaTime;
	}
	else
	{

		mYSpeed = 0.0f;
	}
	if (mGomb->GetPosition().y > (mGame->WINDOW_HEIGHT))
	{
		mGomb->SetState(ActorState::Destroy);
	}
}