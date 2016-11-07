#include "shudu.h"
//数独地图
int map_s[9][9];
BL* bl;
BL* bl_copy;
RL* rl;
CL* cl;

void P()
{
    system("cls");
   for(int i=0; i<9; i++)
   {
        for(int j=0; j<9; j++)
        {
            printf("%d  ", map_s[i][j]);
            if( (j+1)%3 == 0 )
                printf("    ");
        }
        printf("\n");
        if( (i+1)%3 == 0 )
            printf("\n");
   }
}

//初始化可选数据
void init_BL(BL* bl)
{
    if( !bl )
        return;
    //初始数据为1~9
    bl->len = 9;
    for(int i=0; i<9; i++)
        bl->b[i] = i+1;
}

void copy_BL(BL* bl_s, BL* bl_d)
{
    if( !bl_s || !bl_d )
        return;
    bl_d->len = bl_s->len;
    for(int i=0; i<bl_s->len; i++)
        bl_d->b[i] = bl_s->b[i];
}

//从可选数据中删除一个数据n
void re_limit(int n, BL* bl)
{
    if( !bl )
        return;
    //遍历有效数据查找n
    for(int i=0; i<bl->len; i++)
    {
        //找到则删除
        if( bl->b[i] == n )
        {
            for(int j=i; j<bl->len-1; j++)
                bl->b[j] = bl->b[j+1];
            bl->len--;
            continue;
        }
    }
}

//从可选数据中删除指定行数据
void re_RL(RL* rl, BL* bl)
{
    if( !rl || !bl )
        return;
    //删除行结构中限制数据
    for(int i=rl->c_star; i<rl->c_end; i++)
        re_limit(map_s[rl->row][i], bl);
}

//从可选数据中删除指定列数据
void re_CL(CL* cl, BL* bl)
{
    if( !cl || !bl )
        return;
    //删除列结构中指定的行数据
    for(int i=cl->r_start; i<cl->r_end; i++)
        re_limit(map_s[i][cl->column], bl);
}

//从可选数据中随机选择一个数据
void Rand(int r, int c, BL* bl, BL* bl_copy)
{
    if( !bl || !bl_copy || !bl->len )
        return;

    //从有效长度中随机选择一个位置
    int loc = rand()%(bl->len);
    //获取指定位置的数据
    map_s[r][c] = bl->b[loc];
    //删除已选数据
    re_limit(map_s[r][c], bl);
    re_limit(map_s[r][c], bl_copy);
}

//初始化第一行、第一列的方格
void init_1_1()
{
    init_BL( bl );
    copy_BL(bl, bl_copy);
    for(int i=3; i<6; i++)
        for(int j=3; j<6; j++)
            Rand(i, j, bl, bl_copy);
}

//初始化第一行、第零列的方格
bool init_1_0()
{
    init_BL( bl );
    rl->c_star = 3;
    rl->c_end = 6;

    for(int i=3; i<6; i++)
    {
        copy_BL(bl, bl_copy);
        rl->row = i;
        re_RL(rl, bl_copy);
        if( bl_copy->len < 3 )
            return false;
        for(int j=0; j<3; j++)
        {
            Rand(i, j, bl_copy, bl);
        }
    }
    return true;

}

//初始化第零行、第一列的方格
bool init_0_1()
{
    init_BL( bl );
    cl->r_start = 3;
    cl->r_end = 6;

    for(int i=3; i<6; i++)
    {
        copy_BL(bl, bl_copy);
        cl->column = i;
        re_CL(cl, bl_copy);
        if( bl_copy->len < 3 )
            return false;
        for(int j=0; j<3; j++)
        {
            Rand(j, i, bl_copy, bl);
        }
    }
    return true;
}

bool init_1_2()
{
    init_BL( bl );
    rl->c_star = 0;
    rl->c_end = 6;

    for(int i=3; i<6; i++)
    {
        copy_BL(bl, bl_copy);
        rl->row = i;
        re_RL(rl, bl_copy);
        if( bl_copy->len < 3 )
            return false;
        for(int j=6; j<9; j++)
        {
            Rand(i, j, bl_copy, bl);
        }
    }
    return true;
}

