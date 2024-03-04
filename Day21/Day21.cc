#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

void parseInput(std::vector<std::tuple<char,int,int>> &instructions)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input, line))
		{
			size_t pos = 0;
			char instruction = line[0];
			int first = 0;
			int second = 0;
			if(instruction == 'r' && line[1] == 'e')
			{
				instruction = 'e';
			}
			
			if(instruction == 'r')
			{
				first = line[7];
				pos = line.find_first_of("1234567890");
				if(pos != std::string::npos)
				{
					second = line[pos] - '0';
				}
				else
				{
					second = line[line.length()-1];
				}
			}
			else
			{
				pos = line.find_first_of("1234567890");
				if(pos != std::string::npos)
				{
					first = line[pos] - '0';
					second = line[line.length()-1] - '0';
				}
				else
				{
					first = line[12];
					second = line[line.length()-1];
				}
				
			}
			instructions.push_back(std::make_tuple(instruction, first, second));
		}
	}
	input.close();
}

std::string scramble(const std::string &unscrambled, const std::vector<std::tuple<char,int,int>> &instructions)
{
	std::string result = unscrambled;
	
	for(auto it=instructions.begin(); it!=instructions.end(); it++)
	{
		switch(std::get<0>(*it))
		{
			case 'r':
			{
				switch(std::get<1>(*it))
				{
					case 'r':
					{
						int steps = std::get<2>(*it);
						std::string newString = result;
						for(unsigned int i=0; i<result.length(); i++)
						{
							result[(i+steps)%result.length()] = newString[i];
						}
						break;
					}
					case 'l':
					{
						int steps = std::get<2>(*it);
						std::string newString = result;
						for(unsigned int i=0; i<result.length(); i++)
						{
							result[(i-steps)%result.length()] = newString[i];
						}
						break;
					}
					case 'b':
					{
						char letter = std::get<2>(*it);
						int steps = result.find_first_of(letter) +1;
						if(steps >= 5)
						{
							steps++;
						}
						std::string newString = result;
						for(unsigned int i=0; i<result.length(); i++)
						{
							result[(i+steps)%result.length()] = newString[i];
						}
						break;
					}
					case 'B':
					{
						char letter = std::get<2>(*it);
						int steps = result.find_first_of(letter);
						if(steps % 2 == 1)
						{
							steps = (steps/2) + 1;
						}
						else
						{
							if(steps == 2)
							{
								steps = 6;
							}
							else if(steps == 4)
							{
								steps = 7;
							}
							else if(steps == 6)
							{
								steps = 0;
							}
							else
							{
								steps = 1;
							}
						}
						std::string newString = result;
						for(unsigned int i=0; i<result.length(); i++)
						{
							result[(i-steps)%result.length()] = newString[i];
						}
						break;
					}
				}
				break;
			}
			case 's':
			{
				
				if(std::get<1>(*it) <= 9)
				{
					int first = std::get<1>(*it);
					int second = std::get<2>(*it);
					char swapped = result[first];
					result[first] = result[second];
					result[second] = swapped;
				}
				else
				{
					char firstLetter = std::get<1>(*it);
					char secondLetter = std::get<2>(*it);
					int first = result.find_first_of(firstLetter);
					int second = result.find_first_of(secondLetter);
					char swapped = result[first];
					result[first] = result[second];
					result[second] = swapped;
				}
				break;
			}
			case 'e':
			{
				int first = std::get<1>(*it);
				int second = std::get<2>(*it);
				for(int i=0; i<=(second-first)/2; i++)
				{
					char swapped = result[first+i];
					result[first+i] = result[second-i];
					result[second-i] = swapped;
				}
				break;
			}
			case 'm':
			{
				int first = std::get<1>(*it);
				int second = std::get<2>(*it);
				char moved = result[first];
				if(first < second)
				{
					for(int i=first; i<second; i++)
					{
						result[i] = result[i+1];
					}
				}
				else
				{
					for(int i=first; i>second; i--)
					{
						result[i] = result[i-1];
					}
				}
				result[second] = moved;
				break;
			}
		}
	}
	
	return result;
}

std::vector<std::tuple<char,int,int>> reverseInstructions(std::vector<std::tuple<char,int,int>> &instructions)
{
	std::vector<std::tuple<char,int,int>> reverseInstructions;
	
	for(auto it=instructions.begin(); it!=instructions.end(); it++)
	{
		if(std::get<0>(*it) == 'r')
		{
			if(std::get<1>(*it) == 'r')
			{
				std::get<1>(*it) = 'l';
			}
			else if(std::get<1>(*it) == 'l')
			{
				std::get<1>(*it) = 'r';
			}
			else
			{
				std::get<1>(*it) = 'B';
			}
		}
		else if(std::get<0>(*it) == 'm')
		{
			int temp = std::get<1>(*it);
			std::get<1>(*it) = std::get<2>(*it);
			std::get<2>(*it) = temp;
		}
		reverseInstructions.insert(reverseInstructions.begin(), *it);
	}
	
	return reverseInstructions;
}

int main()
{
	std::string resultA;
	std::string resultB;
	std::vector<std::tuple<char,int,int>> instructions;
	std::string unscrambled = "abcdefgh";
	std::string scrambled = "fbgdceah";
	
	parseInput(instructions);

	resultA = scramble(unscrambled, instructions);
	
	instructions = reverseInstructions(instructions);
	
	resultB = scramble(scrambled, instructions);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
