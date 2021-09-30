
#include "ContagionWorld.h"

//Done by Suleiman
ContagionWorld::ContagionWorld(std::string configName) {
    this->configName = configName;
    infectedArea = 0;
    infectiousPeriod = 0;
    contactRate = 0;
    numberOfVaccines = 0;
    regionLayoutFileName = "";
    regionPopulationsFileName = "";
    regionNumber = 0;

    peakInfectedCloseness = 0; // integer that stores the peak number of infected agents
    dayPeakCloseness = 0; // integer that stores the day the peak number of agents were infected
    dayEndCloseness = 0; // integer that stores the day the outbreak ended on
    totalInfectedCloseness = 0; // total number of infected agents

    peakInfectedDegree = 0; // integer that stores the peak number of infected agents
    dayPeakDegree = 0; // integer that stores the day the peak number of agents were infected
    dayEndDegree = 0; // integer that stores the day the outbreak ended on
    totalInfectedDegree = 0; // total number of infected agents

    peakInfectedRandom = 0; // integer that stores the peak number of infected agents
    dayPeakRandom = 0; // integer that stores the day the peak number of agents were infected
    dayEndRandom = 0; // integer that stores the day the outbreak ended on
    totalInfectedRandom = 0; // total number of infected agents

    peakInfectedEqual = 0; // integer that stores the peak number of infected agents
    dayPeakEqual = 0; // integer that stores the day the peak number of agents were infected
    dayEndEqual = 0; // integer that stores the day the outbreak ended on
    totalInfectedEqual = 0; // total number of infected agents

    peakInfectedWeight = 0; // integer that stores the peak number of infected agents
    dayPeakWeight = 0; // integer that stores the day the peak number of agents were infected
    dayEndWeight = 0; // integer that stores the day the outbreak ended on
    totalInfectedWeight = 0; // total number of infected agents

}

//Done by Suleiman
ContagionWorld::~ContagionWorld() {
    std::cout << "Program has stopped\n";
}

//Done by Suleiman
void ContagionWorld::Read() {
    std::ifstream MyReadFile(configName);
    std::string line;

    //File names
    getline(MyReadFile, line);//reading first line of the config file
    this->regionPopulationsFileName = line.substr(line.find_last_of(":") + 1);

    getline(MyReadFile, line);//reading second line of the config file
    this->regionLayoutFileName = line.substr(line.find_last_of(":") + 1);

    //empty line
    getline(MyReadFile, line);

    //Numbers
    getline(MyReadFile, line);//reading third line of the config file
    this->infectedArea = stoi(line.substr(line.find_last_of(":") + 1));

    getline(MyReadFile, line);//reading forth line of the config file
    this->infectiousPeriod = stoi(line.substr(line.find_last_of(":") + 1));

    getline(MyReadFile, line);//reading fifth line of the config file
    this->contactRate = stoi(line.substr(line.find_last_of(":") + 1));

    getline(MyReadFile, line);//reading sixth line of the config file
    this->numberOfVaccines = stoi(line.substr(line.find_last_of(":") + 1));

    MyReadFile.close();
}

//Done by Suleiman
void ContagionWorld::ReadPopulation() {
    std::ifstream MyReadFile(regionPopulationsFileName);
    std::string line;
    int ID = 1;
    int population = 0;
    if (MyReadFile.fail())
    {
        throw "Population File can't be opened";
    }
    while (MyReadFile.good()) {
        getline(MyReadFile, line);

        if (!line.empty()) {
            population = stoi(line.substr(line.find_last_of(":") + 1));//getting population number

            Region region(ID, population);//creating region using ID and population
            regionList.push_back(region);

            ID++;
        }

    }
    //regionList.pop_back();//deleting last empty one
    regionNumber = regionList.size();
    edges.resize(regionNumber + 1);
    MyReadFile.close();
}

//Done by Suleiman
void ContagionWorld::PrintRegionalPopulation() {

    std::cout << "Regional Population" << std::endl;
    for (auto& region : regionList) {
        std::cout << region.getID() << " " << region.getPopulation() << std::endl;
    }
}

