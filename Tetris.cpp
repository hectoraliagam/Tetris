#include "raylib.h"

int main()
{
	Color darkBlue = { 41, 41, 120, 255 };
	InitWindow(300, 600, "Tetris with Raylib");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(darkBlue);

		EndDrawing();
	}

	CloseWindow();
}
