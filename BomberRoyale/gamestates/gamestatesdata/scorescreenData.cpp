#include "scorescreenData.h"

ScorescreenData ::ScorescreenData() {

    //Score screen string elements needed
    scoreScreenElements.emplace_back("Rematch");
    scoreScreenElements.emplace_back("Main Menu");
}

ScorescreenData::~ScorescreenData() {

    //Remove or delete the elements in vector
    scoreScreenElements.clear();

}
