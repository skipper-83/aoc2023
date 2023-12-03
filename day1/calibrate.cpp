#include <iostream>
#include <fstream>
#include <map>
using namespace std;

int	first_txt_num;
int	last_txt_num;


string::size_type	get_first_number(string str)
{
	string numbers[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	string::size_type pos, new_pos;

	pos = string::npos;

	for (int i = 0; i < 9; i++)
	{
		new_pos = str.find(numbers[i]);
		if (new_pos < pos)
		{
			pos = new_pos;
			first_txt_num = i + 1;
		}
	}
	return (pos);
}

string::size_type	get_last_number(string str)
{
	string numbers[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	string::size_type pos, new_pos;

	pos = 0;
	for (int i = 0; i < 9; i++)
	{
		new_pos = str.rfind(numbers[i]);
		if (new_pos != string::npos && new_pos > pos)
		{
			pos = new_pos;
			last_txt_num = i + 1;
		}
	}
	return (pos);
}

int main(int argc, char **argv)
{
	string line, line_number;
	int	number = 0;
	string::size_type	first, last, first_txt, last_txt;

	if (argc != 2)
		return (1);
	ifstream file;
	file.open(argv[1]);
	if (file.is_open())
	{
		getline(file, line);
		while (file)
		{
			first = string::npos;
			first = line.find_first_of("0123456789");
			first_txt = get_first_number(line);
			if (first_txt < first)
				line_number = first_txt_num + '0';
			else
				line_number = line[first] ;
			last = 0;
			last = line.find_last_of("0123456789");
			last_txt = get_last_number(line);
			if (last_txt > last || last == string::npos)
				line_number +=  last_txt_num + '0';
			else
				line_number += line[last];
			number += stoi(line_number);
			cout << line << ": " << line_number << "\n";
			getline(file, line);
		}
	}
	cout << number << "\n";
}