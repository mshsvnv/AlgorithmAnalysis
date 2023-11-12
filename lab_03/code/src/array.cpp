#include "../inc/array.h"

ostream& operator<<(ostream& out, const ArrayT& arr) {
    
    int len = arr.size();

    for (int i = 0; i < len; ++i)
        out << arr[i] << " ";
    
    out << "\n";

    return out;
}

ArrayT::ArrayT(const char* fileName) {

    ifstream file(fileName);
    string line;

    int curElem = 0, idx = 0;

    if (file.is_open() && file.good()) {
        
        while (getline(file, line)) {

            stringstream curRow(line);

            vector<int> tmp;

            while(1) {

                curRow >> curElem;

                if (!curRow)
                    break;
                
                idx++;
                tmp.emplace_back(curElem);
            }

            _arr = tmp;
        }
    }
}

int& ArrayT::operator[](int ind) {
    return _arr[ind];
}

int ArrayT::operator[](int ind) const {
    return _arr[ind];
}

ArrayT ArrayT::operator+(const ArrayT& other) {

    int size1 = this->size(),
        size2 = other.size();

    ArrayT res(size1 + size2);

    for (int i = 0; i < this->size(); i++)
        res[i] = (*this)[i];

    for (int i = 0; i < other.size(); i++)
        res[i + size1] = other[i];

    return res;
}

ArrayT::ArrayT(int len, int num) {
    _arr.resize(len, num);
}

void ArrayT::randomFill() {
    
    int len = size();

    for (int i = 0; i < len; ++i)
        _arr[i] = rand() % 100 - 100;
}

void ArrayT::ascFill() {
    
    int len = size();

    for (int i = 0; i < len; ++i)
        _arr[i] = i;
}

void ArrayT::descFill() {
    
    int len = size();

    for (int i = 0; i < len; ++i)
        _arr[i] = len - i;
}