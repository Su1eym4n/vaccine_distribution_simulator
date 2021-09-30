#include <iostream>
#include <vector>
#include <queue>
class Region{
    int id;
    int population;

    double regionAvgDistance;
    int regionDegree;

    std::deque<std::pair<int, int>> infected_to_recovered; //<number of people that got infected, number of days until recovered>

    //TODO give initial values
    int suspectibleNum;
    int infectiousNum;
    int recoveredNum;
    int vaccinatedNum;

    int recoverDiff;
    bool m_Infected;
    bool m_recovering;
    bool m_fiftyPop;
    bool m_nextDayInfect;

public:
    Region(int id, int population);
    ~Region();

    //GETTERS
    int getPopulation();// returns population number
    int getID();//returns ID
    int getRegionDegree();
    int getVaccinatedNum();
    int getSuspectNum();
    double getRegionAvgD();
    int getInfected();
    int getRecovered();

    //SETTERS
    void setRegionAvgF(double x);
    void setRegionDegree(int);
    void setVaccinatedNum(int);

    void setPopulation(int);//sets new population

    void setSuspectNum(int);
    void setInfectedNum(int);
    void setRecoveredNum(int);

    void infectRegion(); //set m_Infected to true
    void notInfected(); // set m_Infected to false
    bool isInfected();  // determine if region is infected or not

    void recoverRegion(); //set m_recovering to true
    void notRecoverRegion(); //set m_recovering to false
    bool isRecovering(); //determine if region is recovering or not

    void setInfectToRecover(int, int); //Add element to deque
    void getInfectToRecover(Region&); //Perform calculation on deque

    void setRecoverDiff(int); //set difference in recovered people between days
    int getRecoverDiff();

    void setFiftyPopT();
    void setFiftyPopF();
    bool getFiftyPopStatus();

    void setNextDayInfectT();
    void setNextDayInfectF();
    bool getNextDayInfect();

    void vaccineIncrement();

};
