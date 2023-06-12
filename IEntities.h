//
// Created by david on 05.06.2023.
// last edit: 11.06.2023

#ifndef IENTITIES_H
#define IENTITIES_H

#pragma once


class IEntities{
public:
    virtual ~IEntities(){}
    virtual int getXglo() = 0;
    virtual int getYglo() = 0;
    virtual bool playerDetection(int, int) = 0;

protected:

protected:
private:
};

class Camel: public IEntities{
public:
    Camel(int, int);
    virtual ~Camel();

    bool playerDetection(int CamelPosX, int CamelPosY) override; //currently in world.cpp as Cameldetection,can later be put here

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