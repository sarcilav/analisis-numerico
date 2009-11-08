// Sergio Botero - sergiobuj@gmail.com
// Title:
// Submitted:
// OJ:

#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "GrahamScan.cpp"
using namespace std;
#define all(x) x.begin(),x.end()
#define D(x) cout <<__LINE__<<"  "<<#x<<"  is  "<< x << endl
#define D_v(x) for(int __i=0;__i<x.size();cerr<<x[__i++]<<" ")
#define D_m(m,rows,cols) for(int __i=0;__i<rows;cout<<endl,++__i) for(int __j=0;__j<cols;) cout <<m[__i][__j++]<<"  "
#define SWAP(a,b)({(a)^=(b);(b)^=(a);(a)^=(b);})						

int main (){
  int n;
  scanf("%d",&n);
  vector <point> inPoints;
  int x,y;
  for(int i=0;i<n;++i){
    scanf("%d%d",&x,&y);
    inPoints.push_back(point(x,y));
  }
  

  for(int i=0;i<n;++i){
    printf("\n------------------------------%d/%d\n",i+1,n);
    vector <point> p = inPoints;
    printf("Prueba sin punto X=%d Y=%d\n",p[i].x,p[i].y);
    p.erase(p.begin()+i);
    vector<point> ans = graham(p);
    puts("Puntos del convex:");
    for(int i=0;i<ans.size();++i)
      printf("%3d -> %3d %3d\n",i,ans[i].x,ans[i].y);

    double s = 0,area=0; int n = ans.size(); 
    for(int i=0; i < ans.size(); ++i){
      //      s+= ans[i].x % ans[i].y;
      area+=ans[i].x*ans[(i+1)%ans.size()].y;
      area-=ans[i].y*ans[(i+1)%ans.size()].x;
    }
    printf("área = %lf\n",fabs(area)/2.0); 
	
    double perim=0; int x,x1,y,y1;
    for(int i=0; i <ans.size(); ++i){
      x=ans[i].x;
      x1=ans[(i+1)%ans.size()].x;
      y=ans[i].y;
      y1=ans[(i+1)%ans.size()].y;
      perim+=sqrt(      ((x1-x)*(x1-x)) + ((y1-y)*(y1-y))    );
    }
    printf("perim = %lf\n",perim);
    
  }
  return 0;
}
