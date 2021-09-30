#include <iostream>
#include <utility>
#include <algorithm>
#include <sstream>
#include <vector>
#include <fstream>
#include "Region.h"
#include <string>
#include <queue>
#include <iomanip>
#include <math.h>

class ContagionWorld {
    std::string configName;
    int regionNumber;
    std::string regionPopulationsFileName;
    std::string regionLayoutFileName;
    int infectedArea;
    int infectiousPeriod;
    int contactRate;
    int numberOfVaccines;
    std::vector<Region> regionList;
    std::vector<std::vector<int> > contagionMap;
    std::vector<std::vector<int> > edges;

    //All of these variables are here because of how they want us to output totals, peaks, etc..
    int dayPeakCloseness; // integer that stores the day the peak number of agents were infected
    int peakInfectedCloseness; // integer that stores the peak number of infected agents
    int dayEndCloseness; // integer that stores the day the outbreak ended on
    int totalInfectedCloseness; // total number of infected agents

    int peakInfectedDegree; // integer that stores the peak number of infected agents
    int dayPeakDegree; // integer that stores the day the peak number of agents were infected
    int dayEndDegree; // integer that stores the day the outbreak ended on
    int totalInfectedDegree; // total number of infected agents

    int peakInfectedRandom; // integer that stores the peak number of infected agents
    int dayPeakRandom; // integer that stores the day the peak number of agents were infected
    int dayEndRandom; // integer that stores the day the outbreak ended on
    int totalInfectedRandom; // total number of infected agents

    int peakInfectedEqual; // integer that stores the peak number of infected agents
    int dayPeakEqual; // integer that stores the day the peak number of agents were infected
    int dayEndEqual; // integer that stores the day the outbreak ended on
    int totalInfectedEqual; // total number of infected agents

    int peakInfectedWeight; // integer that stores the peak number of infected agents
    int dayPeakWeight; // integer that stores the day the peak number of agents were infected
    int dayEndWeight; // integer that stores the day the outbreak ended on
    int totalInfectedWeight; // total number of infected agents

public:
    ContagionWorld(std::string configName);
    ~ContagionWorld();

    void Read();

    void ReadPopulation(); //this function reads the file and creates Region objects
    void ReadAdjacencyList();//this function reads the file and cretaed 2D vector that stores adjacent regions of every region

    void PrintRegionalPopulation(); //this function prints the population of every region
    void PrintAdjacencyList();//this function prints adjacency list

    void ClosenessCentralityDistribution();

    void DegreeCentralityDistribution();

    void RandomDistribution();
    void EqualDistribution();
    void WeightedDistribution();


    //adds edge between adjacent regions
    void addEdge(std::vector<std::vector<int >>& edges, int u, int v);

    //BFS algorithm that finds shortest distance
    int findMinEdgeDistance(std::vector< std::vector<int> >& edges, int u, int v, int n);

    void printSIRV();

    //resetes the regions before next distribution
    void resetDistribution();

    //launches simulation for ditribution
    void simulateWorld(int);

    //simulates the contagion for every distribution
    void executeWorld();
};

//comparator for 2nd code component
struct compareByD {
public:
    bool operator () (Region r1, Region r2) const;
};


