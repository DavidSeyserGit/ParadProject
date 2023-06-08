//
// Created by rapha on 06.04.2023.
//

#ifndef PARADProjekt_PATCH_H
#define PARADProjekt_PATCH_H


class patch {
public:
    patch(); //default
    virtual ~patch() {}
    void printRow(int, int, int);
    bool addCoin();

	int build(int); // new build func.

    bool getIsOasis() const{return this->isOasis;}
    bool getHasCity() const{return this->hasCity;}
    int getMills() const{return this->mills;}
    int getFields() const{return this->fields;}
    //void addBuilding(int);      //int represents the building type
protected:
private:
    void init();
    enum CONTENT { DESERT, PLAIN , CITY , MILL , FIELD , OASIS , COIN, PLAYER, CAMEL};
    const char symbols[9] = {'~', ' ','H', static_cast<char>(207), static_cast<char>(178), static_cast<char>(254), '$', 'i', 'm' };
    const int colors[9] = {239, 32,32,32,46, 41, 224, 12, 230};

	const int prices[4] = {0,-8, -4,-2}; 	//(0) nothing, city, mill, field

    bool isOasis;
    int patchMap[3][3] = {PLAIN,PLAIN,PLAIN,PLAIN,PLAIN,PLAIN,PLAIN,PLAIN,PLAIN};
    bool hasCity;
    int mills;	//counts number of mills present
    int fields;	//counts number of fields present
    int paCoins;
    bool coinMap[3][3] = {false, false, false,false, false, false,false, false, false}; //"if coin = true"
    static int gloOasis; //counts number of global oasis present
	int income = 0; 
};


#endif //PARADProjekt_PATCH_H
