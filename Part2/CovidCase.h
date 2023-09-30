#ifndef COVIDCASE_H
#define COVIDCASE_H

#include <iostream>
#include <sstream>
#include <cmath>
#include <math.h>
using std::ostream;
using std::cout;
using std::string;
using std::stoi;

// TODO: your code  goes here
class CovidCase {
    private:
    double longitude; 
    double latitude; 
    string patientName;
    int patientAge;
    int time;

    public:
    CovidCase(double nlatitude, double nlongitude, const string pname, const int page, int ptested)
    : latitude(nlatitude), longitude(nlongitude), patientName(pname), patientAge(page), time(ptested) 
    {
    }
    CovidCase(string caseDetails){
        string delimiter = ", ";
        size_t pos;
        string field;
        pos = caseDetails.find(delimiter);
        latitude = stod(caseDetails.substr(0,pos));
        caseDetails.erase(0, pos+ delimiter.length());
        pos = caseDetails.find(delimiter);
        longitude = stod(caseDetails.substr(0,pos));
        caseDetails.erase(0, pos+ delimiter.length());
        pos = caseDetails.find(delimiter);
        patientName = caseDetails.substr(1, pos-2);
        caseDetails.erase(0, pos+ delimiter.length());
        pos = caseDetails.find(delimiter);
        patientAge = stoi(caseDetails.substr(0,pos));
        caseDetails.erase(0, pos+ delimiter.length());
        pos = caseDetails.find(delimiter);
        time = stoi(caseDetails.substr(0,pos));

    }
    const double & getLongitude() const{
        return longitude;
    }
    const double & getLatitude() const{
        return latitude;
    }

    int getAge() const{
        return patientAge;
    }

    const string & getName() const{
        return patientName;
    }

    int getTime() const{
        return time;
    }
    
    
    double distanceTo(CovidCase case2){
        double pi = 3.14159265359;
        double lat1 = getLatitude() * (pi/180);
        double long1 = getLongitude() * (pi/180);
        double lat2 = case2.getLatitude() * (pi/180);
        double long2 = case2.getLongitude() * (pi/180);

        int R = 3960;
        double dlong = long2 - long1;
        double dlat = lat2 - lat1;
        double a = pow((sin(dlat/2)), 2) + cos(lat1) * cos(lat2) * pow((sin(dlong/2)),2);
        double c = 2 * atan2(sqrt(a), sqrt(1-a));
        double distance = R * c;
        cout<< distance<<"\n";
        return distance;
    }

    double startDistanceTo(double caseLat, double caseLong){
        double pi = 3.14159265359;
        double lat1 = getLatitude() * (pi/180);
        double long1 = getLongitude() * (pi/180);
        double lat2 = caseLat * (pi/180);
        double long2 = caseLong * (pi/180);

        int R = 3960;
        double dlong = long2 - long1;
        double dlat = lat2 - lat1;
        double a = pow((sin(dlat/2)), 2) + cos(lat1) * cos(lat2) * pow((sin(dlong/2)),2);
        double c = 2 * atan2(sqrt(a), sqrt(1-a));
        double distance = R * c;
        cout<< distance<<"\n";
        return distance;
    }

    bool operator==(const CovidCase & toCheck) const{
        if (toCheck.getLatitude() == latitude && toCheck.getLongitude() == longitude && toCheck.getAge() == patientAge && toCheck.getTime() == time && toCheck.getName().compare(patientName) == 0){
            return true;
        }
        else {
            return false;
        }
        
    }

};
    ostream & operator<<(ostream & o, const CovidCase & toPrint){
        o << "{" << toPrint.getLongitude() << ", " << toPrint.getLatitude() << ", \"" << toPrint.getName() << "\", " << toPrint.getAge() << ", " << toPrint.getTime() << "}";
        return o;
    }

    








// don't write any code below this line

#endif



