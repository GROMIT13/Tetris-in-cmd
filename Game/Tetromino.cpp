#include "Tetromino.hpp"

Tetromino::Tetromino(int x, int y, Type blockType)
	:Rect(x, y, 4, 4), blockType(blockType)
{
	rotateRect = new Rect(x,y,4,4);
	sprite = new Sprite;
	ChangeBlock(blockType);
}

void Tetromino::ChangeBlock(Type blockType)
{
	if (blockType == Type::NULL_BLOCK)
		return;
	this->blockType = blockType;
	ClearBuffer();
	switch (blockType)
	{
	case Type::I_BLOCK:
		memcpy(GetBuffer(), sprite->GetSprite(blockType), sizeof(CHAR_INFO) * 4 * 4);
		SetDimension(4, 4);
		break;
	case Type::O_BLOCK:
	case Type::J_BLOCK:
	case Type::L_BLOCK:
	case Type::Z_BLOCK:
	case Type::S_BLOCK:
	case Type::T_BLOCK:
		memcpy(GetBuffer(), sprite->GetSprite(blockType), sizeof(CHAR_INFO) * 3 * 3);
		SetDimension(3, 3);
		break;
	default:
	Log log("TetrominoSpriteError.txt");
	log.Error("In file Tetromino.cpp, in line " + std::to_string(__LINE__) + " unknown block type, changed block to I block");
		break;
	}
}

void Tetromino::Rotate(unsigned int rotations)
{
	int y = 0;
	*rotateRect = *this;
	for (int i = 0; i < rotateRect->GetDimension().x * rotateRect->GetDimension().y; i++)
	{
		switch (rotations % 4)
		{
		case 1:
			if (i % rotateRect->GetDimension().x == 0 && i != 0)
				y++;
			rotateRect->GetBuffer()[rotateRect->GetDimension().x * (rotateRect->GetDimension().y - 1) + y - (rotateRect->GetDimension().y * (i % rotateRect->GetDimension().x))] = this->GetBuffer()[i];
			break;
		case 2:
				rotateRect->GetBuffer()[(rotateRect->GetDimension().x * rotateRect->GetDimension().y) - 1 - i] = this->GetBuffer()[i];
			break;
		case 3:
			if (i % rotateRect->GetDimension().x == 0 && i != 0)
				y++;
			rotateRect->GetBuffer()[(rotateRect->GetDimension().x - 1) - y + (rotateRect->GetDimension().x * (i % rotateRect->GetDimension().x))] = this->GetBuffer()[i];
			break;
		default:
			break;
		}

	}
	memcpy(this->GetBuffer(), rotateRect->GetBuffer(), sizeof(CHAR_INFO) * GetDimension().x * GetDimension().y);
}

bool Tetromino::DoesFit(int x, int y, const Board& board) const
{
	for (int i = 0; i < GetDimension().y; i++)
	{
		for (int j = 0; j < GetDimension().x; j++)
		{
			if (board.GetPixel(GetPosition().x - board.GetPosition().x + j, GetPosition().y - board.GetPosition().y + i).has_value())
			{

			}
		}
	}
	return false;
}

CHAR_INFO* Tetromino::GetSprite(Type blockType) const
{
	return sprite->GetSprite(blockType);
}

void Tetromino::Reset(const Board& board)
{
	SetPosition(board.GetPosition().x + board.GetDimension().x / 2 - 1, board.GetPosition().y - 2);
	ChangeBlock(blockType);
}