//Done by Suleiman
void ContagionWorld::ReadAdjacencyList() {
    int xP = 0;
    int yP = 0;
    std::string sCH;

    std::ifstream file(regionLayoutFileName);

    if (file.fail())
    {
        throw "Adjacency File can't be opened";
    }


    if (file.good()) {

        getline(file, sCH); //First Line which has to be skipped
    }
    while (file.good()) {

        std::string line;
        getline(file, line); // reading every line of the file
        std::stringstream ss(line);
        std::vector<int> row;

        getline(ss, sCH, ','); //skipping first
        int id = 0;
        while (ss.good()) {
            getline(ss, sCH, ','); //skipping first becuase it is not needed
            id++;
            if (stoi(sCH) == 1) {
                //TODO add object with this id to the 2D matrix?

                row.push_back(id); //adding ID to the row
                xP++;
            }
        }
        xP = 0;
        yP++;

        contagionMap.push_back(row);// adding row to the map vector
        if (!file.good()) {
            row.clear();
            row.shrink_to_fit();
        }
    }
    contagionMap.pop_back(); //adding row to the map
    file.close();
}

//Done by Suleiman
void ContagionWorld::PrintAdjacencyList() {

    std::cout << "Adjacency List" << std::endl;
    int ID = 1;
    for (int i = 0; (unsigned)i < contagionMap.size(); i++) {
        std::cout << ID << ": ";
        for (int j = 0; (unsigned)j < contagionMap[i].size(); j++) {
            std::cout << contagionMap[i][j] << " ";

            addEdge(edges, ID, contagionMap[i][j]);

        }
        ID++;
        std::cout << std::endl;
    }

}


//Done by Suleiman
void ContagionWorld::printSIRV() {
    for (auto& region : regionList) {
        // printf("%d %*s %d %d\n",region.getID(),5,"POP",region.getPopulation(),region.getVaccinatedNum());
        std::cout << std::left << std::setw(3) << region.getID() << "   Pop: " << std::setw(5) << region.getPopulation() << "   S: " << std::setw(5) << region.getSuspectNum() << "   I: " << std::setw(5) << region.getInfected()
                  << "   R: " << std::setw(6) << region.getRecovered() << "   V: " << region.getVaccinatedNum() << std::endl;
    }
    std::cout << std::endl;
}

bool compareByD::operator()(Region r1, Region r2) const {
    if (r1.getRegionAvgD() == r2.getRegionAvgD())
        return r1.getID() < r2.getID();
    else {
        return r1.getRegionAvgD() < r2.getRegionAvgD();
    }
}
//Done by Suleiman
void ContagionWorld::ClosenessCentralityDistribution() {
    std::cout << "CLOSENESS DISTRIBUTION" << std::endl;
    int sum = 0;
    double avg = 0;
    std::vector<Region> vectorOfSums;
    int temp_vaccines = numberOfVaccines;

    for (auto& i : regionList) {
        for (auto& j : regionList) {
            if (i.getID() != j.getID())
                sum += findMinEdgeDistance(edges, i.getID(), j.getID(), edges.size());
        }
        avg = (double)sum / edges.size();
        i.setRegionAvgF(avg);
        vectorOfSums.push_back(i);
        sum = 0;
        avg = 0;
    }

    //sorting by distance
    std::sort(vectorOfSums.begin(), vectorOfSums.end(), compareByD());

    //distributing vaccines;
    for (int i = 0; (unsigned)i < vectorOfSums.size() && temp_vaccines > 0; ++i) {

        //if number of vaccine bigger or equal to population, vaccinate all people in that region
        int regionPop = vectorOfSums[i].getPopulation();
        if (regionPop <= temp_vaccines) {
            temp_vaccines -= regionPop;
            regionList[vectorOfSums[i].getID() - 1].setVaccinatedNum(regionPop);
        }
            //if number of vaccine is smaller than population, use all vaccines we have
        else if (regionPop > temp_vaccines) {
            regionList[vectorOfSums[i].getID() - 1].setVaccinatedNum(temp_vaccines);
            temp_vaccines -= temp_vaccines;
        }

    }


}

