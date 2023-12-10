#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

bool	from_left(char entry, char dir)
{
	switch (dir)
	{
		case 'N':
			if (entry == 'E')
				return true ;
			break ;
		case 'S' :
			if (entry == 'W')
				return true;
			break ;
		case 'W' :
			if (entry == 'N')
				return true;
			break ;
		case 'E':
			if (entry == 'S')
				return true;
			break ;

	}
	return false;
}

bool	from_right(char entry, char dir)
{
	return (!from_left(entry, dir));
}

char	turn_type(char src, char dst)
{
	switch(src)
	{
		case 'N':
			if (dst == 'W')
				return 1;
			break;
		case 'S':
			if (dst == 'E')
				return 1;
			break;
		case 'E':
			if (dst == 'N')
				return 1;
			break;
		case 'W':
			if (dst == 'S')
				return 1;
			break;
	}
	if (src == dst)
		return 0;
	return 2;
}

char	go_left(char dir)
{
	switch(dir)
	{
		case 'N':
			return 'W';
		case 'S' :
			return 'E';
		case 'W':
			return 'S';
		case 'E':
			return 'N';
		default: 
			return 'B';
	}
}

char	go_right(char dir)
{
	switch(dir)
	{
		case 'N':
			return 'E';
		case 'S' :
			return 'W';
		case 'W':
			return 'N';
		case 'E':
			return 'S';
		default: 
			return 'B';
	}
}

char	make_turn(char inp, char entry_dir)
{
	switch (inp)
	{
		case 'F':
			if (entry_dir == 'N')
				return 'E';
			if (entry_dir == 'W')
				return 'S';
			break ;
		case '7':
			if (entry_dir == 'N')
				return 'W';
			if (entry_dir == 'E')
				return 'S';
			break ;
		case 'J':
			if (entry_dir == 'E')
				return 'N';
			if (entry_dir == 'S')
				return 'W';
			break ;
		case 'L':
			if (entry_dir == 'W')
				return 'N';
			if (entry_dir == 'S')
				return 'E';
			break ;
		case '-':
			if (entry_dir == 'E')
				return 'E';
			if (entry_dir == 'W')
				return 'W';
			break ;
		case '|':
			if (entry_dir == 'N')
				return 'N';
			if (entry_dir == 'S')
				return 'S';
			break;
	}
	return 'B';
}

void	change_pos(char inp, int pos[2])
{
	switch (inp)
	{
		case 'N':
			pos[0]--;
			break ;
		case 'S':
			pos[0]++;
			break ;
		case 'E':
			pos[1]++;
			break ;
		case 'W':
			pos[1]--;
			break ;
	}
}

// bool	must_check (char cur_char, char search_dir)
// {
// 	string dirs = "NSEW";

// 	if (dirs.find(cur_char) == string::npos)
// 		return (false);
// 	if (cur_char == search_dir)
// 		return false;
// 	switch (search_dir)
// 	{
// 	case 'N':
// 		if (cur_char == 'S')
// 		return false;
// 	case 'S':
// 		if (cur_char == 'N')
// 			return false;
// 	case 'E':
// 		if (cur_char == 'W')
// 			return false;
// 	case 'W':
// 		if (cur_char == 'E')
// 			return false;
// 	}
// 	return true;
// }

 char	check_step(vector<vector<pair<char, bool> > >&map, char entry_dir, int pos[2], int step, string &route)
{
	char new_dir, ret_dir;

	map[pos[0]][pos[1]].second = true;
	change_pos(entry_dir, pos);
	if (pos[0] < 0 || pos[0] > map.size() - 1)
		return 'B';
	if (pos[1] < 0 || pos[1] > map[pos[0]].size())
		return 'B';
	if (map[pos[0]][pos[1]].second)
		return 'B';
	new_dir = make_turn(map[pos[0]][pos[1]].first, entry_dir);
	if (new_dir == 'B')
		return new_dir;
	map[pos[0]][pos[1]].first = new_dir;
	ret_dir = check_step(map, new_dir, pos, ++step, route);
	if (ret_dir != 'B')
	{
		route = ret_dir + route;
		if (step < 2)
			route = new_dir + route;
	}
	return new_dir;
	
}

string	 check_route(vector<vector<pair<char, bool> > > &map, int start_pos[2])
{
	string	ret = "";
	int		pos[2];

	pos[0] = start_pos[0];
	pos[1] = start_pos[1];
	check_step(map, 'E', pos, 0, ret);
	if (ret != "")
		return ('E' + ret);
	pos[0] = start_pos[0];
	pos[1] = start_pos[1];
	check_step(map, 'W', pos, 0, ret);
	if (ret != "")
		return ('W' + ret);
	pos[0] = start_pos[0];
	pos[1] = start_pos[1];
	cout << "pos: " << map[start_pos[0]][start_pos[1]].first << "\n\n";
	check_step(map, 'N', pos, 0, ret);
	if (ret != "")
		return ('N' + ret);
	pos[0] = start_pos[0];
	pos[1] = start_pos[1];
	check_step(map, 'S', pos, 0, ret);
	if (ret != "")
		return ('S' + ret);
	return "";
}

