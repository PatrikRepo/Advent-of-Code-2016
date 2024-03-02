#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

void parseInput(std::vector<std::tuple<char, std::string, std::string>> &instructions)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input,line))
		{
			char instruction = line[0];
			size_t pos = line.find_first_of(" ", 4);
			std::string registerOrValue = line.substr(4,pos-4);
			std::string value;
			if(instruction == 'c' || instruction == 'j')
			{
				value = line.substr(pos+1);
			}
			
			instructions.push_back(std::make_tuple(instruction, registerOrValue, value));
		}
	}
	input.close();
}

int64_t executeInstructions(const std::vector<std::tuple<char, std::string, std::string>> &instructions, std::tuple<int,int,int,int> &registers)
{
	int a = std::get<0>(registers);
	int b = std::get<1>(registers);
	int c = std::get<2>(registers);
	int d = std::get<3>(registers);
	
	for(unsigned int i=0; i<instructions.size() && i>= 0; i++)
	{
		char instruction = std::get<0>(instructions[i]);
		
		if(instruction == 'c')
		{
			switch(std::get<2>(instructions[i])[0])
			{
				case 'a':
				{
					switch(std::get<1>(instructions[i])[0])
					{
						case 'a':
							a = a;
							break;
						case 'b':
							a = b;
							break;
						case 'c':
							a = c;
							break;
						case 'd':
							a = d;
							break;
						default:
							a = std::stoi(std::get<1>(instructions[i]));
					}
					break;
				}
				case 'b':
				{
					switch(std::get<1>(instructions[i])[0])
					{
						case 'a':
							b = a;
							break;
						case 'b':
							b = b;
							break;
						case 'c':
							b = c;
							break;
						case 'd':
							b = d;
							break;
						default:
							b = std::stoi(std::get<1>(instructions[i]));
					}
					break;
				}
				case 'c':
				{
					switch(std::get<1>(instructions[i])[0])
					{
						case 'a':
							c = a;
							break;
						case 'b':
							c = b;
							break;
						case 'c':
							c = c;
							break;
						case 'd':
							c = d;
							break;
						default:
							c = std::stoi(std::get<1>(instructions[i]));
					}
					break;
				}
				case 'd':
				{
					switch(std::get<1>(instructions[i])[0])
					{
						case 'a':
							d = a;
							break;
						case 'b':
							d = b;
							break;
						case 'c':
							d = c;
							break;
						case 'd':
							d = d;
							break;
						default:
							d = std::stoi(std::get<1>(instructions[i]));
					}
					break;
				}
			}
		}
		else if(instruction == 'i')
		{
			switch(std::get<1>(instructions[i])[0])
			{
				case 'a':
				{
					a++;
					break;
				}
				case 'b':
				{
					b++;
					break;
				}
				case 'c':
				{
					c++;
					break;
				}
				case 'd':
				{
					d++;
					break;
				}
			}
		}
		else if(instruction == 'd')
		{
			switch(std::get<1>(instructions[i])[0])
			{
				case 'a':
				{
					a--;
					break;
				}
				case 'b':
				{
					b--;
					break;
				}
				case 'c':
				{
					c--;
					break;
				}
				case 'd':
				{
					d--;
					break;
				}
			}
		}
		else if(instruction == 'j')
		{
			switch(std::get<1>(instructions[i])[0])
			{
				case 'a':
				{
					if(a != 0)
					{
						i += std::stoi(std::get<2>(instructions[i]))-1;
					}
					break;
				}
				case 'b':
				{
					if(b != 0)
					{
						i += std::stoi(std::get<2>(instructions[i]))-1;
					}
					break;
				}
				case 'c':
				{
					if(c != 0)
					{
						i += std::stoi(std::get<2>(instructions[i]))-1;
					}
					break;
				}
				case 'd':
				{
					if(d != 0)
					{
						i += std::stoi(std::get<2>(instructions[i]))-1;
					}
					break;
				}
				default:
				{
					if(std::get<1>(instructions[i])[0] != '0')
					{
						i += std::stoi(std::get<2>(instructions[i]))-1;
					}
				}
			}
		}
		
	}
	return a;
}

int main()
{
	int64_t resultA = 0;
	int64_t resultB = 0;
	std::vector<std::tuple<char, std::string, std::string>> instructions;
	std::tuple<int,int,int,int> registers = {0,0,0,0};
	
	parseInput(instructions);
	
	resultA = executeInstructions(instructions, registers);
	
	registers = {0,0,1,0};
	resultB = executeInstructions(instructions, registers);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
