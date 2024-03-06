#include "Goomba.h"
#include "AnimatedSprite.h"
//#include "GoombaMove.h"
#include "CollisionComponent.h"
#include "Game.h"
#include "WrappingMove.h"
#include "GoombaMove.h"

Goomba::Goomba(class Game* game)
: Actor(game)
, mAnimSprite(new AnimatedSprite(this, 200))
, mCollision(new CollisionComponent(this))
, mGMove(new GoombaMove(this))
{
	mGMove->SetForwardSpeed(-100);
	mGame = game;
	mCollision->SetSize(32.0f, 32.0f);
	mGame->AddEnemie(this);
	mIsDead = false;
	mLifetime = 0.25f;
	std::vector<SDL_Texture*> walkAnim{GetGame()->GetTexture("Assets/Goomba/Walk0.png"),
									   GetGame()->GetTexture("Assets/Goomba/Walk1.png")};
	mAnimSprite->AddAnimation("walk", walkAnim);

	std::vector<SDL_Texture*> deadAnim{GetGame()->GetTexture("Assets/Goomba/Dead.png")};
	mAnimSprite->AddAnimation("dead", deadAnim);
}
Goomba::~Goomba()
{
	mGame->DeleteEnemie(this);
}
void Goomba::OnUpdate(float deltaTime)
{
	if (mIsDead)
	{
		mGMove->SetForwardSpeed(0.0f);
		mLifetime -= deltaTime;
		if (mLifetime <= 0.0f)
		{
			SetState(ActorState::Destroy);
		}
	}
}

class AnimatedSprite* Goomba::GetSprite()
{
	return mAnimSprite;
}
class CollisionComponent* Goomba::GetCol()
{
	return mCollision;
}
class GoombaMove* Goomba::GetMove()
{
	return mGMove;
}
bool Goomba::IsDead() const
{
	return mIsDead;
}
void Goomba::SetIsDead(bool isD)
{
	mIsDead = isD;
}