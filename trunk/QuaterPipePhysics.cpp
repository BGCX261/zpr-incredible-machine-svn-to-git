#include "QuaterPipePhysics.h"

//=====================================================================

CQuaterPipePhysics::CQuaterPipePhysics(int size, int pipeWidth, float angle) 
	: size_(size / 100.0f), pipeWidth_(pipeWidth / 100.0f), 
	  angle_(-b2_pi * angle / 180.0f)
{
}

//=====================================================================

CQuaterPipePhysics::~CQuaterPipePhysics(void)
{
}

//=====================================================================

void CQuaterPipePhysics::do_addToWorld(b2World *world, const b2Vec2 &pos)
{	
	b2BodyDef bd;
	bd.position.Set(pos.x, pos.y);
	bd.angle = angle_;					
	body_ = world->CreateBody(&bd);	

	int32 complexity = 15;

	float32 x1 = size_ * cosf(3 * b2_pi / 2) - size_ / 2;
	float32 y1 = size_ * sinf(3 * b2_pi / 2) + size_ / 2;

	for (int32 i = 0; i <= complexity; ++i)
	{
		float32 x2 = size_ * cosf((i / float32(complexity)) * (b2_pi / 2) + 3 * b2_pi / 2) - size_ / 2;
		float32 y2 = size_ * sinf((i / float32(complexity)) * (b2_pi / 2) + 3 * b2_pi / 2) + size_ / 2;

		b2PolygonShape shape;
		shape.SetAsEdge(b2Vec2(x1, y1), b2Vec2(x2, y2));
		body_->CreateFixture(&shape, 0.0f);

		x1 = x2;
		y1 = y2;
	}
	
	x1 = (size_ - pipeWidth_) * cosf(3 * b2_pi / 2) - size_ / 2;
	y1 = (size_ - pipeWidth_) * sinf(3 * b2_pi / 2) + size_ / 2;

	for (int32 i = 0; i <= complexity; ++i)
	{
		float32 x2 = (size_ - pipeWidth_) * cosf((i / float32(complexity)) * (b2_pi / 2) + 3 * b2_pi / 2) - size_ / 2;
		float32 y2 = (size_ - pipeWidth_) * sinf((i / float32(complexity)) * (b2_pi / 2) + 3 * b2_pi / 2) + size_ / 2;

		b2PolygonShape shape;
		shape.SetAsEdge(b2Vec2(x1, y1), b2Vec2(x2, y2));
		body_->CreateFixture(&shape, 0.0f);

		x1 = x2;
		y1 = y2;
	}
}

//=====================================================================

void CQuaterPipePhysics::do_removeFromWorld(b2World *world)
{
	world->DestroyBody(body_);
	body_ = 0L;
}

//=====================================================================

