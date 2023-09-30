#ifndef COVIDCASE_H
#define COVIDCASE_H

#include <iostream>
#include <cmath>
#include <math.h>
using std::ostream;
using std::cout;
using std::string;

// TODO: your code  goes here
class CovidCase {
    private:
    double longitude; 
    double latitude; 
    string patientName;
    int patientAge;
    int tested;

    public:
    CovidCase(double nlatitude, double nlongitude, const string pname, const int page, int ptested)
    : latitude(nlatitude), longitude(nlongitude), patientName(pname), patientAge(page), tested(ptested) 
    {
    }
    const double & getLongitude() const{
        return longitude;
    }
    const double & getLatitude() const{
        return latitude;
    }

    const int & getPatientAge() const{
        return patientAge;
    }

    const string & getPatientName() const{
        return patientName;
    }

    const int & getTested() const{
        return tested;
    }
    
    
    double distanceTo(CovidCase case2){
        double pi = 3.142;
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
        cout<<distance;
        return distance;
    }
};
    ostream & operator<<(ostream & o, const CovidCase & toPrint){
        o << "{" << toPrint.getLatitude() << ", " << toPrint.getLongitude() << ", \"" << toPrint.getPatientName() << "\", " << toPrint.getPatientAge() << ", " << toPrint.getTested() << "}";
        return o;
    }


// don't write any code below this line

#endif

