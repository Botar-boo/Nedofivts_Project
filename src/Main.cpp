#include "../include/Menu.h"

// Start program

int main() {
	GameSettings gameSettings = { false, 0 };
	userRenderWindow App(windowWidth, windowHeight, "TD");
	App.setFramerateLim(60);
	while (true) {
		Menu(App, gameSettings);
		Gameplay(roundsToWin, App, gameSettings);
	}
	return 0;
}
