#include "SingletonTest.h"

TEST_F(SingletonTestCase, SingletonTest) {
	Game* game1 = Game::get_instance();
	Game* game2 = Game::get_instance();
ASSERT_EQ(game1, game2);
}
