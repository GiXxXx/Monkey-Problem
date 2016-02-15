#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <sstream>

using namespace std;

int getDigitSum(int);
void getShortestPath(int, int, int, int);

int main() {
	int x, y, m, n;
	string xCoordinate, yCoordinate;
	string mCoordinate, nCoordinate;

	getline(cin, xCoordinate, ' ');
	getline(cin, yCoordinate, '\n');
	getline(cin, mCoordinate, ' ');
	getline(cin, nCoordinate, '\n');

	x = stoi(xCoordinate);
	y = stoi(yCoordinate);
	m = stoi(mCoordinate);
	n = stoi(nCoordinate);                                                                             //input coordinates of two monkeys (x,y) and (m,n)

	getShortestPath(x, y, m, n);                                                                       //run method getShortestPath to return the shortest path's coordinates

	return 0;
}

void getShortestPath(int x, int y, int m, int n) {
	vector<string> visitedCell;                                                                        //store all visited cells
	vector<string> parentCell;                                                                         //store the parent cell of the corresponding visited cell
	vector<int> dist;                                                                                  //store the distance of reaching the corresponding visited cell
	vector<string> coordinates;                                                                        //a queue to store coordinates that requires analysis
	string destination = to_string(m) + ' ' + to_string(n);                                            //string storing coordinates of the destination (2nd monkey)
	string adjacentCell;                                                                               //store coordinates of the adjacent cell
	string currentCell;                                                                                //store coordinates of the current cell
	int cellValue = 0;                                                                                 //store the cell value of (x,y), which equals to (sum of digits of x + sum of digits of y)
	int xCopy;                                                                                         //copy of x for reset
	int yCopy;                                                                                         //copy of y for reset
	bool isVisited = false;                                                                            //boolean variable to indicate the visit status of a cell
	unsigned position;                                                                                 //iteration of vectors for retrieving values in vectors

	visitedCell.push_back(to_string(x) + ' ' + to_string(y));
	dist.push_back(0);
	parentCell.push_back("");                                                                          
	coordinates.push_back(to_string(x) + ' ' + to_string(y));                                          //initialize the starting cell's attributes: parentCell, distance and visited cells

	while (!coordinates.empty()) {                                                                     //loop until no more coordinates need to be analysed
		currentCell = coordinates.front();
		coordinates.erase(coordinates.begin());                                                        //retrieve and remove the 1st cell in the vector 

		stringstream stream(currentCell);
		stream >> x;
		stream >> y;

		xCopy = x;
		yCopy = y;

		for (int edge = 0; edge < 4; edge++) {                                                        //there are four possible adjacent cells
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

			if (cellValue <= 20) {                                                                   //cells with cell value greater than 20 is not accessible
				adjacentCell = to_string(x) + ' ' + to_string(y);
				isVisited = (find(visitedCell.begin(), visitedCell.end(), adjacentCell) != visitedCell.end());

				if (!isVisited) {                                                                    //no repeat visitng
					visitedCell.push_back(adjacentCell);                                             //the immediate adjacent cell(distance = 1) is now visited
					position = distance(visitedCell.begin(), find(visitedCell.begin(), visitedCell.end(), currentCell));
					dist.push_back(dist.at(position) + 1);                                           //update cooresponding distance
					parentCell.push_back(currentCell);                                               //update cooresponding parent cell
					coordinates.push_back(adjacentCell);                                             //append the new coordinates(distance = 2) to coordinates for later analysis

					if (adjacentCell == destination) {                                               //once we found a path, it will be the shortest path, stop searching and return the result
						cout << "Shortest Path:" << '\n';
						while (adjacentCell != "") {
							cout << adjacentCell << '\n';
							position = distance(visitedCell.begin(), find(visitedCell.begin(), visitedCell.end(), adjacentCell));
							adjacentCell = parentCell.at(position);
						}                                                                            //print shortest path's coordinates
						cout << "Shortest Distance:" << '\n';
						cout << dist.back() << '\n';                                                 //print the shortest distance
					}
				}
			}
		}
	}

	cout << "They cannot meet each other" << '\n';                                                   //if no path found, the two monkeys cannot meet each other

	return;
}

int getDigitSum(int n) {                                                                             //method for getting cell value
	int sum = 0;
	n = abs(n);

	while (n != 0) {
		sum += n % 10;
		n /= 10;
	}

	return sum;
}