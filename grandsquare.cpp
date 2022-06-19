#include "grandsquare.h"
QVector<QVector<int>> bfssquare(int n, int k)
{
    QVector<QVector<int>> curvec;
    curvec.resize(N);
    int looptime=0;
    for(auto &e:curvec) e.resize(N);
    int move_x[]={0,0,1,-1,0};
    int move_y[]={1,-1,0,0,0};
    Point2 p1(N/2,N/2);
    curvec[N/2][N/2]=1;
    std::queue<Point2> que;
    que.push(p1);
    int count = 0;
    while(!que.empty())
    {
        Point2 p = que.front();
        que.pop();
        for(int i=0; i<5; i++)
        {
            Point2 curp(p.x+move_x[i],p.y+move_y[i]);
            looptime++;
            if(looptime>1000) return curvec;
            if(curp.x>=0&&curp.x<N&&curp.y>=0&&curp.y<N&&curvec[curp.x][curp.y]==0&&random_unint(0,100)<=k&&count<n)
            {
                curvec[curp.x][curp.y] = 1;
                count++;
                que.push(curp);
            }
            else if(count<n-1&&que.empty())
            {
                que.push(curp);
            }
        }
    }
    return curvec;
}

GrandSquare::GrandSquare(QObject *parent)
    : QGraphicsScene{parent},
      width(10),
      height(10),
      count(0)
{
    Mmates.resize(width);
    for(auto&e:Mmates)
    {
        e.resize(height);
        for(auto&h:e)
        {
            h.resize(N);
            for(auto&g:h)g.resize(N);
        }
    }
    StatesofMmates.resize(width);
    for(auto &e:StatesofMmates) e.resize(height);
    Initialize();
}

void GrandSquare::Initialize()
{
    for(int x=0;x<width;x++)
        for(int y=0;y<height;y++)
        {
            StatesofMmates[x][y]=0;
            int minn=N, maxx=N*N/2;
            auto randomvec = bfssquare(random_unint((unsigned int)minn,(unsigned int)maxx),80);
            for(int xx=0;xx<N;xx++)
                for(int yy=0;yy<N;yy++)
                {
                    this->Mmates[x][y][xx][yy] = new FigureMate;
                    this->Mmates[x][y][xx][yy]->SetState(randomvec[xx][yy]);
                    connect(Mmates[x][y][xx][yy],&FigureMate::clicked,this,&GrandSquare::select);
                    this->Mmates[x][y][xx][yy]->setPos(QPointF(x*N*squaresize+xx*squaresize,y*N*squaresize+yy*squaresize));
                    this->Mmates[x][y][xx][yy]->setRowAndCol(x,y);
                    this->Mmates[x][y][xx][yy]->SetEditable(false);
                    this->addItem(this->Mmates[x][y][xx][yy]);
                }
        }
}


void GrandSquare::select(int x,int y)
{
    if(StatesofMmates[x][y]!=4)
    {
        qDebug()<<count;
        for(int xx=0;xx<N;xx++)
            for(int yy=0;yy<N;yy++)
            {
                if(Mmates[x][y][xx][yy]->GetState()==3)
                {
                    Mmates[x][y][xx][yy]->SetState(1);
                }
                else if(Mmates[x][y][xx][yy]->GetState()==1&&count<6)
                {
                    Mmates[x][y][xx][yy]->SetState(3);
                }
            }
        switch (StatesofMmates[x][y])
            {
            case 0:
            {
                if(count<6)
                {
                    count++;
                    StatesofMmates[x][y]=2;
                }
                break;

            }
            case 1:
            {
                if(count<6)
                {
                    count++;
                    StatesofMmates[x][y]=3;
                }
                break;
            }
            case 2:
            {
                count--;
                StatesofMmates[x][y]=0;
                break;
            }
            case 3:
            {
                count--;
                StatesofMmates[x][y]=1;
                break;
            }
        }
    }

}
