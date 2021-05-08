#include "Settings.h"

void fillMinimap(std::vector<userSprite>& Minimap, std::vector <userImages>& MinimapTextures, const std::vector<std::string>& tMinimapPath, Vector <float> MinimapPos) {
    for (int i = 0; i < MinimapTextures.size(); ++i) {
        MinimapTextures[i].loadTexture(tMinimapPath[i]);
        userSprite map(MinimapTextures[i]);
        map.setPos(MinimapPos.x, MinimapPos.y);
        Minimap.push_back(map);
    }
}


void Settings(userRenderWindow& Window, GameSettings& gameSettings) {
	const std::vector <std::string> tButtonPath = {
		"images/Eazy.png",
		"images/Hard.png",
		"images/Back.png",
		"images/RButton.png",
		"images/LButton.png"
    };
    const std::vector <std::string> tMinimapPath = {
        "images/Minimap1.png",
        "images/Minimap2.png",
        "images/Minimap3.png"
    };

	const std::string tBackgroundPath = "images/GrassGround.png";

    const int MapQuantity = 3;
    std::vector <userImages> MinimapTextures(tMinimapPath.size());
	std::vector <userImages> ButtonTextures(tButtonPath.size());
	userImages tBackground;

    Vector <float> MinimapPos = { 320, 100 };
	const std::vector <Vector<float>> ButtonPos = { { 234, 402 },
													{ 534, 402 },
													{ 48, 528 },
													{ 704, 156 },
													{ 160, 156 }
    };

    std::vector <userSprite> Minimap;
	std::vector <userSprite> Buttons;
	std::vector <userSprite> Background;
	bool goBack = false;
	Vector<int> Pos = { 0, 0 };

	loadAdditionalWindowTextures(Buttons, ButtonPos, tButtonPath, ButtonTextures, Background, tBackgroundPath, tBackground);
	srand(static_cast <unsigned int> (time(0)));
    fillMinimap(Minimap, MinimapTextures, tMinimapPath, MinimapPos);
    
    userClock Clock;
    float deltaTime;
    float switchTime = 0.15;
    float totalTime = 0;

	while (Window.isOpen() && !goBack) {
        deltaTime = Clock.restart().asSeconds();
        totalTime += deltaTime;
		userEvent e;
		while (Window.pollEvent(e))
			if (e.type == userEvent::Closed) {
				Window.close();
				exit(0);
			}
        
		Vector<float> Pos = { 0.f, 0.f };
		userMouse mouse;
        if (totalTime > switchTime) {
            totalTime -= switchTime;
            if (mouse.buttonPressed('L')) {
			    Pos = { mouse.getPos(Window).x, mouse.getPos(Window).y };
            }
            for (unsigned int i = 0; i < Buttons.size(); i++) {
			    Vector<float> buttonCenter = findCentre(Buttons[i].gGB());
			    if ((Pos.y > buttonCenter.y - Buttons[i].gGB().height / 2) &&
				    (Pos.y < buttonCenter.y + Buttons[i].gGB().height / 2) &&
				    (Pos.x > buttonCenter.x - Buttons[i].gGB().width / 2) &&
				    (Pos.x < buttonCenter.x + Buttons[i].gGB().width / 2)) {
				    switch (i) {
				    case 0: // Eazy mode
					    gameSettings.Hard = false;
					    break;
				    case 1: // Hard mode
					    gameSettings.Hard = true;
					    break;
				    case 2: // Go to menu
					    goBack = true;
					    break;
				    case 3: // Switch Rigth
					    gameSettings.MapNumber = (gameSettings.MapNumber + 1) % 3;
					    break;
				    case 4: //Switch Left
					    gameSettings.MapNumber = (gameSettings.MapNumber + 2) % 3;
					    break;
				    }
			    }
            }
		}
        std::vector <userSprite> CurrentMap = { Minimap[gameSettings.MapNumber] };
		AdditionalWindowDraw(Window, Buttons, Background, CurrentMap);
	}
}