// char	get_loop_dir(vector<vector<pair<char, bool> > >map, int start_pos[2], string route)
// {
// 	int		search_pos[2];
// 	char	search_dir, cur_char, prev = 'x';
	
// 	cout << "sp" << map[start_pos[0]][start_pos[1]].first << "\n";
// 	for(auto it : route)
// 	{
// 		cout << map[start_pos[0]][start_pos[1]].first << ": ";
// 		change_pos(it, start_pos);
// 		search_pos[0] = start_pos[0];
// 		search_pos[1] = start_pos[1];
// 		search_dir = go_right(it);
// 		while (search_pos[0] > 0 && search_pos[0] < map.size()
// 		&& search_pos[1] > 0 && search_pos[1] < map[search_pos[0]].size())
// 		{
// 			cur_char = map[search_pos[
// 				0]][search_pos[1]].first;
// 			cout << "; - " << it << " to: " << cur_char << " dir: " << search_dir;
// 			if (must_check(cur_char, search_dir))
// 			{
// 				if (from_left(search_dir, cur_char))
// 					cout << "booh";
// 			}
// 			change_pos(search_dir, search_pos);
// 			prev = it;
// 		}
// 		cout << "\n";
// 	}
// }
bool	loop_dir_is_cw(string route)
{
	char turn;
	int lefts = 0, rights = 0;

	for (int i = 1; i < route.size(); i++)
	{
		turn = turn_type(route[i - 1], route[i]);
		if (turn == 1)
			lefts++;
		else if (turn == 2)
			rights++;	
	}
	if (rights > lefts)
		return true;
	return false;
}

int	paint_line(int search_pos[2], vector<vector<pair<char, bool> > >&map, char dir)
{
	string dirs = "NSEWGx";
	int	ret = 0;
	while (search_pos[0] > 0 && search_pos[0] < map.size()
		&& search_pos[1] > 0 && search_pos[1] < map[search_pos[0]].size()
		// && !is_inside(map[search_pos[0]][search_pos[1]].first, dir)
		&& dirs.find(map[search_pos[0]][search_pos[1]].first) == string::npos)
		{
			if (map[search_pos[0]][search_pos[1]].first != 'I')
			{
				map[search_pos[0]][search_pos[1]].first = 'I';
				ret ++;
			}
			change_pos(dir, search_pos);
		}
	return (ret);
}

int	paint_inside(vector<vector<pair<char, bool> > >&map, int start_pos[2], string route)
{
	char (*change_dir)(char dir);
	bool (*is_inside)(char entry, char dir);
	char dir, prev = 'z';
	int	search_pos[2], ret = 0;
	

	if (loop_dir_is_cw(route))
	{
		change_dir = go_right;
		is_inside = from_right;
	}
	else
	{
		change_dir = go_left;
		is_inside = from_left;
	}
	for (auto it: route)
	{
		dir = change_dir(it);
		search_pos[0] = start_pos[0];
		search_pos[1] = start_pos[1];
		change_pos(dir, search_pos);
		ret += paint_line(search_pos, map, dir);
		
		if (prev != 'z')
		{
			// cout << "cur: " << map[start_pos[0]][start_pos[1]].first << "\n";
			cout << "prev " << prev << ":" << change_dir(prev) << " - ";
			search_pos[0] = start_pos[0];
			search_pos[1] = start_pos[1];
			change_pos(change_dir(prev), search_pos);
			ret += paint_line(search_pos, map, change_dir(prev));
		}
		prev = it;
		// map[start_pos[0]][start_pos[1]].first = 'x';
		change_pos(it, start_pos);
	}
	cout << "\n";
	return ret;
}

int main(int argc, char **argv)
{
	ifstream file;
	string line, route;
	vector<string> temp_map;
	vector<vector<pair<char, bool> > >map;
	vector<pair<char, bool> > cur_line;
	int idx = 0, pos, start_pos[2], ret;

	if (argc != 2)
		return (1);
	file.open(argv[1]);
	if (file.is_open())
	{
		while (getline(file, line) && line[0])
		{
			if ((pos = line.find('S')) != string::npos)
			{
				start_pos[0] = idx;
				start_pos[1] = pos;
				line[pos] = 'G';
			}
			temp_map.push_back(line);
			idx++;
		}
		for (auto it : temp_map)
		{
			for (auto c : it)
				cur_line.push_back(make_pair(c, false));
			map.push_back(cur_line);
			cur_line.clear();
			cout << it << "\n";
		}
		cout << temp_map[start_pos[0]][start_pos[1]] << "\n";
		route = check_route(map, start_pos);
		cout << "route: " << route << ", size: " << route.size() << ", farthest dist: " << (route.size() / 2) + route.size() % 2 << "\n";
		for (auto it : map)
		{
			for (auto it2 : it)
				cout << it2.first;
			cout << "\n";
		}
		// get_loop_dir(map, start_pos, route);
		if (loop_dir_is_cw(route))
			cout << "loop direction is cw\n";
		else
			cout << "loop direction is ccw\n";
		ret = paint_inside(map, start_pos, route);
		for (auto it : map)
		{
			for (auto it2 : it)
				cout << it2.first;
			cout << "\n";
		}
		cout << "Empty tiles within loop: " << ret << "\n";
	}
}