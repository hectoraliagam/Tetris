#include "game.h"
#include <random>

Game::Game() {
	grid = Grid();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
}

Block Game::GetRandomBlock() {
	if (blocks.empty()) {
		blocks = GetAllBlocks();
	}
	// Old (deprecated)
	//int randomIndex = rand() % blocks.size();

	// New Pro version
	static std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> dist(0, blocks.size() - 1);
	int randomIndex = dist(rng);

	Block block = blocks[randomIndex];
	blocks.erase(blocks.begin() + randomIndex);
	return block;
}

std::vector<Block> Game::GetAllBlocks() {
	return { IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock() };
}

void Game::Draw() {
	grid.Draw();
	currentBlock.Draw();
}

void Game::HandleInput() {
	int keyPressed = GetKeyPressed();
	switch (keyPressed) {
	case KEY_LEFT:
		MoveBlockLeft();
		break;
	case KEY_RIGHT:
		MoveBlockRight();
		break;
	case KEY_DOWN:
		MoveBlockDown();
		break;
	case KEY_UP:
		RotateBlock();
		break;
	}
}

void Game::MoveBlockLeft() {
	currentBlock.Move(0, -1);
	if (IsBlockOutside() || !BlockFits()) {
		currentBlock.Move(0, 1);
	}
}

void Game::MoveBlockRight() {
	currentBlock.Move(0, 1);
	if (IsBlockOutside() || !BlockFits()) {
		currentBlock.Move(0, -1);
	}
}

void Game::MoveBlockDown() {
	currentBlock.Move(1, 0);
	if (IsBlockOutside() || !BlockFits()) {
		currentBlock.Move(-1, 0);
		LockBlock();
	}
}

bool Game::IsBlockOutside() {
	std::vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item : tiles) {
		if (grid.IsCellOutside(item.row, item.column)) {
			return true;
		}
	}
	return false;
}

void Game::RotateBlock() {
	currentBlock.Rotate();
	if (IsBlockOutside() || !BlockFits()) {
		currentBlock.UndoRotation();
	}
}

void Game::LockBlock() {
	std::vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item : tiles) {
		grid.grid[item.row][item.column] = currentBlock.id;
	}
	currentBlock = nextBlock;
	nextBlock = GetRandomBlock();
}

bool Game::BlockFits()
{
	std::vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item : tiles) {
		if (grid.IsCellEmpty(item.row, item.column) == false) {
			return false;
		}
	}
	return true;
}
