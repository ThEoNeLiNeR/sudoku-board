// global variables ke liye memset mat lagana, nahi toh lag jayenge
// Set is faster for insertion and deletion of elements at the middle of the container.
// Vector is faster for insertion and deletion of elements at the end of the container.
// predefine vectors size
// memset can sometimes cake your pants

#include<bits/stdc++.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<string>
#include<map>
#include<set>
#include<sstream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

using namespace std;

#define fast ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define linebreak cout<<"\n"
#define lli long long int
// const int MOD = 1000000007;
// const int N = 100005;
// const lli p = 53;
// const lli m = 1000000000000000009;
// int dx[] = {-1,-1,-1,0,0,1,1,1};
// int dy[] = {-1,0,1,-1,1,-1,0,1};

int grid[10][10];
vector<int> randSeq(81, 0);
vector<int> rowsVals[10], colsVals[10];
map<int, vector<int> > boxToVal;
map<int, vector<int> > boxToIndex;
int isFixed[10][10]; // {0->free, 1->pencil, 2->fixed}
char choice;
int val, r, c;
bool rewrite;
bool eraseCell;
lli yes = 0;


















// CHECKING VALIDITY STARTS

#define N 10

// Function to check if all elements
// of the board[][] array store
// value in the range[1, 9]
bool isinRange(int board[][N])
{

	// Traverse board[][] array
	for (int i = 1; i < N;
		i++) {
		for (int j = 1; j < N;
			j++) {

			// Check if board[i][j]
			// lies in the range
			if (board[i][j] <= 0 || board[i][j] > 9) {
				return false;
			}
		}
	}
	return true;
}

// Function to check if the solution
// of sudoku puzzle is valid or not
bool isValidSudoku(int board[][N])
{
	// Check if all elements of board[][]
	// stores value in the range[1, 9]
	if (isinRange(board)
		== false) {
		return false;
	}

	// Stores unique value
	// from 1 to N
	bool unique[N + 1];

	// Traverse each row of
	// the given array
	for (int i = 1; i < N; i++) {

		// Initiliaze unique[]
		// array to false
		memset(unique, false,
			sizeof(unique));

		// Traverse each column
		// of current row
		for (int j = 1; j < N;
			j++) {

			// Stores the value
			// of board[i][j]
			int Z = board[i][j];

			// Check if current row
			// stores duplicate value
			if (unique[Z]) {
				return false;
			}
			unique[Z] = true;
		}
	}

	// Traverse each column of
	// the given array
	for (int i = 1; i < N; i++) {

		// Initiliaze unique[]
		// array to false
		memset(unique, false,
			sizeof(unique));

		// Traverse each row
		// of current column
		for (int j = 1; j < N;
			j++) {

			// Stores the value
			// of board[j][i]
			int Z = board[j][i];

			// Check if current column
			// stores duplicate value
			if (unique[Z]) {
				return false;
			}
			unique[Z] = true;
		}
	}

	// Traverse each block of
	// size 3 * 3 in board[][] array
	for (int i = 1; i < N - 2;
		i += 3) {

		// j stores first column of
		// each 3 * 3 block
		for (int j = 1; j < N - 2;
			j += 3) {

			// Initiliaze unique[]
			// array to false
			memset(unique, false,
				sizeof(unique));

			// Traverse current block
			for (int k = 1; k < 3;
				k++) {

				for (int l = 1; l < 3;
					l++) {

					// Stores row number
					// of current block
					int X = i + k;

					// Stores column number
					// of current block
					int Y = j + l;

					// Stores the value
					// of board[X][Y]
					int Z = board[X][Y];

					// Check if current block
					// stores duplicate value
					if (unique[Z]) {
						return false;
					}
					unique[Z] = true;
				}
			}
		}
	}

	// If all conditions satisfied
	return true;
}

// CHECKING VALIDITY ENDS

















// IMPORTANT HELPER FUNCTIONS
/*
    1 -> (<=3, <=3)  2 -> (<=3, <=6)  3 -> (<=3, <=9)
    4 -> (<=6, <=3)  5 -> (<=6, <=6)  6 -> (<=6, <=9)
    7 -> (<=9, <=3)  8 -> (<=9, <=6)  9 -> (<=9, <=9)
*/

