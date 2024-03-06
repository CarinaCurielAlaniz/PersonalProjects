#include "Spawner.h"
#include "SpriteComponent.h"
#include "Goomba.h"
#include "Player.h"
#include "CollisionComponent.h"
#include "Game.h"
#include "WrappingMove.h"
#include "AnimatedSprite.h"

Spawner::Spawner(class Game* game)
: Actor(game)
{
	mGame = game;
}
void Spawner::OnUpdate(float deltaTime)
{
	if ((GetPosition().x - mGame->GetMario()->GetPosition().x) < 600)
	{
		Goomba* goomba = new Goomba(mGame);
		goomba->SetPosition(GetPosition());
		goomba->GetSprite()->SetAnimation("walk");
		SetState(ActorState::Destroy);
	}
}