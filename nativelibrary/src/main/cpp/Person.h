//
// Created by 张世东 on 2020/10/31.
//

#ifndef NATIVEAPPLICATION_PERSON_H
#define NATIVEAPPLICATION_PERSON_H

class Person {
private:
    int mAge;
    char* mName;
public:
    Person(){
    }
    int getAge() {
        return mAge;
    };

    void setAge(int age) {
        mAge = age;
    };

    void setName(char* name) {
        mName = name;
    };

    char* getName() {
        return mName;
    };
};
#endif //NATIVEAPPLICATION_PERSON_H
