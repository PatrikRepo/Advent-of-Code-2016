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

uint64_t findKey(const std::string &secret, const unsigned int stretches)
{
	uint64_t result = 0;
	std::vector<std::string> hashedStrings;
	
	for(int i=0; i<64; i++)
	{
		bool foundKey = false;
		
		while(!foundKey)
		{
			std::string * hashedString;
			if(result < hashedStrings.size())
			{
				hashedString = &hashedStrings[result];
			}
			else
			{
				std::string hash = md5(secret + std::to_string(result));
				for(unsigned int j=1; j<=stretches; j++)
				{
					hash = md5(hash);
				}
				hashedStrings.push_back(hash);
				hashedString = &hashedStrings.back();
			}
			
			bool potentialKeyFound = false;
			char keyElement = 0;
			for(unsigned int j=0; j<hashedString->length()-2; j++)
			{
				if((*hashedString)[j] == (*hashedString)[j+1] && (*hashedString)[j] == (*hashedString)[j+2])
				{
					potentialKeyFound = true;
					keyElement = (*hashedString)[j];
					break;
				}
			}
			
			if(potentialKeyFound)
			{
				for(int j=1; j<=1000; j++)
				{
					if(result+j < hashedStrings.size())
					{
						hashedString = &hashedStrings[result+j];
					}
					else
					{
						std::string hash = md5(secret + std::to_string(result+j));
						for(unsigned int k=1; k<=stretches; k++)
						{
							hash = md5(hash);
						}
						hashedStrings.push_back(hash);
						hashedString = &hashedStrings.back();
					}
					for(unsigned int k=0; k<hashedString->length()-4; k++)
					{
						if((*hashedString)[k] == keyElement && (*hashedString)[k+1] == keyElement && (*hashedString)[k+2] == keyElement && (*hashedString)[k+3] == keyElement && (*hashedString)[k+4] == keyElement)
						{
							foundKey = true;
							break;
						}
					}
					if(foundKey)
					{
						break;
					}
				} 
			}
			
			result++;
		}
	}
	result--;
	return result;
}

int main()
{
	uint64_t resultA;
	uint64_t resultB;
	std::string secret;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		getline(input, secret);
	}
  input.close();
	
	resultA = findKey(secret, 0);
	resultB = findKey(secret, 2016);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;

	return 0;
}
