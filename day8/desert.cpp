
# define GRAY "\e[38;5;243m"
# define NO_COLOR "\e[0m"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <unistd.h>
#include <numeric>
// #include <algorithm>
using namespace  std;

struct binTree
{
	binTree* left ;
	binTree* right;
	string		name ;
};

int	traverse(map<string, binTree> nodes, string route, string start, string end)
{
	string	current = start, buf;
	int		i = 0, ret = 0;

	while (nodes[current].name[2] != 'Z')
	{
		// cout << "ha";
		ret++;
		if (route[i] == 'R')
			buf = nodes[current].right->name;
		else if (route[i] == 'L')
			buf = nodes[current].left->name;
		current = buf;
		i++;
		if (i == route.size())
			i = 0;
	}
	return ret;
}

long	calc_lcm(int a, int b)
{
	return a /  gcd(a,b) * b;
}

long	calc_lcm(vector<int> vec)
{
	long result = vec[0];
	for(int i = 1; i < vec.size(); i++)
	{
		result = lcm(result, vec[i]);
	}
	return (result);
}

unsigned long	traverse_ghost(map<string, binTree> nodes, vector<binTree> ghosts, string route)
{
	vector<int>	ways;

	for (int i = 0; i < ghosts.size(); i++)
		ways.push_back(traverse(nodes, route, ghosts[i].name, ghosts[i].name.substr(0,2) + 'Z'));
	return calc_lcm(ways);

}

int main(int argc, char **argv)
{
	ifstream file;
	string line, directions, left, right, current;
	map<string, binTree>	nodes;
	string::size_type pos, pos2;
	binTree	leftN, rightN, currentN, *edit;
	vector<binTree> ghost_starts;

	if (argc != 2)
		return (1);
	file.open(argv[1]);
	if (file.is_open())
	{
		getline(file, line);
		directions = line;
		cout <<directions << "\n";
		getline(file, line);
		while (getline(file, line))
		{
			pos = line.find('=');
			pos2 = line.find(',');
			current = line.substr(0, pos - 1);
			left = line.substr(pos + 3, (pos2 - 1) - (pos + 2));
			right = line.substr(pos2 + 2, line.size() - (pos2 + 3));
			if (nodes.find(current) == nodes.end())
				nodes.emplace(current, binTree());
			if (nodes.find(left) == nodes.end())
				nodes.emplace(left, binTree());
			if (nodes.find(right) == nodes.end())
				nodes.emplace(right, binTree());
			nodes[current].name = current;
			nodes[current].left = &nodes[left];
			nodes[current].right = &nodes[right];
			if (current[2] == 'A')
				ghost_starts.push_back(nodes[current]);
		}
	cout << "steps: " << traverse(nodes, directions, "AAA", "ZZZ") << "\n";
	cout << "ghost steps: " << traverse_ghost(nodes, ghost_starts, directions) << "\n";

	}
}