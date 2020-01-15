#include <json/json.h>
#include <iostream>
#include <fstream>
#include "highscores.h"

Highscores::~Highscores() {
    //Cleared the vector to be sure
    vectorOfHighscores.clear();
}

void Highscores::writeToJson(const std::string& filename) {

    //Root, value to store the json text in.
    Json::Value root;

    for (int i = 0; i < vectorOfHighscores.size(); ++i) {
        root["highscore"][std::to_string(i)]["name"] = vectorOfHighscores.at(i)->name;
        root["highscore"][std::to_string(i)]["score"] = vectorOfHighscores.at(i)->score;
    }

    //Setting up the write builder
    Json::StreamWriterBuilder wbuilder;

    // Configure the Builder
    std::string outputConfig = Json::writeString(wbuilder, root);

    //The out put stream to file
    std::ofstream streamWriter;
    streamWriter.open(filename);
    streamWriter << outputConfig;
    streamWriter.close();

}

bool Highscores::readFromJson(const std::string& filename) {

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

    //For each loop. Every objects that is inside highscore
    for (Json::Value& high: root["highscore"]) {
        //Make a stats struct to hold the values.
        stats *h = new stats;
        //Set the stats, name and score
        h->name = high["name"].asCString();
        h->score =high["score"].asCString();
        //Add them to the vector the highscore have over them so we easly can use them.
        vectorOfHighscores.emplace_back(h);
    }

    file.close();

    return true;
}
