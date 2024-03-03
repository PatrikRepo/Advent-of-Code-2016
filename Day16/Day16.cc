#include <iostream>
#include <fstream>

void parseInput(std::string &startingData)
{
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		getline(input, startingData);
	}
	input.close();
}

std::string getChecksum(const std::string &startingData, const unsigned int diskSize)
{
	std::string result;
	std::string data = startingData;
	
	while(data.length() < diskSize)
	{
		std::string reverseData = data;
		for(unsigned int i=0; i<data.length(); i++)
		{
			reverseData[data.length()-1-i] = data[i];
		}
		for(unsigned int i=0; i<data.length(); i++)
		{
			if(reverseData[i] == '1')
			{
				reverseData[i] = '0';
			}
			else
			{
				reverseData[i] = '1';
			}
		}
		data += '0' + reverseData;
	}
	
	std::string checksum;
	for(unsigned int i=0; i<diskSize; i+=2)
	{
		if(data[i] == data[i+1])
		{
			checksum += '1';
		}
		else
		{
			checksum += '0';
		}
	}
	while(checksum.length()%2 == 0)
	{
		std::string newChecksum;
		for(unsigned int i=0; i<checksum.length(); i+=2)
		{
			if(checksum[i] == checksum[i+1])
			{
				newChecksum += '1';
			}
			else
			{
				newChecksum += '0';
			}
		}
		checksum = newChecksum;
	}
	
	result = checksum;
	return result;
}

int main()
{
	std::string resultA;
	std::string resultB;
	std::string startingData;

	parseInput(startingData);

	resultA = getChecksum(startingData, 272);
	
	resultB = getChecksum(startingData, 35651584);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
