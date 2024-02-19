#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include <unordered_map>
#include <queue>
#include <utility>

struct orderLetters
{
	bool operator()(const std::pair<char, int> pair1, const std::pair<char, int> pair2)
	{
		if(pair1.second == pair2.second)
		{
			return pair1.first > pair2.first;
		}
		else
		{
			return pair1.second < pair2.second;
		}
	} 
};

void parseInput(std::vector<std::tuple<std::string, int, std::string>> &rooms)
{
	std::string line;

	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input, line))
		{
			std::tuple<std::string, int, std::string> room;
			size_t pos = 0;
			size_t endpos = 0;
			
			pos = line.find_first_of("1234567890");
			std::get<0>(room) = line.substr(0, pos);

			endpos = line.find_first_of("[", pos);
			std::get<1>(room) = std::stoi(line.substr(pos, endpos-pos));
			
			std::get<2>(room) = line.substr(endpos+1, 5);		
			
			rooms.push_back(room);
		}
	}
	input.close();
	

}

uint64_t calculateRealRooms(const std::vector<std::tuple<std::string, int, std::string>> &rooms)
{
	uint64_t result = 0;
	
	for(auto it=rooms.begin(); it!=rooms.end(); it++)
	{
		std::unordered_map<char, int> letters;
		std::priority_queue<std::pair<char, int>, std::vector<std::pair<char, int>>, orderLetters> queue;
		for(unsigned int i=0; i<std::get<0>(*it).length(); i++)
		{	
			char c = std::get<0>(*it)[i];
			if(c != '-')
			{
				letters[c] += 1;
			}
		}
		
		for(auto jt=letters.begin(); jt!=letters.end(); jt++)
		{
			queue.push(std::make_pair(jt->first,jt->second));
		}
		
		bool realRoom = true;

		for(int i=0; i<5; i++)
		{
			if(queue.top().first != std::get<2>(*it)[i])
			{
				realRoom = false;
				break;
			}
			queue.pop();
		}
		if(realRoom)
		{
			result += std::get<1>(*it);
		}
	}
	
	return result;
}

uint64_t decryptRooms(const std::vector<std::tuple<std::string, int, std::string>> &rooms)
{
	uint64_t result = 0;
	std::string key = "northpole object storage ";
	for(auto it=rooms.begin(); it!=rooms.end(); it++)
	{
		std::string room = std::get<0>(*it);
		if(1)
		{
			int shift = std::get<1>(*it) % 26;
			for(unsigned int i=0; i<room.length(); i++)
			{
				if(room[i] == '-')
				{
					room[i] = ' ';
				}
				else
				{
					int shiftedChar = room[i];
					shiftedChar += shift;
					if(shiftedChar > 'z')
					{
						shiftedChar -= 26;
					}
					room[i] = shiftedChar;
				}
			}
			if(room == key)
			{
				result = std::get<1>(*it);
				break;
			}
		}
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::vector<std::tuple<std::string, int, std::string>> rooms;

	parseInput(rooms);
	
	resultA = calculateRealRooms(rooms);
	resultB = decryptRooms(rooms);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;	
}

