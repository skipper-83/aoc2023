#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>


using namespace std;


void	get_nums(string &line, vector<vector<int> > &sequences)
{
	stringstream ss(line);
	vector<int> cur_line;
	int	num = 0;

	while (ss >> num)
		cur_line.push_back(num);
	sequences.push_back(cur_line);
}

int	get_increment(vector<int> seq)
{
	int	dif;
	vector<int> difs;
	bool	recurse = false;

	difs.push_back(seq[1] - seq[0]);
	for (int i = 2; i < seq.size(); i++)
	{
		dif = seq[i] - seq[i - 1];
		if (dif != difs[i - 2])
			recurse = true;
		difs.push_back(dif);
	}
	if (recurse)
		dif += get_increment(difs);
	return dif;

}

int	get_decrement(vector<int> seq)
{
	int	dif;
	vector<int> difs;
	bool	recurse = false;

	
	difs.push_back(seq[1] - seq[0]);
	for (int i = 2; i < seq.size(); i++)
	{
		dif = seq[i] - seq[i - 1];
		if (dif != difs[i - 2])
			recurse = true;
		difs.push_back(dif);
	}
	dif = difs[0];
	if (recurse)
		 dif -= get_decrement(difs);
	return dif;

}

int main(int argc, char **argv)
{
	ifstream file;
	string line;
	vector<vector<int> > sequences;
	int	ret = 0, ret2 = 0;

	if (argc != 2)
		return (1);
	file.open(argv[1]);
	if (file.is_open())
	{
		while (getline(file, line))
			get_nums(line, sequences);
		for (auto it : sequences)
		{
			for (auto it2 : it)
				cout << it2 << " ";
			cout << "\n";
			ret += it[it.size() - 1] + get_increment(it);
			ret2 += it[0] - get_decrement(it);
		}
			
	}
	cout << "increments: " << ret << "\n"
	<< "decrements: " << ret2 << "\n";
	
}