#include "Array.h"
#include "MusCompClass.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Array::Array(){
    objects = NULL;
    size = 0;
}

Array::Array(const Array &oldArray){
    size = oldArray.getSize();
    objects = new MusCompClass[size];

    for(int i = 0; i < size; i++){
        objects[i] = oldArray.getObject(i);
    }
}

Array::~Array(){
    delete [] objects;
}

void Array::add(const MusCompClass& newObj) {
    addOnePlace();
    objects[size] = newObj;
    size++;
}

void Array::insert(const MusCompClass& newObj, int num) {
    MusCompClass *newArr = new MusCompClass[size+1];
    for (int i = 0; i < size; i++) {
        newArr[i] = objects[i];
    }
    delete [] objects;
    objects = newArr;
    int i;
    objects[size] = objects[size-1];
    for(i = size-1; i >= num; i--) {
        objects[i + 1] = objects[i];
    }
    objects[i+1] = newObj;
    size++;
}

void Array::del(){
    MusCompClass *newArr = new MusCompClass[size-1];
    for (int i = 0; i < size - 1; i++)
        newArr[i] = objects[i];
    delete [] objects;
    size--;
    objects = newArr;
}

void Array::del(int num){
    if (num < 0 || num > size) {
        cout << "Error" << endl;
        return;
    }

    MusCompClass *newArr = new MusCompClass[size-1];
    int i;

    for(i = 0; i < num; i++)
        newArr[i] = objects[i];
    for (i = i + 1; i < size; i++)
        newArr[i-1] = objects[i];

    delete [] objects;
    size--;
    objects = newArr;
}

void Array::delAll() {
    delete [] objects;
    objects = NULL;
    size = 0;
}

void Array::addOnePlace(){
    MusCompClass *newArr = new MusCompClass[size+1];
    for (int i = 0; i < size; i++)
        newArr[i] = objects[i];
    delete [] objects;
    objects = newArr;
}

const int Array::getSize() const {
    return size;
}

MusCompClass &Array::getObject(int num) const{
    if(num < 0 || num >= size) {
        cout << "Error" << endl;
        num = 0;
    }
    return objects[num];
}

MusCompClass &Array::getLastObject() const {
    return objects[size-1];
}

Array Array::sortLimit(double minFMood, double maxFMood, double minSMood, double maxSMood){
    if (minFMood < 0){
        cout << "Min first mood can't be less then 0. It changed on 0" << endl;
        minFMood = 0.0;
    }
    if (minSMood < 0){
        cout << "Min second mood can't be less then 0. It changed on 0" << endl;
        minSMood = 0.0;
    }
    if (maxFMood > 10){
        cout << "Max first mood can't be more then 10. It changed on 10" << endl;
        maxFMood = 10.0;
    }
    if (maxSMood > 10){
        cout << "Max second mood can't be more then 10. It changed on 10" << endl;
        maxSMood = 10.0;
    }

    Array middleArr, resultArr;
    mood middleMood, lastMood;
    int minNum = 0;
    double minD = 15, D;
    int newSizeArr;

    for(int i = 0; i < size; i++){
        middleMood = this->getObject(i).getMood();
        cout << middleMood.first << endl;
        if (middleMood.first >= minFMood && middleMood.first <= maxFMood &&
            middleMood.second >= minSMood && middleMood.second <= maxSMood)
            middleArr.add(this->getObject(i));
    }

    if(middleArr.getSize() == 0)
        return resultArr;


    newSizeArr = middleArr.getSize();
    if(resultArr.getSize() == 0){
        for(int i = 0; i < newSizeArr; i++){
            middleMood = middleArr.getObject(i).getMood();
            D = sqrt((0 - middleMood.first)*(0 - middleMood.first) + (0 - middleMood.second)*(0 - middleMood.second));
            if (D < minD) {
                minD = D;
                minNum = i;
            }
        }
        resultArr.add(middleArr.getObject(minNum));
        middleArr.del(minNum);
    }
    while (middleArr.getSize() != 0){
        minD = 15;
        minNum = 0;
        lastMood = resultArr.getLastObject().getMood();
        newSizeArr = middleArr.getSize();
        for(int i = 0; i < newSizeArr; i++){
            middleMood = middleArr.getObject(i).getMood();
            D = sqrt((lastMood.first - middleMood.first)*(lastMood.first - middleMood.first) + (lastMood.second - middleMood.second)*(lastMood.second - middleMood.second));
            if (D < minD) {
                minD = D;
                minNum = i;
            }
        }
        resultArr.add(middleArr.getObject(minNum));
        cout << resultArr.getLastObject().getName() << endl;
        middleArr.del(minNum);
    }





}

void Array::fromFile(const string& nameFile){

    string author, name, fMoodS, sMoodS;
    double fMood, sMood;

    ifstream file(nameFile);

    if (!file) {
        cout << "File not found" << endl;
    } else {
        while(!file.eof()){
            getline(file, author);
            getline(file, name);
            getline(file, fMoodS);
            getline(file, sMoodS);
            stringstream promF(fMoodS), promS(sMoodS);
            promF >> fMood;
            promS >> sMood;
            MusCompClass obj(name, author, {fMood, sMood});
            this->add(obj);
        };
        file.close();
    }
}