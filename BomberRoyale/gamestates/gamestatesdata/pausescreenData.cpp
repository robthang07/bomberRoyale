#include "pausescreenData.h"

PausescreenData ::PausescreenData() {
    //adds all the different names of the buttons to the pause screen buttons
    pauseScreenElements.emplace_back("Resume");
    pauseScreenElements.emplace_back("Setting");
    pauseScreenElements.emplace_back("Main Menu");

}
