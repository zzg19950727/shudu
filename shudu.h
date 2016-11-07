#ifndef SHUDU_H
#define SHUDU_H
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define NUM 50

//当前行限制的数据
struct R_limit
{
    int row;    //所在地图的行
    int c_star; //限制数据列的开始
    int c_end;  //限制数据列的结束
};
typedef struct R_limit RL;

//当前列限制的数据
struct C_limit
{
    int column; //所在列
    int r_start;//限制数据行的开始
    int r_end;  //限制数据行的结束
};
typedef struct C_limit CL;

//当前可选的数据
struct block
{
    int b[9];   //前len个数据有效
    int len;    //有效长度
};
typedef struct block BL;

void init_map_s();
void rand_map_s();
#endif // SHUDU_H

