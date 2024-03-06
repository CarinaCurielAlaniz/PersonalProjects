#include "Player.h"
#include "AnimatedSprite.h"
#include "CollisionComponent.h"
#include "Game.h"
#include "WrappingMove.h"
#include "PlayerMove.h"

Player::Player(class Game* game)
: Actor(game)
, mAnimSprite(new AnimatedSprite(this, 200))
, mCollision(new CollisionComponent(this))
, mMove(new PlayerMove(this))
{
	mGame = game;
	mCollision->SetSize(32.0f, 32.0f);
	std::vector<SDL_Texture*> idleAnim{GetGame()->GetTexture("Assets/Mario/Idle.png")};
	mAnimSprite->AddAnimation("idle", idleAnim);

	std::vector<SDL_Texture*> deadAnim{GetGame()->GetTexture("Assets/Mario/Dead.png")};
	mAnimSprite->AddAnimation("dead", deadAnim);

	std::vector<SDL_Texture*> jumpLeftAnim{GetGame()->GetTexture("Assets/Mario/JumpLeft.png")};
	mAnimSprite->AddAnimation("jumpLeft", jumpLeftAnim);
	std::vector<SDL_Texture*> jumpRightAnim{GetGame()->GetTexture("Assets/Mario/JumpRight.png")};
	mAnimSprite->AddAnimation("jumpRight", jumpRightAnim);
	std::vector<SDL_Texture*> runLeftAnim{GetGame()->GetTexture("Assets/Mario/RunLeft0.png"),
										  GetGame()->GetTexture("Assets/Mario/RunLeft1.png"),
										  GetGame()->GetTexture("Assets/Mario/RunLeft2.png")};
	mAnimSprite->AddAnimation("runLeft", runLeftAnim);
	std::vector<SDL_Texture*> runRightAnim{GetGame()->GetTexture("Assets/Mario/RunRight0.png"),
										   GetGame()->GetTexture("Assets/Mario/RunRight1.png"),
										   GetGame()->GetTexture("Assets/Mario/RunRight2.png")};
	mAnimSprite->AddAnimation("runRight", runRightAnim);

	mAnimSprite->SetAnimation("idle");
}
void Player::OnProcessInput(const Uint8* keyState)
{
}
void Player::OnUpdate(float deltaTime)
{
}