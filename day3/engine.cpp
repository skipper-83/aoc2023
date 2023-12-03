#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool	checkAddNumber(int pos, int end_pos, int i, string *lines)
{
	string check_line;

	if ((pos > 0 && lines[i][pos -1] != '.') || (lines[i][end_pos] && lines[i][end_pos] != '.'))
		return true;
	if (pos == 0)
		pos = 1;
	if (lines[i - 1] != "")
	{
		check_line = lines[i - 1].substr(pos - 1, end_pos - pos + 2);
		if (check_line.find_first_not_of("0123456789.") != string::npos)
			return true;
	}
	if (lines[i + 1] != "")
	{
		check_line = lines[i + 1].substr(pos - 1, end_pos - pos + 2);
		if (check_line.find_first_not_of("0123456789.") != string::npos)
			return true;
	}
	return false;
}

void	checkLine(int i, string *lines, int &sum)
{
	string::size_type 	pos, end_pos;
	int					num;
	
	pos = 0;
	cout << lines[i];
	while ((pos = lines[i].find_first_of("0123456789", pos)) != string::npos)
	{
		end_pos = lines[i].find_first_not_of("0123456789", pos);
		if (end_pos == string::npos) end_pos = lines[i].length();
		num = stoi(lines[i].substr(pos, end_pos - pos));
		cout << " [" << lines[i].substr(pos, end_pos - pos) << "]"; 
		if (checkAddNumber(pos, end_pos, i, lines)) {
			cout << "!";
			sum += num;
		}
		pos = end_pos + 1;
	}
	cout << "\n";
}

int	main(int argc, char **argv)
{
	ifstream			file;
	string				lines[3], buffer[2], line;
	int					sum;

	if (argc != 2)
		return (1);
	file.open(argv[1]);
	if (file.is_open())
	{
		sum = 0;
		while(getline(file, line))
		{
			buffer[0] = lines[1];
			buffer[1] = lines[2];
			lines[2] = line;
			lines[1] = buffer[1];
			lines[0] = buffer[0];
			checkLine(1, lines, sum);
		}
		checkLine(2, lines, sum); // check last line
		cout << "sum: " << sum << "\n";

	}
}