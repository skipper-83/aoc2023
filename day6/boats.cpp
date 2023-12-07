#include <vector>
#include <tuple>
#include <iostream>

using namespace std;
using boatRace = tuple<long, long>;



long	winning_options(boatRace &race)
{
	long	ret = 0, time, distance, travel_time;

	tie(time, distance) = race;
	for (long press_time = 0; press_time <= time; press_time++)
	{
		travel_time = time - press_time;
		if (travel_time * press_time > distance)
			ret++;
	}
	return ret;
}

int main(int argc, char **argv)
{
	vector<boatRace>	races = {
		{12,345},
		{34,567},
		{89,1011},
		{12,1314}

	};
	vector<boatRace>	big_race = {
		{12348912,34556710111314}
	};
	long ret = 1;
	for (int i = 0; i < races.size(); i++)
		ret *= winning_options(races[i]);
	cout << "Product of winning options: " << ret << "\n";
	cout << "Big race winning options " << winning_options(big_race[0]) << "\n";

}