#include "SingletonTest.h"

TEST_F(SingletonTestCase, SingletonTest) {
	Game* game1 = Game::get_instance();
	Game* game2 = Game::get_instance();
	ASSERT_EQ(game1, game2);
}

TEST_F(SingletonTestCase, TypeTest) {
	Game* game1 = Game::get_instance();
	Game* game2 = Game::get_instance();
	ASSERT_EQ(typeid(game1), typeid(game2));
}

TEST_F(SingletonTestCase, GameOverTest) {
	Game* game1 = Game::get_instance();
	game1->startGame(true);
	ASSERT_EQ(false, game1->get_gameOver());
}

TEST_F(SingletonTestCase, SwitchGameOverTest) {
	Game* game1 = Game::get_instance();
	game1->startGame(true);
	game1->switch_gameOver();
	ASSERT_EQ(true, game1->get_gameOver());
}

TEST_F(SingletonTestCase, Game1SetGameOverTest) {
	Game* game1 = Game::get_instance();
	Game* game2 = Game::get_instance();
	game1->startGame(true);
	game2->switch_gameOver();
	ASSERT_EQ(true, game1->get_gameOver());
}

TEST_F(SingletonTestCase, EazyTest) {
	Game* game1 = Game::get_instance();
	game1->startGame(true);
	ASSERT_EQ(true, game1->get_difficulty());
}

TEST_F(SingletonTestCase, HardTest) {
	Game* game1 = Game::get_instance();
	game1->startGame(false);
	ASSERT_EQ(false, game1->get_difficulty());
}
