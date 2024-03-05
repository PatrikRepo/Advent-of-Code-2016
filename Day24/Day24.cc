#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <utility>

struct Node
{
	unsigned int id = 0;
	size_t posX = 0;
	size_t posY = 0;
};

void parseInput(std::vector<std::string> &map)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input, line))
		{
			map.push_back(line);
		}
	}
	input.close();
}

bool isNode(const size_t posX, const size_t posY, const std::vector<std::string> &map)
{
	bool result = false;
	int count = 0;
	if(posX+1 < map[0].length() && (map[posY][posX+1] != '#'))
	{
		count++;
	}
	if(posX > 0 && (map[posY][posX-1] != '#'))
	{
		count++;
	}
	if(posY+1 < map.size() && (map[posY+1][posX] != '#'))
	{
		count++;
	}
	if(posY > 0 && (map[posY-1][posX] != '#'))
	{
		count++;
	}
	if(count>2)
	{
		result = true;
	}
	return result;
}

bool isDeadEnd(const size_t posX, const size_t posY, const std::vector<std::string> &map)
{
	bool result = false;
	if(map[posY][posX] != '#')
	{
		int count = 0;
		if(posX+1 < map[0].length() && (map[posY][posX+1] != '#'))
		{
			count++;
		}
		if(posX > 0 && (map[posY][posX-1] != '#'))
		{
			count++;
		}
		if(posY+1 < map.size() && (map[posY+1][posX] != '#'))
		{
			count++;
		}
		if(posY > 0 && (map[posY-1][posX] != '#'))
		{
			count++;
		}
		if(count<=1)
		{
			result = true;
		}
	}
	return result;
}

Node * getNode(const size_t posX, const size_t posY, std::vector<Node> &nodes)
{
	for(auto it=nodes.begin(); it!=nodes.end(); it++)
	{
		if(it->posX == posX && it->posY == posY)
		{
			return &(*it);
		}
	}
	return nullptr;
}

std::tuple<Node,Node,unsigned int> * getEdge(const unsigned int node1Id, const unsigned int node2Id, std::vector<std::tuple<Node,Node,unsigned int>> &graph)
{
	for(auto it=graph.begin(); it!=graph.end(); it++)
	{
		if(std::get<0>(*it).id == node1Id && std::get<0>(*it).id == node2Id)
		{
			return &(*it);
		}
	}
	return nullptr;
}

