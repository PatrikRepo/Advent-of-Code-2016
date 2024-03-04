#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

void parseInput(std::vector<std::pair<uint32_t,uint32_t>> &bannedIPs)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input, line))
		{
			size_t pos = line.find_first_of("-");
			uint32_t from = std::stoll(line.substr(0,pos));
			uint32_t to = std::stoll(line.substr(pos+1));
			bannedIPs.push_back(std::make_pair(from,to));
		}
	}
	input.close();
}

uint32_t findLowestIP(std::vector<std::pair<uint32_t,uint32_t>> &bannedIPs, const uint32_t startIP)
{
	uint32_t result = startIP;
	bool foundIP = false;
	uint32_t newMin = result;
	
	while(!foundIP)
	{
		foundIP = true;
		for(auto it=bannedIPs.begin(); it!=bannedIPs.end(); it++)
		{
			if(it->first <= newMin)
			{
				if(it->second >= newMin)
				{
					if(it->second == 4294967295)
					{
						newMin = it->second;
					}
					else
					{
						newMin = it->second+1;
					}
					foundIP = false;
				}
				bannedIPs.erase(it);
				it=bannedIPs.begin()-1;
			}
		}
		if(result <= newMin)
		{
			result = newMin;
		}
	}
	
	for(auto it=bannedIPs.begin(); it!=bannedIPs.end(); it++)
	{
		if(it->first <= result)
		{
			bannedIPs.erase(it);
			it--;
		}
	}
	
	return result;
}

uint32_t findAllowedIPs(std::vector<std::pair<uint32_t,uint32_t>> &bannedIPs)
{
	uint32_t result = 0;
	uint32_t lowestIP = 0;
	uint64_t maxIP = 4294967295;
	
	while(bannedIPs.size() != 0)
	{
		lowestIP = findLowestIP(bannedIPs, lowestIP);
		uint64_t firstForbiddenIP = maxIP;
		for(auto it=bannedIPs.begin(); it!=bannedIPs.end(); it++)
		{
			if(firstForbiddenIP > it->first)
			{
				firstForbiddenIP = it->first;
			}
		}
		result += firstForbiddenIP - lowestIP;
		lowestIP = firstForbiddenIP;
	}
	
	return result;
}

int main()
{
	uint32_t resultA;
	uint32_t resultB;
	std::vector<std::pair<uint32_t,uint32_t>> bannedIPs;
	std::vector<std::pair<uint32_t,uint32_t>> bannedIPs2;

	parseInput(bannedIPs);
	bannedIPs2 = bannedIPs;
	
	resultA = findLowestIP(bannedIPs, 0);
	
	resultB = findAllowedIPs(bannedIPs2);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
