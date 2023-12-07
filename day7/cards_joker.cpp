#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

#define HIGH_CARD 0
#define PAIR 1
#define TWO_PAIR 2
#define THREE_OF_A_KIND 3
#define FULL_HOUSE 4
#define FOUR_OF_A_KIND 5
#define FIVE_OF_A_KIND 6

map<char, int>	card_worths;


class camelCard
{
private:
	void	_calcWorth();
	bool	_twoPairsFullHouse(char foundChar);
	void	_handleJokers(int jokers);

public:
	string _card;
	int		_bid;
	int		_worth;
	char	_high_card;
	vector<string>	_scores = {
		"high card",
		"pair",
		"two pair",
		"three of a kind",
		"full house",
		"four of a kind",
		"five of a kind"
	};
	// bool	operator<(camelCard const &rhs);

	camelCard(string const &card, int const &bid);
	~camelCard();
};

bool camelCard::_twoPairsFullHouse(char foundChar)
{
	int	reps = 1;
	for (int i = 0; i < _card.size(); i++)
	{
		if (_card[i] != foundChar)
		{
			for(int j = 0; j < _card.size(); j++)
				if (j != i && _card[i] == _card[j])
					reps++;
			if (reps == 2)
				return true;
		}
	}
return false;
}

void camelCard::_handleJokers(int jokers)
{
	if (!jokers)
		return ;
	switch (_worth)
	{
		case HIGH_CARD:
			_worth = PAIR;
			break ;
		case PAIR:
			_worth = THREE_OF_A_KIND;
			break ;
		case TWO_PAIR:
			if (jokers == 1)
				_worth = FULL_HOUSE;
			else
				_worth = FOUR_OF_A_KIND;
			break ;
		case THREE_OF_A_KIND:
			_worth = FOUR_OF_A_KIND;
			break ;
		default:
			_worth = FIVE_OF_A_KIND;
	}
}

void	camelCard::_calcWorth(void)
{
	int		reps = 0, char_reps, jokers = 0;
	char	rep_char = '0', high_card = '2';



	for(int i = 0; i < _card.size(); i++)
	{
		char_reps = 1;
		if (_card[i] == 'J')
			jokers++;
		if (card_worths[_card[i]] > card_worths[high_card])
			high_card = _card[i];
		for(int j = 0; j < _card.size(); j++)
		{
			if (_card[i] == _card[j] && i !=j)
				char_reps++;
		}
		if (char_reps > reps)
		{
			reps = char_reps;
			rep_char = _card[i];
		}
	}
	switch (reps)
	{
	case 1:
		_worth = 0;
		break ;
	case 2:
		_twoPairsFullHouse(rep_char) ? _worth = 2 : _worth = 1;
		break;
	case 3:
		_twoPairsFullHouse(rep_char) ? _worth = 4 : _worth = 3;
		break ;
	default:
		_worth = reps + 1;
		break ;
	}
	_high_card = high_card;
	_handleJokers(jokers);
	cout << _card << ": "
	<< reps << " x " << rep_char 
	<< "; hicard: " << high_card 
	<< "; worth: " << _scores[_worth] << " [" << _worth << "] "
	<< "; bid: " << _bid << "\n";
}

bool smallerThan(camelCard const &lhs, camelCard const &rhs)
{
	if (lhs._worth > rhs._worth)
		return false;
	if (lhs._worth < rhs._worth)
		return  true;

		for (int i = 0; i < 5; i++)
		{
			if (card_worths[lhs._card[i]] < card_worths[rhs._card[i]])
				return true;
			if (card_worths[lhs._card[i]] > card_worths[rhs._card[i]])
				return false;
		}
	return true;
}

camelCard::camelCard(string const &card, int const &bid) : _card(card), _bid(bid)
{
	this->_calcWorth();
}

camelCard::~camelCard()
{
}

bool newComp(camelCard const &lhs, camelCard const &rhs)
{
	if (strcmp(lhs._card.c_str(), rhs._card.c_str()) > 0)
		return false;
	return true;
}

int main(int argc, char **argv)
{
	ifstream file;
	string line;
	vector<camelCard> cards;
	string::size_type pos, pos2;
	string cur_card;
	int	cur_bid;
	long score = 0;

	card_worths.insert({'A', 14});
	card_worths.insert({'K', 13});
	card_worths.insert({'Q', 12});
	card_worths.insert({'T', 10});
	card_worths.insert({'9', 9});
	card_worths.insert({'8', 8});
	card_worths.insert({'7', 7});
	card_worths.insert({'6', 6});
	card_worths.insert({'5', 5});
	card_worths.insert({'4', 4});
	card_worths.insert({'3', 3});
	card_worths.insert({'2', 2});
	card_worths.insert({'J', 1});

	if (argc != 2)
		return (1);
	file.open(argv[1]);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			pos = line.find(' ');
			cur_card = line.substr(0, pos);
			cur_bid = stoi(line.substr(pos + 1, line.size() - pos + 1));
			cards.push_back(camelCard(cur_card, cur_bid));
		}
	}
	stable_sort(cards.begin(), cards.end(), smallerThan);
	cout << "\n\n SCORES \n\n";
	for (int i = 0; i < cards.size(); i++)
	{
		cout << cards[i]._card << ": "
		<< "; hicard: " << cards[i]._high_card 
		<< "; worth: " << cards[i]._scores[cards[i]._worth] << " [" <<cards[i]. _worth << "] "
		<< "; bid: " << cards[i]._bid << "\n";
		score += (i + 1) * cards[i]._bid;
	}
	cout << "score: " << score << "\n";

}