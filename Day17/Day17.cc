#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <openssl/md5.h>
#include <vector>

//Blatantly stolen from https://terminalroot.com/how-to-generate-md5-hash-with-cpp-and-openssl/
std::string md5(const std::string &str){
  unsigned char hash[MD5_DIGEST_LENGTH];

  MD5_CTX md5;
  MD5_Init(&md5);
  MD5_Update(&md5, str.c_str(), str.size());
  MD5_Final(hash, &md5);

  std::stringstream ss;

  for(int i = 0; i < MD5_DIGEST_LENGTH; i++){
    ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>( hash[i] );
  }
  return ss.str();
}

void findPath(const std::string &secret, std::string path, const size_t posX, const size_t posY, uint16_t &shortestPathLength, std::string &result)
{
	if(posX == 3 && posY == 3)
	{
		if(path.length() < shortestPathLength)
		{
			shortestPathLength = path.length();
			result = path;
		}
	}
	else
	{
		std::string hash = md5(secret+path);
		if(hash[0] >= 'b' && hash[0] <= 'f' && posY > 0 && path.length()+1 < shortestPathLength)
		{
			findPath(secret, path+'U', posX, posY-1, shortestPathLength, result);
		}
		if(hash[1] >= 'b' && hash[1] <= 'f' && posY < 3 && path.length()+1 < shortestPathLength)
		{
			findPath(secret, path+'D', posX, posY+1, shortestPathLength, result);
		}
		if(hash[2] >= 'b' && hash[2] <= 'f' && posX > 0 && path.length()+1 < shortestPathLength)
		{
			findPath(secret, path+'L', posX-1, posY, shortestPathLength, result);
		}
		if(hash[3] >= 'b' && hash[3] <= 'f' && posX < 3 && path.length()+1 < shortestPathLength)
		{
			findPath(secret, path+'R', posX+1, posY, shortestPathLength, result);
		}
	}
}

std::string findPath(const std::string &secret)
{
	std::string result;
	size_t posX = 0;
	size_t posY = 0;
	uint16_t shortestPathLength = UINT16_MAX;
	findPath(secret, "", posX, posY, shortestPathLength, result);

	return result;
}

void findLongestPath(const std::string &secret, std::string path, const size_t posX, const size_t posY, uint64_t &shortestPathLength, std::string &result)
{
	if(posX == 3 && posY == 3)
	{
		if(path.length() > shortestPathLength)
		{
			shortestPathLength = path.length();
			result = path;
		}
	}
	else
	{
		std::string hash = md5(secret+path);
		if(hash[0] >= 'b' && hash[0] <= 'f' && posY > 0)
		{
			findLongestPath(secret, path+'U', posX, posY-1, shortestPathLength, result);
		}
		if(hash[1] >= 'b' && hash[1] <= 'f' && posY < 3)
		{
			findLongestPath(secret, path+'D', posX, posY+1, shortestPathLength, result);
		}
		if(hash[2] >= 'b' && hash[2] <= 'f' && posX > 0)
		{
			findLongestPath(secret, path+'L', posX-1, posY, shortestPathLength, result);
		}
		if(hash[3] >= 'b' && hash[3] <= 'f' && posX < 3)
		{
			findLongestPath(secret, path+'R', posX+1, posY, shortestPathLength, result);
		}
	}
}

uint64_t findLongestPath(const std::string &secret)
{
	uint64_t result = 0;
	std::string longestPath;
	size_t posX = 0;
	size_t posY = 0;
	uint64_t shortestPathLength = 0;
	
	findLongestPath(secret, "", posX, posY, shortestPathLength, longestPath);
	
	result = longestPath.length();
	
	return result;
}

int main()
{
	std::string resultA;
	uint64_t resultB;
	std::string secret;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		getline(input, secret);
	}
  input.close();
	
	resultA = findPath(secret);
	resultB = findLongestPath(secret);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;

	return 0;
}
