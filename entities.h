#ifndef ENTITIES_H
#define ENTITIES_H

#pragma once


class entities{
public:
    virtual ~entities(){}
    virtual int getXglo() = 0;
    virtual int getYglo() = 0;
    virtual bool playerDetection(int PlayerX, int PlayerY) = 0;

protected:

protected:
private:
};

class Camel: public entities{
public:
    Camel(int, int);
    virtual ~Camel();

    bool playerDetection(int PlayerX, int PlayerY) override;

    int getXglo() override {return  xGlo;}
    int getYglo() override {return yGlo;}
    int getAge() {return age;}

protected:
    void init();
    int xGlo;
    int yGlo;
    const int xLoc = 1;
    const int yLoc = 1;
    int age;
};

#endif