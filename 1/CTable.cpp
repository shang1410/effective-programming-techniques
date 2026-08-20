#include "CTable.h"
#include "Constans.h"
#include <iostream>

CTable::CTable() {
    sName = DEFAULT_NAME;
    iTableLen = DEFAULT_SIZE;
    piTable = new int[iTableLen];
    std::cout << "bezp: '" << sName << "'\n";
}

CTable::CTable(std::string sName, int iTableLen) {
    this->sName = sName;
    this->iTableLen = iTableLen;
    piTable = new int[iTableLen];
    std::cout << "parametr: '" << sName << "'\n";
}

CTable::CTable(const CTable &pcOther) {
    sName = pcOther.sName + "_copy";
    iTableLen = pcOther.iTableLen;
    piTable = new int[iTableLen];
    for (int i = 0; i < iTableLen; i++) {
        piTable[i] = pcOther.piTable[i];
    }
    std::cout << "kopiuj: '" << sName << "'\n";
}

CTable::~CTable() {
    std::cout << "usuwam: '" << sName << "'\n";
    delete[] piTable;
}

void CTable::vSetName(std::string sName) {
    this->sName = sName;
}

bool CTable::bSetNewSize(int iNewLen) {
    if (iNewLen <= 0) {
        return false;
    }

    int* newTable = new int[iNewLen];

    int minLen;
    if (iNewLen < iTableLen) {
        minLen = iNewLen;
    } else {
        minLen = iTableLen;
    }

    for (int i = 0; i < minLen; i++) {
        newTable[i] = piTable[i];
    }

    delete[] piTable;
    piTable = newTable;
    iTableLen = iNewLen;
    return true;
}

CTable* CTable::pcClone() {
    return new CTable(*this);
}

void CTable::vPrint() {
    std::cout << "Nazwa: " << sName << ", Rozmiar: " << iTableLen << "\n";
}

void vModTab(CTable* pcTab, int iNewSize) {
    pcTab->bSetNewSize(iNewSize);
}

void vModTab(CTable cTab, int iNewSize) {
    cTab.bSetNewSize(iNewSize);
}