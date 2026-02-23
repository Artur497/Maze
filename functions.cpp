#include <iostream>
#include "functions.h"
#include <chrono>
#include <random>
#include <vector>
#include <chrono>
#include <thread>
#include <cmath>
#include <queue>
#include <algorithm>

extern int start;
void set_cursor(int height, int length) {
	std::cout << "\033[" << height + start + 1 << ";" << length + 1 << "H";
}


void animation(const point & Point)
{

	if (Point.c == 'S' || Point.c == 'E')
	{
		set_cursor(Point.y, Point.x * 2);
		std::cout << "\033[31m" << "\033[?25l" << Point.c << " " << "\033[0m" << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(4));
	}

	else if (Point.c != char(254))
	{
		set_cursor(Point.y, Point.x * 2);
		std::cout << "\033[?25l" << Point.c << " " << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(4));
	}

	
}


int random_int(const int& min, const int& max)
{
	static std::default_random_engine engine(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int> dist(min, max);
	return dist(engine);
}

point random_point(maze & Maze, const char & c)
{

	point random_point{ random_int(1, Maze.width - 1), random_int(1, Maze.height - 1), c };
	replace_point(Maze, random_point);
	return random_point;
	
}


maze generate_maze(const int& width, const int& height)
{
	maze Maze{ width, height };
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			point Point{ x, y ,(char)254};

			if (Point.x == 0 || Point.y == 0 || Point.x == Maze.width - 1 || Point.y == Maze.height - 1)
				Point.wall = true;

			Maze.points.push_back(Point);
		}
	}

	return Maze;
}

void replace_point(maze& Maze, const point& new_point)
{
	int index = new_point.y * Maze.width + new_point.x;
	Maze.points[index].c = new_point.c;
}


void print_maze(const maze & Maze)
{
	int newline = 0;
	for (const auto point : Maze.points)
	{
		if (newline == Maze.width)
		{
			std::cout << std::endl;
			newline = 0;
		}
		switch (point.c)
		{
			case char(254):
				std::cout <<  point.c << " ";
				break;
			case ' ':
				std::cout << point.c << " ";
				break;
			case '*':
				std::cout << point.c << " ";
				break;
			default:
				std::cout << "\033[31m" <<  point.c << "\033[0m" << " ";
		}
		newline++;
	}
}


bool check_params(int& amount, char* params[], int& width, int& height)
{

	bool _w = false;
	bool _h = false;

	for (int i = 0; i < amount - 1; i++)
	{
		std::string param = std::string(params[i]);

		if (param == "-w")
		{
			width = atoi(params[i + 1]);
			_w = true;
		}

		else if (param == "-h")
		{
			height = atoi(params[i + 1]);
			_h = true;
		}

	}

	if (width < 0 or height < 0)
		return false;
	else if (_w && _h)
		return true;
	return false;
}


//*** BACKPROPAGATION ALGORITHM ***


void backpropagation(maze& Maze)
{
	std::vector <point> stack;
	
	std::vector <point> Neighbours;

	point start = random_point(Maze, ' ');
	stack.push_back(start);
	while (!stack.empty())
	{


		Neighbours.clear();
		point current_point = stack.back();


		neighbours(Maze, current_point, Neighbours);
		bool has_neighbours = false;
		if (!Neighbours.empty())
			has_neighbours = check_neighbour(Neighbours);
		if (check_neighbour(Neighbours))
		{
			int i = random_int(0, Neighbours.size() - 1);

			point chosen_neighbour = Neighbours[i];

			int dx = current_point.x - chosen_neighbour.x;
			int dy = current_point.y - chosen_neighbour.y;

			point remove_wall;

			remove_wall.x = (current_point.x + chosen_neighbour.x) / 2;
			remove_wall.y = (current_point.y + chosen_neighbour.y) / 2;
			remove_wall.c = ' ';
			replace_point(Maze, remove_wall);
			current_point.c = ' ';
			chosen_neighbour.c = ' ';
			replace_point(Maze, chosen_neighbour);

			stack.push_back(chosen_neighbour);
		}
		else
		{
			stack.pop_back();
		}
		start.c = 'S';
		replace_point(Maze, start);
		Maze.start = start;


	}
	bool found = false;

	while(!found)
	{
		point end = random_point(Maze, ' ');

		Neighbours.clear();
		b_neighbours(Maze, end, Neighbours, 0);

		for (auto n : Neighbours)
		{
			if (n.c == ' ')
			{
				end.c = 'E';
				replace_point(Maze, end);
				Maze.end = end;
				found = true;
			}
		}
	}
	


}

bool check_neighbour(const std::vector <point>& Neighbours)
{
	bool has_neighbours = false;
	for (auto Neighbour : Neighbours)
	{
		if (Neighbour.c == (char)254)
			has_neighbours = true;
	}
	return has_neighbours;
}

void neighbours(maze& Maze, point& given, std::vector <point>& Neighbours)
{

	int index = given.y * Maze.width + given.x;

	if (given.y > 1)
	{
		point up = Maze.points[index - (Maze.width * 2)];
		if (up.c == (char)254 && up.wall == false)
			Neighbours.push_back(up);
	}

	if (given.y < Maze.height - 2)
	{
		point down = Maze.points[index + (Maze.width * 2)];
		if (down.c == (char)254 && down.wall == false)
			Neighbours.push_back(down);
	}

	if (given.x > 1)
	{
		point left = Maze.points[index - 2];
		if (left.c == (char)254 && left.wall == false)
			Neighbours.push_back(left);
	}

	if (given.x < Maze.width - 2)
	{
		point right = Maze.points[index + 2];
		if (right.c == (char)254 && right.wall == false)
			Neighbours.push_back(right);
	}

}

