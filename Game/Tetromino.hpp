#pragma once
#include "..\Engine\DataStructures\Rect.hpp"
#include "..\Engine\Input.hpp"
#include "..\Engine\Time.hpp"
#include "..\Log.hpp"
#include "Board.hpp"

class Board;

class Tetromino : public Rect
{
public:

	enum class Type : char
	{
		NULL_BLOCK = 0,
		I_BLOCK,
		O_BLOCK,
		J_BLOCK,
		L_BLOCK,
		Z_BLOCK,
		S_BLOCK,
		T_BLOCK
	};

	class Sprite
	{
	private:
		CHAR_INFO* I;	//[4 * 4]
		CHAR_INFO* O;	//[4 * 4]
		CHAR_INFO* J;	//[3 * 3]
		CHAR_INFO* L;	//[3 * 3]
		CHAR_INFO* Z;	//[3 * 3]
		CHAR_INFO* S;	//[3 * 3]
		CHAR_INFO* T;	//[3 * 3]
	public:
		Sprite();
		~Sprite();
		CHAR_INFO* GetSprite(Type blockType);
	};
private:
	Board& board;
	Type blockType;
	Sprite* sprite;
	Rect* rotateRect;
	Clock* updateClock;
	Clock* horizontalMovementClock;
	unsigned long long updateSpeed;

public:
	Tetromino(int x, int y, unsigned long long updateSpeed, Board& board);
	CHAR_INFO* GetSprite(Type blockType) const;
	void ChangeBlock(Type blockType);
	void Rotate(unsigned int rotations);
	void Reset();
	bool DoesFit(int x, int y);
	void Update();
	void DrawTetromino(GConsole& screen);
	//Movement
	void HoldTetromino();
	void HardDrop();
};
