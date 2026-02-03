///@file
//#pragma once

#ifndef FUNKCJE_H
#define FUNKCJE_H
#include <vector>


struct point;

struct maze
{
	int width;
	int height;
	std::vector <point> points;
};
struct point
{
	int x, y;
	char c;
};

void generate_maze(const int& width, const int& height);

int random_int(const int& min, const int& max);

void print_maze(const maze& Maze);

void replace_point(maze& Maze, const point& new_point);





#endif
