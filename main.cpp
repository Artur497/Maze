
#include "functions.h"
#include <iostream>
#include <iomanip>

int start = 0;

int main(int amount, char* params[])
{

	int width, height;
	if (!check_params(amount, params, width, height))
	{
		std::cout << "[ERROR] Invalid arguments. Valid usage: main.exe -w width  -h height" << std::endl;
		exit(1);
	}

	maze Maze = generate_maze(width, height);
	
	backpropagation(Maze);
	print_maze(Maze);

	bool running = true;
	int action = 0;

	std::vector <score> history;

	while (running)
	{

		if (action == 0)
		{
			Maze.solution_size = 0;
			std::cout << std::endl;
			std::cout << "Type number " << std::endl;
			std::cout << "[1] - Breadth First Search" << std::endl;
			std::cout << "[2] - A*" << std::endl;
			std::cout << "[3] - New Labirynth" << std::endl;
			std::cout << "[4] - History" << std::endl;
			std::cout << "\033[?25h" << ">>";
			std::cin >> action;

			if (action != 1 && action != 2 && action != 3 && action != 4)
			{
				action = 0;
			}
			else
			{
				system("cls");
				clear_maze(Maze);
				print_maze(Maze);
			}
		}

		if (action == 1)
		{
			breadth_first_search(Maze);
			set_cursor(Maze.height + 3, 0); 
			std::cout << "Points visited: " << Maze.count << std::endl;
			std::cout << "Solution size: " << Maze.solution_size << std::endl;
			double accuracy = 0.0;
			if (Maze.count != 0) 
			{
				accuracy = (Maze.solution_size * 100.0) / Maze.count;
				score Score{ "Breadth First Search", accuracy};
				history.push_back(Score);
			}
				std::cout << "Accuracy: " << accuracy << "%" << std::endl;
			action = 0;
		}

		else if (action == 2)
		{
			a_star(Maze);
			set_cursor(Maze.height + 3, 0);
			std::cout << "Points visited: " << Maze.count << std::endl;
			std::cout << "Solution size: " << Maze.solution_size << std::endl;
			double accuracy = 0.0;
			if (Maze.count != 0) 
			{
				accuracy = (Maze.solution_size * 100.0) / Maze.count;
				score Score{ "A *", accuracy};
				history.push_back(Score);
			}
				std::cout << "Accuracy: " << accuracy << "%" << std::endl;
			action = 0;
		}

		else if (action == 3)
		{
			char decision;
			std::cout << std::endl;
			std::cout << "Same parameters ( W: " << Maze.width << " H: " << Maze.height << ") " << "[y/n]" << std::endl;
			std::cin >> decision;

			if (decision == 'n')
			{
				std::cout << "Width: ";
				std::cin >> width; 
				std::cout << std::endl;
				std::cout << "Height: ";
				std::cin >> height; 
				std::cout << std::endl;
			}

			Maze = generate_maze(width, height);
			system("cls"); 
			backpropagation(Maze);
			print_maze(Maze);
			action = 0;
		}

		else if (action == 4)
		{
			set_cursor(Maze.height + 3, 0);
			if (history.empty())
				std::cout << "Nothing found " << std::endl;
			for (auto a : history)
			{
				std::cout << '[' << "Algorithm: " << a.algorithm << ", Accuracy: " << a.accuracy << "%" << ']' <<  std::endl;
			}
			action = 0;
		}
	}
	return 0;



	

	
}

