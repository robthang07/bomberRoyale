#ifndef BOMBER_ROYALE_CREDITS_H
#define BOMBER_ROYALE_CREDITS_H

#include <string>

class Credits {
public:
    /**
     * Read the credits from the file.
     *
     * @param filename is the path to the file
     */
    bool readFromJson(const std::string& filename);

    /**
     * Return the credits text
     * @return credits text in a string.
     */
    std::string getText(){
        return text;
    }

protected:
    std::string text;
};


#endif //BOMBER_ROYALE_CREDITS_H