//Done by Phong
void ContagionWorld::DegreeCentralityDistribution() {
    std::cout << "DEGREE DISTRIBUTION" << std::endl;
    //std::cout << "Number of Vaccines: " << numberOfVaccines << std::endl;
    int temp_vaccines = numberOfVaccines;

    //Loop to check and set each region's degree
    for (int i = 0; (unsigned)i < regionList.size(); i++) {
        /*std::cout << "Region #" << regionList[i].getID() << " of adjacent regions: ";*/
        regionList[i].setRegionDegree(contagionMap[i].size());
        /*std::cout << regionList[i].getRegionDegree() << std::endl;*/
    }

    //Sort the region in descending order base on the region's degree
    std::sort(regionList.begin(), regionList.end(), [](Region& lhs, Region& rhs) {
        return lhs.getRegionDegree() > rhs.getRegionDegree();
    });

    //Assign Vaccine to region
    for (auto it = regionList.begin(); it != regionList.end(); it++) {
        int temp;
        if (temp_vaccines > it->getPopulation()) {
            temp = it->getPopulation();
            it->setVaccinatedNum(temp);
            temp_vaccines -= temp;
        }
        else {
            it->setVaccinatedNum(temp_vaccines);
            temp_vaccines -= temp_vaccines;
        }
        /*std::cout << "Region " << it->getID() << ": # of degrees: " << it->getRegionDegree() << "| # of population: " << it->getPopulation() << "| # of vaccines: " << it->getVaccinatedNum();
        std::cout << "| Vaccines remaining: " << numberOfVaccines << std::endl;*/
    }
    //Return region back to normal with ID starting from 1
    std::sort(regionList.begin(), regionList.end(), [](Region& lhs, Region& rhs) {
        return lhs.getID() < rhs.getID();
    });
}

void ContagionWorld::addEdge(std::vector<std::vector<int> >& edges, int u, int v) {
    edges[u].push_back(v);
    // edges[v].push_back(u);
}

//BFS Algorithm
int ContagionWorld::findMinEdgeDistance(std::vector<std::vector<int>>& edges, int u, int v, int n) {
    std::vector<bool> visited(n, 0);
    std::vector<int> distance(n, 0);

    // queue to do BFS.
    std::queue <int> Q;
    distance[u] = 0;

    Q.push(u);
    visited[u] = true;
    while (!Q.empty())
    {
        int x = Q.front();
        Q.pop();

        for (int i = 0; (unsigned)i < edges[x].size(); i++)
        {
            if (visited[edges[x][i]])
                continue;

            // update distance for i
            distance[edges[x][i]] = distance[x] + 1;
            Q.push(edges[x][i]);
            visited[edges[x][i]] = 1;
        }
    }
    return distance[v];
}

//Done by Fernando
void ContagionWorld::RandomDistribution() {
    std::cout << "RANDOM DISTRIBUTION" << std::endl;
    int remaining_vaccines = numberOfVaccines;
    int vaccines;

    for (auto it = regionList.begin(); it != regionList.end(); it++) {
        //if remaining vaccines is greater than population assign vaccines to population
        if (remaining_vaccines > it->getPopulation()) {
            vaccines = it->getPopulation();
            it->setVaccinatedNum(vaccines);
            remaining_vaccines = remaining_vaccines - vaccines;
        }

            //if there are not enough vaccines for the region but there are still vaccines
        else if (remaining_vaccines < it->getPopulation()) {
            vaccines = remaining_vaccines;
            it->setVaccinatedNum(vaccines);
            remaining_vaccines = remaining_vaccines - vaccines;

        }

        else if (remaining_vaccines == 0) {
            it->setVaccinatedNum(0);
        }

    }
}

void ContagionWorld::EqualDistribution() {
    std::cout << "EQUAL DISTRIBUTION" << std::endl;
    int remaining_vaccines = numberOfVaccines;
    int smallestVaccineAmount = 0;
    smallestVaccineAmount = regionList[0].getPopulation();

    //finding smallest value
    for (auto it = regionList.begin(); it != regionList.end(); it++) {
        if (smallestVaccineAmount > it->getPopulation()) {
            smallestVaccineAmount = it->getPopulation();
        }
    }

    //giving minimum number
    for (auto it = regionList.begin(); it != regionList.end(); it++) {
        if (it->getPopulation() >= smallestVaccineAmount && remaining_vaccines >= smallestVaccineAmount) {
            it->setVaccinatedNum(smallestVaccineAmount);
            remaining_vaccines -= smallestVaccineAmount;
        }
    }

    while (remaining_vaccines > 0) {
        for (auto it = regionList.begin(); it != regionList.end(); it++) {
            if (it->getPopulation() > it->getVaccinatedNum() && remaining_vaccines > 0) {
                it->vaccineIncrement();
                remaining_vaccines--;
            }
        }
    }
}

