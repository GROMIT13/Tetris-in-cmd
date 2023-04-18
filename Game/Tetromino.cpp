#include "Tetromino.hpp"

Tetromino::Tetromino(int x, int y, Board& board)
	:Rect(x, y, 4, 4), updateSpeed(800),board(board),rotationState(0)
{
	rotateRect = new Rect(x,y,4,4);
	sprite = new Sprite;
	blockType = (Tetromino::Type)board.MoveNextList();
	ChangeBlock(blockType);
	Reset();
	updateClock = new Clock(updateSpeed);
	horizontalMovementClock = new Clock(200);
}

CHAR_INFO* Tetromino::GetSprite(Type blockType) const
{
	return sprite->GetSprite(blockType);
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
	if (blockType == Type::O_BLOCK)
		return;

	int y = 0;
	*rotateRect = *this;
	for (int i = 0; i < rotateRect->GetDimension().x * rotateRect->GetDimension().y; i++)
	{
		switch (rotations % 4)
		{
		case 1:
			if (i % rotateRect->GetDimension().x == 0 && i != 0)
				y++;
			rotateRect->GetBuffer()[(rotateRect->GetDimension().x - 1) - y + (rotateRect->GetDimension().x * (i % rotateRect->GetDimension().x))] = this->GetBuffer()[i];
			break;
		case 2:
			rotateRect->GetBuffer()[(rotateRect->GetDimension().x * rotateRect->GetDimension().y) - 1 - i] = this->GetBuffer()[i];
			break;
		case 3:
			if (i % rotateRect->GetDimension().x == 0 && i != 0)
				y++;
			rotateRect->GetBuffer()[rotateRect->GetDimension().x * (rotateRect->GetDimension().y - 1) + y - (rotateRect->GetDimension().y * (i % rotateRect->GetDimension().x))] = this->GetBuffer()[i];
			break;
		default:
			break;
		}

	}
	
	if (DoesFit(*rotateRect, rotateRect->GetPosition().x, rotateRect->GetPosition().y))
	{
		memcpy(this->GetBuffer(), rotateRect->GetBuffer(), sizeof(CHAR_INFO) * GetDimension().x * GetDimension().y);
		rotationState += rotations % 4;
		rotationState %= 4;
		return;
	}

}

void Tetromino::Reset()
{
	SetPosition(board.GetPosition().x + board.GetDimension().x / 2 - 2, board.GetPosition().y + 2);
	ChangeBlock(blockType);
	rotationState = 0;
}

int Tetromino::CalculateUpdateSpeed()
{
	int newUpdeteSpeed = (int)updateSpeed;

	for (int i = 0; i < board.GetLevel() - 1; i++)
	{
		if (i >= 30)
			return newUpdeteSpeed = 20;

		if (i >= 27){
			newUpdeteSpeed -= 3; continue;
		}

		if (i >= 22){
			newUpdeteSpeed -= 4; continue;
		}

		if (i >= 16){
			newUpdeteSpeed -= 5; continue;
		}

		if (i == 15){
			newUpdeteSpeed -= 10; continue;
		}

		if (i == 14){
			newUpdeteSpeed -= 20; continue;
		}

		if (i == 13){
			newUpdeteSpeed -= 40; continue;
		}
		newUpdeteSpeed -= 50;
	}

	return newUpdeteSpeed;
}

//NOTE: x and y are tetromino position
bool Tetromino::DoesFit(Rect& tetromino, int x, int y)
{
	bool output = false;
	
	for (int i = 0; i < tetromino.GetDimension().y; i++)
	{
		for (int j = 0; j < tetromino.GetDimension().x; j++)
		{
			if (tetromino.GetPixel(j, i)->Attributes == FG_COLOR_BLACK)
				continue;

			Vec2 position(x - board.GetPosition().x + j, y - board.GetPosition().y + i);
			if (board.GetPixel(position).has_value() && board.GetPixel(position)->Attributes == FG_COLOR_BLACK)
				output = true;
			else
				return false;
		}
	}
	return output;
}

