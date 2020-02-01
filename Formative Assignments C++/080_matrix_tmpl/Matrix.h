#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;
//YOUR CODE GOES HERE!
template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  vector<T> ** rows;

 public:
  Matrix() : numRows(0), numColumns(0), rows(NULL) {}
  Matrix(int r, int c) : numRows(r), numColumns(c), rows(new vector<T> *[r]) {
    for (int i = 0; i < r; i++) {
      rows[i] = new vector<T>(c);
    }
  }
  Matrix(const Matrix & rhs) :
      numRows(rhs.numRows),
      numColumns(rhs.numColumns),
      rows(new vector<T> *[rhs.numRows]) {
    for (int i = 0; i < numRows; i++) {
      rows[i] = new vector<T>(numColumns);
    }

    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        (*this)[i][j] = rhs[i][j];
      }
    }
  }

  ~Matrix() {
    for (int i = 0; i < numRows; i++) {
      delete rows[i];
    }
    delete[] rows;
  }

  Matrix & operator=(const Matrix & rhs) {
    if (this != &rhs) {
      numRows = rhs.numRows;
      numColumns = rhs.numColumns;
      vector<T> ** temp = new vector<T> *[rhs.numRows];

      for (int i = 0; i < numRows; i++) {
        temp[i] = new vector<T>(numColumns);
        *(temp[i]) = *(rhs.rows[i]);
      }

      delete[] rows;
      rows = temp;
    }
    return *this;
  }

  int getRows() const { return numRows; }
  int getColumns() const { return numColumns; }
  const vector<T> & operator[](int index) const {
    assert(index >= 0 && index < numRows);
    return *rows[index];
  }
  vector<T> & operator[](int index) {
    assert(index >= 0 && index < numRows);
    return *rows[index];
  }
  bool operator==(const Matrix & rhs) const {
    if (numRows != rhs.numRows || numColumns != rhs.numColumns) {
      return false;
    }
    else {
      for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numColumns; j++) {
          if ((*this)[i][j] != rhs[i][j]) {
            return false;
          }
        }
      }
    }
    return true;
  }

  Matrix operator+(const Matrix & rhs) const {
    assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
    Matrix ans(numRows, numColumns);
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        ans[i][j] = (*this)[i][j] + rhs[i][j];
      }
    }
    return ans;
  }
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  s << "[ ";
  for (int i = 0; i < rhs.getRows() - 1; i++) {
    s << rhs[i] << ",\n";
  }
  if (rhs.getRows() > 0) {
    s << rhs[rhs.getRows() - 1] << " ]";
  }
  else {
    s << "]";
  }
  return s;
}

template<typename T>
std::ostream & operator<<(std::ostream & s, const vector<T> & rhs) {
  s << "{";
  for (size_t i = 0; i < rhs.size(); i++) {
    s << rhs[i];
    if (i != rhs.size() - 1) {
      s << ", ";
    }
  }
  s << "}";
  return s;
}

#endif
