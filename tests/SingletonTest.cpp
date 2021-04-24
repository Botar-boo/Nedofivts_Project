#include "SingletonTestCase.h"
#include "Game.h"

TEST_F(SingletonTestCase, SingletonTest) {
Game* instance1 = Game* get_instance();
Game* instance2 = Game* get_instance();
ASSERT_EQ(instance1, instance2);
}
