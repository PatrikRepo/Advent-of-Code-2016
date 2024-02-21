#include <iostream>
#include <fstream>
#include <vector>

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

void rect(unsigned int screen[6][50], const unsigned int width, const unsigned int height)
{
	for(unsigned int i=0; i<height; i++)
	{
		for(unsigned int j=0; j<width; j++)
		{
			screen[i][j] = 1;
		}
	}
}

void rotateRow(unsigned int (&row)[50], const unsigned int steps)
{
	unsigned int newRow[50]; 

	for(int i=0; i<50; i++)
	{
		newRow[(i+steps)%50] = row[i];
	}
	for(int i=0; i<50; i++)
	{
		row[i] = newRow[i];
	}
}

void rotateColumn(unsigned int (&column)[6], const unsigned int steps)
{
	unsigned int newColumn[6]; 
	for(int i=0; i<6; i++)
	{
		newColumn[(i+steps)%6] = column[i];
	}
	for(int i=0; i<6; i++)
	{
		column[i] = newColumn[i];
	}
}

uint64_t followInstructions(const std::vector<std::string> &instructions)
{
	uint64_t result = 0;
	unsigned int screen[6][50];
	
	for(int i=0; i<6; i++)
	{
		for(int j=0; j<50; j++)
		{
			screen[i][j] = 0;
		}
	}
	
	for(auto it=instructions.begin(); it!=instructions.end(); it++)
	{
		if((*it)[1] == 'e')
		{
			size_t x = (*it).find_first_of("x");
			unsigned int width = std::stoi(it->substr(5,x-5));
			unsigned int height = (*it)[x+1] - '0';
			rect(screen, width, height);
		}
		else if((*it)[7] == 'r')
		{
			size_t pos = (*it).find_first_of("1234567890");
			int rowNumber = (*it)[pos] - '0';
			
			pos = (*it).find_first_of("1234567890",pos+1);
			int steps = std::stoi(it->substr(pos));
			
			rotateRow(screen[rowNumber], steps);
		}
		else
		{
			size_t pos = (*it).find_first_of("b")-1;
			int columnNumber = std::stoi(it->substr(16,pos-16));
			
			int steps = (*it)[pos+4] - '0';
			
			unsigned int newColumn[6];
			for(int i=0; i<6; i++)
			{
				newColumn[i] = screen[i][columnNumber];
			}
			
			rotateColumn(newColumn, steps);
			
			for(int i=0; i<6; i++)
			{
				screen[i][columnNumber] = newColumn[i];
			}
		}
	}
	
	for(int i=0; i<6; i++)
	{
		for(int j=0; j<50; j++)
		{
			std::cout << screen[i][j];
			if(screen[i][j] == 1)
			{
				result += 1;
			}
		}
		std::cout << '\n';
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	std::vector<std::string> instructions;
	
	parseInput(instructions);
	
	resultA = followInstructions(instructions);
	
	std::cout << "resultA: " << resultA << '\n';

	return 0;
}
