#include <iostream>
#include "functions.h"
#include <chrono>
#include <random>
#include <vector>
#include <chrono>
#include <thread>
#include <algorithm>
#include <cmath>
#include <queue>


void set_cursor(int height,int  length)
{
	std::cout << "\033[" << height + 1 << ";" << length + 1 << "H";
}

void animation(const point & Point)
{
	
	if (Point.c != char(254))
	{
		set_cursor(Point.x, Point.y * 2);
		std::cout << "\033[?25l" << Point.c << " " << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(40));
	}

	else if (Point.c == 'S' || Point.c == 'E')
	{
		set_cursor(Point.x, Point.y * 2);
		
		std::cout << "\033[?25l" << Point.c << " " << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(40));
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

	

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++) 
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

	for (auto & Point : Maze.points)
	{
		if (Point.x == new_point.x && Point.y == new_point.y)
		{
			Point.x = new_point.x;
			Point.y = new_point.y;
			Point.c = new_point.c;
		}
	}
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

	print_maze(Maze);

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

			animation(remove_wall);
			animation(current_point);
			animation(chosen_neighbour);

			stack.push_back(chosen_neighbour);


		}

		else
			stack.pop_back();
			start.c = 'S';
			replace_point(Maze, start);
			animation(start);
			Maze.start = start;


	}
	point end = random_point(Maze, 'E');
	replace_point(Maze, end);
	animation(end);
	set_cursor(Maze.height + 1, 1);
	Maze.end = end;


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

	for (auto Point : Maze.points)
	{
		if (given.x + 2 == Point.x && given.y == Point.y && Point.c == (char)254 && Point.wall == false)
		{
			point neighbour{ Point.x, Point.y, (char)254 }; // right
			Neighbours.push_back(neighbour);

		}

		if (given.x - 2 == Point.x && given.y == Point.y && Point.c == (char)254 && Point.wall == false)
		{
			point neighbour{ Point.x, Point.y, (char)254 }; // left
			Neighbours.push_back(neighbour);


		}

		if (given.x == Point.x && given.y + 2 == Point.y && Point.c == (char)254 && Point.wall == false)
		{
			point neighbour{ Point.x, Point.y, (char)254 }; // up
			Neighbours.push_back(neighbour);


		}

		if (given.x == Point.x && given.y - 2 == Point.y && Point.c == (char)254 && Point.wall == false)
		{
			point neighbour{ Point.x, Point.y, (char)254 }; // down
			Neighbours.push_back(neighbour);


		}

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



void breadth_first_search(maze& Maze)
{
	std::queue <point> queue;
	std::vector <point> neighbours;
	point current_point;

	queue.push(Maze.start);

	set_cursor(Maze.start.y, Maze.start.x);
	while (!queue.empty())
	{
		current_point = queue.front();
		replace_point(Maze, current_point);
		animation(current_point);

		if (distance(current_point, Maze.end) <= 1)
			break;
		
		
		neighbours.clear();
		b_neighbours(Maze, current_point, neighbours);
	
		queue.pop();
		for (auto a : neighbours)
		{
			
			a.c = '*';
			queue.push(a);
			replace_point(Maze, a);

		}

		

	}

	set_cursor(Maze.height, Maze.width);

}




double distance(point& first, point& second)
{
	int x = (second.x - first.x);
	int y = (second.y - first.y);

	return sqrt(x * x + y * y);
}


void b_neighbours(maze& Maze, point& given, std::vector <point>& Neighbours)
{

	for (auto& Point : Maze.points)
	{


		if (given.x + 1 == Point.x && given.y == Point.y && Point.c == ' ')
		{
			point neighbour{ Point.x, Point.y, '*' }; // right
			Neighbours.push_back(neighbour);

		}

		else if (given.x - 1 == Point.x && given.y == Point.y && Point.c == ' ')
		{
			point neighbour{ Point.x, Point.y, '*' }; // left
			Neighbours.push_back(neighbour);


		}

		else if (given.x == Point.x && given.y + 1 == Point.y && Point.c == ' ')
		{
			point neighbour{ Point.x, Point.y, '*' }; // up
			Neighbours.push_back(neighbour);


		}

		else if (given.x == Point.x && given.y - 1 == Point.y && Point.c == ' ')
		{
			point neighbour{ Point.x, Point.y, '*' }; // down
			Neighbours.push_back(neighbour);


		}
	}

	

}





