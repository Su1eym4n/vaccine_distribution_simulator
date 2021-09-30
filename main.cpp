#include <iostream>
#include <string>
#include <fstream>
#include "ContagionWorld.h"
int main(){
    std::string fileName;
    std::cout<<"Contagion Simulator"<<std::endl;
    std::cout<<"To quit enter Q"<<std::endl;
    std::ifstream infile;
    do{
        std::cout << "Enter configuration file:";
        std::getline(std::cin, fileName);
        infile.open(fileName);

        if(fileName.compare("Q")==0){
            std::cout<<"Simulation was terminated manually"<<std::endl;
            return 0;
        }

    }while(infile.fail());
    ContagionWorld world(fileName);
    try{
        world.Read();
        world.ReadPopulation();
        world.PrintRegionalPopulation();
        std::cout<<std::endl;
        world.ReadAdjacencyList();
        world.PrintAdjacencyList();
        std::cout << std::endl;

        world.executeWorld();
        infile.close();
    }catch(const char* msg){

        std::cerr<<msg<<std::endl;
    }

}