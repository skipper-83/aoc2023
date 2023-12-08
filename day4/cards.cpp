#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

void	makeArray(vector<int> &array, string input)
{
	string::size_type pos, pos2;

	pos = 0;
	while (true)
	{
		pos = input.find_first_of("0123456789", pos);
		pos2 = input.find(' ', pos);
		if (pos2 == string::npos)
			pos2 = input.length();
		array.push_back(stoi(input.substr(pos, pos2 - pos)));
		if (pos2 == input.length())
			break ;
		pos = pos2;
	}
}

int	getScore(vector<int> myNumbers, vector<int>winningNumbers)
{
	int	score = 0;

	for(int i = 0; i < myNumbers.size(); i++)
	{
		for (int j = 0; j < winningNumbers.size(); j++)
		{
			if(myNumbers[i] == winningNumbers[j])
				score++;
		}
	}
	return pow(2, score - 1);
}

int	main(int argc, char** argv)
{
	ifstream			file;
	string				line;
	string::size_type	pos, pos2;
	vector<int>			myNumbers, winningNumbers;
	int					score = 0;

	if (argc != 2)
		return (1);
	file.open(argv[1]);
	if (file.is_open())
	{
		while(getline(file, line))
		{
			cout << line << "\n";
			pos = line.find(':');
			pos2 = line.find('|');
			makeArray(myNumbers, line.substr(pos + 2, pos2 - pos - 3));
			makeArray(winningNumbers, line.substr(pos2 + 2, line.length() - pos2 + 2));
			cout << getScore(myNumbers, winningNumbers) << "\n";
			score += getScore(myNumbers, winningNumbers);
			myNumbers.clear();
			winningNumbers.clear();
		}
	}
	cout << "Score: " << score << "\n";
}
