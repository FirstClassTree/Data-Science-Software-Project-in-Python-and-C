# Import necessary modules
import copy
import sys


def main( ):
    # initialize the variables
    try:
        if len(sys.argv) == 5:
            k = int(sys.argv[1])
            n = int(sys.argv[2])
            dimensions = int(sys.argv[3])
            max_iterations = 200
            input_file = sys.argv[4]
        elif len(sys.argv) == 6:
            k = int(sys.argv[1])
            n = int(sys.argv[2])
            dimensions = int(sys.argv[3])
            max_iterations = int(sys.argv[4])
            input_file = sys.argv[5]

        else:
            print("An Error Has Occured")
            return
        if k < 1:
            print("Invalid number of clusters!")
            return
        if n < 1 or n < k:
            print("Invalid number of points!")
            return
        if dimensions < 1 :
            print("Invalid number of dimensions!")
            return
        if max_iterations < 1 or max_iterations > 1000:
            print("Invalid number of iterations!")
            return
    
    
        centeroids = [] #matrix of centeroids
        points = [] #matrix of points

        count = 0
        with open(input_file, 'r') as file:
            for line in file:
                #initize  the points array, the final index in each row is the cluster index 
                points.append([float(x) for x in line.strip().split(',')] + [0])
                if count < k:
                    centeroids.append([float(x) for x in line.strip().split(',')])
                    count += 1

        #main algohrithm
        kMeans(k,centeroids,points,dimensions,max_iterations)
    
    except Exception as e:
        print("An Error Has Occured", e)



    return
    


def kMeans(k,centeroids, points, dimensions,max_iterations = 200):
    # Implement the kMeans algorithm
    tmpCenteroids = copy.deepcopy(centeroids)
    pointsInCluster = [0 for i in range(k)]
    
    epsilon = 0.001
    changes = 1.000 
    for i in range(max_iterations):
        #stop iterating if the changes are less than epsilon
        if changes <= epsilon:
            break

        #initize the temp centeroid holder to zero
        for i in range(len(tmpCenteroids)):
            for j in range(len(tmpCenteroids[i])):
                tmpCenteroids[i][j] = 0
            pointsInCluster[i] = 0
        
        for point in points:
            minDistance = calculateDistance(point,centeroids[0],dimensions)
            minCluster = 0
            #calculate the distance between the point and each of the centeroids and get the minimum distance
            for j in range(k):
                tmpDistance = calculateDistance(point,centeroids[j],dimensions)
                if tmpDistance < minDistance:
                    minDistance = tmpDistance
                    minCluster = j
            #update the cluster index of the point and calculate the changes from past cluster:
            # if the point is in a new cluster, add the point to the new cluster and remove it from the old cluster
            if(point[dimensions] != minCluster):
                #point[dimensions] is the cluster index of the point
                point[dimensions] = minCluster
                for t in range(dimensions):
                    tmpCenteroids[minCluster][t] = tmpCenteroids[minCluster][t] + point[t]
                pointsInCluster[minCluster] = pointsInCluster[minCluster] + 1
            #if the point is in the same cluster, add the point to the cluster that is saved in the point last index (dimensions)
            else:
                for t in range(dimensions):
                    tmpCenteroids[point[dimensions]][t] = tmpCenteroids[point[dimensions]][t] + point[t]
                pointsInCluster[point[dimensions]] = pointsInCluster[point[dimensions]] + 1    

        #update the centeroids
        changes = 0
        for i in range(k):
            if pointsInCluster[i] == 0:
                #for j in range(dimensions):
                #tmpCenteroids[i][j] = centeroids[i][j] 
                continue
            else:
                for j in range(dimensions):
                    tmpCenteroids[i][j] = tmpCenteroids[i][j] / pointsInCluster[i]

        #calculate the changes from the past centeroids and update the centeroids from the temp centeroids to the real centeroids
        for i in range(k):
            changes = changes + calculateDistance(tmpCenteroids[i],centeroids[i],dimensions)
            for j in range(dimensions):
                centeroids[i][j] = tmpCenteroids[i][j]

    #print centeroids:
    for i in range(k):
        for j in range (dimensions-1):
            print(round(centeroids[i][j],4), end = ",")
        print(round(centeroids[i][dimensions-1],4))

    return

    

def calculateDistance(point1, point2,dimensions):
    # Implement the distance calculation between two points
    calcualted_distance = 0
    for i in range(dimensions):
        calcualted_distance += (point1[i] - point2[i])**2
    calcualted_distance = calcualted_distance**0.5
    
    return calcualted_distance




if __name__ == "__main__":
    main()
