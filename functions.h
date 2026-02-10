///@file
//#pragma once

#ifndef FUNKCJE_H
#define FUNKCJE_H

#include <vector>


struct point
{
	int x, y;
	char c;
	bool wall = false;
};


struct maze
{
	int width;
	int height;
	std::vector <point> points;
	point start;
	point end;

};




maze generate_maze(const int& width, const int& height);

int random_int(const int& min, const int& max);

void print_maze(const maze& Maze);

void replace_point(maze& Maze, const point& new_point);

bool check_params(int& amount, char* params[], int& width, int& height);

point random_point(maze& Maze, const char& c);

void backpropagation(maze& Maze);

void neighbours(maze& Maze, point& given, std::vector <point>& Neighbours);

bool check_neighbour(const std::vector <point>& Neighbours);

void set_cursor(int height, int  length);

void animation(const point& Point);

void list_points(const maze& Maze);

void b_neighbours(maze& Maze, point& given, std::vector <point>& Neighbours);

void breadth_first_search(maze& Maze);

double distance(point& first, point& second);


#endif