bool init_2_1()
{
    init_BL( bl );
    cl->r_start = 0;
    cl->r_end = 6;

    for(int i=3; i<6; i++)
    {
        copy_BL(bl, bl_copy);
        cl->column = i;
        re_CL(cl, bl_copy);
        if( bl_copy->len < 3 )
            return false;
        for(int j=6; j<9; j++)
        {
            Rand(j, i, bl_copy, bl);
        }
    }
    return true;
}

bool init_0_0()
{
    init_BL( bl );

    rl->c_star = 3;
    rl->c_end = 6;

    cl->r_start = 3;
    cl->r_end = 6;

    for(int i=0; i<3; i++)
    {
        copy_BL(bl, bl_copy);
        rl->row = i;
        re_RL(rl, bl_copy);
        for(int j=0; j<3; j++)
        {
            cl->column = j;
            re_CL(cl, bl_copy);

            if( bl_copy->len < 1 )
                return false;

            Rand(i, j, bl_copy, bl);
            copy_BL(bl, bl_copy);
            re_RL(rl, bl_copy);
        }
    }
    return true;
}

bool init_0_2()
{
    init_BL( bl );

    rl->c_star = 0;
    rl->c_end = 6;

    cl->r_start = 3;
    cl->r_end = 6;

    for(int i=0; i<3; i++)
    {
        copy_BL(bl, bl_copy);
        rl->row = i;
        re_RL(rl, bl_copy);
        for(int j=6; j<9; j++)
        {
            cl->column = j;
            re_CL(cl, bl_copy);

            if( bl_copy->len < 1 )
                return false;

            Rand(i, j, bl_copy, bl);
            copy_BL(bl, bl_copy);
            re_RL(rl, bl_copy);
        }
    }
    return true;
}

bool init_2_2()
{
    init_BL( bl );

    rl->c_star = 3;
    rl->c_end = 6;

    cl->r_start = 0;
    cl->r_end = 6;

    for(int i=6; i<9; i++)
    {
        copy_BL(bl, bl_copy);
        rl->row = i;
        re_RL(rl, bl_copy);
        for(int j=6; j<9; j++)
        {
            cl->column = j;
            re_CL(cl, bl_copy);

            if( bl_copy->len < 1 )
                return false;

            Rand(i, j, bl_copy, bl);
            copy_BL(bl, bl_copy);
            re_RL(rl, bl_copy);
        }
    }
    return true;
}

bool init_2_0()
{
    init_BL( bl );

    rl->c_star = 3;
    rl->c_end = 9;

    cl->r_start = 0;
    cl->r_end = 6;

    for(int i=6; i<9; i++)
    {
        copy_BL(bl, bl_copy);
        rl->row = i;
        re_RL(rl, bl_copy);
        for(int j=0; j<3; j++)
        {
            cl->column = j;
            re_CL(cl, bl_copy);

            if( bl_copy->len < 1 )
                return false;

            Rand(i, j, bl_copy, bl);
            copy_BL(bl, bl_copy);
            re_RL(rl, bl_copy);
        }
    }
    return true;
}

bool check()
{
    for(int i=0; i<9; i++)
        for(int j=0; j<9; j++)
            if( map_s[i][j] == 0)
                return false;
    return true;
}

void init_map_s()
{
    //初始化随机种子
    srand( time(NULL) );

    bl = new BL;
    bl_copy = new BL;
    rl = new RL;
    cl = new CL;

    while( !check() )
    {
        for(int i=0; i<9; i++)
        for(int j=0; j<9; j++)
            map_s[i][j] = 0;
        init_1_1();

        init_1_0();
        init_0_1();
        init_1_2();
        init_2_1();

        init_0_0();
        init_0_2();
        init_2_2();
        init_2_0();
    }

}


void rand_map_s()
{
    srand( time(NULL) );
    int r, c;
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            for(int k=0; k<5; k++)
            {
                r = rand()%3;
                c= rand()%3;
                if( map_s[3*i+r][3*j+c] == 0 )
                    k--;
                else
                    map_s[3*i+r][3*j+c] = 0;
            }
        }
    }
}
