#include "PlayerMove.h"
#include "Actor.h"
#include "Game.h"
#include "Goomba.h"
#include "AnimatedSprite.h"
#include "SpriteComponent.h"
#include "Player.h"
#include "Block.h"
#include "CollisionComponent.h"

PlayerMove::PlayerMove(class Actor* owner)
: MoveComponent(owner)

{
	mActor = owner;
	mYSpeed = 0.0f;
	mLastFrame.insert(std::make_pair(SDL_SCANCODE_W, false));
	mLastFrame.insert(std::make_pair(SDL_SCANCODE_A, false));
	mLastFrame.insert(std::make_pair(SDL_SCANCODE_S, false));
	mLastFrame.insert(std::make_pair(SDL_SCANCODE_D, false));
	mLifetime = 0.25f;
	mGame = mOwner->GetGame();
	mMario = static_cast<Player*>(mOwner);
}
void PlayerMove::Update(float deltaTime)
{
	mPos = mActor->GetPosition();
	Vector2 offset;
	mPos.x += mForwardSpeed * deltaTime;
	mPos.y += mYSpeed * deltaTime;

	if (mPos.y >= mGame->WINDOW_HEIGHT)
	{
		mMario->GetSprite()->SetAnimation("dead");
		mMario->SetState(ActorState::Paused);
		Mix_HaltChannel(mGame->GetBackgroundChannel());
		Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/Dead.wav"), 0);
	}
	if (mPos.x >= 6368)
	{
		Mix_HaltChannel(mGame->GetBackgroundChannel());
		Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/StageClear.wav"), 0);
		mMario->SetState(ActorState::Paused);
	}
	mActor->SetPosition(mPos);

	Vector2& cameraPos = mOwner->GetGame()->GetCameraPos();
	if (mPos.x < cameraPos.x + 32)
	{
		mPos.x = cameraPos.x + 32;
		mActor->SetPosition(mPos);
	}
	if (mOldPos.x < mPos.x)
	{
		cameraPos.x = mActor->GetPosition().x - 300;
	}
	if (cameraPos.x < mOldCamera.x)
	{
		cameraPos.x = mOldCamera.x;
	}
	if (cameraPos.x < 0)
	{
		cameraPos.x = 0;
	}
	mInAir = true;
	std::vector<class Block*> blockCop = mGame->GetBlock();
	for (size_t i = 0; i < blockCop.size(); i++)
	{
		CollSide collide = mMario->GetCol()->GetMinOverlap(blockCop[i]->GetCol(), offset);
		if (collide == CollSide::Top && mYSpeed > 0.0f)
		{
			mYSpeed = 0.0f;
			mInAir = false;
		}
		else if (collide == CollSide::Bottom && mYSpeed < 0.0f)
		{
			Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/Bump.wav"), 0);
			mYSpeed = 0.0f;
		}
		if (collide != CollSide::None)
		{
			mActor->SetPosition(mActor->GetPosition() + offset);
			if (CollSide::Left == collide || CollSide::Right == collide)
			{

				mOldPos += offset;
			}
		}
	}
	mYSpeed += 2000.0f * deltaTime;
	bool isStomp = false;
	std::vector<class Goomba*> goombas = mGame->GetEnemies();
	for (size_t i = 0; i < goombas.size(); i++)
	{
		CollSide marioStomp = mMario->GetCol()->GetMinOverlap(goombas[i]->GetCol(), offset);
		if ((marioStomp == CollSide::Top || marioStomp == CollSide::Left ||
			 marioStomp == CollSide::Right) &&
			mMario->GetMove()->mInAir)
		{
			goombas[i]->GetSprite()->SetAnimation("dead");
			goombas[i]->SetIsDead(true);
			mForwardSpeed = 0;
			mYSpeed = -350.f;
			mInAir = true;
			isStomp = true;
			Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/Stomp.wav"), 0);
		}
		if (marioStomp != CollSide::None && !isStomp)
		{
			mMario->GetSprite()->SetAnimation("dead");
			mMario->SetState(ActorState::Paused);
			Mix_HaltChannel(mGame->GetBackgroundChannel());
			Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/Dead.wav"), 0);
		}
	}
	mOldCamera = cameraPos;
	MarioAnim();
	mOldPos = mPos;
}
void PlayerMove::ProcessInput(const Uint8* keyState)
{
	mForwardSpeed = 0.0f;
	if (keyState[SDL_SCANCODE_SPACE] && !mLastFrame.find(SDL_SCANCODE_SPACE)->second)
	{
		if (!mInAir)
		{
			mYSpeed = -700.0f;
			mInAir = true;
			Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/Jump.wav"), 0);
		}
	}
	mLastFrame[SDL_SCANCODE_SPACE] = keyState[SDL_SCANCODE_SPACE];

	if (keyState[SDL_SCANCODE_A] && keyState[SDL_SCANCODE_D])
	{
		mForwardSpeed = 0.0f;
	}
	if (keyState[SDL_SCANCODE_D])
	{
		mForwardSpeed = 300.0f;
	}
	if (keyState[SDL_SCANCODE_A])
	{
		mForwardSpeed = -300.0f;
	}
}
void PlayerMove::MarioAnim()
{
	if (mMario->GetState() != ActorState::Paused)
	{
		if (mPos.x > mOldPos.x)
		{

			mMario->GetSprite()->SetAnimation("runRight");
		}
		if (mPos.x < mOldPos.x)
		{
			mMario->GetSprite()->SetAnimation("runLeft");
		}
		if (mInAir)
		{
			if (mPos.x > mOldPos.x)
			{
				mMario->GetSprite()->SetAnimation("jumpRight");
			}
			else if (mPos.x < mOldPos.x)
			{
				mMario->GetSprite()->SetAnimation("jumpLeft");
			}
		}
		if (mInAir && mPos.x == mOldPos.x)
		{
			std::string animName = mMario->GetSprite()->GetAnimName();
			if (animName == "runRight" || animName == "jumpRight" || animName == "idle")
			{
				mMario->GetSprite()->SetAnimation("jumpRight");
			}
			else
			{
				mMario->GetSprite()->SetAnimation("jumpLeft");
			}
		}
		else if (mPos.x == mOldPos.x)
		{
			mMario->GetSprite()->SetAnimation("idle");
		}
	}
}