void createUnrefinedGraph(std::vector<std::tuple<Node,Node,unsigned int>> &unrefinedGraph, std::vector<std::string> &map, std::vector<Node> &nodes)
{
	for(auto it=nodes.begin(); it!=nodes.end(); it++)
	{
		size_t posX = it->posX;
		size_t posY = it->posY;

		if(posX+1 < map[0].length() && (map[posY][posX+1] != '#'))
		{
			unsigned int steps = 1;
			size_t newX = posX+1;
			size_t newY = posY;
			Node* otherNode;

			while(map[newY][newX] == '.')
			{
				map[newY][newX] = '#';
				if(map[newY-1][newX] != '#')
				{
					newY--;
				}
				else if(map[newY][newX+1] != '#')
				{
					newX++;
				}
				else if(map[newY+1][newX] != '#')
				{
					newY++;
				}
				else if(map[newY][newX-1] != '#')
				{
					newX--;
				}
				steps++;
			}
			otherNode = getNode(newX, newY, nodes);
			if(otherNode)
			{
				std::tuple<Node,Node,unsigned int> * edge;
				
				if(it->id < otherNode->id)
				{
					edge = getEdge(it->id, otherNode->id, unrefinedGraph);
					if(!edge)
					{
						unrefinedGraph.push_back(std::make_tuple(*it, *otherNode, steps));
					}
					else
					{
						if(std::get<2>(*edge) > steps)
						{
							std::get<2>(*edge) = steps;
						}
					}
				}
				else
				{
					edge = getEdge(otherNode->id, it->id, unrefinedGraph);
					if(!edge)
					{
						unrefinedGraph.push_back(std::make_tuple(*otherNode, *it, steps));
					}
					else
					{
						if(std::get<2>(*edge) > steps)
						{
							std::get<2>(*edge) = steps;
						}
					}
				}
			}
		}
		
		if(posX > 0 && (map[posY][posX-1] != '#'))
		{
			unsigned int steps = 1;
			size_t newX = posX-1;
			size_t newY = posY;
			Node* otherNode;

			while(map[newY][newX] == '.')
			{
				map[newY][newX] = '#';
				if(map[newY+1][newX] != '#')
				{
					newY++;
				}
				else if(map[newY][newX-1] != '#')
				{
					newX--;
				}
				else if(map[newY-1][newX] != '#')
				{
					newY--;
				}
				else if(map[newY][newX+1] != '#')
				{
					newX++;
				}
				steps++;
			}
			otherNode = getNode(newX, newY, nodes);
			if(otherNode)
			{
				std::tuple<Node,Node,unsigned int> * edge;
				
				if(it->id < otherNode->id)
				{
					edge = getEdge(it->id, otherNode->id, unrefinedGraph);
					if(!edge)
					{
						unrefinedGraph.push_back(std::make_tuple(*it, *otherNode, steps));
					}
					else
					{
						if(std::get<2>(*edge) > steps)
						{
							std::get<2>(*edge) = steps;
						}
					}
				}
				else
				{
					edge = getEdge(otherNode->id, it->id, unrefinedGraph);
					if(!edge)
					{
						unrefinedGraph.push_back(std::make_tuple(*otherNode, *it, steps));
					}
					else
					{
						if(std::get<2>(*edge) > steps)
						{
							std::get<2>(*edge) = steps;
						}
					}
				}
			}
		}
		if(posY+1 < map.size() && (map[posY+1][posX] != '#'))
		{
			unsigned int steps = 1;
			size_t newX = posX;
			size_t newY = posY+1;
			Node* otherNode;

			while(map[newY][newX] == '.')
			{
				map[newY][newX] = '#';
				
				if(map[newY][newX-1] != '#')
				{
					newX--;
				}
				else if(map[newY][newX+1] != '#')
				{
					newX++;
				}
				else if(map[newY+1][newX] != '#')
				{
					newY++;
				}
				else if(map[newY-1][newX] != '#')
				{
					newY--;
				}
				steps++;
			}
			otherNode = getNode(newX, newY, nodes);
			if(otherNode)
			{
				std::tuple<Node,Node,unsigned int> * edge;
				
				if(it->id < otherNode->id)
				{
					edge = getEdge(it->id, otherNode->id, unrefinedGraph);
					if(!edge)
					{
						unrefinedGraph.push_back(std::make_tuple(*it, *otherNode, steps));
					}
					else
					{
						if(std::get<2>(*edge) > steps)
						{
							std::get<2>(*edge) = steps;
						}
					}
				}
				else
				{
					edge = getEdge(otherNode->id, it->id, unrefinedGraph);
					if(!edge)
					{
						unrefinedGraph.push_back(std::make_tuple(*otherNode, *it, steps));
					}
					else
					{
						if(std::get<2>(*edge) > steps)
						{
							std::get<2>(*edge) = steps;
						}
					}
				}
			}
		}
		if(posY > 0 && (map[posY-1][posX] != '#'))
		{
			unsigned int steps = 1;
			size_t newX = posX;
			size_t newY = posY-1;
			Node* otherNode;

			while(map[newY][newX] == '.')
			{
				map[newY][newX] = '#';
				if(map[newY][newX+1] != '#')
				{
					newX++;
				}
				else if(map[newY][newX-1] != '#')
				{
					newX--;
				}
				else if(map[newY-1][newX] != '#')
				{
					newY--;
				}
				else if(map[newY+1][newX] != '#')
				{
					newY++;
				}
				steps++;
			}
			otherNode = getNode(newX, newY, nodes);
			if(otherNode)
			{
				std::tuple<Node,Node,unsigned int> * edge;
				
				if(it->id < otherNode->id)
				{
					edge = getEdge(it->id, otherNode->id, unrefinedGraph);
					if(!edge)
					{
						unrefinedGraph.push_back(std::make_tuple(*it, *otherNode, steps));
					}
					else
					{
						if(std::get<2>(*edge) > steps)
						{
							std::get<2>(*edge) = steps;
						}
					}
				}
				else
				{
					edge = getEdge(otherNode->id, it->id, unrefinedGraph);
					if(!edge)
					{
						unrefinedGraph.push_back(std::make_tuple(*otherNode, *it, steps));
					}
					else
					{
						if(std::get<2>(*edge) > steps)
						{
							std::get<2>(*edge) = steps;
						}
					}
				}
			}
		}
			
	}
}

