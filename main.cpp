
#include "functions.h"
#include <iostream>



int main(int amount, char* params[])
{

	int width, height;
	if (!check_params(amount, params, width, height))
	{
		std::cout << "[ERROR] Invalid arguments. Valid usage: main.exe -w width  -h height" << std::endl;
		exit(1);
	}

	maze Maze = generate_maze(width, height);

	
	create_paths(Maze);

	std::cout << "\033[1;31mTo jest czerwony tekst\033[0m" << std::endl;

	
	print_maze(Maze);

		

}

