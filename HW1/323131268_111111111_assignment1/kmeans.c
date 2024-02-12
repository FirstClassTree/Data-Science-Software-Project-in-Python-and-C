#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculateDistance(double point1[], double point2[], int dimensions){
    double distance = 0;
    int i;
   

    for(i = 0; i < dimensions; i++){
        distance += (point1[i] - point2[i]) * (point1[i] - point2[i]);
    }
    distance = sqrt(distance);
    
    
    return distance;
} 


int main(int argc, char *argv[]) {
    int i,j,t;
    double **clusterMatrix;
    double **pointMatrix;
    double **tempClusters; 
    int *pointsInCluster;
    FILE *file;

    
    double epsilon;
    double change;
    int minCluster;
    double minDistance;
    double distance;




    int k; 
    int n;
    int d;
    int max_iter;
    if (argc == 4){
        k = atoi(argv[1]);
        n = atoi(argv[2]);
        d = atoi(argv[3]);
        max_iter = 200;
    }
    else if (argc == 5){
        k = atoi(argv[1]);
        n = atoi(argv[2]);
        d = atoi(argv[3]);
        max_iter = atoi(argv[4]);
    }
    else{
        printf("An Error Has Occured\n");
        return 1;
    }
    /*initailize the matrix for clusters and points and a temp matrix for clusters*/
    clusterMatrix = (double **)malloc(k * sizeof(double *));
    for (i = 0; i < k; i++){
        clusterMatrix[i] = (double *)malloc(d * sizeof(double));
    }
    pointMatrix = (double **)malloc(n * sizeof(double *));
    for (i = 0; i < n; i++){
        pointMatrix[i] = (double *)malloc((d+1)* sizeof(double));
    }
    tempClusters = (double **)malloc(k * sizeof(double *));
    for (i = 0; i < k; i++){
        tempClusters[i] = (double *)malloc(d * sizeof(double));
    }
    /* initialize the pointsInCluster array stating how many points are in each cluster */
    pointsInCluster = (int *)malloc(k * sizeof(int));
    for (i = 0; i < k; i++){
        pointsInCluster[i] = 0;
    }

    

    file = stdin; 
    if (file == NULL){
        printf("An Error Has Occured\n");
        return 1;
    }

    
    for (i = 0; i < n; i++) {
        for (j = 0; j <= d; j++) {
            /* The final index in each pointer is the cluster index so we set it to 0 */
            if (j == d){
                pointMatrix[i][j] = 0;
            }
            /* reads into pointerMatrix from file */
            else if (fscanf(file, "%lf,", &pointMatrix[i][j]) != 1) {
                printf("An Error Has Occured\n");
                printf("Failed to read number at row %d, column %d\n", i, j);
                return 1;
            }
            else if (i < k){
                /* reads first k values into clusterMatrix */
                clusterMatrix[i][j] = pointMatrix[i][j];
            }
        }
    }
    fclose(file);
    


    epsilon = 0.001;
    change = 1.000;
    minCluster = 0;
    minDistance = 0;
    distance = 0;

    for (t = 0; t < max_iter; t++){
        /* if the change from last iteration is less than epsilon, break */
        if (change < epsilon){
            break;
        }
        /* initialize tempClusters to zero
        initialize pointsInCluster to zero */
        for ( i = 0; i < k; i++){
            for ( j = 0; j < d; j++){
                tempClusters[i][j] = 0;
            }
            pointsInCluster[i] = 0;
        }
        /* assign each point to the closest cluster based on distance */
        for ( i = 0; i < n; i++){
            minDistance = calculateDistance(pointMatrix[i], clusterMatrix[0], d);
            minCluster = 0;
            for (j = 1; j < k; j++){
                distance = calculateDistance(pointMatrix[i], clusterMatrix[j], d);
                if (distance < minDistance){
                    minDistance = distance;
                    minCluster = j;
                }
            }
            if(pointMatrix[i][d] != minCluster){
                pointMatrix[i][d] = minCluster;
                pointsInCluster[minCluster]++;
                for (j = 0; j < d; j++){
                    tempClusters[minCluster][j] += pointMatrix[i][j];
                }
            }
            else {
                pointsInCluster[minCluster]++;
                for (j = 0; j < d; j++){
                    tempClusters[minCluster][j] += pointMatrix[i][j];
                }
            }
        }
        
        /*calculate the new clusters*/
        for ( i = 0; i < k; i++){
            for ( j = 0; j < d; j++){
                tempClusters[i][j] = tempClusters[i][j] / pointsInCluster[i];
            }
        }
        /*check if the clusters have changed and add change to the total change
        set the new clusters to the clusterMatrix from tempClusters */
        change = 0;
        for ( i = 0; i < k; i++){
            change += calculateDistance(clusterMatrix[i], tempClusters[i], d);

            for (j = 0; j < d; j++){
                clusterMatrix[i][j] = tempClusters[i][j];
            }
        }
    




     } 
 
    for ( i = 0; i < k; i++){
        for ( j = 0; j < d; j++){
            if (j == d-1 ){
                printf("%.4f", clusterMatrix[i][j]);
            }
            else{
                printf("%.4f,", clusterMatrix[i][j]);
            }
        }
        printf("\n");
    }


    for ( i = 0; i < k; i++) {
        free(clusterMatrix[i]);
    }
    free(clusterMatrix);
    for ( i = 0; i < k; i++) {
        free(tempClusters[i]);
    }
    free(tempClusters);
    for ( i = 0; i < n; i++) {
        free(pointMatrix[i]);
    }
    free(pointMatrix);
    free(pointsInCluster);
    
    return 0;
}