int findKey(int x, int y) {
    if(x <= 3 && y <= 3) { return 1; }
    else if(x <= 3 && y <= 6) { return 2; }
    else if(x <= 3 && y <= 9) { return 3; }
    else if(x <= 6 && y <= 3) { return 4; }
    else if(x <= 6 && y <= 6) { return 5; }
    else if(x <= 6 && y <= 9) { return 6; }
    else if(x <= 9 && y <= 3) { return 7; }
    else if(x <= 9 && y <= 6) { return 8; }
    else { return 9; }
}

pair<int, int> indexToRC(int index) {
    int r = index/9 + 1, c = index%9 + 1;
    return {r, c};
}

void print() {
    cout << "Your sudoku grid looks like this ... ('.' refers to empty cells) \n";
    
    for(int i = 1; i <= 9; i++) {
        for(int j = 1; j <= 9; j++) {
            if(grid[i][j] == 0) { cout << ". "; }
            else { cout << grid[i][j] << " "; }
        }
        linebreak;
    }
    cout << "\n .................................................. \n";
}

void init2() { // this init will give you a valid Sudoku board, but it is not necessary solvable! 

//     for(int i = 0; i < 81; i++) {
//         pair<int, int> rc = indexToRC(i);
//         int key = findKey(rc.first, rc.second);
//         boxToIndex[key].push_back(i);
//     }
//     // cout << "done .. \n";


//     for(int i = 1; i <= 9; i++) {
//         // cout << "starting  ... " << i << "\n";
//         bool visited[9];
//         for(int j = 0; j < 9; j++) { visited[j] = false; }

//         int nn = (rand()%2 == 0)?4:5;
//         vector<int> randomIndexes;

//         for(int j = 0; j < nn; j++) {
//             int index = rand()%9;
//             while(visited[index]) { index = rand()%9; }
//             randomIndexes.push_back(boxToIndex[i][index]);
//             visited[index] = true;
//         }
        
//         // for(auto itr : randomIndexes) { cout << itr << " "; }
//         // linebreak; linebreak;

//         for(auto itr : randomIndexes) {
//             pair<int, int> rc = indexToRC(itr);
//             set<int> alreadyPresent;

//             for(int j : rowsVals[rc.first]) { alreadyPresent.insert(j); }
//             for(int j : colsVals[rc.second]) { alreadyPresent.insert(j); }
//             for(int j : boxToVal[i]) { alreadyPresent.insert(j); }

//             // for(auto tr : alreadyPresent) { cout << tr << " "; } linebreak;
            
//             int mn = -1;
//             for(int j = 0; j <= 9; j++) {
//                 if(!alreadyPresent.empty() && *alreadyPresent.begin() == j) { alreadyPresent.erase(alreadyPresent.begin()); continue; }
//                 mn = j; break;
//             }

//             // cout << itr << " " << mn << "\n";

//             if(mn == -1) { randSeq[itr] = 0; }
//             else { randSeq[itr] = mn; rowsVals[rc.first].push_back(mn); colsVals[rc.second].push_back(mn); boxToVal[i].insert(mn); }
//         }

//     }

//     int cindex = 0;
//     for(int i = 1; i <= 9; i++) {
//         for(int j = 1; j <= 9; j++) {
//             grid[i][j] = randSeq[cindex++];
//             if(grid[i][j] > 0) { isFixed[i][j] = 2; }
//             else { grid[i][j] = false; }
//         }
//     }
}

bool checkCols(int col, int x) { for(int i = 1; i <= 9; i++) { if(grid[i][col] == x) { return true; } } return false; }

bool checkBoxes(int k, int x) { for(int i : boxToVal[k]) { if(i == x) { return true; } } return false; }

bool checkRows(int row, int x) { for(int i = 1; i <= 9; i++) { if(grid[row][i] == x) { return true; } } return false; }

