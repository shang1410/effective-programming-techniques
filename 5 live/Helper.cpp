#include "Helper.h"

tuple<int, int, int> countErrors(const vector<MySmartPointer<Product>>& list) {
    unordered_set<string> dict;
    unordered_map<string, int> refCounts;
    int totalLost = 0;

    for (size_t i = 0; i < list.size(); i++) {
        string desc = list[i].getObjectPointer()->getDescription();
        dict.insert(desc);

        int refCount = list[i].getRefCount() - 1;

        if (refCounts.find(desc) == refCounts.end() || refCounts[desc] < refCount) {
            refCounts[desc] = refCount;
        }
    }

    int productsWithLostInstructions = 0;

    unordered_map<string, int>::iterator it;
    for (it = refCounts.begin(); it != refCounts.end(); ++it) {
        string productDesc = it->first;
        int refCount = it->second;

        /*cout << productDesc << endl;
        cout << refCount << endl;*/


        int onList = 0;
        for (size_t j = 0; j < list.size(); j++) {
            if (list[j].getObjectPointer()->getDescription() == productDesc) {
                onList++;
            }
        }

        int lost = refCount - onList;
        if (lost > 0) {
            totalLost += lost;
            productsWithLostInstructions++;
        }
    }

    return make_tuple(dict.size(), totalLost, productsWithLostInstructions);
}
