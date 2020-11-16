#ifndef L1_MUSCOMPCLASS_H
#define L1_MUSCOMPCLASS_H

#include <string>

using namespace std;

struct mood{
    double first;
    double second;
};

class MusCompClass {
public:
    MusCompClass() = default;
    MusCompClass(const string& newName, const string& newAuthor, const mood& newMood);
    MusCompClass(const MusCompClass& existMusic);

    [[nodiscard]] const string& getName()const;
    [[nodiscard]] const string& getAuthor()const;
    [[nodiscard]] const mood& getMood() const;

    void setName(const string& newName);
    void setAuthor(const string& newAuthor);
    void setMood(const mood& newMood);
    void setMood(const double& fMood, const double& sMood);
    bool equalObj(const MusCompClass& secondObj);
private:
    string musicName {"no name"};
    string musicAuthor {"no author"};
    mood musicMood{0.0, 0.0};
};


#endif //L1_MUSCOMPCLASS_H
