//骑士周游(qishizhouyou），with method of trace back
//Note:This program can list all probable ways , but costs a lot of time.
//Compiled in Code::Blocks on Ubuntu platform

//step[N*N]   record the direction of each step
//move[8][2]  eight probable directions
//chess[N][N] the order of points/grids
//pro in function trace(int ,int ,int) means pro steps jumped

#include <iostream>
#include <iomanip>
using namespace std;


const int N = 8;
int k = 0,i = 0;
int step[N*N];
int move[8][2] = {{2,1}, {1,2}, {-1,2}, {-2,1}, {-2,-1}, {-1,-2}, {1,-2}, {2,-1}}; //counter-clockwise direction
int chess[N][N];

void init() //initialize
{
    int i;
    for(i = 0; i< N*N; ++i) {
        step[i] = -1;
        chess[i/8][i%8] = 0;
    }
}


inline int canjump(int x,int y)
{
    if(x>=0 && x<N && y>=0 && y<N && chess[x][y]==0)
        return 1;
    else
        return 0;
}

inline void Print()
{
    for(int i=0;i<N;++i)
    {
        for(int j=0;j<N;++j)
            cout<<setw(3)<<chess[i][j];
        cout<<endl;
    }
    cout<<endl;
}


void trace(int pro,int x,int y)
{
    if(pro>=N*N)
    {
        Print();
    }
    else
    {
        for(int i=0;i<8;++i)
        {
            if(canJump(x+move[i][0], y+move[i][1]))
            {
                x+=move[i][0];
                y+=move[i][1];
                chess[x][y]=pro+1;
                step[pro]=i;
                trace(pro+1,x,y);//after finish this step,try next step

                chess[x][y]=0;//trace back
                x-=move[i][0];
                y-=move[i][1];
            }
        }
    }
}



int main(int argc, char *argv[])
{
    int x=2;
    int y=5;
    chess[x][y]=1;
    trace(1,x,y);

    return 0;
}
