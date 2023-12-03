#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define LEFT 0
#define RIGHT 1

int	getNumber(string line, int pos, int dir)
{
	int	num_pos, num_end_pos, num;

	num_pos = pos + dir;
	num = 0;
	if (dir == LEFT)
	{
		while (num_pos >= 0 && isdigit(line[num_pos - 1]))
			num_pos--;
	}
	num_end_pos = line.find_first_not_of("0123456789", num_pos);
	if (num_end_pos == string::npos) num_end_pos = line.length();
	num = stoi(line.substr(num_pos, num_end_pos - num_pos));
	return (num);
}

void getTopBottomNo(string line, int pos, int all_nums[6], int i)
{
	if(line != "")
	{
		if(isdigit(line[pos]))
			all_nums[i] = getNumber(line, pos, LEFT);
		else
		{
			if(pos > 0 && isdigit(line[pos - 1]))
				all_nums[i] = getNumber(line, pos - 1, LEFT);
			if(pos < line.length() && isdigit(line[pos + 1]))
				all_nums[i + 1] = getNumber(line, pos, RIGHT);
		}
	}
}

bool	checkProdNumber(int pos, int end_pos, int i, string *lines, int &sum)
{
	string check_line;
	int		all_nums[6] = {-1,-1,-1,-1,-1,-1};
	int		prod_nums[2], prod_counter;
	if (pos > 0 && isdigit(lines[i][pos - 1]))
		all_nums[0] = getNumber(lines[i], pos, LEFT);
	if (lines[i][end_pos] && isdigit(lines[i][end_pos]))
		all_nums[1] = getNumber(lines[i], pos, RIGHT);
	getTopBottomNo(lines[i - 1], pos, all_nums, 2);
	getTopBottomNo(lines[i + 1], pos, all_nums, 4);
	prod_counter = 0;
	for (int i = 0; i < 6; i++)
	{
		if (all_nums[i] >=0)
		{
			cout   << all_nums[i] <<" ";
			if (prod_counter < 2)
				prod_nums[prod_counter] = all_nums[i];
				
			prod_counter++;
		}
	}
	if (prod_counter == 2)
		sum += prod_nums[0] * prod_nums[1];
	return false;
}

void	checkLine(int i, string *lines, int &sum)
{
	string::size_type 	pos, end_pos;
	int					num;
	
	pos = 0;
	cout << lines[i];
	while ((pos = lines[i].find('*', pos)) != string::npos)
	{
		end_pos = pos + 1;
		if (end_pos == string::npos) end_pos = lines[i].length();
		checkProdNumber(pos, end_pos, i, lines, sum);
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