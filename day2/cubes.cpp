#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <tuple>

#define REDS 12
#define GREENS 13
#define BLUES 14
using namespace std;

using rgb = tuple<int, int, int>;

int	max_color(string line, string color)
{
	string::size_type searchPos, left, right;
	int maxColor = 0, curColor = 0;

	searchPos = 0;
	while ((searchPos = line.find(color, searchPos)) != string::npos)
	{
		right = line.rfind(' ', searchPos - 1);
		left = line.rfind(' ', right - 1);
		curColor = stoi(line.substr(left + 1, right - (left + 1)));
		// cout << "[" << curColor << "]\n";
		if (curColor > maxColor) maxColor = curColor;
		searchPos++;
	}
	// cout << "Max of " << color << " is " << maxColor << "\n";
	return maxColor;
}

int main(int argc, char **argv)
{
	string line;
	ifstream file;
	string::size_type right, left;
	// map<int, map<int, int, int>> games;
	vector<rgb> games;

	int	reds, blues, greens, searchPos;

	if (argc != 2)
		return (1);

	file.open(argv[1]);
	if (file.is_open())
	{
		while (getline(file, line))
			games.push_back(make_tuple(max_color(line, "red"), max_color(line, "green"), max_color(line, "blue")));
	}
	int red,green,blue, i=1, sum=0, pow=0;
	for (const auto &it : games)
	{	
		tie(red, green, blue) = it;
		cout << i << ": " << red << " " << green << " " << blue << "\n";
		if (red <= REDS && green <= GREENS && blue <= BLUES) sum += i;
		pow += red * green * blue;
		i++;
	}
	cout << "sum: " << sum << "; pow: " << pow << "\n";
}
