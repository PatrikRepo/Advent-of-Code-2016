#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

void parseInput(std::vector<std::string> &messages)
{
	std::string line;

	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input, line))
		{
			messages.push_back(line);
		}
	}
	input.close();
	
}

std::string recoverMessage(const std::vector<std::string> &messages)
{
	std::string result = "00000000";
	
	for(int i=0; i<8; i++)
	{
		std::unordered_map<char,int> map;
		for(unsigned int j=0; j<messages.size(); j++)
		{
			map[messages[j][i]] += 1;
		}
		
		int highestNumber = 0;
		for(auto it=map.begin(); it!=map.end(); it++)
		{
			if(it->second > highestNumber)
			{
				highestNumber= it->second;
				result[i] = it->first;
			}
		}
	}
	
	return result;
}

std::string recoverModifiedMessage(const std::vector<std::string> &messages)
{
	std::string result = "00000000";
	
	for(int i=0; i<8; i++)
	{
		std::unordered_map<char,int> map;
		for(unsigned int j=0; j<messages.size(); j++)
		{
			map[messages[j][i]] += 1;
		}
		
		uint16_t highestNumber = UINT16_MAX;
		for(auto it=map.begin(); it!=map.end(); it++)
		{
			if(it->second < highestNumber)
			{
				highestNumber= it->second;
				result[i] = it->first;
			}
		}
	}
	
	return result;
}

int main()
{
	std::string resultA;
	std::string resultB;
	std::vector<std::string> messages;
	
	parseInput(messages);
	
	resultA = recoverMessage(messages);
	resultB = recoverModifiedMessage(messages);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;

	return 0;
}