//BONUS Done by Suleiman
void ContagionWorld::WeightedDistribution() {
    std::cout << "WEIGHTED DISTRIBUTION" << std::endl;
    int remaining_vaccines = numberOfVaccines;
    int totalPopulation = 0;
    int vaccineAmount = 0;
    double proportionValue = 0.0;
    //finding total pop for all regions
    for (auto it = regionList.begin(); it != regionList.end(); it++) {
        totalPopulation += it->getPopulation();
    }



    //distributing vaccines using proportions
    for (auto it = regionList.begin(); it != regionList.end(); it++) {
        proportionValue = (double) numberOfVaccines/totalPopulation;
        vaccineAmount = floor(it->getPopulation()*proportionValue);
        it->setVaccinatedNum(vaccineAmount);
        remaining_vaccines-=vaccineAmount;

    }

    // distribute remainings
    while (remaining_vaccines > 0) {
        for (auto it = regionList.begin(); it != regionList.end(); it++) {
            if (it->getPopulation() > it->getVaccinatedNum() && remaining_vaccines > 0) {
                it->vaccineIncrement();
                remaining_vaccines--;
            }
        }
    }


}

void ContagionWorld::resetDistribution() {
    for (auto& region : regionList) {

        region.setVaccinatedNum(0);
        region.setSuspectNum(0);
        region.setInfectedNum(0);
        region.setRecoveredNum(0);
        region.setRegionAvgF(0.0);
        region.setRegionDegree(0);

        region.setRecoverDiff(0);
        region.notInfected();
        region.notRecoverRegion();
        region.setFiftyPopF();
        region.setNextDayInfectF();
    }
}


