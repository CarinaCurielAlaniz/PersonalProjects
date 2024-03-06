#include "Actor.h"
class Goomba : public Actor
{
public:
	Goomba(class Game* game);
	~Goomba();
	class AnimatedSprite* GetSprite();
	class CollisionComponent* GetCol();
	class GoombaMove* GetMove();
	bool IsDead() const;
	void SetIsDead(bool isD);
	void OnUpdate(float deltaTime) override;

private:
	class Game* mGame;
	class AnimatedSprite* mAnimSprite;
	class CollisionComponent* mCollision;
	class GoombaMove* mGMove;
	float mLifetime;
	bool mIsDead;
};