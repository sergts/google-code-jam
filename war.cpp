#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;

/*
    Google code jam 2014 qualification round problem D
    Description: https://code.google.com/codejam/contest/2974486/dashboard#s=p3
    Solution: non-deceitful war strategy is simple: Ken chooses smallest block that is larger
    than Naomi's. If there is no such block, he gives his smallest block.
    Deceitful-war strategy: Naomi exchanges her smallest block for Ken's largest by telling him
    that her block weights is a range between Ken's second heaviest and the heaviest block.
    If Naomi compares her and Ken's sorted blocks with same indices and finds that
    her blocks beat Ken's, then the number of blocks left is Naomi's score basically.
*/

int main()
{
    int tests,s,t = 1;
    double num;
    cin >> tests;
    while(tests--){
        cin >> s;
        vector<double> k;
        vector<double> n;
        for(int i = 0; i < s; ++i){
            cin >> num;
            n.push_back(num);
        }
        for(int i = 0; i < s; ++i){
            cin >> num;
            k.push_back(num);
        }
        sort(k.begin(), k.end());
        sort(n.begin(), n.end());
        list<double> ln;
        list<double> lk;
        for(int i = 0; i < s; ++i){
            ln.push_back(n[i]);
            lk.push_back(k[i]);
        }

        //game loop for war
        int cnt = 0;
        for(int i = 0; i < s; ++i){
            double ch = ln.front();
            ln.pop_front();
            bool found = false;
            for(list<double>::iterator it = lk.begin(); it != lk.end(); ++it){
                if(*it > ch){
                    found = true;
                    lk.erase(it);
                    break;
                }
            }
            if(!found){
                lk.pop_front();
                cnt++;
            }

        }

        ln.clear();
        lk.clear();
        for(int i = 0; i < s; ++i){
            ln.push_back(n[i]);
            lk.push_back(k[i]);
        }
        int cnt2 = 0;
        //game loop for deceitful war
        for(int i = 0; i < s; ++i){
            bool win = true;
            for(list<double>::iterator it = ln.begin(), it2 = lk.begin(); it != ln.end(); ++it, ++it2){
                if(*it < *it2){
                    win = false;
                    break;
                }
            }
            if(win){
                cnt2 = s - i;
                break;
            }
            ln.pop_front();
            lk.pop_back();

        }

        cout << "Case #" << t << ": " << cnt2 << " " << cnt << endl;

        t++;
    }
    return 0;
}