std::vector<unsigned int> dijkstras(const std::vector<std::tuple<Node,Node,unsigned int>> &unrefinedGraph, const unsigned int startNode, const unsigned int endNode, const unsigned int numberOfNodes)
{
	std::vector<unsigned int> result;
	for(unsigned int i=0; i<numberOfNodes; i++)
	{
		result.push_back(0);
	}
	
	std::vector<std::pair<unsigned int,uint64_t>> distances; 
	for(unsigned int i=0; i<numberOfNodes; i++)
	{
		distances.push_back(std::make_pair(i,UINT64_MAX));
	}

	bool inPath[numberOfNodes] = {false};
	unsigned int nodesDone = 0;
	
	distances[startNode].second = 0;
	
	for(unsigned int i=0; i<numberOfNodes; i++)
	{
		uint64_t minDist = UINT64_MAX;
		unsigned int node = 0;
		for(unsigned int j=0; j<numberOfNodes; j++)
		{
			if(!inPath[j] && minDist > distances[j].second)
			{
				minDist = distances[j].second;
				node = distances[j].first;
			}
		}
		inPath[node] = true;
		
		for(auto it=unrefinedGraph.begin(); it!=unrefinedGraph.end(); it++)
		{
			unsigned int otherNode = 0;
			bool foundNode = false;
			if(std::get<0>(*it).id == node)
			{
				otherNode = std::get<1>(*it).id;
				foundNode = true;
			}
			else if(std::get<1>(*it).id == node)
			{
				otherNode = std::get<0>(*it).id;
				foundNode = true;
			}
			if(foundNode)
			{
				for(unsigned int j=0; j<numberOfNodes; j++)
				{
					if(distances[j].first == otherNode && distances[j].second > minDist + std::get<2>(*it))
					{
						distances[j].second = minDist + std::get<2>(*it);
						break;
					}
				}
			}
		}

		if(node > startNode && node < endNode)
		{
			result[node] = minDist;
			nodesDone++;
		}

		if(nodesDone == endNode - 1 - startNode)
		{
			break;
		}
	}

	return result;
}