// LOGIC STARTS
bool backtrack(int x, int y) {
    if(x == 10) { return true; }
    // cout << x << " " << y << "\n";
    vector<int> left(9);
    for(int i = 0; i < 9; i++) { left[i] = i+1; }
    random_shuffle(left.begin(), left.end());
    bool is = false;
    while(!left.empty()) {
        int el = left.back();
        // cout << "trying .. " << left.back() << "\n";
        if(checkRows(x, left.back()) || checkCols(y, left.back()) || checkBoxes(findKey(x, y), left.back())) { left.pop_back(); continue; }

        grid[x][y] = left.back();
        boxToVal[findKey(x, y)].push_back(el);
        left.pop_back();
        // cout << "goiing .. \n";
        if(y == 9) { is = backtrack(x+1, 1); }
        else { is = backtrack(x, y+1); }

        if(is) { break; }
        grid[x][y] = 0;
        boxToVal[findKey(x, y)].pop_back();
    }
    if(is) { return true; }
    return false;
}

void init() {
    
    // for(int i = 0; i < 9; i++) { v[i] = i+1; }

    // random_shuffle(v.begin(), v.end());
    // // filling the first row
    // for(int i = 1; i <= 9; i++) {
    //     grid[1][i] = v[i-1];
    //     boxToVal[findKey(1, i)].push_back(v[i]);
    // }

    //trying to fill the forthcoming rows
    
    if(backtrack(1, 1)) {}
    else { cout << "nahi chala"; }
    // print();
}
// LOGIC ENDS

void initperm() {
    vector<int> v(9);
    for(int i = 0; i < 9; i++) { v[i] = i+1; }
    random_shuffle(v.begin(), v.end());
    for(int i = 0; i < 9; i++) { grid[0][i] = v[i]; }
    bool is = true;

    while(is) {
        for(int i = 1; i < 9; i++) {
            random_shuffle(v.begin(), v.end());
            for(int j = 0; j < 9; j++) {
                grid[i][j] = v[j];
            }
        }

        if(isValidSudoku(grid)) { is = false; }
        else { yes++; }
    }

    print();
}



void getReady() {
    init(); // making a solved sudoku puzzle
    print();
    // removing random numbers

    int num = 38 + (rand()%5);
    for(int i = 1; i <= num; i++) {
        int sval = rand()%81;
        int rval = 1 + sval/9, cval = 1 + sval%9;
        while(grid[rval][cval] == 0) { sval = rand()%81; rval = 1 + sval/9; cval = 1 + sval%9; }
        int key = findKey(rval, cval); boxToVal[key].erase(find(boxToVal[key].begin(), boxToVal[key].end(), grid[rval][cval]));
        grid[rval][cval] = 0; 
    }

    for(int i = 1; i <= 9; i++) {
        for(int j = 1; j <= 9; j++) {
            if(grid[i][j] == 0) { isFixed[i][j] = 0; }
            else { isFixed[i][j] = 2; rowsVals[i].push_back(grid[i][j]); colsVals[j].push_back(grid[i][j]); }
        }
    }
}

// CLI programming :
set<int> optionsForCell(int r, int c) {

    set<int> op, retop;
    for(int i = 1; i <= 9; i++) { retop.insert(i); }

    for(int i : rowsVals[r]) { op.insert(i); }
    for(int i : colsVals[c]) { op.insert(i); }
    for(int i : boxToVal[findKey(r, c)]) { op.insert(i); }

    for(int i : op) {
        retop.erase(i);
    }

    return retop;
}

void valid(string message) {
    while(r <= 0 || r > 10 || c <= 0 || c > 10 || isFixed[r][c] == 2) {
        // cout << r << " " << c << " " << isFixed[r][c] << "\n";
        cout << "Oops! This cell not be " << message << " :(\n";
        cout << "Kindly choose another ... \n";
        
        cin >> r;
        if(r == -1) { choice = 'n'; return; }
        cin >> c;
        if(c == -1) { choice = 'n'; return; }
    }
}

void options() {
    
    cout << "Which cell do you want to fill? We'll provide some hints as well ;) ... (eg : 2 3)\n";
    cin >> r;
    if(r == -2) {
        cout << "Which cell do you want to clear? (eg : 2 3)\n";
        cin >> r >> c;
        valid("cleared");
        if(choice == 'n') { return; }
        eraseCell = true; return;
    } 
    if(r == -1) { choice = 'n'; return; }
    cin >> c;
    if(c == -1) { choice = 'n'; return; }

    
    valid("changed");
    if(choice == 'n') { return; }



    cout << "Here are some of your valid choices, choose any one ... (eg : 5)\n";
    set<int> opt = optionsForCell(r, c);
    if(isFixed[r][c] == 1) {
        rewrite = true;
        opt.insert(grid[r][c]);
    }
    if(opt.empty()) {
        cout << "Looks like there are no valid choices for this cell :( ... \n";
        cout << "You will have to rewrite some cells"; return;
    }
    for(auto itr : opt) { cout << itr; if(itr != *opt.rbegin()) { cout << ", "; } }
    linebreak;
    cin >> val;
    if(val == -1) { choice = 'n'; return; }
    
    while(opt.find(val) == opt.end()) {
        cout << "Kindly choose the correct value ... \n";
        cin >> val;
        if(val == -1) { choice = 'n'; return; }
    }

}

