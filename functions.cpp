#include <iostream>
#include "functions.h"
#include <chrono>
#include <random>

int random_int(const int& min, const int& max)
{
	static std::default_random_engine engine(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int> dist(min, max);
	return dist(engine);
}

maze generate_maze(const int& width, const int& height)
{
	maze Maze{ width, height };

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++) 
		{
			point Point{ x, y, '#' };

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

void print_maze(const maze& Maze)
{
	int width = Maze.width;
	int newline = 0;
	for (const auto point : Maze.points)
	{
		newline++;
		std::cout << point.c;
		if (newline == width)
		{
			std::cout << std::endl;
			newline = 0;
		}
		
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
			int width = atoi(params[i + 1]);
			_w = true;
		}

		else if (param == "-h")
		{
			int height = atoi(params[i + 1]);
			_h = true;
		}

	}

	if (width < 0 or height < 0)
		return false;
	else if (_w && _h)
		return true;
	return false;
}