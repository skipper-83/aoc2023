#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
#define GALAXY_AGE 999999

int main(int argc, char **argv)
{
	ifstream file;
	string line, route;
	vector<string> universe;
	bool	all_dots;
	vector<pair<int, int> > galaxies;
	vector<int> empty_rows, empty_cols;
	int	lines = 0, extra_lines, x_dist, y_dist;
	long distances = 0;


	if (argc != 2)
		return (1);
	file.open(argv[1]);
	if (file.is_open())
	{
		while (getline(file, line) && line[0])
		{
			all_dots = true;
			universe.push_back(line);
			for (auto it : line)
				if (it != '.')
					all_dots = false;
			if (all_dots)
				empty_rows.push_back(lines);
			lines++;
		}
		for (int i = 0; i < universe[0].size(); i++)
		{
			all_dots = true;
			for (int j = 0; j < universe.size(); j++)
				if (universe[j][i] != '.')
					all_dots = false;
			if (all_dots)
				empty_cols.push_back(i);
		}
		for (int i = 0; i < universe.size(); i++)
		{
			for(int j = 0; j < universe[i].size(); j++)
			{
				if (universe[i][j] == '#')
					galaxies.push_back({i, j});
			}
		}
		for (int i = 0; i < galaxies.size(); i++)
		{
			for(int j = 1; j < galaxies.size(); j++)
			{
				if (i != j && j > i)
				{
					int	x_start, x_end, y_start, y_end;
					if (galaxies[i].first < galaxies[j].first)
					{
						x_start = galaxies[i].first;
						x_end = galaxies[j].first;
					} else {
						x_start = galaxies[j].first;
						x_end = galaxies[i].first;
					}
					if (galaxies[i].second < galaxies[j].second)
					{
						y_start = galaxies[i].second;
						y_end = galaxies[j].second;
					} else {
						y_start = galaxies[j].second;
						y_end = galaxies[i].second;
					}
					
					x_dist = x_end - x_start;
					y_dist = y_end - y_start;
					extra_lines = 0;
					for (int x = x_start; x <= x_end; x++)
						if (find(empty_rows.begin(), empty_rows.end(), x) != empty_rows.end())
							extra_lines++;
					for (int y = y_start; y <= y_end; y++)
						if (find(empty_cols.begin(), empty_cols.end(), y) != empty_cols.end())
							extra_lines++;
					distances += x_dist + y_dist + extra_lines * GALAXY_AGE;
				}
			}
			
		}
		cout << distances << "\n";
	}
}