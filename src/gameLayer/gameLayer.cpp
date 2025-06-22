#define GLM_ENABLE_EXPERIMENTAL
#include "gameLayer.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "platformInput.h"
#include "imgui.h"
#include <iostream>
#include <sstream>
#include "imfilebrowser.h"
#include <gl2d/gl2d.h>
#include <platformTools.h>
#include <IconsForkAwesome.h>
#include <imguiTools.h>
#include <logs.h>
#include <string>
#include <vector>
#include <filesystem>
#include <player.h>

// const char* RESOURCES_PATH = "~/Documents/Coding\ Projects/Platformer\ game/cmakeSetup/resources";

// static constexpr const char* RESOURCES_PATH = "~/Documents/Coding\xa0Projects/Platformer\xa0Game/cmakeSetup/resources/";

struct GameData
{
	glm::vec2 rectPos = {100,100};

} gameData;

gl2d::Renderer2D renderer;

gl2d::Texture minecraft;

gl2d::Texture knightTexture;
gl2d::TextureAtlasPadding knightAtlas;


Player knight;



bool initGame()
{
	//initializing stuff for the renderer
	gl2d::init();
	renderer.create();

	//textures
	knightTexture.loadFromFileWithPixelPadding(RESOURCES_PATH "brackeys/sprites/knight.png", 32, true);
	knightAtlas = gl2d::TextureAtlasPadding(8, 8, knightTexture.GetSize().x, knightTexture.GetSize().y);

	knight.spawn();

	//loading the saved data. Loading an entire structure like this makes savind game data very easy.
	platform::readEntireFile(RESOURCES_PATH "gameData.data", &gameData, sizeof(GameData));

	platform::log("Init");

	return true;
}


//IMPORTANT NOTICE, IF YOU WANT TO SHIP THE GAME TO ANOTHER PC READ THE README.MD IN THE GITHUB
//https://github.com/meemknight/cmakeSetup
//OR THE INSTRUCTION IN THE CMAKE FILE.
//YOU HAVE TO CHANGE A FLAG IN THE CMAKE SO THAT RESOURCES_PATH POINTS TO RELATIVE PATHS
//BECAUSE OF SOME CMAKE PROGBLMS, RESOURCES_PATH IS SET TO BE ABSOLUTE DURING PRODUCTION FOR MAKING IT EASIER.

bool gameLogic(float deltaTime, platform::Input &input)
{
#pragma region init stuff
	int w = 0; int h = 0;
	w = platform::getFrameBufferSizeX(); //window w
	h = platform::getFrameBufferSizeY(); //window h
	
	glViewport(0, 0, w, h);
	glClear(GL_COLOR_BUFFER_BIT); //clear screen

	renderer.updateWindowMetrics(w, h);
#pragma endregion

	//you can also do platform::isButtonHeld(platform::Button::Left)

#pragma region movement

	if (input.isButtonHeld(platform::Button::Left))
	{
		gameData.rectPos.x -= deltaTime * 100;
	}
	if (input.isButtonHeld(platform::Button::Right))
	{
		gameData.rectPos.x += deltaTime * 100;
	}
	if (input.isButtonHeld(platform::Button::Up))
	{
		gameData.rectPos.y -= deltaTime * 100;
	}
	if (input.isButtonHeld(platform::Button::Down))
	{
		gameData.rectPos.y += deltaTime * 100;
	}

	knight.update(deltaTime, input);



#pragma endregion



	gameData.rectPos = glm::clamp(gameData.rectPos, glm::vec2{0,0}, glm::vec2{w - 100,h - 100});	

	knight.render(
		renderer,
		gameData.rectPos,
		100, //size
		knightTexture,
		knightAtlas
	);

	// renderer.renderRectangle({gameData.rectPos, 100, 100}, knightTexture, Colors_White, {}, 0, knightAtlas.get(0, 0));
	// renderer.renderRectangle({gameData.rectPos, 100, 100}, knightTexture);
	// renderer.renderRectangle({gameData.rectPos, 100, 100}, Colors_Blue);

	renderer.flush();

	//ImGui::ShowDemoWindow();
	ImGui::PushMakeWindowNotTransparent();
	ImGui::Begin("Test Imgui");

	ImGui::DragFloat2("Positions", &gameData.rectPos[0]);
	ImGui::DragFloat2("Direction (x, y)", &knight.forcingDirection.x);
	// ImGui::Int("SpriteIndex", &*knight.spriteIndex);

	ImGui::Text("Sprite Index %d", *knight.spriteIndex);

	ImGui::Text("Is Moving? %d", knight.isMoving);
	ImGui::Text("Is Idle? %d", knight.isIdle);

	ImGui::Text("Emoji moment: " ICON_FK_AMBULANCE);

	ImGui::helpMarker("test");

	ImGui::addErrorSymbol();
	ImGui::addWarningSymbol();

	ImGui::BeginChildFrameColoured(1, Colors_Gray, {100,100}, 0);

	ImGui::Text("Test");

	ImGui::EndChildFrame();


	ImGui::PopMakeWindowNotTransparent();
	ImGui::End();

	return true;
#pragma endregion

}

//This function might not be be called if the program is forced closed
void closeGame()
{

	//saved the data.
	platform::writeEntireFile(RESOURCES_PATH "gameData.data", &gameData, sizeof(GameData));

}
