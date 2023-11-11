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
                    cout << trips[stopTime.tripId].id << "(" << stops[sourceStopId].name << " > " << stops[destStopId].name << ")" << endl;
                }
            }
        }
    }

    void findJourneysWithOneTransfer(const string& sourceid, const string& destifd) {
        cout << "Journeys with one transfer: ";
        set<string> visitedStops;

        for (const StopTime& stopTime : stopTimes) {
            if (stopTime.stopId == sourceStopId) {
                visitedStops.insert(stopTime.stopId);

                for (const StopTime& transferStopTime : stopTimes) {
                    if (transferStopTime.tripId != stopTime.tripId && transferStopTime.stopId != sourceStopId && transferStopTime.stopId != destStopId) {
                        if (visitedStops.find(transferStopTime.stopId) == visitedStops.end()) {
                            visitedStops.insert(transferStopTime.stopId);
                            cout << trips[stopTime.tripId].id << "(" << stops[sourceStopId].name << " > " << stops[transferStopTime.stopId].name << ") - "
                                << trips[transferStopTime.tripId].id << "(" << stops[transferStopTime.stopId].name << " > " << stops[destStopId].name << "), ";
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

int main(int argc, char* argv[]) {
   

    GTFSReader reader;
    reader.readStops(argv[1]);  // fie path will be provided as arguments when we run
    reader.readTrips(argv[2]);
    reader.readStopTimes(argv[3]);

    string sourceid ;
    string destid;
    cin>>sourceid;
    cin>>destid;

    reader.findDirectJourneys(sourceStopId, destid);
    reader.findJourneysWithOneTransfer(sourceid, destid);

    return 0;
}
