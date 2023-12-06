#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>

using namespace std;

class SeedMap
{
public:
	SeedMap();
	SeedMap(istream &file);
	void fill(std::istream &file);
	long inv_apply_range(long input);
	using rangeT = tuple<long, long, long>;
	vector<rangeT> ranges;
};

ostream &operator<<(ostream &os, SeedMap &t)
{
	long a, b, c;

	for (int i = 0; i < t.ranges.size(); i++)
	{
		tie(a, b, c) = t.ranges[i];
		os << a << " " << b << " " << c << "\n";
	}
	return os;
}

istream &operator>>(istream &is, SeedMap::rangeT &t)
{
	long a, b, c;
	is >> a >> b >> c;
	t = std::make_tuple(a, b, c);
	return is;
}

SeedMap::SeedMap(istream &file)
{
	fill(file);
}

long SeedMap::inv_apply_range(long input)
{
	long dest, source, size, ret, conversion;

	ret = input;
	for (int i = 0; i < ranges.size(); i++)
	{
		tie(source, dest, size) = ranges[i];
		conversion = dest - source;
		if (input >= source && input <= (source + size))
			return (input + conversion);
	}
	return ret;
}

void SeedMap::fill(std::istream &file)
{
	rangeT range;

	while (file >> range)
		ranges.push_back(range);
	file.clear();
}

void getSeeds(vector<long> &seeds, string const &input)
{
	std::stringstream ss(input);
	long num;

	while (ss >> num)
		seeds.push_back(num);
}

long get_smallest(vector<SeedMap> &maps, vector<long> seeds)
{
	long ret;
	for (long i = 0; i < INT_MAX; i++)
	{
		ret = i;
		for (int j = maps.size() - 1; j >= 0; j--)
			ret = maps[j].inv_apply_range(ret);
		for (int j = 0; j < seeds.size(); j++)
			if (ret == seeds[j])
				return (i);
	}
	return -1;
}

long get_smallest_range(vector<SeedMap> &maps, vector<long> seeds)
{
	long ret;
	for (long i = 0; i < INT_MAX; i++)
	{
		ret = i;
		for (int j = maps.size() - 1; j >= 0; j--)
			ret = maps[j].inv_apply_range(ret);
		for (int j = 0; j < seeds.size(); j += 2)
			if (ret >= seeds[j] && ret <= seeds[j] + seeds[j + 1])
				return (i);
	}
	return -1;
}

int main(int argc, char **argv)
{
	ifstream file;
	string line;
	vector<long> seeds;
	vector<SeedMap> maps;
	string::size_type pos, pos2;

	if (argc != 2)
		return (1);
	file.open(argv[1]);
	if (file.is_open())
	{
		getline(file, line);
		pos = line.find(':');
		getSeeds(seeds, line.substr(pos + 1, line.size() - pos));
		while (getline(file, line))
			if (line[0] && !isdigit(line[0]))
				maps.push_back(SeedMap(file));
		cout << "Smallest: " << get_smallest(maps, seeds) << "\n";
		cout << "Smallest (range): " << get_smallest_range(maps, seeds) << "\n";
	}
}