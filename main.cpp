
#include "functions.h"
#include <iostream>

int main(int amount, char * params[])
{

	int width, height;
	if (!check_params(amount, params, width, height))
	{
		std::cout << "[ERROR] Invalid arguments. Valid usage: main.exe -w width  -h height" << std::endl;
		exit(1);
	}

	maze Maze = generate_maze(width, height);

	point Start = { random_int(0, Maze.width - 1),random_int(0, Maze.height - 1), 'S' };
	point End = { random_int(0, Maze.width - 1), random_int(0, Maze.height - 1), 'E' };


	replace_point(Maze, Start);
	replace_point(Maze, End);

	print_maze(Maze);

}

