#include "Actor.h"
class Block : public Actor
{
public:
	Block(class Game* game, char symbol, int idx, int line);
	~Block();
	class CollisionComponent* GetCol();
	class SpriteComponent* GetSprite();

private:
	class Game* mGame;
	class SpriteComponent* mSpriteComp;
	class CollisionComponent* mCollision;
};