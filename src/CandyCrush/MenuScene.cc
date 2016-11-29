#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "MenuScene.hh"
#include "SceneManager.hh"
#include "GameScene.hh"

using namespace Logger;

#define CELL_WIDTH 80
#define CELL_HEIGHT 80

MenuScene::MenuScene(void) {
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };
}

MenuScene::~MenuScene(void) {
}

void MenuScene::OnEntry(void) {
}

void MenuScene::OnExit(void) {
}

void MenuScene::Update(void) {
	static MouseCoords mouseCoords(0, 0);
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		Println("===============");
		Println("mxp: ", mouseCoords);
		mouseCoords = IM.GetMouseCoords();
		if (mouseCoords.x < 586 && mouseCoords.x > 438 && mouseCoords.y < 423 && mouseCoords.y > 346) {
			SetState<SceneState::EXIT>();
		}
		if (mouseCoords.x < 586 && mouseCoords.x > 438 && mouseCoords.y < 268 && mouseCoords.y > 191) {
			SM.SetCurScene<GameScene>();
		}
	}
	else if (IM.IsMouseUp<MOUSE_BUTTON_LEFT>()) {
		Println("mxn: ", IM.GetMouseCoords());
		
	}
	
							// Test InputManager key methods
	if (IM.IsKeyHold<'a'>()) Println("a hold");
	if (IM.IsKeyDown<'0'>()) Println("0 down");
	if (IM.IsKeyUp<KEY_BUTTON_DOWN>()) Println("down arrow up");
}

void MenuScene::Draw(void) {
	m_background.Draw(); // Render background
	GUI::DrawTextShaded<FontID::FACTORY>("MENU",
			{ W.GetWidth() >> 1, int(W.GetHeight()*.1f), 1, 1 },
			{ 255, 255, 255 }, { 200, 20, 20 });

	GUI::DrawTextShaded<FontID::FACTORY>("PLAY",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.3f), 1, 1 },
	{ 255, 255, 255 }, { 200, 20, 20 });

	GUI::DrawTextShaded<FontID::FACTORY>("EXIT",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.5f), 1, 1 },
	{ 255, 255, 255 }, { 200, 20, 20 });
	
}
