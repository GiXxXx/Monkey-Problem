#include <iostream>
#include <list>
#include <string>
#include <stdlib.h>

using namespace std;

int getDigitSum(int);
int getLongestPath(int, int, list<string>);

int main() {
	int x, y;
	string xCoordinate, yCoordinate;
	list<string> visitedCell;

	getline(cin, xCoordinate, ' ');
	getline(cin, yCoordinate, '\n');

	x = stoi(xCoordinate);                                                                         //read value of x-coordinates from console
	y = stoi(yCoordinate);                                                                         //read value of y-coordinates from console

	cout << "longest distance is: " << getLongestPath(x, y, visitedCell) << '\n';                  //run method getLogestPath and print out the longest distance starting from (x,y)

	return 0;
}

int getLongestPath(int x, int y, list<string> visitedCell) {                                       //method that takes in starting location (x,y) and a list of already visited cells, return the longest possible travel distance
	int dist = 0;                                                                                  //variable dist, store the distance traveled from initial location to another location
	int max = 0;                                                                                   //variable max, store the max distance traveled from initial location to another location
	int xCopy = x;                                                                                 //a copy of the initial x-coordination, for reset purpose
	int yCopy = y;                                                                                 //a copy of the initial y-coordination, for reset purpose
	int cellValue = 0;                                                                             //variable cellValue, store the (sum of digits of x + sum of digits of y) for location (x,y)
	bool isVisited = false;                                                                        //boolean variable to check if the cell has already been visited
	string currentCoordinates = to_string(x) + ' ' + to_string(y);                                 //store current cell's coordinates using string in the format of "x y"
	string coordinatesToClear;                                                                     //store cell's coordinates to reset their visit status
	list<string>::iterator positionToClear;                                                        //iterator for retrieving the coordinates of cells that need status reset

	visitedCell.push_front(currentCoordinates);

	for (int edge = 0; edge < 4; edge++) {                                                         //each cell will have four edges going out
		x = xCopy;
		y = yCopy;

		switch (edge) {
		case(0) :
			x += 1;
			break;
		case(1) :
			x -= 1;
			break;
		case(2) :
			y += 1;
			break;
		case(3) :
			y -= 1;
			break;
		}

		cellValue = getDigitSum(x) + getDigitSum(y);                                              

		if (cellValue <= 20) {                                                                     //cells with cellValue greater than 20(高于3速度就慢到发指了，20肯定跑不出来..) is not reachable
			currentCoordinates = to_string(x) + ' ' + to_string(y);                                 
			isVisited = (find(visitedCell.begin(), visitedCell.end(), currentCoordinates) != visitedCell.end());
			 
			if (!isVisited) {                                                                      //no repeat visit
				dist = 1 + getLongestPath(x, y, visitedCell);                                      //distance to a cell = 1 + distance to the adjacent cell

				if (dist > max) {
					max = dist;
				}
			}
		}
	}

	coordinatesToClear = to_string(xCopy) + ' ' + to_string(yCopy);                                
	positionToClear = find(visitedCell.begin(), visitedCell.end(), coordinatesToClear);
	visitedCell.erase(positionToClear);                                                            //reset visit status
	
	cout << dist << '\n';                                         

	return max;
}

int getDigitSum(int n) {                                                                           //method for calculating the cell value base on absolute value of digits
	int sum = 0;
	n = abs(n);

	while (n != 0) {
		sum += n % 10;
		n /= 10;
	}

	return sum;
}