#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <openssl/md5.h>

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

std::string decrypt(const std::string &secret)
{
	std::string result = "00000000";
	uint64_t index = 0;
	
	for(int i=0; i<8; i++)
	{
		bool foundDigit = false;
		while(!foundDigit)
		{
			std::string key = std::to_string(index);
			std::string hash = md5(secret+key);

			if(hash[0] == '0' && hash[1] == '0' && hash[2] == '0' && hash[3] == '0' && hash[4] == '0')
			{
				result[i] = hash[5];
				foundDigit = true;
			}
			index++;
		}
		std::cout << result << std::endl;
	}
	return result;
}

std::string decryptWithPositions(const std::string &secret)
{
	std::string result = "00000000";
	int foundIndex[8] = {0,0,0,0,0,0,0,0};
	uint64_t index = 0;
	
	for(int i=0; i<8; i++)
	{
		bool foundDigit = false;
		while(!foundDigit)
		{
			std::string key = std::to_string(index);
			std::string hash = md5(secret+key);

			if(hash[0] == '0' && hash[1] == '0' && hash[2] == '0' && hash[3] == '0' && hash[4] == '0')
			{
				int pos = hash[5]-'0';
				if(pos<8 && foundIndex[pos] == 0)
				{
					foundIndex[pos] = 1;
					result[pos] = hash[6];
					foundDigit = true;
				}
			}
			index++;
		}
		std::cout << result << std::endl;
	}
	return result;
}

int main()
{
	std::string resultA;
	std::string resultB;
	std::string secret;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		getline(input, secret);
	}
  input.close();
	
	resultA = decrypt(secret);
	resultB = decryptWithPositions(secret);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;

	return 0;
}
