#ifndef _WIN32
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include "../BallPhysics.h"
#include "../RampPhysics.h"
#include "../PipePhysics.h"
#include "../AntigravityPhysics.h"
#include "../BucketPhysics.h"
#include "../ConveyorPhysics.h"
#include "../QuaterPipePhysics.h"
#include "../SpringBoardPhysics.h"
#include "../PhysicsWorld.h"

using namespace boost::unit_test;

bool floatEqual(float f1, float f2)
{
	static float epsilon = 0.00001f;
	return fabs(f1 - f2) < epsilon;
}

void worldAddElement()
{
	PhysicsWorld world(new CPhysicsWorld);

	BallPhysics ball(new CBallPhysics(100));
	world->addElement(ball, 120, 100);
	BOOST_CHECK_MESSAGE((floatEqual(ball->positionX(), 120)) && (floatEqual(ball->positionY(), 100)),
		"(Ball) Pozycja (" << ball->positionX() << "," << ball->positionY() << ") - Powinno byæ (120, 100)");

	RampPhysics ramp(new CRampPhysics(100, 100, 0.0l));
	world->addElement(ramp, 0, 0);
	BOOST_CHECK_MESSAGE((floatEqual(ramp->positionX(), 0)) && (floatEqual(ramp->positionY(), 0)),
		"(Ramp) Pozycja (" << ramp->positionX() << "," << ramp->positionY() << ") - Powinno byæ (0, 0)");

	PipePhysics pipe(new CPipePhysics(100, 100, 0.0l));
	world->addElement(pipe, 0, 0);
	BOOST_CHECK_MESSAGE((floatEqual(pipe->positionX(), 0)) && (floatEqual(pipe->positionY(), 0)),
		"(Pipe) Pozycja (" << pipe->positionX() << "," << pipe->positionY() << ") - Powinno byæ (0, 0)");

	AntigravityPhysics anti(new CAntigravityPhysics(100, 100, 100));
	world->addElement(anti, 10, 10);
	BOOST_CHECK_MESSAGE((floatEqual(anti->positionX(), 10)) && (floatEqual(anti->positionY(), 10)),
		"(Antigravity) Pozycja (" << anti->positionX() << "," << anti->positionY() << ") - Powinno byæ (10, 10)");

	BucketPhysics bucket(new CBucketPhysics(100, 100, 0.0l));
	world->addElement(bucket, 20, 20);
	BOOST_CHECK_MESSAGE((floatEqual(bucket->positionX(), 20)) && (floatEqual(bucket->positionY(), 20)),
		"(Bucket) Pozycja (" << bucket->positionX() << "," << bucket->positionY() << ") - Powinno byæ (20, 20)");

	ConveyorPhysics conv(new CConveyorPhysics(100, 100, 0.2l));
	world->addElement(conv, 30, 30);
	BOOST_CHECK_MESSAGE((floatEqual(conv->positionX(), 30)) && (floatEqual(conv->positionY(), 30)),
		"(Conveyor) Pozycja (" << conv->positionX() << "," << conv->positionY() << ") - Powinno byæ (30, 30)");

	QuaterPipePhysics qpipe(new CQuaterPipePhysics(100, 100, 0.0l));
	world->addElement(qpipe, 40, 40);
	BOOST_CHECK_MESSAGE((floatEqual(qpipe->positionX(), 40)) && (floatEqual(qpipe->positionY(), 40)),
		"(QuaterPipe) Pozycja (" << qpipe->positionX() << "," << qpipe->positionY() << ") - Powinno byæ (40, 40)");

	SpringBoardPhysics spring(new CSpringBoardPhysics(100, 100, 0.0l));
	world->addElement(spring, 50, 50);
	BOOST_CHECK_MESSAGE((floatEqual(spring->positionX(), 50)) && (floatEqual(spring->positionY(), 50)),
		"(SpringBoard) Pozycja (" << spring->positionX() << "," << spring->positionY() << ") - Powinno byæ (50, 50)");
}

void worldRemoveElement()
{
	PhysicsWorld world(new CPhysicsWorld);

	BallPhysics ball(new CBallPhysics(100));
	world->addElement(ball, 120, 100);

	RampPhysics ramp(new CRampPhysics(100, 100, 0.0l));
	world->addElement(ramp, 0, 0);

	PipePhysics pipe(new CPipePhysics(100, 100, 0.0l));
	world->addElement(pipe, 0, 0);
	
	AntigravityPhysics anti(new CAntigravityPhysics(100, 100, 100));
	world->addElement(anti, 10, 10);

	BucketPhysics bucket(new CBucketPhysics(100, 100, 0.0l));
	world->addElement(bucket, 20, 20);

	ConveyorPhysics conv(new CConveyorPhysics(100, 100, 0.2l));
	world->addElement(conv, 30, 30);

	QuaterPipePhysics qpipe(new CQuaterPipePhysics(100, 100, 0.0l));
	world->addElement(qpipe, 40, 40);

	SpringBoardPhysics spring(new CSpringBoardPhysics(100, 100, 0.0l));
	world->addElement(spring, 50, 50);

	BOOST_CHECK_NO_THROW(world->removeElement(ball));
	BOOST_CHECK_NO_THROW(world->removeElement(ramp));
	BOOST_CHECK_NO_THROW(world->removeElement(pipe));
	BOOST_CHECK_NO_THROW(world->removeElement(anti));
	BOOST_CHECK_NO_THROW(world->removeElement(bucket));
	BOOST_CHECK_NO_THROW(world->removeElement(conv));
	BOOST_CHECK_NO_THROW(world->removeElement(qpipe));
	BOOST_CHECK_NO_THROW(world->removeElement(spring));
}

#ifndef _WIN32
BOOST_AUTO_TEST_SUITE( test )
BOOST_AUTO_TEST_CASE( world_add_test )
{
	worldAddElement();
}

BOOST_AUTO_TEST_CASE( world_remove_test )
{
	worldRemoveElement();
}

BOOST_AUTO_TEST_SUITE_END()

#else
test_suite* init_unit_test_suite(int argc,char* argv[])
{
	test_suite* suite=BOOST_TEST_SUITE("Test silnika fizyki");
	suite->add(BOOST_TEST_CASE(worldAddElement));
	suite->add(BOOST_TEST_CASE(worldRemoveElement));
	return suite;
}
#endif