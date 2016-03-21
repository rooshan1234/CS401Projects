#include <iostream>
#include <math.h>
#include <thread>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

void pointsAssigned();
void pickRandomCeteriod();

const int K_MEANS = 3;
const int POINTS_SIZE = 16;

struct coordinate2D {
	double x;
	double y;
	double distanceToClosestCeteriod;
	int assignedToCluster;
};

coordinate2D points[100];
coordinate2D clusters[K_MEANS];

void closetsclusterperpoint(int tid, coordinate2D points[], int start, int end, coordinate2D clusters[]) {
	/*std::cout << "Thread: " << tid << " is going calculate the points starting from: " << start
		<< "to: " << end << endl;*/

	for (int i = start; i < end; i++) {
		for (int x = 0; x < K_MEANS; x++) {

			if (points[i].distanceToClosestCeteriod >= sqrt(pow((points[i].x - clusters[x].x), 2) + pow((points[i].y - clusters[x].y), 2))) {
				
				points[i].distanceToClosestCeteriod = sqrt(pow((points[i].x - clusters[x].x), 2) + pow((points[i].y - clusters[x].y), 2));
				points[i].assignedToCluster = x;
			}

		}
	}
}



int main() {
	
	pointsAssigned();

	std::thread t[K_MEANS];

	//divide the array into the number of threads working on the array
	int divisions = (POINTS_SIZE - 1) / K_MEANS;


	/* initialize random seed: */
	srand((int)time(NULL));

	int tempRandomPoint;

	/*for (int i = 0; i < K_MEANS; i++) {
		tempRandomPoint = rand() % (POINTS_SIZE - 1);

		cout << "temprandompoint" << tempRandomPoint << endl;

		//assign random cluster values
		clusters[i].x = points[tempRandomPoint].x;
		clusters[i].y = points[tempRandomPoint].y;
	}*/

	pickRandomCeteriod();

	//check random point assigning
	for (int i = 0; i < K_MEANS; i++) {
		cout << "x " << clusters[i].x << "y " << clusters[i].y << endl;
	}

	for (int i = 0; i < K_MEANS; i++) {
		//cout << i << "ith chunk: " << "from " << (i*divisions) << " to: " << ((i + 1)*divisions) << endl;
		//create cluster number of threads
		t[i] = std::thread(closetsclusterperpoint,i, points, i*divisions, (i+1)*divisions, clusters); 
	}

	//join all the threads after they finish running
	for (int i = 0; i < K_MEANS; i++) {
		t[i].join();
	}

	for (int i = 0; i < POINTS_SIZE; i++) {
		cout << "point: " << "(" << points[i].x << " ," << points[i].y << ")" << ": " <<  points[i].assignedToCluster << endl;
	}
}
void pickRandomCeteriod() {
	//picks random ceteriod from the given points;
	//this will be the number of clusters

	//first cluster
	clusters[0].x = points[0].x;
	clusters[0].y = points[0].y;

	//second cluster
	clusters[1].x = points[7].x;
	clusters[1].y = points[7].y;

	clusters[2].x = points[13].x;
	clusters[2].y = points[13].y;


}
void pointsAssigned() {
	
	for (int i = 0; i < POINTS_SIZE; i++) {
		points[i].distanceToClosestCeteriod = 10000;
	}

	//left cluster
	points[0].x = -1;
	points[0].y = 2;

	points[1].x = -2;
	points[1].y = 1;

	points[2].x = -3;
	points[2].y = 2;

	points[3].x = -2;
	points[3].y = 3;

	points[4].x = -1;
	points[4].y = 3;

	//right cluster
	points[5].x = 3;
	points[5].y = 2;

	points[6].x = 2;
	points[6].y = 1;

	points[7].x = 3;
	points[7].y = 2;

	points[8].x = 2;
	points[8].y = 3;

	points[9].x = 3;
	points[9].y = 3;

	//top cluster
	points[10].x = 3;
	points[10].y = 307;

	points[11].x = 2;
	points[11].y = 306;

	points[12].x = 3;
	points[12].y = 309;

	points[13].x = 2;
	points[13].y = 308;

	points[14].x = 3;
	points[14].y = 300;
}