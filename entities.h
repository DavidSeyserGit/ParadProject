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

#endif