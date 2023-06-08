#ifndef ENTITIES_H
#define ENTITIES_H

#pragma once


class entities{
public:

protected:
virtual int getXglo() = 0;
virtual int getYglo() = 0;
virtual bool playerDetection(int PlayerX, int PlayerY);
protected:
private:
};

#endif