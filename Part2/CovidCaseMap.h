#ifndef COVIDCASEMAP_H
#define COVIDCASEMAP_H

#include "CovidCase.h"
#include <vector>
using std::vector;
// TODO: your code goes here

class TimeAndCaseData {
    private:
    int time;
    int numberOfCases;
    
    public:
    TimeAndCaseData(int testTime, int cases)
    : time(testTime), numberOfCases(cases) {
    }
    
    int getTime() const {
        return time;
    }
    int getNumberOfCases() const {
        return numberOfCases;
    }

};

class CovidCaseMap {
    private:
    vector <CovidCase> CovidMap;
    vector <TimeAndCaseData> activeCases;
    public:
    void addCase(CovidCase newCase){
        CovidMap.push_back(newCase);
    }

    vector <TimeAndCaseData> getCasesOverTime(int n){
        int x = 0;
        int g = 0;
        int i = 0;
        int testTime = 0;
        int recoveryTime = 0;
        activeCases.push_back(TimeAndCaseData(0, x));
        while (i < CovidMap.size()){
            testTime = CovidMap[i].getTime();
            recoveryTime = CovidMap[g].getTime() + n;
            if (recoveryTime < testTime){
                activeCases.push_back(TimeAndCaseData(recoveryTime, --x));
                g++;
            }
            if (testTime < recoveryTime){
            activeCases.push_back(TimeAndCaseData(testTime, ++x));
            i++;
            }
        }
        for (g; g < CovidMap.size(); g++){
        activeCases.push_back(TimeAndCaseData(CovidMap[g].getTime() + n, --x));
        }
        return activeCases;
    }

    double supportVisitGreedyTSP(double latitude, double longitude, int time, int length){
        vector <CovidCase> tspMap = CovidMap;
        CovidCase visitedCase = tspMap[0];
        double startLat = latitude;
        double startLong = longitude;
        double shortestDistance = 10000.0;
        double totalDistance = 0;
        double distance;
        for (auto iter = tspMap.begin(); iter != tspMap.end();){
            if ((time >= (*iter).getTime() + length) || (time < (*iter).getTime())){
                tspMap.erase(iter);
            }
            else {iter++;}
        }
        auto visitedPatient = tspMap.begin();
        while (tspMap.size() > 0){
            for (auto iter = tspMap.begin(); iter != tspMap.end(); iter++){
            distance = (*iter).startDistanceTo(latitude,longitude);
                if (distance < shortestDistance){
                    shortestDistance = distance;
                    visitedPatient = iter;
                    visitedCase = *iter;
                }
            }
            totalDistance = totalDistance + shortestDistance;
            cout<< "chosen" << shortestDistance<< "\n";
            shortestDistance = 1000.0;
            latitude = visitedCase.getLatitude();
            longitude = visitedCase.getLongitude();
            tspMap.erase(visitedPatient);
        }
        totalDistance += visitedCase.startDistanceTo(startLat,startLong);
        return totalDistance;
    }
};

// don't write any code below this line

#endif

