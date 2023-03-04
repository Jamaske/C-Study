#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;


double distance(int vx,int vy,int vxt,int vyt) {

    if(vx*vxt+vy*vyt>0){
        if(vx*(vx-vxt)+vy*(vy-vyt)>0){
            return ((vxt*vy-vyt*vx)/(sqrt(vx * vx + vy * vy)));
        }else return sqrt((vxt-vx)*(vxt-vx)+(vyt-vy)*(vyt-vy));

    } else return sqrt(vxt*vxt+vyt*vyt);

}


int main() {
    int n;
    int yPrev,xPrev, yCur,xCur;
    int xt,yt;
    int x0, y0;
    int vx,vy;
    int vxt,vyt;
    bool bFlag=false;
    double MIN=INT16_MAX;

    cin >> xt >> yt >>n;
    cin >> xPrev >> yPrev;
    x0=xPrev;
    y0=yPrev;

    for(int i=1;i<n;i++) {
        cin >> xCur >> yCur;
        vx = xCur - xPrev;
        vy = yCur - yPrev;
        vxt = xt - xPrev;
        vyt = yt - yPrev;
        if (vxt * vy - vx * vyt > 0) {
            bFlag = true;
            MIN = min(MIN, distance(vx,vy,vxt,vyt));
        }
        xPrev=xCur;
        yPrev=yCur;
    }
    vx = x0 - xPrev;
    vy = y0 - yPrev;
    vxt = xt - xPrev;
    vyt = yt - yPrev;
    if (vxt * vy - vx * vyt > 0) {
        bFlag = true;
        MIN = min(MIN, distance(vx,vy,vxt,vyt));
    }

    cout << fixed << setprecision(3);
    if(!bFlag) MIN = 0;
    cout<< MIN;
}