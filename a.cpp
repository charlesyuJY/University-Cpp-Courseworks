#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <vector>


bool valid_sudoku(const std::vector<int>& g);
bool check_sequence(const std::vector<int>& v);
int mfind(int n, const std::vector<int>& v);

void extract_row(int r, const std::vector<int>& in, std::vector<int>& out);
void extract_col(int c, const std::vector<int>& in, std::vector<int>& out);
void extract_subsq(int subs, const std::vector<int>& in, std::vector<int>& out);

int xytoi(int x, int y, int rowlen);



int main(){

    std::vector<int> s;

    // we are going to represent the sudoku as a one dimensional vector
    // linearised by row, for instance the 4x4 sudoku in the readme will be
    // represented as: 1 2 3 4 4 1 2 76 4 4 4 1 9 4 1 -7

    // begin of block of code reading the sudoku from the text file
    std::string filename;

    std::cout << "please enter name of file containing the sudoku" << std::endl;
    std::cin >> filename;

    std::ifstream infile;
    infile.open(filename.c_str());

    if(!infile.is_open()){
        std::cout << "error, can't open input file" << std::endl;
        exit(EXIT_FAILURE);
    }

    int tmp;

    while(infile >> tmp){
        s.push_back(tmp);
    }
    // end of block of code reading the sudoku from the text file
    // we now have the content of the sudoku in vector s

    int side = std::sqrt(s.size());
    // assuming it is a valid square grid in terms of size
    // (if it isn't, the program will not work properly, which is expected)

    // printing the content of the sudoku (as a square);
    // the sudoku is stored as a one-dimensional vector
    // but the vector can be indexed using two indices
    // by converting the indices of a two dimensional representation
    // into the corresponding one-dimensional index (using our function xytoi)

    for(int i = 0; i < side; i++){
        for(int j = 0; j < side; j++){
            std::cout << s[xytoi(i,j,side)] << " ";
        }
        std::cout << std::endl;
    }

    // calling the function checking if the sudoku is a valid one:

    bool valid = valid_sudoku(s);

    if(valid){
        std::cout << "valid" << std::endl;
    }
    else{
        std::cout << "not valid" << std::endl;
    }

    return 0;
}

// function xytoi maps two-dimensional indices to a one-dimensional one
// it takes in input:
// - the two indices x and y of a two dimensional data structure
// - the length of the row, rowlen
// it returns:
// - the corresponding one-dimensional index

int xytoi(int x, int y, int rowlen){
    return x*rowlen+y;
}

// function valid_sudoku
// takes in input:
// - a one dimensional vector representing a sudoku
// returns:
// - a boolean which is true if the sudoku is valid and false if it isn't valid

// write your code where indicated
// i.e. within the two remaining incomplete `for' loops
// do not alter anything else

bool valid_sudoku(const std::vector<int>& g){
    int side = std::sqrt(g.size());

    // for each row...
    for(int i = 0; i < side; i++){
        std::vector<int> row;
        extract_row(i, g, row);

     if(!check_sequence(row)){
            return false;
        }
    }

    // for each column...
    for(int i = 0; i < side; i++){
      std::vector<int> column;
      extract_col(i,g,column);

      if(!check_sequence(column)){
        return false;
      }
        // write your code here
    }

    // for each subsquare...
    for(int i = 0; i < side; i++){
     std::vector<int> subsquare;
     extract_subsq(i,g,subsquare);

     if(!check_sequence(subsquare)){
       return false;
     }
       // write your code here
    }

    // if the program execution gets to here it means that
    // it hasn't executed a "return false" above
    // so the sudoku is valid:

    return true;
}


// function mfind
// takes in input:
// - a vector of integers v
// - an integer n
// returns:
// the index of the element n in v, if n is in v
// -1 if n is not in v
// for instance:
// v: 3 2 5; n: 2 | return: 1
// v: 3 1 2; n: -6 | return: -1
// v: 1 1 -12 1 5; n: 5 | return: 4

int mfind(int n, const std::vector<int>& v){
  for(int i=0;i<v.size();i++){
    if(n== v[i]){
      return i;
    }
  }
  return  -1;
    // write your code here
}

// function check_sequence
// takes in input:
// - a vector of integers v
// returns:
// - true if v contains all the numbers from 1 to v.size() and false otherwise
// for instance:
// v: 3 2 5 | return: false
// v: 3 1 2 | return: true
// v: 1 1 -12 1 5 | return: false
// note that check_sequence should call mfind
bool check_sequence(const std::vector<int>& v){
  for(int i=1; i<= v.size();i++){
      if(mfind(i,v)== -1){
        return false;
      }
      }
      return true;
    // write your code here
}

// note that all the following functions should call function xytoi

// function extract_row
// takes in input:
// - a row index r
// - a one dimensional vector `in' representing a sudoku
// provides in output:
// - a vector out containing the r-th row of in
// for example:
// r: 0; in: 1 2 3 4 4 1 2 76 4 4 4 1 9 4 1 -7 | out: 1 2 3 4
// r: 3; in: 1 2 3 4 4 1 2 76 4 4 4 1 9 4 1 -7 | out: 9 4 1 -7
void extract_row(int r, const std::vector<int>& in, std::vector<int>& out){
  int r_len=std::sqrt(in.size());

  for(int i=0; i<r_len;i++){
    out.push_back(in[xytoi(r,i,r_len)]);
  }
    // write your code here
}

// function extract_col
// like extract_row but for columns
// for example:
// c: 0; in: 1 2 3 4 4 1 2 76 4 4 4 1 9 4 1 -7 | out: 1 4 4 9
void extract_col(int c, const std::vector<int>& in, std::vector<int>& out){
  int c_len=std::sqrt(in.size());

  for(int i=0; i<c_len;i++){
    out.push_back(in[xytoi(i,c,c_len)]);
  }
    // write your code here
}

// function extract_subsq
// like the two functions above but for subsquares
// we consider subsquares to be indexed from left to right
// and then from top to bottom
// for example:
// subs: 0; in: 1 2 3 4 4 1 2 76 4 4 4 1 9 4 1 -7 | out: 1 2 4 1
// subs: 1; in: 1 2 3 4 4 1 2 76 4 4 4 1 9 4 1 -7 | out: 3 4 2 76
// subs: 2; in: 1 2 3 4 4 1 2 76 4 4 4 1 9 4 1 -7 | out: 4 4 9 4
// subs: 3; in: 1 2 3 4 4 1 2 76 4 4 4 1 9 4 1 -7 | out: 4 1 1 -7
void extract_subsq(int subs, const std::vector<int>& in, std::vector<int>& out){

  int square_len = std::sqrt(in.size());
  int subs_len = std::sqrt(square_len);
  int remainder;
  int quotient;

  remainder = subs%subs_len;
  quotient = subs/subs_len;

    for(int j = 0;j<subs_len;j++){
    for(int i = 0;i<subs_len;i++){
        out.push_back(in[xytoi(remainder,i,subs_len)+(subs_len*square_len*quotient)+(j *square_len)]);
      }
    }

    // write your code here
}
