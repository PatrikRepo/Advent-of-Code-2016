#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <utility>

struct Bot
{
	unsigned int id = 0;
	unsigned int low = 0;
	unsigned int high = 0;
	int lowTo = 0;
	int highTo = 0;
	void addChip(unsigned int chip)
	{
		if(low == 0)
		{
			low = chip;
		}
		else if(low < chip)
		{
			high = chip;
		}
		else
		{
			high = low;
			low = chip;
		}
	}
};

void parseInput(std::unordered_map<unsigned int,Bot> &bots, std::unordered_map<int, unsigned int> &outputBuckets)
{
	std::string line;

	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input, line))
		{
			if(line[0] == 'b')
			{
				Bot bot;
				size_t pos = line.find_first_of("1234567890");
				size_t endpos = line.find_first_of(" ", pos);
				unsigned int id = std::stoi(line.substr(pos, endpos-pos));
				if(bots.count(id) == 0)
				{
					bot.id = id;
				}
				else
				{
					bot = bots[id];
				}
				
				pos = line.find_first_of("w",endpos);
				char botOrOutput = line[pos + 5];
				pos = line.find_first_of("1234567890", pos);
				endpos = line.find_first_of(" ", pos);
				int to = std::stoi(line.substr(pos, endpos-pos));
				if(botOrOutput == 'o')
				{
					if(to!=0)
					{
						outputBuckets[to] = 0;
						to = -to;
					}
					else
					{
						to = 1000;
						outputBuckets[to] = 0;
						to = -to;
					}
				}
				bot.lowTo = to;
				
				botOrOutput = line[line.find_first_of("o",endpos) + 2];
				pos = line.find_first_of("1234567890", endpos);
				to = std::stoi(line.substr(pos));
				if(botOrOutput == 'o')
				{
					outputBuckets[to] = 0;
					to = -to;
				}
				bot.highTo = to;
				
				bots[id] = bot;
			}
			else
			{
				size_t pos = line.find_first_of("1234567890");
				size_t endpos = line.find_first_of(" ", pos);
				unsigned int chip = std::stoi(line.substr(pos, endpos-pos));
				
				pos = line.find_first_of("1234567890", endpos);
				unsigned int id = std::stoi(line.substr(pos));
				
				if(bots.count(id) == 0)
				{
					Bot bot;
					bot.id = id;
					bots[id] = bot;
				}
				bots[id].addChip(chip);
			}
		}
	}
	input.close();
	
}

std::pair<uint64_t,uint64_t> runBots(std::unordered_map<unsigned int,Bot> &bots, std::unordered_map<int, unsigned int> &outputBuckets)
{
	std::pair<uint64_t,uint64_t> result;
	std::queue<Bot*> botQueue;
	for(auto it=bots.begin(); it!=bots.end(); it++)
	{
		if(it->second.high != 0)
		{
			botQueue.push(&(it->second));
		}
	}
	
	while(!botQueue.empty())
	{
		Bot * bot = botQueue.front();

		if(bot->low == 17 && bot->high == 61)
		{
			result.first = bot->id;
		}
		if(bot->lowTo >= 0)
		{
			bots[bot->lowTo].addChip(bot->low);
			if(bots[bot->lowTo].high != 0)
			{
				botQueue.push(&(bots[bot->lowTo]));
			}
		}
		else
		{
			outputBuckets[abs(bot->lowTo)] += bot->low;
		}
		if(bot->highTo >= 0)
		{
			bots[bot->highTo].addChip(bot->high);
			if(bots[bot->highTo].high != 0)
			{
				botQueue.push(&(bots[bot->highTo]));
			}
		}
		else
		{
			outputBuckets[abs(bot->highTo)] += bot->high;
		}
		bot->low = 0;
		bot->high = 0;
		botQueue.pop();
		
	}
	result.second = (outputBuckets[1000]*outputBuckets[1]*outputBuckets[2]);
	return result;
}

int main()
{
	std::pair<uint64_t,uint64_t> result;
	std::unordered_map<unsigned int,Bot> bots;
	std::unordered_map<int, unsigned int> outputBuckets;
	parseInput(bots, outputBuckets);
	
	result = runBots(bots, outputBuckets);
	
	std::cout << "resultA: " << result.first << '\n';
	std::cout << "resultB: " << result.second << std::endl;

	return 0;
}