void buildGraph(std::vector<std::string> &map, std::vector<std::tuple<unsigned int,unsigned int,unsigned int>> &graph)
{
	std::vector<Node> nodes;
	std::vector<Node> nodesToVisit;
	for(unsigned int i=0; i<map.size(); i++)
	{
		for(unsigned int j=0; j<map[0].length(); j++)
		{
			if(map[i][j] != '#' && map[i][j] != '.')
			{
				Node node;
				node.id = map[i][j] - '0';
				node.posX = j;
				node.posY = i;
				nodes.push_back(node);
				nodesToVisit.push_back(node);
			}
		}
	}
	
	for(unsigned int i=0; i<map.size(); i++)
	{
		for(unsigned int j=0; j<map[0].length(); j++)
		{
			if(map[i][j] == '.')
			{
				if(isDeadEnd(j, i, map))
				{
					bool deadEndRemoved = false;
					int deadEndI = i;
					int deadEndJ = j;
					while(!deadEndRemoved)
					{
						deadEndRemoved = true;
						map[deadEndI][deadEndJ] = '#';
						
						if(isDeadEnd(deadEndJ+1,deadEndI,map))
						{
							deadEndRemoved = false;
							deadEndJ++;
						}
						else if(isDeadEnd(deadEndJ-1,deadEndI,map))
						{
							deadEndRemoved = false;
							deadEndJ--;
						}
						else if(isDeadEnd(deadEndJ,deadEndI+1,map))
						{
							deadEndRemoved = false;
							deadEndI++;
						}
						else if(isDeadEnd(deadEndJ,deadEndI-1,map))
						{
							deadEndRemoved = false;
							deadEndI--;
						}
					}
				}
			}

		}
	}

	int nodeId = nodes.size();
	for(unsigned int i=0; i<map.size(); i++)
	{
		for(unsigned int j=0; j<map[0].length(); j++)
		{
			if(map[i][j] == '.')
			{
				if(isNode(j, i, map))
				{
					map[i][j] = 'N';
					Node node;
					node.id = nodeId;
					node.posX = j;
					node.posY = i;
					nodes.push_back(node);
					nodeId++;
				}
			}
		}
	}

	std::vector<std::tuple<Node,Node,unsigned int>> unrefinedGraph;
	createUnrefinedGraph(unrefinedGraph, map, nodes);
	
	std::vector<unsigned int> distances;
	for(unsigned int i=0; i<nodesToVisit.size()-1; i++)
	{
		distances = dijkstras(unrefinedGraph, i, nodesToVisit.size(), nodes.size());
		
		for(unsigned int j=i+1; j<nodesToVisit.size(); j++)
		{
			graph.push_back(std::make_tuple(i,j,distances[j]));
		}
	}

}

uint64_t shortestDistance(std::vector<std::tuple<unsigned int,unsigned int,unsigned int>> &graph, std::vector<int> visited, const unsigned int from, const unsigned int here, const unsigned int visNum, const bool backAgain)
{
	uint64_t result = 0;
	
	if(visNum < visited.size()-1)
	{
		result = UINT64_MAX;
		visited[here] = 1;
		
		uint64_t newResult = 0;		
		for(unsigned int i=1; i<visited.size(); i++)
		{
			if(visited[i] == 0)
			{
				newResult = shortestDistance(graph, visited, here, i, visNum+1, backAgain);
				if(newResult < result)
				{
					result = newResult;
				}			
			}
		}
	}
	else
	{
		if(backAgain)
		{
			result += shortestDistance(graph, visited, here, 0, visNum+1, false);
		}
	}
	for(auto it=graph.begin(); it!=graph.end(); it++)
	{
		if((from == std::get<0>(*it) && here == std::get<1>(*it)) || (from == std::get<1>(*it) && here == std::get<0>(*it)))
		{
			uint64_t temp = std::get<2>(*it);
			result = result + temp;
			break;
		}
	}
	
	return result;
}

uint64_t shortestDistance(std::vector<std::tuple<unsigned int,unsigned int,unsigned int>> &graph, bool backAgain)
{
	uint64_t result = UINT64_MAX;
	unsigned int numberOfNodes = std::get<1>(graph.back())+1;
	unsigned int lastNode = 0;
	std::vector<int> visited;
	visited.push_back(1);
	for(unsigned int i=1; i<numberOfNodes; i++)
	{
		visited.push_back(0);
	}
	
	for(unsigned int i=1; i<numberOfNodes; i++)
	{
		uint64_t newResult = shortestDistance(graph, visited, 0, i, 1, backAgain);

		if(result > newResult)
		{
			result = newResult;
		}
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::vector<std::string> map;
	std::vector<std::tuple<unsigned int,unsigned int,unsigned int>> graph;
	parseInput(map);

	buildGraph(map, graph);
	
	resultA = shortestDistance(graph, false);

	resultB = shortestDistance(graph, true);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
		
	return 0;
}