void ContagionWorld::simulateWorld(int iterate) {
    unsigned int recoverCounter = 0; //Counter variable to determine when infecting is over
    bool infecting = false; //variable to determine if infecting is still occuring
    int dayNum = 1;
    int NewDay = 0;

    //bool noInfected; // experiement stops if this is equal to true at the end of the loop
    int peakInfectedTemp = 0; // integer that stores the peak number of infected agents
    int dayPeakTemp = 0; // integer that stores the day the peak number of agents were infected
    int dayEndTemp = 0; // integer that stores the day the outbreak ended on
    int totalInfectedTemp = 0; // total number of infected agents
    int iteration = iterate;


    for (auto it = regionList.begin(); it != regionList.end(); it++) {
        if (it->getPopulation() != it->getVaccinatedNum()) {
            if (it->getVaccinatedNum() < it->getPopulation())
                it->setSuspectNum(it->getPopulation() - it->getVaccinatedNum());
            else
                it->setSuspectNum(it->getPopulation());
        }
    } //For Loop to set the number of susceptible agents.

    //Inital infection
    std::cout << "Day 0" << std::endl;
    if (regionList[infectedArea - 1].getSuspectNum() > 0) {
        regionList[infectedArea - 1].setInfectedNum(1); //Set intial infected area == 1
        regionList[infectedArea - 1].infectRegion();
        if (regionList[infectedArea - 1].isInfected()) {
            //std::cout << "Region is infected" << std::endl;
            infecting = true;
        }
        regionList[infectedArea - 1].setSuspectNum(regionList[infectedArea - 1].getSuspectNum() - 1);
        regionList[infectedArea - 1].setInfectToRecover(regionList[infectedArea - 1].getInfected(), infectiousPeriod);
    }
    printSIRV();
    while (infecting) {
        peakInfectedTemp = 0;
        for (auto& region : regionList) {
            if (region.isRecovering()) {
                region.getInfectToRecover(region); //Look at deque and do calculations
                if (region.getRecovered() == region.getPopulation())
                    region.notRecoverRegion(); //Region is no longer recovering
            }//If region is recovering.
            if (region.isInfected()) {
                region.getInfectToRecover(region); //Look at deque and do calculations. determine recovered people
                // std::cout << "Region ID infected " << region.getID() << " " << region.getInfected() << " " << region.getPopulation() << std::endl;
                if (region.getNextDayInfect() && dayNum == NewDay) {
                    region.setInfectedNum(1); //Set region inital infected number to 1
                    region.setSuspectNum(region.getSuspectNum() - 1); //Update susceptible number
                    region.setInfectToRecover(region.getInfected(), infectiousPeriod);
                    region.setNextDayInfectF();
                }
                else if (region.getInfected() > (region.getPopulation() / 2)) {
                    region.setInfectedNum(region.getSuspectNum() + region.getInfected() - region.getRecoverDiff()); //New infected number
                    if(region.getSuspectNum() != 0)
                        region.setInfectToRecover(region.getSuspectNum(), infectiousPeriod); //Add to deque
                    region.setSuspectNum(region.getSuspectNum() - region.getSuspectNum()); //New susceptible number
                    region.setFiftyPopT();
                    region.setNextDayInfectT();
                } //If number of infected people is 50% or more of region's total population
                else if ((region.getInfected() * contactRate) > region.getSuspectNum()) {
                    region.setInfectedNum((region.getInfected() + region.getSuspectNum()) - region.getRecoverDiff()); //New infected = old infected + old susceptible - (recover difference)
                    if (region.getSuspectNum() != 0)
                        region.setInfectToRecover(region.getSuspectNum(), infectiousPeriod); //Add to deque
                    region.setSuspectNum(region.getSuspectNum() - region.getSuspectNum()); //Update susceptible. Should be 0
                }
                else {
                    region.setInfectToRecover((region.getInfected() * contactRate), infectiousPeriod);
                    region.setSuspectNum(region.getSuspectNum() - (region.getInfected() * contactRate)); //new susceptible = old susceptible - (infected difference)
                    region.setInfectedNum((region.getInfected() * contactRate + region.getInfected()) - region.getRecoverDiff()); //new infected = old inf * contact rate + old inf - (new rec - old rec)
                }

                if (region.getSuspectNum() == 0 && region.getFiftyPopStatus()) {
                    region.notInfected();
                    region.recoverRegion();
                    region.setFiftyPopF();
                    for (int i = 0; (unsigned)i < contagionMap[region.getID() - 1].size(); i++) {
                        //std::cout << regionList[contagionMap[region.getID() - 1][i] - 1].getID() << " " << regionList[contagionMap[region.getID() - 1][i] - 1].getSuspectNum() << " " << regionList[contagionMap[region.getID() - 1][i] - 1].getPopulation() << std::endl;
                        if ((regionList[contagionMap[region.getID() - 1][i] - 1].getSuspectNum() > 0) && !regionList[contagionMap[region.getID() - 1][i] - 1].isInfected()) {
                            if (regionList[contagionMap[region.getID() - 1][i] - 1].getID() > region.getID()) {
                                regionList[contagionMap[region.getID() - 1][i] - 1].infectRegion(); //Set infected status of region to true
                                regionList[contagionMap[region.getID() - 1][i] - 1].setNextDayInfectT();
                                NewDay = dayNum;
                            }
                            else {
                                regionList[contagionMap[region.getID() - 1][i] - 1].infectRegion(); //Set infected status of region to true
                                regionList[contagionMap[region.getID() - 1][i] - 1].setInfectedNum(1); //Set region inital infected number to 1
                                regionList[contagionMap[region.getID() - 1][i] - 1].setSuspectNum(regionList[contagionMap[region.getID() - 1][i] - 1].getSuspectNum() - 1); //Update susceptible number
                                regionList[contagionMap[region.getID() - 1][i] - 1].setInfectToRecover(regionList[contagionMap[region.getID() - 1][i] - 1].getInfected(), infectiousPeriod);
                            }
                        }
                    }
                }

            }
            peakInfectedTemp += region.getInfected();
            dayPeakTemp = dayNum;

            if (region.getInfected() == 0.0) {
                recoverCounter++;
            }
        }
        if (recoverCounter == regionList.size()) {
            infecting = false;
            //     std::cout << "no more infecting" << std::endl;
        }
        else
            recoverCounter = 0;
        std::cout << "Day " << dayNum << std::endl;
        printSIRV();
        dayNum++;

        switch (iteration) {
            case 0:
                if (peakInfectedTemp > peakInfectedCloseness) {
                    peakInfectedCloseness = peakInfectedTemp;
                    dayPeakCloseness = dayPeakTemp;
                }
                else
                    peakInfectedTemp = 0;
                break;

            case 1:
                if (peakInfectedTemp > peakInfectedDegree) {
                    peakInfectedDegree = peakInfectedTemp;
                    dayPeakDegree = dayPeakTemp;
                }
                else
                    peakInfectedTemp = 0;
                break;

            case 2:
                if (peakInfectedTemp > peakInfectedRandom) {
                    peakInfectedRandom = peakInfectedTemp;
                    dayPeakRandom = dayPeakTemp;
                }
                else
                    peakInfectedTemp = 0;
                break;

            case 3:
                if (peakInfectedTemp > peakInfectedEqual) {
                    peakInfectedEqual = peakInfectedTemp;
                    dayPeakEqual = dayPeakTemp;
                }
                else
                    peakInfectedTemp = 0;
                break;

            case 4:
                if (peakInfectedTemp > peakInfectedWeight) {
                    peakInfectedWeight = peakInfectedTemp;
                    dayPeakWeight = dayPeakTemp;
                }
                else
                    peakInfectedTemp = 0;
                break;
        }

    }

    for (auto& region : regionList) {
        if (region.getRecovered() > 0)
            totalInfectedTemp += region.getRecovered();
    }//To determine the total number of infected individuals


    switch (iteration) {
        case 0:
            dayEndCloseness = dayNum - 1;
            if (totalInfectedTemp > totalInfectedCloseness) totalInfectedCloseness = totalInfectedTemp;
            break;

        case 1:
            dayEndDegree = dayNum - 1;
            if (totalInfectedTemp > totalInfectedDegree) totalInfectedDegree = totalInfectedTemp;
            break;

        case 2:
            dayEndRandom = dayNum - 1;
            if (totalInfectedTemp > totalInfectedRandom) totalInfectedRandom = totalInfectedTemp;
            break;

        case 3:
            dayEndEqual = dayNum - 1;
            if (totalInfectedTemp > totalInfectedEqual) totalInfectedEqual = totalInfectedTemp;
            break;

        case 4:
            dayEndWeight = dayNum - 1;
            if (totalInfectedTemp > totalInfectedWeight) totalInfectedWeight = totalInfectedTemp;
            break;
    }
}

