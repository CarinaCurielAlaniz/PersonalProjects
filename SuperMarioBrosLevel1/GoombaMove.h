#include "MoveComponent.h"
class GoombaMove : public MoveComponent
{
public:
	GoombaMove(class Goomba* owner);
	void Update(float deltaTime) override;

private:
	Goomba* mGomb;
	float mYSpeed;
	bool mInAir = false;
};