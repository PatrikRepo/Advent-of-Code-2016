#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>

void parseInput(std::vector<std::tuple<unsigned int, unsigned int, unsigned int>> &triangles)
{
	std::string line;

	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input, line))
		{
			std::tuple<unsigned int, unsigned int, unsigned int> triangle;
			size_t pos = 0;
			size_t endpos = 0;
			
			pos = line.find_first_of("1234567890");
			endpos = line.find_first_of(" ", pos);
			std::get<0>(triangle) = std::stoi(line.substr(pos, endpos-pos));

			pos = line.find_first_of("1234567890", endpos);
			endpos = line.find_first_of(" ", pos);
			std::get<1>(triangle) = std::stoi(line.substr(pos, endpos-pos));

			pos = line.find_first_of("1234567890", endpos);
			endpos = line.length();
			std::get<2>(triangle) = std::stoi(line.substr(pos, endpos-pos));		
			
			triangles.push_back(triangle);
		}
	}
	input.close();
}

unsigned int isTriangle(const int a, const int b, const int c)
{
	unsigned int result = 0;
	
	if(((a+b-c)>0) && ((b+c-a)>0) && ((c+a-b)>0))
	{
		result = 1;
	}
	return result;
}

uint64_t findTriangles(const std::vector<std::tuple<unsigned int, unsigned int, unsigned int>> &triangles)
{
	uint64_t result = 0;
	for(auto it=triangles.begin(); it!=triangles.end(); it++)
	{
		result += isTriangle(std::get<0>(*it),std::get<1>(*it),std::get<2>(*it));
	}
	return result;
}

uint64_t findColumnTriangles(const std::vector<std::tuple<unsigned int, unsigned int, unsigned int>> &triangles)
{
	uint64_t result = 0;
	for(unsigned int i=0; i<triangles.size(); i=i+3)
	{
		result += isTriangle(std::get<0>(triangles[i]),std::get<0>(triangles[i+1]),std::get<0>(triangles[i+2]));
		result += isTriangle(std::get<1>(triangles[i]),std::get<1>(triangles[i+1]),std::get<1>(triangles[i+2]));
		result += isTriangle(std::get<2>(triangles[i]),std::get<2>(triangles[i+1]),std::get<2>(triangles[i+2]));
	}
	return result;
}
	
int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::vector<std::tuple<unsigned int, unsigned int, unsigned int>> triangles;
	
	parseInput(triangles);
	
	resultA = findTriangles(triangles);
	resultB = findColumnTriangles(triangles);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;	
}

