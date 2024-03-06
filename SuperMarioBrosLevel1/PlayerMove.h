#include "MoveComponent.h"
#include "Actor.h"
#include "Math.h"
#include <unordered_map>
#include "Game.h"

class PlayerMove : public MoveComponent
{
public:
	PlayerMove(class Actor* owner);
	void Update(float deltaTime) override;
	void ProcessInput(const Uint8* keyState) override;
	void MarioAnim();

private:
	Vector2 mOldPos;
	Vector2 mOldCamera;
	Actor* mActor;
	float mYSpeed;
	float mLifetime;
	std::unordered_map<SDL_Scancode, bool> mLastFrame;
	bool mInAir = false;
	Vector2 mDirection;
	Game* mGame;
	class Player* mMario;
	Vector2 mPos;
};