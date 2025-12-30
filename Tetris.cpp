#include <raylib.h>
#include "game.h"
#include "colors.h"

double lastUpdateTime = 0;

bool EventTriggered(double interval) {
	double currentTime = GetTime();
	if (currentTime - lastUpdateTime >= interval) {
		lastUpdateTime = currentTime;
		return true;
	}
	return false;
}

int main()
{
	InitWindow(500, 620, "Tetris with Raylib");
	SetTargetFPS(60);

	Font font = LoadFontEx("assets/fonts/monogram.ttf", 64, 0, 0);

	Game game = Game();

	while (!WindowShouldClose()) {
		game.HandleInput();
		if (EventTriggered(0.2)) {
			game.MoveBlockDown();
		}

		BeginDrawing();
		ClearBackground(darkBlue);
		DrawTextEx(font, "Score", { 365, 15 }, 28, 2, WHITE);
		DrawTextEx(font, "Next", { 370, 175 }, 32, 2, WHITE);
		if (game.gameOver) {
			DrawTextEx(font, "GAME OVER", { 320, 450 }, 29, 2, WHITE);
		}
		DrawRectangleRounded({ 320, 55, 170, 60 }, 0.3, 6, lightBlue);
		DrawRectangleRounded({ 320, 215, 170, 180 }, 0.3, 6, lightBlue);
		game.Draw();
		EndDrawing();
	}

	CloseWindow();
}
