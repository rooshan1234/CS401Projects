#include <iostream>
#include <math.h>
#include <thread>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include <fstream>
#include <mutex>
#include <string>

using namespace std;

std::mutex mtx;           // mutex for critical section

void pointsAssigned();
void pickRandomCeteriod();

const int K_MEANS = 50;
const int POINTS_SIZE = 5000;

struct coordinate2D {
	double x;
	double y;
	double distanceToClosestCeteriod;
	int assignedToCluster;
};
struct clusterPoints2D {
	vector <coordinate2D> clusterPoints;
	coordinate2D centerOfGravity;
};
coordinate2D points[POINTS_SIZE];
coordinate2D clusters[K_MEANS];

clusterPoints2D history[2][K_MEANS];

clusterPoints2D clusterPoints[K_MEANS];

void closetsclusterperpoint(int tid, coordinate2D points[], int start, int end, coordinate2D clusters[], clusterPoints2D clusterPoints[]) {
	/*std::cout << "Thread: " << tid << " is going calculate the points starting from: " << start
		<< "to: " << end << endl;*/

	for (int i = start; i < end; i++) {
		for (int x = 0; x < K_MEANS; x++) {

			if (points[i].distanceToClosestCeteriod > sqrt(pow((points[i].x - clusters[x].x), 2) + pow((points[i].y - clusters[x].y), 2))) {
				
				points[i].distanceToClosestCeteriod = sqrt(pow((points[i].x - clusters[x].x), 2) + pow((points[i].y - clusters[x].y), 2));
				points[i].assignedToCluster = x;

			}
			else if (points[i].distanceToClosestCeteriod == sqrt(pow((points[i].x - clusters[x].x), 2) + pow((points[i].y - clusters[x].y), 2))) {
				//stay in the same cluster
				points[i].assignedToCluster = points[i].assignedToCluster;
			}
		}
		mtx.lock();
		/*START CRITICAL SECTION*/
			clusterPoints[points[i].assignedToCluster].clusterPoints.push_back(points[i]);
		/*END CRITICAL SECTION*/
		mtx.unlock();
	}
}

void calculateCenterOfGravity(int tid, clusterPoints2D clusterPoints[], int clusterNumber) {
	
	for (unsigned int x = 0; x < clusterPoints[clusterNumber].clusterPoints.size(); x++) {
		clusterPoints[clusterNumber].centerOfGravity.x += clusterPoints[clusterNumber].clusterPoints.at(x).x;
		clusterPoints[clusterNumber].centerOfGravity.y += clusterPoints[clusterNumber].clusterPoints.at(x).y;
	}

	clusterPoints[clusterNumber].centerOfGravity.x = clusterPoints[clusterNumber].centerOfGravity.x / clusterPoints[clusterNumber].clusterPoints.size();
	clusterPoints[clusterNumber].centerOfGravity.y = clusterPoints[clusterNumber].centerOfGravity.y / clusterPoints[clusterNumber].clusterPoints.size();
}


