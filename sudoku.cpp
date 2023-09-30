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
map<int, set<int> > boxToVal;
map<int, vector<int> > boxToIndex;
int isFixed[10][10]; // {0->free, 1->pencil, 2->fixed}
char choice;
int val, r, c;
bool rewrite;
bool eraseCell;

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

void makeValid(int index) {
    // pair<int, int> rc = indexToRC(index);
    // int key = findKey(rc.first, rc.second);

    // vector<int> cnt(10, 0);
    
    // for(auto rtr : rowsVals[rc.first]) { cnt[rtr]++; }

    // for(auto ctr : colsVals[rc.second]) { cnt[ctr]++; }

    // for(auto btr : mpToBoxes[key]) { cnt[btr]++; }

    // int before = randSeq[index];
    // if(cnt[randSeq[index]] > 1) {
    //     for(int i = 1; i < 10; i++) {
    //         if(cnt[i] == 0) { randSeq[index] = i; cnt[i]++; break; }
    //     }
    //     if(cnt[randSeq[index]] > 1) {
    //         randSeq[index] = 0;
    //     }
    //     auto itr = find(rowsVals[rc.first].begin(), rowsVals[rc.first].end(), before);
    //     if(itr != rowsVals[rc.first].end()) { rowsVals[rc.first].erase(itr); }
    //     itr = find(colsVals[rc.second].begin(), colsVals[rc.second].end(), before);
    //     if(itr != colsVals[rc.second].end()) { colsVals[rc.second].erase(itr); }
    //     itr = find(mpToBoxes[key].begin(), mpToBoxes[key].end(), before);
    //     if(itr != mpToBoxes[key].end()) { mpToBoxes[key].erase(itr); }


    //     rowsVals[rc.first].push_back(randSeq[index]);
    //     colsVals[rc.second].push_back(randSeq[index]);
    //     mpToBoxes[key].push_back(randSeq[index]);
    // }

}

void init() {

    // int numOfBoxesToBeFilled = 38 + (rand()%5);
    // cout << numOfBoxesToBeFilled << "\n \n";
    // for(int i = 0; i < numOfBoxesToBeFilled; i++) {
    //     int val = rand()%10;
    //     while(val == 0) { val = rand()%10; };
    //     randSeq[i] = val;
    // }

    // random_shuffle(randSeq.begin(), randSeq.end());

    // for(int i = 0; i < 81; i++) {
    //     pair<int, int> rc = indexToRC(i);
    //     mpToBoxes[findKey(rc.first, rc.second)].push_back(randSeq[i]);
    //     rowsVals[rc.first].push_back(randSeq[i]);
    //     colsVals[rc.second].push_back(randSeq[i]);
    // }

    // for(int i = 0; i < 81; i++) {
    //     if(randSeq[i] != 0) {
    //         makeValid(i);
    //     }
    // }

    // int cindex = 0;
    // for(int i = 1; i <= 9; i++) {
    //     for(int j = 1; j <= 9; j++) {
    //         grid[i][j] = randSeq[cindex++];
    //     }
    // }
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
    // cout << "\n .................................................. \n";
}

void init2() { // this init will give you a valid Sudoku board, but it is not necessary solvable! 

    for(int i = 0; i < 81; i++) {
        pair<int, int> rc = indexToRC(i);
        int key = findKey(rc.first, rc.second);
        boxToIndex[key].push_back(i);
    }
    // cout << "done .. \n";


    for(int i = 1; i <= 9; i++) {
        // cout << "starting  ... " << i << "\n";
        bool visited[9];
        for(int j = 0; j < 9; j++) { visited[j] = false; }

        int nn = (rand()%2 == 0)?4:5;
        vector<int> randomIndexes;

        for(int j = 0; j < nn; j++) {
            int index = rand()%9;
            while(visited[index]) { index = rand()%9; }
            randomIndexes.push_back(boxToIndex[i][index]);
            visited[index] = true;
        }
        
        // for(auto itr : randomIndexes) { cout << itr << " "; }
        // linebreak; linebreak;

        for(auto itr : randomIndexes) {
            pair<int, int> rc = indexToRC(itr);
            set<int> alreadyPresent;

            for(int j : rowsVals[rc.first]) { alreadyPresent.insert(j); }
            for(int j : colsVals[rc.second]) { alreadyPresent.insert(j); }
            for(int j : boxToVal[i]) { alreadyPresent.insert(j); }

            // for(auto tr : alreadyPresent) { cout << tr << " "; } linebreak;
            
            int mn = -1;
            for(int j = 0; j <= 9; j++) {
                if(!alreadyPresent.empty() && *alreadyPresent.begin() == j) { alreadyPresent.erase(alreadyPresent.begin()); continue; }
                mn = j; break;
            }

            // cout << itr << " " << mn << "\n";

            if(mn == -1) { randSeq[itr] = 0; }
            else { randSeq[itr] = mn; rowsVals[rc.first].push_back(mn); colsVals[rc.second].push_back(mn); boxToVal[i].insert(mn); }
        }

    }

    int cindex = 0;
    for(int i = 1; i <= 9; i++) {
        for(int j = 1; j <= 9; j++) {
            grid[i][j] = randSeq[cindex++];
            if(grid[i][j] > 0) { isFixed[i][j] = 2; }
            else { grid[i][j] = false; }
        }
    }
}


// void init3() { // this will give you a valid board which is solvable! 
//     // basically fill the entire grid with the answer
//     // and then remove some random elements
       // did this in the optimal sudoku file
//     for(int i = 1; i <= 9; i++) {
//         if(backtrack(1, 1, i)) { break; }
//     }
// }

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
        cout << "Oops! This cell not be " << message << " :(\n";
        cout << "Kindly choose another ... \n";
        
        cin >> r;
        if(r == -1) { choice = 'n'; return; }
        cin >> c;
        if(c == -1) { choice = 'n'; return; }
    }
}

void options() {
    
    cout << "Which cell do you want to fill? We'll provide some hints as well ;) ... (eg : 2,3)\n";
    cin >> r;
    if(r == -2) {
        cout << "Which cell do you want to clear? (eg : 2,3)\n";
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
    init2();
    
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

        if(eraseCell) {
            rowsVals[r].erase(find(rowsVals[r].begin(), rowsVals[r].end(), grid[r][c]));
            colsVals[c].erase(find(colsVals[c].begin(), colsVals[c].end(), grid[r][c]));
            boxToVal[findKey(r, c)].erase(grid[r][c]);
            isFixed[r][c] = 0;
            grid[r][c] = 0;
            continue;
        }

        if(rewrite) {
            rowsVals[r].erase(find(rowsVals[r].begin(), rowsVals[r].end(), grid[r][c]));
            colsVals[c].erase(find(colsVals[c].begin(), colsVals[c].end(), grid[r][c]));
            boxToVal[findKey(r, c)].erase(grid[r][c]);
        }
        isFixed[r][c] = 1;
        grid[r][c] = val;
        rowsVals[r].push_back(val);
        colsVals[c].push_back(val);
        boxToVal[findKey(r, c)].insert(val);
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
    while(t!=0) {t--;
        srand(time(0));
        testCase();
    }
    return 0;
}
