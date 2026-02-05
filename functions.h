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
	bool wall = false;
};


maze generate_maze(const int& width, const int& height);

int random_int(const int& min, const int& max);

void print_maze(const maze& Maze);

void replace_point(maze& Maze, const point& new_point);

bool check_params(int& amount, char* params[], int& width, int& height);

point random_point(maze& Maze, const char& c);

void create_paths(maze& Maze);

void neighbours(maze& Maze, point& given, std::vector <point>& Neighbours);

bool check_neighbour(const std::vector <point>& Neighbours);

#endif