void ContagionWorld::executeWorld() {
    for (int i = 0; i < 5; i++) {
        if (i == 0)
            ClosenessCentralityDistribution();  //Distribute vaccines
        if (i == 1)
            DegreeCentralityDistribution(); //Distribute vaccines
        if (i == 2)
            RandomDistribution();
        if (i == 3)
            EqualDistribution();
        if (i == 4)
            WeightedDistribution();


        simulateWorld(i);
        resetDistribution();
    }
    std::cout << "Using the closeness centrality distribution method, the peak number of infected was " << peakInfectedCloseness << " on day " << dayPeakCloseness << ". The outbreak ended on day " << dayEndCloseness << " and the total number of infected individuals was " << totalInfectedCloseness << "." << std::endl;
    std::cout << "Using the degree centrality distribution method, the peak number of infected was " << peakInfectedDegree << " on day " << dayPeakDegree << ". The outbreak ended on day " << dayEndDegree << " and the total number of infected individuals was " << totalInfectedDegree << "." << std::endl;
    std::cout << "Using the random distribution method, the peak number of infected was " << peakInfectedRandom << " on day " << dayPeakRandom << ". The outbreak ended on day " << dayEndRandom << " and the total number of infected individuals was " << totalInfectedRandom << "." << std::endl;
    std::cout << "Using the equal centrality distribution method, the peak number of infected was " << peakInfectedEqual << " on day " << dayPeakEqual << ". The outbreak ended on day " << dayEndEqual << " and the total number of infected individuals was " << totalInfectedEqual << "." << std::endl;
    std::cout << "Using the equal weighted distribution method, the peak number of infected was " << peakInfectedWeight << " on day " << dayPeakWeight << ". The outbreak ended on day " << dayEndWeight << " and the total number of infected individuals was " << totalInfectedWeight << "." << std::endl;

}



