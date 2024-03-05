#include <iostream>
#include <fstream>
#include <vector>

void parseInput(std::vector<std::string> &textstrings)
{
	std::string line;

	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input, line))
		{
			textstrings.push_back(line);
		}
	}
	input.close();
	
}

uint64_t findABBA(const std::vector<std::string> &messages)
{
	uint64_t result = 0;
	
	for(auto it=messages.begin(); it!=messages.end(); it++)
	{
		int ABBA = 0;
		bool hypernet = false;
		for(unsigned int i=0; i<it->length()-3; i++)
		{
			if((*it)[i] == '[')
			{
				hypernet = true;
			}
			else if((*it)[i] == ']')
			{
				hypernet = false;
			}
			else if((*it)[i] == (*it)[i+3] && (*it)[i] != (*it)[i+1] && (*it)[i+1] == (*it)[i+2])
			{
				if(hypernet)
				{
					ABBA = 0;
					break;
				}
				else
				{
					ABBA = 1;
				}
			}
		}
		result += ABBA;
	}
	
	return result;
}

uint64_t findABA(const std::vector<std::string> &messages)
{
	uint64_t result = 0;
	
	for(auto it=messages.begin(); it!=messages.end(); it++)
	{
		std::string normal = (*it);
		std::string hyper;
		
		size_t pos = normal.find_first_of("[");
		size_t endpos = 0;
		while(pos != std::string::npos)
		{
			endpos = normal.find_first_of("]",pos);
			hyper += normal.substr(pos+1,endpos-pos-1) + " ";
			normal.erase(pos+1, endpos-pos-1);
			pos = normal.find_first_of("[",pos+1);
		}
		bool found = false;
		for(unsigned int i=0; i<normal.length()-2; i++)
		{
			if(normal[i] == normal[i+2] && normal[i] != normal[i+1])
			{
				char first = normal[i];
				char second = normal[i+1];
				
				for(unsigned int j=0; j<hyper.length()-2; j++)
				{
					if(hyper[j] == second && hyper[j+1] == first && hyper[j+2] == second)
					{
						found = true;
						break;
					}
				}
			}
			if(found)
			{
				break;
			}
		}
		if(found)
		{
			result += 1;
		}
	}
	
	return result;
}

int main()
{
	uint64_t resultA;
	uint64_t resultB;
	std::vector<std::string> textstrings;
	
	parseInput(textstrings);
	
	resultA = findABBA(textstrings);
	resultB = findABA(textstrings);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;

	return 0;
}
