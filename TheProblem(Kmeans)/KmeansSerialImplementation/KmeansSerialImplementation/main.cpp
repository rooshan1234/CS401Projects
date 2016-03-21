#include <iostream>
#include <math.h>

using namespace std;

void pickRandomCeteriod();
void pointsAssigned();

const int K_MEANS = 3;
const int POINTS_SIZE = 16;

struct coordinate2D{
	double x;
	double y;
	double distanceToClosestCeteriod;
	int assignedToCluster;
};
struct centeriod2D {
	coordinate2D clusterPoints[100];
};
coordinate2D points[100];
centeriod2D cluster[K_MEANS];

int main() {
	
	pointsAssigned();
	pickRandomCeteriod();
	double distance;

	//first step is to assign the closest cluster to each point
	for (int x = 0; x < POINTS_SIZE; x++) {
		for (int i = 0; i < K_MEANS; i++) {
			
			distance = sqrt(pow((points[x].x - cluster[i].clusterPoints[0].x), 2) + pow((points[x].y - cluster[i].clusterPoints[0].y), 2));
			
			if (distance < points[x].distanceToClosestCeteriod) {
				points[x].distanceToClosestCeteriod = distance;
			}
		}
	}

	//first step is to assign the closest cluster to each point
	for (int x = 0; x < POINTS_SIZE; x++) {
		for (int i = 0; i < K_MEANS; i++) {

			distance = sqrt(pow((points[x].x - cluster[i].clusterPoints[0].x), 2) + pow((points[x].y - cluster[i].clusterPoints[0].y), 2));

			if (distance <= points[x].distanceToClosestCeteriod) {
				cluster[i].clusterPoints[x + 1].x = points[x].x;
				cluster[i].clusterPoints[x + 1].y = points[x].y;
				points[x].distanceToClosestCeteriod = distance;
			}
		}
	}
	/*for (int i = 0; i < 2; i++) {
		for (int x = 0; x < 10; x++) {
			//calcualte euclidean distance from each point to a randomly assigned cluster
			distance = sqrt (pow((points[x].x - cluster[i].clusterPoints[0].x),2) + pow((points[x].y - cluster[i].clusterPoints[0].y),2));
			
			//chose the smallest cluster for given point
			if (distance < points[x].distanceToClosestCeteriod) {
				
				//inital point is the chosen random value
				cluster[i].clusterPoints[x + 1].x = points[x].x;
				cluster[i].clusterPoints[x + 1].y = points[x].y;

				points[x].distanceToClosestCeteriod = distance;

				points[x].assignedToCluster = i;
			}
		}
	}*/

	double sumx = 0;
	double sumy = 0;

	double newCenteriordX = 0;
	double newCenteriordY = 0;

	double clusterSize = 0;

	//calculate the average of each cluster
	for (int i = 0; i < K_MEANS; i++) {
		for (int x = 1; x < POINTS_SIZE; x++) {
			sumx += cluster[i].clusterPoints[x].x;
			
			sumy += cluster[i].clusterPoints[x].y;
			if (cluster[i].clusterPoints[x].x != 0 && cluster[i].clusterPoints[x].y != 0) {
				clusterSize++;
			}
		}
		cout << "CLUSTER SIZE: " <<  clusterSize << endl;
		cout << "SUMX: " << sumx << endl;
		cout << "SUMY: " << sumy << endl;

		newCenteriordX = (double) sumx / (double) clusterSize;
		newCenteriordY = (double) sumy / (double) clusterSize;

		cluster[i].clusterPoints[0].x = newCenteriordX;
		cluster[i].clusterPoints[0].y = newCenteriordY;

		clusterSize = 0;
		newCenteriordX = 0;
		newCenteriordY = 0;

		sumx = 0;
		sumy = 0;

	}

	for (int i = 0; i < K_MEANS; i++) {
		for (int x = 0; x < POINTS_SIZE; x++) {
			cout << "cluster number: " << i << " contains coordinates " << "(" <<cluster[i].clusterPoints[x].x << "," << cluster[i].clusterPoints[x].y << ")" << endl;
		}
		cout << endl;
		//cout << "Point: " << i << "assigned to cluster " << points[i].assignedToCluster;
		//cout << endl;
	}

	for (int i = 0; i < K_MEANS; i++) {
		cout << "New Centeroid points for cluster number: " << i << " (" << cluster[i].clusterPoints[0].x << "," << cluster[i].clusterPoints[0].y << ")" << endl;
	}


}
void pickRandomCeteriod() {
	//picks random ceteriod from the given points;
	//this will be the number of clusters
	
	//first cluster
	cluster[0].clusterPoints[0].x = points[0].x;
	cluster[0].clusterPoints[0].y = points[0].y;

	//second cluster
	cluster[1].clusterPoints[0].x = points[7].x;
	cluster[1].clusterPoints[0].y = points[7].y;

	cluster[2].clusterPoints[0].x = points[13].x;
	cluster[2].clusterPoints[0].y = points[13].y;


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