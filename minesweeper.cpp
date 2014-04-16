#include <iostream>
#include <cstring>
using namespace std;

/*
    Google code jam 2014 qualification round problem C
    Desciption: https://code.google.com/codejam/contest/2974486/dashboard#s=p2
    Solution: unfortunately my solution only works for small input.
    The idea is to generate empty cell configuration using depth-first search and
    and then check if it is consistent with requirements:
    all empty cells are adjacent, each non-zero empty cell has 0 cell as a neighbour,
    all zero cells are connected together through other zero cells.
*/

int f[50][50], m, c, r, s, t = 1;
bool solve(int, int, int);
void helper(int, int);

int main()
{
    int tests;
    cin >> tests;
    while(tests--){
        cin >> r >> c >> m;
        s = r*c;
        memset(f, 0, sizeof f);
        bool solved = false;
        if(s - 1 == m){
            solved = true;
            cout << "Case #" << t << ":" << endl;
            bool click = false;
            for(int i = 0; i < r; ++i){
                for(int j = 0; j < c; ++j){
                    if(!click){
                        cout << 'c';
                        click = true;
                    }
                    else{
                        cout << '*';
                    }
                }
                cout << endl;
            }
        }
        if(!solved){
            if(solve(0,0,1)) solved = true;
        }
        if(!solved) cout << "Case #" << t << ":" << endl << "Impossible" << endl;
        t++;
    }
    return 0;
}


int ff[50][50];
int fff[50][50];

bool solve(int x, int y, int n)
{
    f[x][y] = 1;
    if(n < (s - m)){
        for(int dx = -1; dx <= 1; ++dx){
            for(int dy = -1; dy <= 1; ++dy){
                if(!dx && !dy || dx && dy) continue;
                    int nx = x + dx;
                    int ny = y + dy;
                    if( (nx < c && nx >= 0) && (ny < r && ny >= 0) ){
                        if(!f[nx][ny])
                            if(solve(nx, ny, n+1)) return true;
                    }


            }
        }

    }
    else{
        for(int i = 0; i < c; ++i){
            for(int j = 0; j < r; ++j){
                ff[i][j] = f[i][j] - 1;
            }
        }



        //mark number of mines adjacent to empty cells
        for(int i = 0; i < c; ++i){
              for(int j = 0; j < r; ++j){
                if(ff[i][j] == -1){
                    for(int dx = -1; dx <= 1; ++dx){
                        for(int dy = -1; dy <= 1; ++dy){
                            if(!dx && !dy) continue;
                            int nx = i + dx;
                            int ny = j + dy;
                            if( (nx < c && nx >= 0) && (ny < r && ny >= 0) ){
                                if(ff[nx][ny] > -1)
                                    ++ff[nx][ny];
                            }
                        }
                    }
                }
              }
        }

        //check that all empty cells adjacent to mines are also adjacent to empty cells which are not adjacent to mines
        bool disconnected = false; //if graph as a whole is disconnected
        for(int i = 0; i < c; ++i){
              for(int j = 0; j < r; ++j){
                if(ff[i][j] > 0){
                    bool connected = false; //is this cell connected with zeros
                    for(int dx = -1; dx <= 1; ++dx){
                        for(int dy = -1; dy <= 1; ++dy){
                            if(!dx && !dy) continue;
                            int nx = i + dx;
                            int ny = j + dy;
                            if( (nx < c && nx >= 0) && (ny < r && ny >= 0) ){
                                if(!ff[nx][ny]){
                                    connected = true;
                                    break;
                                }

                            }
                        }
                        if(connected) break;
                    }
                    if(!connected){
                        disconnected = true;
                        break;
                    }
                }
              }
              if(disconnected) break;
        }


        //count number of zeros
        //also put values into matrix which is then used in helper function
        int zerosCnt = 0;
        for(int i = 0; i < c; ++i){
            for(int j = 0; j < r; ++j){
                fff[i][j] = ff[i][j];
                if(fff[i][j] == 0){
                    zerosCnt++;
                }
            }
        }

        //check if zeros are all connected together
        bool connectedZeros = true;
        if(zerosCnt > 0){
            helper(0, 0);
            //check if all zeros has been connected
            int connCnt = 0;
            for(int i = 0; i < c; ++i){
                for(int j = 0; j < r; ++j){
                    if(fff[i][j] == -2){
                        connCnt++;
                    }
                }
            }
            if(zerosCnt > connCnt) connectedZeros = false;
        }






        if(!disconnected && connectedZeros){
            cout << "Case #" << t << ":" << endl;
            bool click = false;
            for(int i = 0; i < r; ++i){
                for(int j = 0; j < c; ++j){
                    if(ff[j][i] > -1){
                        if(!click && !ff[j][i]){
                            cout << 'c';
                            click = true;
                        }
                        else{
                            cout << '.';
                        }
                    }
                    else{
                        cout << '*';
                    }
                }
                cout << endl;
            }

            return true;
        }

    }
    f[x][y] = 0;
    return false;
}

//marks all interconnected zero cells from (0,0) source
void helper(int x, int y)
{
    fff[x][y] = -2;
    for(int dx = -1; dx <= 1; ++dx){
        for(int dy = -1; dy <= 1; ++dy){
            if(!dx && !dy || dx && dy) continue;
            int nx = x + dx;
            int ny = y + dy;
            if( (nx < c && nx >= 0) && (ny < r && ny >= 0) ){
                if(!fff[nx][ny]){
                    helper(nx,ny);
                }

            }
        }
    }
}
