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
	int rotationState;
	Board& board;
	Type blockType;
	Sprite* sprite;
	Rect* rotateRect;
	Clock* updateClock;
	unsigned long long updateSpeed;

	//SRS WALLKICK DATA
	static std::vector<Vec2> JLZST_wallkickData;
	static std::vector<Vec2> I_wallkickData;

public:
	Tetromino(int x, int y, Board& board);
	CHAR_INFO* GetSprite(Type blockType) const;
	void ChangeBlock(Type blockType);
	void Rotate(unsigned int rotations);
	void Reset();
	int  CalculateUpdateSpeed();
	bool DoesFit(Rect& tetromino, int x, int y);
	bool DoesFit(Rect& tetromino, Vec2 position);
	void SRS(int rotations);
	void InitSRS();
	void Update();
	void DrawTetromino(GConsole& screen);
	void IfCantMoveDown();
	void IfRotationFits(int rotations,Vec2& offset);
	//Movement
	void MoveVertically();
	void MoveHorizontally();
	void MoveRotation();
	void HoldTetromino();
	void HardDrop();
};
