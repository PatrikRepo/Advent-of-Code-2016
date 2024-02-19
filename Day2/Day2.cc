#include <iostream>
#include <fstream>
#include <vector>

struct Keypad
{
	unsigned int row = 1;
	unsigned int column = 2;
	std::string code;
	
	void moveUp()
	{
		row = (row == 0 ? 0 : row-1);
	}
	void moveDown()
	{
		row = (row == 2 ? 2 : row+1);
	}
	void moveRight()
	{
		column = (column == 3 ? 3 : column+1);
	}
	void moveLeft()
	{
		column = (column == 1 ? 1 : column-1);
	}
	void setDigit()
	{
		code += std::to_string(column + (row*3));
	}
};

struct WeirdKeypad
{
	unsigned int row = 2;
	unsigned int column = 0;
	std::string code;
	
	void moveUp()
	{
		row = (abs(row-1-2) + abs(column-2) == 3 ? row : row-1);
	}
	void moveDown()
	{
		row = (abs(row+1-2) + abs(column-2) == 3 ? row : row+1);
	}
	void moveRight()
	{
		column = (abs(row-2) + abs(column+1-2) == 3 ? column : column+1);
	}
	void moveLeft()
	{
		column = (abs(row-2) + abs(column-1-2) == 3 ? column : column-1);
	}
	void setDigit()
	{
		switch(row)
		{
			case(0):
				code += "1";
				break;
			case(1):
				switch(column)
				{
					case(1):
						code += "2";
						break;
					case(2):
						code += "3";
						break;
					case(3):
						code += "4";
						break;
				}
				break;
			case(2):
				switch(column)
				{
					case(0):
						code += "5";
						break;
					case(1):
						code += "6";
						break;
					case(2):
						code += "7";
						break;
					case(3):
						code += "8";
						break;
					case(4):
						code += "9";
						break;
				}
				break;
			case(3):
				switch(column)
				{
					case(1):
						code += "A";
						break;
					case(2):
						code += "B";
						break;
					case(3):
						code += "C";
						break;
				}
				break;
			case(4):
				code += "D";
				break;
		}
	}
};

void parseInput(std::vector<std::string> &instructions)
{
	std::string line;

	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input, line))
		{
			instructions.push_back(line);
		}
	}
	input.close();
}

void getCode(const std::vector<std::string> &instructions, Keypad &keypad, WeirdKeypad &weirdKeypad)
{
	
	for(unsigned int i=0; i<instructions.size(); i++)
	{
		for(unsigned int j=0; j<instructions[i].length(); j++)
		{
			switch(instructions[i][j])
			{
				case 'U':
					keypad.moveUp();
					weirdKeypad.moveUp();
					break;
				case 'R':
					keypad.moveRight();
					weirdKeypad.moveRight();
					break;
				case 'D':
					keypad.moveDown();
					weirdKeypad.moveDown();
					break;
				case 'L':
					keypad.moveLeft();
					weirdKeypad.moveLeft();
					break;
			}
		}
		keypad.setDigit();
		weirdKeypad.setDigit();
	}
}

int main()
{
	Keypad keypad;
	WeirdKeypad weirdKeypad;
	
	std::vector<std::string> instructions;
	parseInput(instructions);

	getCode(instructions, keypad, weirdKeypad);
	
	std::cout << "resultA: " << keypad.code << '\n';
	std::cout << "resultB: " << weirdKeypad.code << std::endl;
	
	return 0;	
}

