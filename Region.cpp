#include "Region.h"
Region::Region(int id, int population){
    this->id = id;
    this->population = population;
    regionAvgDistance=0;
    regionDegree=0;
    suspectibleNum=0;
    infectiousNum=0;
    recoveredNum=0;
    vaccinatedNum=0;

    recoverDiff = 0;
    m_Infected = false;
    m_recovering = false;
    m_fiftyPop = false;
    m_nextDayInfect = false;
}

Region::~Region(){}

int Region::getPopulation() {
    return population;
}

void Region::setPopulation(int newPopulation) {
    population=newPopulation;
}

int Region::getID() {
    return id;
}

int Region::getRegionDegree() {
    return regionDegree;
}
void Region::setRegionDegree(int Num_adjRegions) {
    regionDegree = Num_adjRegions;
}
void Region::setVaccinatedNum(int vaccines) {
    vaccinatedNum = vaccines;
}
int Region::getVaccinatedNum() {
    return vaccinatedNum;
}

double Region::getRegionAvgD() {
    return regionAvgDistance;
}

void Region::setRegionAvgF(double x) {
    regionAvgDistance=x;
}

int Region::getSuspectNum() {
    return suspectibleNum;
}

int Region::getInfected() {
    return infectiousNum;
}

int Region::getRecovered() {
    return recoveredNum;
}

void Region::setSuspectNum(int newNum) {
    suspectibleNum = newNum;
}

void Region::setInfectedNum(int newNum) {
    infectiousNum = newNum;
}

void Region::setRecoveredNum(int newNum) {
    recoveredNum = newNum;
}

void Region::infectRegion(){
    m_Infected = true;
}

void Region::notInfected(){
    m_Infected = false;
}

bool Region::isInfected(){
    return m_Infected;
}

void Region::recoverRegion() {
    m_recovering = true;
}

void Region::notRecoverRegion() {
    m_recovering = false;
}

bool Region::isRecovering() {
    return m_recovering;
}

void Region::setRecoverDiff(int newNum ) {
    recoverDiff = newNum;
}

int Region::getRecoverDiff() {
    return recoverDiff;
}


void Region::setInfectToRecover(int x, int y) {
    infected_to_recovered.push_back(std::pair<int, int>(x, y));
}

void Region::getInfectToRecover(Region &x) {
    int new_recovered = 0;
    for (int i = 0; (unsigned)i < infected_to_recovered.size(); i++) {
        if (infected_to_recovered[i].second > 0) {
            infected_to_recovered[i].second--;

        }
        if (infected_to_recovered[i].second == 0) {
            new_recovered += infected_to_recovered[i].first;
        }
    } //Deque used to determine when infected people become recovered

    x.setRecoverDiff(new_recovered);
    x.setRecoveredNum(new_recovered + x.getRecovered());

    if (infected_to_recovered.size() > 0) {
        if (infected_to_recovered.front().second == 0) //Might have to change. If second == 0, it means infectious period is over so pop element out.
            infected_to_recovered.pop_front();
    }

    if (x.getSuspectNum() == 0 && x.isRecovering()) {
        x.setInfectedNum(x.getInfected() - new_recovered);
    }//Update number of infected once infecting has stop

    if (x.getInfected() == 0) {
        infected_to_recovered.clear();
    }//

}

void Region::setFiftyPopT() {
    m_fiftyPop = true;
}
void Region::setFiftyPopF() {
    m_fiftyPop = false;
}
bool Region::getFiftyPopStatus() {
    return m_fiftyPop;
}

void Region::setNextDayInfectT() {
    m_nextDayInfect = true;
}
void Region::setNextDayInfectF() {
    m_nextDayInfect = false;
}
bool Region::getNextDayInfect() {
    return m_nextDayInfect;
}

void Region::vaccineIncrement() {
    vaccinatedNum++;
}
