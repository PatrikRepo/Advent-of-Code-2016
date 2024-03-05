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

std::string executeInstructions(std::vector<std::tuple<char, std::string, std::string>> instructions, std::tuple<int,int,int,int> &registers, std::string &clockSignal)
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
						int j = i;
						switch(std::get<2>(instructions[i])[0])
						{
							case 'a':
								j += a;
								break;
							case 'b':
								j += b;
								break;
							case 'c':
								j += c;
								break;
							case 'd':
								j += d;
								break;
							default:
								j += std::stoi(std::get<2>(instructions[i]));
						}
						j--;
						if(j >= 0)
						{
							i = j;
						}
					}
					break;
				}
				case 'b':
				{
					if(b != 0)
					{
						int j = i;
						switch(std::get<2>(instructions[i])[0])
						{
							case 'a':
								j += a;
								break;
							case 'b':
								j += b;
								break;
							case 'c':
								j += c;
								break;
							case 'd':
								j += d;
								break;
							default:
								j += std::stoi(std::get<2>(instructions[i]));
						}
						j--;
						if(j >= 0)
						{
							i = j;
						}
					}
					break;
				}
				case 'c':
				{
					if(c != 0)
					{
						int j = i;
						switch(std::get<2>(instructions[i])[0])
						{
							case 'a':
								j += a;
								break;
							case 'b':
								j += b;
								break;
							case 'c':
								j += c;
								break;
							case 'd':
								j += d;
								break;
							default:
								j += std::stoi(std::get<2>(instructions[i]));
						}
						j--;
						if(j >= 0)
						{
							i = j;
						}
					}
					break;
				}
				case 'd':
				{
					if(d != 0)
					{
						int j = i;
						switch(std::get<2>(instructions[i])[0])
						{
							case 'a':
								j += a;
								break;
							case 'b':
								j += b;
								break;
							case 'c':
								j += c;
								break;
							case 'd':
								j += d;
								break;
							default:
								j += std::stoi(std::get<2>(instructions[i]));
						}
						j--;
						if(j >= 0)
						{
							i = j;
						}
					}
					break;
				}
				default:
				{
					if(std::get<1>(instructions[i])[0] != '0')
					{
						int j = i;
						switch(std::get<2>(instructions[i])[0])
						{
							case 'a':
								j += a;
								break;
							case 'b':
								j += b;
								break;
							case 'c':
								j += c;
								break;
							case 'd':
								j += d;
								break;
							default:
								j += std::stoi(std::get<2>(instructions[i]));
						}
						j--;
						if(j >= 0)
						{
							i = j;
						}
					}
				}
			}
		}
		else if(instruction == 't')
		{
			switch(std::get<1>(instructions[i])[0])
			{
				case 'a':
				{
					if(i+a >= 0 && i+a < instructions.size())
					{
						char newInstruction = std::get<0>(instructions[i+a]);
						switch(newInstruction)
						{
							case 'i':
								newInstruction = 'd';
								break;
							case 'd':
								newInstruction = 'i';
								break;
							case 't':
								newInstruction = 'i';
								break;
							case 'j':
								newInstruction = 'c';
								break;
							case 'c':
								newInstruction = 'j';
								break;
						}
						std::get<0>(instructions[i+a]) = newInstruction;
					}
					break;
				}
				case 'b':
				{
					if(i+b >= 0 && i+b < instructions.size())
					{
						char newInstruction = std::get<0>(instructions[i+b]);
						switch(newInstruction)
						{
							case 'i':
								newInstruction = 'd';
								break;
							case 'd':
								newInstruction = 'i';
								break;
							case 't':
								newInstruction = 'i';
								break;
							case 'j':
								newInstruction = 'c';
								break;
							case 'c':
								newInstruction = 'j';
								break;
						}
						std::get<0>(instructions[i+b]) = newInstruction;
					}
					break;
				}
				case 'c':
				{
					if(i+c >= 0 && i+c < instructions.size())
					{
						char newInstruction = std::get<0>(instructions[i+c]);
						switch(newInstruction)
						{
							case 'i':
								newInstruction = 'd';
								break;
							case 'd':
								newInstruction = 'i';
								break;
							case 't':
								newInstruction = 'i';
								break;
							case 'j':
								newInstruction = 'c';
								break;
							case 'c':
								newInstruction = 'j';
								break;
						}
						std::get<0>(instructions[i+c]) = newInstruction;
					}
					break;
				}
				case 'd':
				{
					if(i+d >= 0 && i+d < instructions.size())
					{
						char newInstruction = std::get<0>(instructions[i+d]);
						switch(newInstruction)
						{
							case 'i':
								newInstruction = 'd';
								break;
							case 'd':
								newInstruction = 'i';
								break;
							case 't':
								newInstruction = 'i';
								break;
							case 'j':
								newInstruction = 'c';
								break;
							case 'c':
								newInstruction = 'j';
								break;
						}
						std::get<0>(instructions[i+d]) = newInstruction;
					}
					break;
				}
			}
		}
		else if(instruction == 'o')
		{
			switch(std::get<1>(instructions[i])[0])
				{
					case 'a':
					{
						clockSignal += std::to_string(b);
						break;
					}
					case 'b':
					{
						clockSignal += std::to_string(b);
						break;
					}
					case 'c':
					{
						clockSignal += std::to_string(b);
						break;
					}
					case 'd':
					{
						clockSignal += std::to_string(b);
						break;
					}
					default:
					{
						clockSignal += std::get<1>(instructions[i]);
						break;
					}
				}
		}
		if(clockSignal.length() > 10)
		{
			break;
		}
	}
	return clockSignal;
}

int main()
{
	std::vector<std::tuple<char, std::string, std::string>> instructions;
	std::tuple<int,int,int,int> registers = {0,0,0,0};
	bool foundRegisterValue = false;
	
	parseInput(instructions);
	
	while(!foundRegisterValue)
	{
		foundRegisterValue = true;
		std::string clockSignal;
		clockSignal = executeInstructions(instructions, registers, clockSignal);
		for(unsigned int i=0; i<clockSignal.length(); i++)
		{
			if((clockSignal[i] != '0' && i%2 == 0) || (clockSignal[i] != '1' && i%2 == 1))
			{
				foundRegisterValue = false;
				std::get<0>(registers) += 1;
				break;
			}
		}
	}

	
	std::cout << "result: " << std::get<0>(registers) << '\n';
	
	return 0;
}
