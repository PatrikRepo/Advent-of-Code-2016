#include <iostream>
#include <fstream>

void parseInput(unsigned int &numberOfElves)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		getline(input, line);
		numberOfElves = std::stoi(line);
	}
	input.close();
}

//Known formula for Josephus problem
uint64_t stealPresents(unsigned int numberOfElves)
{
	uint64_t result = 0;
	unsigned int twoPower = 1;
	
	while(twoPower*2 < numberOfElves)
	{
		twoPower *= 2;
	}
	
	unsigned int remainder = numberOfElves - twoPower;
	result = (remainder*2) + 1;
	return result;
}

//Found pattern by checking bunch of numbers
uint64_t stealPresentsNewRules(unsigned int numberOfElves)
{
	uint64_t result = 0;
	
	for(unsigned int i=1; i<=numberOfElves; i++)
	{
		result++; 
		if(result>i/2)
		{
			result++;
		}
		result %= i;
	}
	
	return result;
}

int main()
{
	uint64_t resultA;
	uint64_t resultB;
	unsigned int numberOfElves;

	parseInput(numberOfElves);
	
	resultA = stealPresents(numberOfElves);
	
	resultB = stealPresentsNewRules(numberOfElves);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
