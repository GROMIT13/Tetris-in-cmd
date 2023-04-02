#pragma once
#include "..\Engine\DataStructures\Rect.hpp"
#include "..\Log.hpp"

class Tetromino : public Rect
{
public:

	enum class Type : char
	{
		I_BLOCK = 0,
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
	Type blockType;
	Sprite* sprite;

public:
	Tetromino(int x, int y,Type blockType);
	void ChangeBlock(Type blockType);
};
