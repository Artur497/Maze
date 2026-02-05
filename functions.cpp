#include <iostream>
#include "functions.h"
#include <chrono>
#include <random>
#include <vector>

#include <chrono> 
#include <thread> 
#include <stdlib.h>

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
			point Point{ x, y , (char)254 };

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

void create_paths(maze& Maze)
{
	std::vector <point> stack;

	point start = random_point(Maze, ' ');
	stack.push_back(start);


	std::vector <point> Neighbours;


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
			stack.pop_back();
		start.c = 'S';
		replace_point(Maze, start);

	}
	point end = random_point(Maze, 'E');
	end.c = 'E';
	replace_point(Maze, end);


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

void neighbours(maze& Maze, point & given, std::vector <point> & Neighbours)
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