bool Tetromino::DoesFit(Rect& tetromino, Vec2 position)
{
	return DoesFit(tetromino, position.x, position.y);
}

void Tetromino::Update()
{
	if (board.GetHasLost())
		return;

	unsigned long long fallSpeed = CalculateUpdateSpeed();
	if (Input::GetKey(VK_DOWN).present)
		fallSpeed /= 15;

	if (updateClock->HasPassed(fallSpeed))
	{
		if (DoesFit(*this, GetPosition().x, GetPosition().y + 1))
			Move(0, 1);
		else
			IfCantMoveDown();
	}

	HoldTetromino();
	HardDrop();

	if (Input::GetState(VK_LEFT) == State::Enter)
	{
		horizontalMovementClock->ResetHasPassed();
		if (DoesFit(*this,GetPosition().x - 1, GetPosition().y))
		{
			Move(-1, 0);
		}
	}

	if (Input::GetState(VK_LEFT) == State::Stay && horizontalMovementClock->HasPassed())
	{
		if (DoesFit(*this, GetPosition().x - 1, GetPosition().y))
		{
			Move(-1, 0);
		}
	}

	if (Input::GetState(VK_LEFT) == State::Exit)
		horizontalMovementClock->ResetHasPassed();


	if (Input::GetState(VK_RIGHT) == State::Enter)
	{
		if (DoesFit(*this, GetPosition().x + 1, GetPosition().y))
		{
			Move(1, 0);
		}
	}

	if (Input::GetState('Z') == State::Enter)
		Rotate(3);
	if (Input::GetState('X') == State::Enter)
		Rotate(1);
	if (Input::GetState('A') == State::Enter)
		Rotate(2);
}

void Tetromino::DrawTetromino(GConsole& screen)
{
	if (board.GetHasLost())
		return;

	//Calculate, draw tetromino shadow
	Vec2 position = { GetPosition().x,GetPosition().y + 1 };

	while (DoesFit(*this, GetPosition().x, position.y))
		position.y++;
	position.y--;
	
	for (int y = 0; y < GetDimension().y; y++)
	{
		for (int x = 0; x < GetDimension().x; x++)
		{
			if (GetPixel(x, y).value().Attributes != FG_COLOR_BLACK)
				screen.Draw(position.x + x, position.y + y, CHARACTER_QUARTER, FG_COLOR_GRAY);
		}
	}
	//Draw tetromino
	screen.DrawRectTransparent(*this, FG_COLOR_BLACK);
}

void Tetromino::IfCantMoveDown()
{
	int linesCleared = 0;
	board.PlaceBlock(*this);
	linesCleared = board.ClearLines((GetPosition().y - board.GetPosition().y), GetDimension().y);
	board.CountScore(linesCleared);
	board.CountLevel(linesCleared);
	board.HasLost();
	Reset();
	blockType = (Tetromino::Type)board.MoveNextList();
	ChangeBlock(blockType);
	board.SetCanHoldTetromino(true);
}

void Tetromino::HoldTetromino()
{
	if (Input::GetState('C') == State::Enter && board.GetCanHoldTetromino())
	{
		Type holdTetromino;
		holdTetromino = (Tetromino::Type)board.GetHoldTetromino();

		board.SetCanHoldTetromino(false);
		board.SetHoldTetromino((char)blockType);
		Reset();

		if (holdTetromino == Tetromino::Type::NULL_BLOCK)
		{
			blockType = (Tetromino::Type)board.MoveNextList();
			ChangeBlock(blockType);
		}
		else
		{
			blockType = holdTetromino;
			ChangeBlock(holdTetromino);
		}

	}
}

void Tetromino::HardDrop()
{
	if (Input::GetState(VK_SPACE) == State::Enter)
	{
		while (true)
		{
			if (DoesFit(*this, GetPosition().x, GetPosition().y + 1))
				Move(0, 1);
			else
			{
				IfCantMoveDown();
				return;
			}
		}	
	}
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
