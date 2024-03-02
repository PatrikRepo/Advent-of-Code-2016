#include <iostream>
#include <fstream>

void parseInput(std::string &compressedLine)
{
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		getline(input, compressedLine);
	}
	input.close();
	
}

uint64_t decompressLine(const std::string &compressedLine)
{
	uint64_t result = 0;
	
	for(unsigned int i=0; i<compressedLine.length(); i++)
	{
		if(compressedLine[i] != '(')
		{
			result++;
		}
		else
		{
			size_t pos = i+1;
			size_t endpos = compressedLine.find_first_of("x",pos);
			int numberOfChars = std::stoi(compressedLine.substr(pos,endpos-pos));
			
			pos = endpos+1;
			endpos = compressedLine.find_first_of(")",pos);
			int numberOfRepeats = std::stoi(compressedLine.substr(pos,endpos-pos));
			
			result += numberOfChars*numberOfRepeats;
			i = endpos + numberOfChars;
		}
	}
	
	return result;
}

uint64_t decompressSubstring(const std::string &compressedSubstring, const int numberOfRepeats)
{
	uint64_t result = 0;
	
	for(unsigned int i=0; i<compressedSubstring.length(); i++)
	{
		if(compressedSubstring[i] != '(')
		{
			result++;
		}
		else
		{
			size_t pos = i+1;
			size_t endpos = compressedSubstring.find_first_of("x",pos);
			int newNumberOfChars = std::stoi(compressedSubstring.substr(pos,endpos-pos));
			
			pos = endpos+1;
			endpos = compressedSubstring.find_first_of(")",pos);
			int newNumberOfRepeats = std::stoi(compressedSubstring.substr(pos,endpos-pos));
			
			std::string newCompressedSubstring = compressedSubstring.substr(endpos+1,newNumberOfChars);
			result += decompressSubstring(newCompressedSubstring, newNumberOfRepeats);
			i = endpos + newNumberOfChars;
		}
	}
	result *= numberOfRepeats;
	return result;
}

uint64_t maxDecompressLine(const std::string &compressedLine)
{
	uint64_t result = 0;
	for(unsigned int i=0; i<compressedLine.length(); i++)
	{
		if(compressedLine[i] != '(')
		{
			result++;
		}
		else
		{
			size_t pos = i+1;
			size_t endpos = compressedLine.find_first_of("x",pos);
			int numberOfChars = std::stoi(compressedLine.substr(pos,endpos-pos));
			
			pos = endpos+1;
			endpos = compressedLine.find_first_of(")",pos);
			int numberOfRepeats = std::stoi(compressedLine.substr(pos,endpos-pos));
			
			std::string compressedSubstring = compressedLine.substr(endpos+1,numberOfChars);
			result += decompressSubstring(compressedSubstring, numberOfRepeats);
			i = endpos + numberOfChars;
		}
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::string compressedLine;
	
	parseInput(compressedLine);
	
	resultA = decompressLine(compressedLine);
	resultB = maxDecompressLine(compressedLine);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;

	return 0;
}
