#include <vector>
#include <tuple>
#include <iostream>

using namespace std;
using boatRace = tuple<long, long>;

/*
Time:      7  15   30
Distance:  9  40  200
		{7,9},
		{15,40},
		{30,200}
*/


/*
Time:        48     98     90     83
Distance:   390   1103   1112   1360
48989083
390110311121360
		{48,390},
		{98,1103},
		{90,1112},
		{83,1360}
*/


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
		{48,390},
		{98,1103},
		{90,1112},
		{83,1360}

	};
	vector<boatRace>	big_race = {
		{48989083,390110311121360}
	};
	long ret = 1;
	for (int i = 0; i < races.size(); i++)
		ret *= winning_options(races[i]);
	cout << "Product of winning options: " << ret << "\n";
	cout << "Big race winning options " << winning_options(big_race[0]) << "\n";

}