Tetromino::Sprite::Sprite()
{
	I = new CHAR_INFO[4 * 4];
	O = new CHAR_INFO[4 * 4];
	J = new CHAR_INFO[3 * 3];
	L = new CHAR_INFO[3 * 3];
	Z = new CHAR_INFO[3 * 3];
	S = new CHAR_INFO[3 * 3];
	T = new CHAR_INFO[3 * 3];

	//Filling I block
	for (int i = 0; i < 16; i++)
	{
		if (i == 4 || i == 5 || i == 6 || i == 7)
		{
			I[i].Attributes = FG_COLOR_AQUA;
			I[i].Char.UnicodeChar = CHARACTER_FULL;
		}
		else
		{
			I[i].Attributes = FG_COLOR_BLACK;
			I[i].Char.UnicodeChar = CHARACTER_FULL;
		}
	}
	//Filling O block
	for (int i = 0; i < 9; i++)
	{
		if (i == 1 || i == 2 || i == 4 || i == 5)
		{
			O[i].Attributes = FG_COLOR_LIGHT_YELLOW;
			O[i].Char.UnicodeChar = CHARACTER_FULL;
		}
		else
		{
			O[i].Attributes = FG_COLOR_BLACK;
			O[i].Char.UnicodeChar = CHARACTER_FULL;
		}
	}
	//Filling J block
	for (int i = 0; i < 9; i++)
	{
		if (i == 0 || i == 3 || i == 4 || i == 5)
		{
			J[i].Attributes = FG_COLOR_BLUE;
			J[i].Char.UnicodeChar = CHARACTER_FULL;
		}
		else
		{
			J[i].Attributes = FG_COLOR_BLACK;
			J[i].Char.UnicodeChar = CHARACTER_FULL;
		}
	}
	//Filling L block
	for (int i = 0; i < 9; i++)
	{
		if (i == 2 || i == 3 || i == 4 || i == 5)
		{
			L[i].Attributes = FG_COLOR_YELLOW;
			L[i].Char.UnicodeChar = CHARACTER_FULL;
		}
		else
		{
			L[i].Attributes = FG_COLOR_BLACK;
			L[i].Char.UnicodeChar = CHARACTER_FULL;
		}
	}
	//Filling Z block
	for (int i = 0; i < 9; i++)
	{
		if (i == 1 || i == 2 || i == 3 || i == 4)
		{
			Z[i].Attributes = FG_COLOR_LIGHT_GREEN;
			Z[i].Char.UnicodeChar = CHARACTER_FULL;
		}
		else
		{
			Z[i].Attributes = FG_COLOR_BLACK;
			Z[i].Char.UnicodeChar = CHARACTER_FULL;
		}
	}
	//Filling S block
	for (int i = 0; i < 9; i++)
	{
		if (i == 0 || i == 1 || i == 4 || i == 5)
		{
			S[i].Attributes = FG_COLOR_RED;
			S[i].Char.UnicodeChar = CHARACTER_FULL;
		}
		else
		{
			S[i].Attributes = FG_COLOR_BLACK;
			S[i].Char.UnicodeChar = CHARACTER_FULL;
		}
	}
	//Filling T block
	for (int i = 0; i < 9; i++)
	{
		if (i == 1 || i == 3 || i == 4 || i == 5)
		{
			T[i].Attributes = FG_COLOR_LIGHT_PURPLE;
			T[i].Char.UnicodeChar = CHARACTER_FULL;
		}
		else
		{
			T[i].Attributes = FG_COLOR_BLACK;
			T[i].Char.UnicodeChar = CHARACTER_FULL;
		}
	}
}

Tetromino::Sprite::~Sprite()
{
	delete[] I;
	delete[] O;
	delete[] J;
	delete[] L;
	delete[] Z;
	delete[] S;
	delete[] T;
}

CHAR_INFO* Tetromino::Sprite::GetSprite(Type blockType)
{
	switch (blockType)
	{
	case Type::I_BLOCK: return I; break;
	case Type::O_BLOCK: return O; break;
	case Type::J_BLOCK: return J; break;
	case Type::L_BLOCK: return L; break;
	case Type::Z_BLOCK: return Z; break;
	case Type::S_BLOCK: return S; break;
	case Type::T_BLOCK: return T; break;
	default:
	Log log("TetrominoSpriteError.txt");
	log.Error("In file Tetromino.cpp, in line " + std::to_string(__LINE__) + " unknown block type, returned I block instead");
		return I;
		break;
	}
}