////


void list_points(const maze& Maze)
{
	std::cout << "[";
	for (auto a : Maze.points)
	{
		std::cout << a.c << ", ";
	}
	std::cout << ']' << std::endl;
}

//*** BREADTH FIRST SEARCH ALGORITHM ***


void breadth_first_search(maze& Maze)
{
	std::queue <point> queue;
	std::vector <point> neighbours;


	point current_point;
	Maze.start.step = 0;
	Maze.count = 0;
	queue.push(Maze.start);
	set_cursor(Maze.start.y, Maze.start.x);
	while (!queue.empty())
	{
		current_point = queue.front();
		queue.pop();
		Maze.count++;
		int d = current_point.step;
		replace_point(Maze, current_point);
		animation(current_point);

		if (distance(current_point, Maze.end) <= 1)
		{
			Maze.end.step = d + 1;
			Maze.count++;
			break;
		}
		
		
		neighbours.clear();
		b_neighbours(Maze, current_point, neighbours, 0);
	
		for (auto a : neighbours)
		{
			a.c = '*';
			a.step = d + 1;
			int index = a.y * Maze.width + a.x;
			Maze.points[index].step = a.step;
			queue.push(a);
			replace_point(Maze, a);
		}
	}
	
	set_cursor(Maze.height, Maze.width);
	backtracing(Maze);

	

}

void backtracing(maze & Maze)
{
	point current_point = Maze.end;
	std::vector<point> solution;
	solution.push_back(current_point); 

	std::vector<point> Neighbours;
	while (current_point.step != 0) 
	{
		Neighbours.clear();
		b_neighbours(Maze, current_point, Neighbours, 1);
		

		bool moved = false;
		for (auto n : Neighbours) 
		{
			if (n.step == current_point.step - 1)
			{
				current_point = n;
				solution.push_back(n);
				moved = true;
				break; 
			}
		}
	
		if (!moved) {
			std::cout << "[Error] Path is not continuos" << std::endl;
			break;
		}
	}

	std::reverse(solution.begin(), solution.end());

	for (auto a : solution)
	{
		if (a.c != 'E')
			set_cursor(a.y, a.x * 2);
			std::cout << "\033[31m" << "\033[?25l" << "*" << " " << "\033[0m" << std::flush;
			std::this_thread::sleep_for(std::chrono::milliseconds(4));
	}
	
	Maze.solution_size = solution.size();
	
}




double distance(const point& first, const point& second)
{
	int x = (second.x - first.x);
	int y = (second.y - first.y);

	return sqrt(x * x + y * y);
}


void b_neighbours(const maze& Maze, point& given, std::vector <point>& Neighbours, bool type)
{
	char target = ' ';
	

	int index = given.y * Maze.width + given.x;

	if (given.y > 0)
	{
		point up = Maze.points[index - Maze.width];
		if ((type == 0 && up.c == target) || (type == 1 && !up.wall))
			Neighbours.push_back(up);
	}

	if (given.y < Maze.height - 1)
	{
		point down = Maze.points[index + Maze.width];
		if ((type == 0 && down.c == target) || (type == 1 && !down.wall))
			Neighbours.push_back(down);
	}

	if (given.x > 0)
	{
		point left = Maze.points[index - 1];
		if ((type == 0 && left.c == target) || (type == 1 && !left.wall))
			Neighbours.push_back(left);
	}

	if (given.x < Maze.width - 1)
	{
		point right = Maze.points[index + 1];
		if ((type == 0 && right.c == target) || (type == 1 && !right.wall))
			Neighbours.push_back(right);
	}
	
}

void clear_maze(maze& Maze)
{
	for (auto & p : Maze.points)
	{
		if (p.c == '*')
		{
			p.c = ' ';
		}
	}
}

//*** A * ALGORITHM ***


void a_star(maze& Maze)
{
	std::vector<point> Neighbours;
	auto comp = [&Maze](const point& first, const point& second) {return cost(first, Maze) > cost(second, Maze);  };

	std::priority_queue <point, std::vector <point>, decltype(comp)> queue(comp);

	point current_point = Maze.start;
	queue.push(current_point);

	Maze.start.step = 0;
	Maze.count = 0;
	
	while (!queue.empty())
	{
		current_point = queue.top();
		queue.pop();
		Maze.count++;
		Neighbours.clear();

		if (distance(current_point, Maze.end) <= 1)
		{
			Maze.points[Maze.end.y * Maze.width + Maze.end.x].step = current_point.step + 1;
			Maze.end.step = current_point.step + 1;
			Maze.count++;
			break;
		}
		b_neighbours(Maze, current_point, Neighbours, 0);


		for (auto & n : Neighbours)
		{
			n.step = current_point.step + 1;
			n.c = '*';
			Maze.points[n.y * Maze.width + n.x].step = n.step;
			replace_point(Maze, n);
			queue.push(n);
		}
		
		if (current_point.c != 'S' && current_point.c != 'E')
			current_point.c = '*';
		replace_point(Maze, current_point);
		animation(current_point);
	}
	set_cursor(Maze.height, Maze.width);
	backtracing(Maze);

}



int cost(const point& Point, const maze & Maze)
{
	return Point.step + abs(Maze.end.x - Point.x) + abs(Maze.end.y - Point.y);
}




