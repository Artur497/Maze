#include <iostream>
#include "functions.h"
#include <chrono>
#include <random>

int random_int(const int& min, const int& max)
{
	std::default_random_engine engine(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int> dist(min, max);
	return dist(engine);
}

void generate_maze(const int& width, const int& height)
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



	point Start = { random_int(0, width) ,random_int(0, height), 'S' };
	point End = { random_int(0, width), random_int(0, height), 'E' };

	replace_point(Maze, Start);
	replace_point(Maze, End);

	
	print_maze(Maze);

}

void replace_point(maze& Maze, const point& new_point)
{
	bool check = false;

	for (auto & Point : Maze.points)
	{
		if (Point.x == new_point.x && Point.y == new_point.y)
		{
			Point.x = new_point.x;
			Point.y = new_point.y;
			Point.c = new_point.c;
			check = true;
		}
	}

	



}

void print_maze(const maze& Maze)
{
	int height = Maze.height;
	int width = Maze.width;

	int newline = 0;
	std::cout << width << std::endl;

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