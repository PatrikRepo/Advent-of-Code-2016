#include <iostream>
#include <fstream>
#include <utility>
#include <vector>

void parseInput(std::vector<std::pair<unsigned int, unsigned int>> &discs)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		int i=1;
		while(getline(input,line))
		{
			size_t pos = 8;
			size_t endpos = 0;
			
			pos = line.find_first_of("1234567890", pos);
			endpos = line.find_first_of(" ", pos);
			unsigned int slots = std::stoi(line.substr(pos, endpos-pos));
			
			pos = line.find_first_of("1234567890", endpos);
			pos = line.find_first_of("1234567890", pos+1);
			endpos = line.find_first_of(" ", pos);
			unsigned int currentSlot = (std::stoi(line.substr(pos, endpos-pos)) +i)%slots;
			
			discs.push_back(std::make_pair(slots, currentSlot));
			i++;
		}
	}
	input.close();
}

uint64_t getCapsule(const std::vector<std::pair<unsigned int, unsigned int>> &discs)
{
	uint64_t result = 1;
	
	unsigned int steps = 1;
	for(unsigned int i=0; i<discs.size(); i++)
	{
		while(!((discs[i].second+result)%discs[i].first == 0))
		{
			result += steps;
		}
		steps *= discs[i].first;
	}

	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::vector<std::pair<unsigned int, unsigned int>> discs;

	parseInput(discs);

	resultA = getCapsule(discs);
	
	discs.push_back(std::make_pair(11,discs.size()+1));
	resultB = getCapsule(discs);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
