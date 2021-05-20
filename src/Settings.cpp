#include "../include/Settings.h"

void fillAdditional(std::vector<userSprite>& Minimap,
					std::vector <userImages>& MinimapTextures,
					const std::vector<std::string>& tMinimapPath,
					Vector <float> MinimapPos,
					std::vector<std::pair<userImages, userImages>>& AddTextures,
					GameSettings gameSettings) {

    for (unsigned int i = 0; i < MinimapTextures.size(); ++i) {
        MinimapTextures[i].loadTexture(tMinimapPath[i]);
        userSprite map(MinimapTextures[i]);
        map.setPos(MinimapPos.x, MinimapPos.y);
        Minimap.push_back(map);
    }
		AddTextures[0].first.loadTexture("images/EazyPressed.png");
		AddTextures[0].second.loadTexture("images/Hard.png");
		AddTextures[1].first.loadTexture("images/Eazy.png");
		AddTextures[1].second.loadTexture("images/HardPressed.png");
}

void switchDifficulty(std::vector<userSprite>& Buttons, std::vector<std::pair<userImages, userImages>>& AddTextures, bool isPressed) {
	Buttons[0].setTexture(AddTextures[isPressed].first, true);
	Buttons[1].setTexture(AddTextures[isPressed].second, true);
}


void Settings(userRenderWindow& Window, GameSettings& gameSettings) {
	std::vector <std::string> tButtonPath;

	if (gameSettings.Hard == false) {
		tButtonPath.push_back("images/EazyPressed.png");
		tButtonPath.push_back("images/Hard.png");
	}
	else {
		tButtonPath.push_back("images/Eazy.png");
		tButtonPath.push_back("images/HardPressed.png");
	}
	tButtonPath.push_back("images/RButton.png");
	tButtonPath.push_back("images/LButton.png");
	tButtonPath.push_back("images/Back.png");

	
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
													{ 704, 156 },
													{ 160, 156 },
													{ 48, 528 }
    };

	std::vector<std::pair<userImages, userImages>> AdditionalTextures(2);

    std::vector <userSprite> Minimap;
	std::vector <userSprite> Buttons;
	std::vector <userSprite> Background;
	bool goBack = false;
	Vector<int> Pos = { 0, 0 };

	loadAdditionalWindowTextures(Buttons, ButtonPos, tButtonPath, ButtonTextures, Background, tBackgroundPath, tBackground);
	srand(static_cast <unsigned int> (time(0)));
    fillAdditional(Minimap, MinimapTextures, tMinimapPath, MinimapPos, AdditionalTextures, gameSettings);
    
    userClock Clock;
    float deltaTime;
    float switchTime = 0.15f;
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
						switchDifficulty(Buttons, AdditionalTextures, false);
						gameSettings.Hard = false;
						break;
					case 1: // Hard mode
						switchDifficulty(Buttons, AdditionalTextures, true);
						gameSettings.Hard = true;
						break;
					case 2: // Switch Rigth
						gameSettings.MapNumber = (gameSettings.MapNumber + 1) % 3;
						break;
					case 3: //Switch Left
						gameSettings.MapNumber = (gameSettings.MapNumber + 2) % 3;
						break;
					case 4: // Go to menu
						goBack = true;
						break;
					}
				}
			}
		}
        std::vector <userSprite> CurrentMap = { Minimap[gameSettings.MapNumber] };
		AdditionalWindowDraw(Window, Buttons, Background, CurrentMap);
	}
}
