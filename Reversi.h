#ifndef REVERSI_H
#define REVERSI_H

#define REVERSI_BOARD_ELEMENT_EMPTY 0
#define REVERSI_BOARD_ELEMENT_LIGHT 2
#define REVERSI_BOARD_ELEMENT_DARK -2
#define REVERSI_BOARD_ELEMENT_VAILD_LIGHT 1
#define REVERSI_BOARD_ELEMENT_VAILD_DARK -1

#define REVERSI_TURN_DARK true
#define REVERSI_TURN_LIGHT false

#define REVERSI_RESULT_DARK -1
#define REVERSI_RESULT_LIGHT -2
#define REVERSI_RESULT_DRAW -3

#include <vector>
#include <iostream>

class Reversi {
private:
	unsigned int rowSize, colSize;
	unsigned int diskNum;

	//unsigned int vaildLightNum, vaildDarkNum;

	void ReplaceColor(unsigned int newRowIdx, unsigned int newColIdx, bool newColor);
	unsigned int ValidPosUpdate(bool Color);
	unsigned int CountDisks(bool Color);
public:
	bool turn;
	short** board; // [0][0] at top left

	Reversi(unsigned int colSize = 8, unsigned  int rowSize = 8);

	int Put(unsigned int rowIdx, unsigned int colIdx);
	int Put(unsigned int rowIdx, unsigned int colIdx, bool turn);

	void NewGame();
	void Delete();
};

#endif