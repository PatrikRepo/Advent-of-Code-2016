#include <iostream>
#include <fstream>

void parseInput(unsigned int &offset)
{
	std::string line;

	std::ifstream input("input.txt");
	if(input.is_open())
	{
		int i=0;
		while(getline(input, line))
		{
			int numberOfChips = 0;
			for(unsigned int j=0; j<line.length(); j++)
			{
				if(line[j] == '-')
				{
					numberOfChips++;
				}
			}
			offset += numberOfChips*i*2;
			i++;
		}
	}
	input.close();
	
}

unsigned int calculateSteps(const unsigned int numberOfChips, const unsigned int offset)
{
	unsigned int result = 0;
	
	//Formula is 12*(numberOfChips-4) + 16-offset + 23
	//16 - offset are the first two to go up, meaning the ones who might be located on higher floors
	//23 are the last two which will need fewer steps. Offset is calculated according to 2*Number Of Levels above lowest for all chips.
	//12*(numberOfChips-4) means that any additional will add 12 extra steps. This is the length of the cycle that raises one additional chip from the lowest level up one level. In the cycle every chip is raised one extra step
	//and generators are moved to enable moving the chips up. So each cycle takes all chips one step closer.
	
	result = 12*(numberOfChips-4) + 16 - offset + 23;
	
	return result;
}

int main()
{
	unsigned int resultA = 0;
	unsigned int resultB = 0;
	unsigned int offset = 0;
	parseInput(offset);
	
	
	resultA = calculateSteps(5,offset);
	resultB = calculateSteps(7,offset);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;

	return 0;
}