void testCase() {
    boxToVal.clear();
    for(int i = 0; i < 10; i++) { for(int j = 0; j < 10; j++) { grid[i][j] = 0; isFixed[i][j] = 0; } }
    getReady();
    print();

    // for(int i = 1; i <= 9; i++) {
    //     cout << i << " ";
    //     for(auto itr : boxToVal[i]) { cout << itr << " "; } cout << "\n";
    // }
    // cout << "./ ........................\n";
    // for(int i = 1; i < 10; i++) { cout << i << " "; 
    //     for(auto itr : rowsVals[i]) { cout << itr << " "; } cout << "\n";
    // }
    // cout << " ./..................... \n";
    // for(int i = 1; i < 10; i++) { cout << i << " "; 
    //     for(auto itr : colsVals[i]) { cout << itr << " "; } cout << "\n";
    // }

    // if(isValidSudoku(grid)) { yes++; }

    cout << "Hey there!\nWanna play a game of sudoku?(y/n)";
    cin >> choice;
    if(choice == 'y' || choice == 'Y') {
        cout << "You can always input -1, to abort the game....\n";
        cout << "If you wish to clear some unfixed cell, input -2 ...\n";
    }
    while(choice == 'y' || choice == 'Y') {
        rewrite = false, eraseCell = false;
        print();
        options();
        if(choice == 'n' || choice == 'N') { break; }
        int key = findKey(r, c);
        if(eraseCell) {
            rowsVals[r].erase(find(rowsVals[r].begin(), rowsVals[r].end(), grid[r][c]));
            colsVals[c].erase(find(colsVals[c].begin(), colsVals[c].end(), grid[r][c]));
            
            boxToVal[key].erase(find(boxToVal[key].begin(), boxToVal[key].end(), grid[r][c]));
            isFixed[r][c] = 0;
            grid[r][c] = 0;
            continue;
        }

        if(rewrite) {
            rowsVals[r].erase(find(rowsVals[r].begin(), rowsVals[r].end(), grid[r][c]));
            colsVals[c].erase(find(colsVals[c].begin(), colsVals[c].end(), grid[r][c]));
            boxToVal[key].erase(find(boxToVal[key].begin(), boxToVal[key].end(), grid[r][c]));
        }
        isFixed[r][c] = 1;
        grid[r][c] = val;
        rowsVals[r].push_back(val);
        colsVals[c].push_back(val);
        boxToVal[key].push_back(val);
    }
    cout << "Thanks for playing with me!!";
}

int main() {

    // auto start = chrono::steady_clock::now();
    // auto end = chrono::steady_clock::now();
    // cout << "\nElapsed time in milliseconds : "
    //     << chrono::duration_cast<chrono::milliseconds>(end - start).count()
    //     << " ms\n";
    // fast;
    // preFact[0] = 1;
    // invMod[0] = 1;
    // prePow[0] = 1;
    // for(int i = 1; i < N; i++) {
    //     preFact[i] = (i*preFact[i-1])%MOD;
    //     prePow[i] = (prePow[i-1]*p)%m;
    //     invMod[i] = (modPower(preFact[i], MOD-2, MOD))%MOD;
    // }
    int t=1;
    // cin >> t;
    auto start = chrono::steady_clock::now();
    while(t!=0) {t--;
        srand(time(0));

        testCase();
    }
    // cout << yes << "\n";
    auto end = chrono::steady_clock::now();
    cout << "\nElapsed time in milliseconds : "
        << chrono::duration_cast<chrono::milliseconds>(end - start).count()
        << " ms\n";
    return 0;
}
