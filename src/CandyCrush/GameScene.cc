/******************************************************************
* Copyright (C) 2016 Jordi Serrano Berbel <jsberbel95@gmail.com> *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "GameScene.hh"
using namespace Logger;

/*#define CELL_WIDTH 80
#define CELL_HEIGHT 80*/

int X_X = 512;
int Y_Y = 360;

int XD = X_X;
int YD = Y_Y;



GameScene::GameScene(void) {
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };
	player_sprite = { { X_X, Y_Y, W.GetWidth()/10, W.GetHeight()/10}, ObjectID::PLAYER };
	disparo = { { X_X, Y_Y, W.GetWidth()/20, W.GetHeight() / 20 }, ObjectID::CANDY_BLUE };
}

GameScene::~GameScene(void){
}

void GameScene::OnEntry(void) {
}

void GameScene::OnExit(void) {
}

void GameScene::Update(void) {
	static MouseCoords mouseCoords(0,0);

	if (IM.IsKeyHold<KEY_BUTTON_LEFT>()) {
		Println("LEFT");
		if (X_X > 0) {
			X_X -= 1;
		}
		
	}

	if (IM.IsKeyHold<KEY_BUTTON_RIGHT>()) {
		Println("RIGHT");
		if (X_X < 920) {
			X_X += 1;
		}
	}

	if (IM.IsKeyHold<KEY_BUTTON_UP>()) {
		Println("UP");
		
		if (Y_Y > 0) {
			Y_Y -= 1;
		}
	}

	if (IM.IsKeyHold<KEY_BUTTON_DOWN>()) {
		Println("DOWN");
		if (Y_Y < 700) {
			Y_Y += 1;
		}
	}

	if (IM.IsKeyHold<KEY_BUTTON_LCTRL>()) {
		Println("SHOOOOOOOOOOOOOOOOOT");

			YD -= 1;
			disparo = { { XD , YD, W.GetWidth() / 20 , W.GetHeight() / 20 }, ObjectID::CANDY_BLUE };

	}
	else {
		disparo = { { X_X , Y_Y, W.GetWidth() / 20 , W.GetHeight() / 20 }, ObjectID::CANDY_BLUE };
		XD = X_X;
		YD = Y_Y;
	}

	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		//Println("===============");
		//Println("mxp: ", mouseCoords);
		mouseCoords = IM.GetMouseCoords();
		
	
		

		//disparo = { { xx, yy, W.GetWidth()/20 , W.GetHeight()/20 }, ObjectID::CANDY_BLUE };

	} else if (IM.IsMouseUp<MOUSE_BUTTON_LEFT>()) {
		//Println("mxn: ", IM.GetMouseCoords());
		//m_grid.CheckMouseSwift(mouseCoords, IM.GetMouseCoords());
	}
	//m_grid.Update(m_score); // Update grid
	// Test InputManager key methods
	//if (IM.IsKeyHold<'a'>()) Println("a hold");
	//if (IM.IsKeyDown<'0'>()) Println("0 down");

	
	
	
	
	player_sprite = { { X_X, Y_Y, W.GetWidth() / 10, W.GetHeight() / 10 }, ObjectID::PLAYER };
}

void GameScene::Draw(void) {
	m_background.Draw(); // Render background
	//m_grid.Draw(); // Render grid
	player_sprite.Draw();
	disparo.Draw();
	GUI::DrawTextShaded<FontID::FACTORY>("ENTI CRUSH",
										{ W.GetWidth() >> 1, int(W.GetHeight()*.1f), 1, 1 }, 
										{ 190, 0, 160 }, { 50, 200, 230 }); // Render score that will be different when updated

	/*GUI::DrawTextBlended<FontID::CANDY>("Score: " + std::to_string(m_score), 
										{ W.GetWidth() >> 1, int(W.GetHeight()*.9f), 1, 1 }, 
										{ 115, 0, 180 }); // Render score that will be different when updated*/
}
