#include <json/json.h>
#include <fstream>
#include "credits.h"

bool Credits::readFromJson(const std::string &filename) {

    //Root, value to store the json text in
    Json::Value root;

    //Reader for the file
    Json::Reader reader;

    // Stream used for reading the data file.
    std::ifstream file(filename);

    // Read data from file into root objects
    bool parsingSuccessful = reader.parse(file, root);

    // Check for success
    if (!parsingSuccessful) {
        return false;
    }
    
    int nr = 0;

    //For each loop. Every objects that is inside credits
    for (Json::Value& creditObject: root["credits"]) {

        text +=  ((std::string) root["credits"].getMemberNames().at(nr)) + ":\n" + creditObject.asCString() + "\n\n";
        nr++;

    }

    file.close();

    return true;

}