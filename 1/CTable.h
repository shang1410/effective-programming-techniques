//
// Created by XYZ on 18.10.2025.
//

#ifndef TEP_ZAD4_H
#define TEP_ZAD4_H

#include <iostream>


class CTable {
    public:
        CTable();
        CTable(std::string sName, int iTableLen);
        CTable(const CTable &pcOther);
        ~CTable();
        void vSetName(std::string sName);
        bool bSetNewSize(int iTableLen);
        CTable* pcClone();
        void vPrint();

    private:
        std::string sName;
        int* piTable;
        int iTableLen;
};

void vModTab(CTable* pcTab, int iNewSize);
void vModTab(CTable cTab, int iNewSize);

#endif //TEP_ZAD4_H