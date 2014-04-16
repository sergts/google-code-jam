#include <iostream>
#include <iomanip>
using namespace std;
/*
    Code jam qualification round 2014 problem B

    Description:
    https://code.google.com/codejam/contest/2974486/dashboard#s=p1

    Solution: when you have enough money to buy a farm, calculate which way you would gather
    enough cookies faster: by buying a farm or by not buying it.
    If you do not buy a farm, then you just add number of cookies left to gather divided by cookies per second
    to total time elapsed. If you choose to buy a farm, then number of cookies goes to zero but you have increased
    cookies per second parameter.
*/
int main()
{
    int tests, t = 1;
    double c,f,x,cps,tt,t1,t2,t3;
    cin >> tests;
    while(tests--){
        cps = 2;
        tt = 0;
        cin >> c >> f >> x;
        t1 = x/cps;
        t2 = c/cps;
        t3 = x/(cps+f);
        while( t1 > (t2+t3)){
            tt += t2;
            cps += f;
            t1 = x/cps;
            t2 = c/cps;
            t3 = x/(cps+f);
        }
        tt += t1;
        cout << "Case #" << t << ": " << fixed << setprecision(7) << tt << endl;
        t++;
    }
    return 0;
}
