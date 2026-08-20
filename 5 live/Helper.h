#include <iostream>
#include <vector>
#include <tuple>
#include <unordered_set>
#include <unordered_map>
#include "MySmartPointer.h"
#include "Product.h"

using namespace std;

tuple<int, int, int> countErrors(const vector<MySmartPointer<Product>>& list);