int main() {
	
	pointsAssigned();

	/* initialize random seed: */
	srand((int)time(NULL));

	int tempRandomPoint[2];

	tempRandomPoint[0] = 0;

	tempRandomPoint[1] = rand() % (POINTS_SIZE - 1);
	
	
	for (int i = 0; i < K_MEANS; i++) {

		//problem: temp point sometimes regenerates the same number
		//tempRandomPoint[0] = tempRandomPoint[1];

		tempRandomPoint[1] = rand() % (POINTS_SIZE - 1);

		/*while ((tempRandomPoint[1] - 20) < tempRandomPoint[1] < (tempRandomPoint[1] + 20)) {
			
			tempRandomPoint[1] = rand() % (POINTS_SIZE - 1);
		}*/
		//tempRandomPoint += tempRandomPoint % POINTS_SIZE;

		cout << "temprandompoint" << tempRandomPoint[1] << endl;

		//assign random cluster values
		clusters[i].x = points[tempRandomPoint[1]].x;
		clusters[i].y = points[tempRandomPoint[1]].y;
	}

	//pickRandomCeteriod();

	//check random point assigning
	for (int i = 0; i < K_MEANS; i++) {
		//cout << "x " << clusters[i].x << "y " << clusters[i].y << endl;
	}



	/*THREADING*/
	
	std::thread t[K_MEANS];

	//divide the array into the number of threads working on the array
	int divisions = (POINTS_SIZE) / K_MEANS;

	for (int i = 0; i < K_MEANS; i++) {
		//cout << "i: " << i*divisions << " ";
		//cout << "i+1: " << ((i + 1)*divisions)-1 << endl;
	}

	/*for (int i = 0; i < K_MEANS; i++) {
		for (int x = 0; x < history[1][i].clusterPoints.size(); x++) {
			history[0][i].clusterPoints.at(x).assignedToCluster = 0;
			history[1][i].clusterPoints.at(x).assignedToCluster = 0;
		}
	}*/

	unsigned int andBit;

	int counter = 0;

	clock_t tStart = clock();
	do{
	
		andBit = 1;
		for (int i = 0; i < K_MEANS; i++) {
			//cout << i << "ith chunk: " << "from " << (i*divisions) << " to: " << ((i + 1)*divisions) << endl;
			//create cluster number of threads
			t[i] = std::thread(closetsclusterperpoint, i, points, i*divisions, ((i + 1)*divisions) - 1, clusters, clusterPoints);
			//cout << "RUNNING THREAD: " << i << endl;
		}

		//join all the threads after they finish running
		for (int i = 0; i < K_MEANS; i++) {
			//cout << "joining THREAD: " << i << endl;
			t[i].join();
		}

		for (int i = 0; i < K_MEANS; i++) {
			t[i] = std::thread(calculateCenterOfGravity, i, clusterPoints, i);
		}

		//join all the threads after they finish running
		for (int i = 0; i < K_MEANS; i++) {
			t[i].join();
		}
		
		//RECALIBRATING
		
		for (int i = 0; i < K_MEANS; i++) {
			//cout << "Recalculated centers for cluster: " << i << " ( " << clusterPoints[i].centerOfGravity.x << ", " << clusterPoints[i].centerOfGravity.y << ")" << endl;
			clusters[i].x = clusterPoints[i].centerOfGravity.x;
			clusters[i].y = clusterPoints[i].centerOfGravity.y;

			//history[0] = history[1]
			history[0][i].clusterPoints = history[1][i].clusterPoints;

			//history[1] = clusterPoints (Actual data)
			history[1][i].clusterPoints = clusterPoints[i].clusterPoints;

			/*for (unsigned int x = 0; x < clusterPoints[i].clusterPoints.size(); x++) {
				cout << "Point: (" << clusterPoints[i].clusterPoints.at(x).x << " ," << clusterPoints[i].clusterPoints.at(x).y << ")" << "belongs to cluster: " << i << endl;
			}*/

			//clear current points assigned to clusters
			clusterPoints[i].clusterPoints.clear();

			andBit &= history[0][i].clusterPoints.size() == history[1][i].clusterPoints.size();
		}


		//RECALIBRATING
		for (int i = 0; i < POINTS_SIZE; i++) {
			points[i].distanceToClosestCeteriod = (double)10000;
		}

		/*for (int i = 0; i < POINTS_SIZE-1; i++) {
			cout << "point: " << "(" << points[i].x << " ," << points[i].y << ")" << ": " <<  points[i].assignedToCluster << endl;
		}*/

		counter++;

	} while (andBit!=1);
	
	printf("Time taken: %fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

	ofstream outputfile;
	outputfile.open("plotcuster0.csv");

	for (int i = 0; i < K_MEANS; i++) {
		for (unsigned int x = 0; x < history[1][i].clusterPoints.size(); x++) {
			outputfile << history[1][i].clusterPoints.at(x).x << ", " << history[1][i].clusterPoints.at(x).y << endl;
			//cout << "Point: (" << history[1][i].clusterPoints.at(x).x << " ," << history[1][i].clusterPoints.at(x).y << ")";
		}
		outputfile << endl;
		outputfile.close();
		string filename = "plotcuster" + to_string(i+1) + ".csv";
		outputfile.open(filename);
	}



	/*for (int i = 0; i < K_MEANS; i++) {
		cout << "Recalculated centers for cluster: " << i << " ( " << clusterPoints[i].centerOfGravity.x << ", " << clusterPoints[i].centerOfGravity.y << ")" << endl;
	}*/
	//cout << "COUNT " << counter;

	



}
void pickRandomCeteriod() {
	//picks random ceteriod from the given points;
	//this will be the number of clusters

	//11, 14, 2

	//first cluster
	clusters[0].x = points[11].x;
	clusters[0].y = points[11].y;

	//second cluster
	clusters[1].x = points[14].x; //3
	clusters[1].y = points[14].y; //2

	clusters[2].x = points[2].x; //2
	clusters[2].y = points[2].y; //1


}
void pointsAssigned() {
	
	for (int i = 0; i < POINTS_SIZE; i++) {
		points[i].distanceToClosestCeteriod = (double)10000;
	}

	ifstream pointsfile("points.txt");
	string garbage;

	for (int i = 0; i < POINTS_SIZE; i++) {
		pointsfile >> points[i].x;
		pointsfile >> points[i].y;
	}

	/*
	for (int i = 0; i < POINTS_SIZE; i++) {
		cout << points[i].x << points[i].y << endl;

	}*/

	pointsfile.close();
	/*
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
	points[7].y = 1;

	points[8].x = 2;
	points[8].y = 3;

	points[9].x = 3;
	points[9].y = 3;

	//top cluster
	points[10].x = 0;
	points[10].y = 10;

	points[11].x = 2;
	points[11].y = 11;

	points[12].x = 3;
	points[12].y = 12;

	points[13].x = 1;
	points[13].y = 13;

	points[14].x = 0;
	points[14].y = 14;*/
}