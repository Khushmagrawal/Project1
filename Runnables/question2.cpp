/*Modern routing platforms like Google Maps use routing engines to plan passenger journeys. These engines
use timetable information in the GTFS format (refer reference guide) to find possible journeys between
a starting point and a destination. In this context, a ”stop” refers to a specific location where public
transportation vehicles, such as buses or trains, pick up or drop off passengers. Each stop is identified
by a unique stop ID, and a ”route” represents a specific path taken by a transportation vehicle.

The code reads the input GTFS data (input data) and takes two command-line inputs, the source stop ID and
the destination stop ID. The code prints all possible direct journeys and journeys with one transfer.*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

struct Stop {
    string id;
    string name;
};

struct Trip {
    string id;
    string routeId;
};

struct StopTime {
    string tripId;
    string stopId;
};

struct Transfer {
    string fromStopId;
    string toStopId;
};

class GTFSReader {
public:
    void readStops(const string& stopsFile) {
        ifstream file(stopsFile);
        string line;
        getline(file, line);        // To skip the first line

        while (getline(file, line)) {
            stringstream ss(line);
            string id, name;
            getline(ss, id, ',');    // To get the value of 'id' till it encounter ','
            getline(ss, name, ',');  // Same as above for name

            stops[id] = {id, name}; // Stores the result to fill the map 'stops' at line 117
        }
        file.close();
    }

    void readTrips(const string& tripsFile) {
        ifstream file(tripsFile);
        string line;
        getline(file, line); // Skip header

        while (getline(file, line)) {
            stringstream ss(line);
            string routeId, serviceId, tripId, headsign, shortName;
            getline(ss, routeId, ',');
            getline(ss, serviceId, ',');
            getline(ss, tripId, ',');
            getline(ss, headsign, ',');
            getline(ss, shortName, ',');

            trips[tripId] = {tripId, routeId};
        }
        file.close();
    }

    void readStopTimes(const string& stopTimesFile) {
        ifstream file(stopTimesFile);
        string line;
        getline(file, line); 

        while (getline(file, line)) {
            stringstream ss(line);
            string tripId, stopId;
            getline(ss, tripId, ',');
            getline(ss, stopId, ',');

            stopTimes.push_back({tripId, stopId});
        }
        file.close();
    }

    void findDirectJourneys(const string& sourceid, const string& destid) {
        cout << "Direct journeys: ";
        for (const StopTime& stopTime : stopTimes) {
            if (stopTime.stopId == destid) {
                if (stops[stopTime.stopId].name == stops[sourceid].name) {
                    cout << trips[stopTime.tripId].id << "(" << stops[sourceid].name << " > " << stops[destid].name << ")" << endl;
                }
            }
        }
    }

    void findJourneysWithOneTransfer(const string& sourceid, const string& destifd) {
        cout << "Journeys with one transfer: ";
        set<string> visitedStops;

        for (const StopTime& stopTime : stopTimes) {
            if (stopTime.stopId == sourceid) {
                visitedStops.insert(stopTime.stopId);

                for (const StopTime& transferStopTime : stopTimes) {
                    if (transferStopTime.tripId != stopTime.tripId && transferStopTime.stopId != sourceid && transferStopTime.stopId != destid) {
                        if (visitedStops.find(transferStopTime.stopId) == visitedStops.end()) {
                            visitedStops.insert(transferStopTime.stopId);
                            cout << trips[stopTime.tripId].id << "(" << stops[sourceid].name << " > " << stops[transferStopTime.stopId].name << ") - "
                                << trips[transferStopTime.tripId].id << "(" << stops[transferStopTime.stopId].name << " > " << stops[destid].name << "), ";
                        }
                    }
                }
            }
        }
        cout << endl;
    }

private:
    unordered_map<string, Stop> stops;
    unordered_map<string, Trip> trips;
    vector<StopTime> stopTimes;        //Vector to maintain the order of stop times
};

int main( char* argv[]) {
   

    GTFSReader reader;
    reader.readStops(argv[1]);  // fie path will be provided as arguments when we run
    reader.readTrips(argv[2]);
    reader.readStopTimes(argv[3]);

    string sourceid ;
    string destid;
    cin>>sourceid;
    cin>>destid;

    reader.findDirectJourneys(sourceid, destid);
    reader.findJourneysWithOneTransfer(sourceid, destid);

    return 0;
}
