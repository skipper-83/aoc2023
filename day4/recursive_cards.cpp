#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

class happyCard
{
public:
	vector<int>	_myNumbers;
	vector<int> _winningNumbers;
	int			_id;
	int			_score;
	happyCard(int id, vector<int> myNumbers, vector<int> winningNumbers, int score);
	~happyCard();
};

happyCard::happyCard(int id, vector<int> myNumbers, vector<int> winningNumbers, int score) : _id(id), _score(score)
{
	for(int i = 0; i < myNumbers.size(); i++)
		this->_myNumbers.push_back(myNumbers[i]);
	for(int i = 0; i < winningNumbers.size(); i++)
		this->_winningNumbers.push_back(winningNumbers[i]);
}

happyCard::~happyCard()
{
}

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
	return score;
}

int	getRecursiveScore(vector<happyCard> cards, int idx)
{
	int	score = 0;
	for (int i = idx + 1; i < cards[idx]._score + idx + 1; i++)
		score += getRecursiveScore(cards, i);
	score += cards[idx]._score;
	return score;
}

int	main(int argc, char** argv)
{
	ifstream			file;
	string				line;
	string::size_type	pos, pos2;
	vector<int>			myNumbers, winningNumbers;
	vector<happyCard>	cards;
	int					score = 0, i = 1, recursiveScore = 0, curRecScore, curScore;

	if (argc != 2)
		return (1);
	file.open(argv[1]);
	if (file.is_open())
	{
		while(getline(file, line))
		{
			pos = line.find(':');
			pos2 = line.find('|');
			makeArray(myNumbers, line.substr(pos + 2, pos2 - pos - 3));
			makeArray(winningNumbers, line.substr(pos2 + 2, line.length() - pos2 + 2));
			curScore = getScore(myNumbers, winningNumbers);
			score += pow(2, curScore - 1);
			cards.push_back(happyCard(i, myNumbers, winningNumbers, curScore));
			i++;
			myNumbers.clear();
			winningNumbers.clear();
		}
	}
	for (int i = 0; i < cards.size(); i++)
	{
		cout << "Card " << setw(3) << cards[i]._id  << ":";
		
		for(int j = 0; j < cards[i]._myNumbers.size(); j++)
		{
			cout << " " << setw(2) << cards[i]._myNumbers[j];
			
		}
		cout << " |";
		for(int j = 0; j < cards[i]._winningNumbers.size(); j++)
			cout << " " << setw(2) << cards[i]._winningNumbers[j];
		curRecScore = getRecursiveScore(cards, i);
		cout << " rec_score: " << curRecScore + 1<<"\n";
		recursiveScore += curRecScore + 1;
	}
	cout << "Score: " << score << " rec score: " << recursiveScore << " \n";
}
