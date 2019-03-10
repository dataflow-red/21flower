#include <stdio.h>
#include<time.h>

typedef struct Uint96
{
    unsigned int f;
    unsigned int m;
    unsigned int t;
}uint96;
uint96 f21s[10][20] = {{{0, 0, 0}}/*0*/, {{0, 0, 1}}/*1*/, {{0, 0, 2097152}}/*2*/,
                       {{0, 2, 0x6F7C52B3}}/*3*/, {{0, 0x400, 0}}/*4*/,
                       {{0, 0x1B1AE, 0x4D6E2EDC}}/*5*/, {{0, 0x4DEF8A, 0x56600000}}/*6*/,
                       {{0, 0x7C05A81, 0x0B72A027}}/*7*/, {{0, 0x80000000,0}}/*8*/,
                       {{5, 0xEE7E56E3, 0x721F2929}}/*9*/};

void Uint96Add(uint96 *lh, uint96 *rh, uint96 *rs)
{
      uint96 r;
      unsigned int ft, fm, trm;
      //低位求和
      r.t = (*lh).t + (*rh).t;
      //低位进位
      ft = r.t < (*lh).t || r.t < (*rh).t;
      //中间位求和
      trm = (*lh).m + (*rh).m;
      //中间位的进位
      fm = trm < (*lh).m || trm < (*rh).m;
      //中间位的和再加上低位进位
      r.m = trm + ft;
      //中间位两次求和的进位和
      fm += r.m < trm || r.m < ft;

      r.f = (*lh).f + (*rh).f + fm;

      *rs = r;
}

void Init()
{
    int i, j;

    for(i = 0; i < 10; i++)
        for(j = 1; j < 20;  j++)
            Uint96Add(&f21s[i][0], &f21s[i][j - 1], &f21s[i][j]);
}

int AreEqual(uint96 lh, uint96 rh)
{
    return lh.f == rh.f && lh.m == rh.m && lh.t == rh.t;
}

int Compare(uint96 *lh, uint96 *rh)
{
    if((*lh).f == (*rh).f && (*lh).m == (*rh).m && (*lh).t == (*rh).t) return 0;
    if((*lh).f > (*rh).f ||
       (*lh).f == (*rh).f && (*lh).m > (*rh).m ||
       (*lh).f == (*rh).f && (*lh).m == (*rh).m && (*lh).t > (*rh).t)
       return 1;
    return -1;
}

typedef struct Int22
{
    int d[22];
}int22;

int22 f10[10][22] = {{0}/*0*/,
                     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}/*1*/,
                     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,9,7,1,5,2}/*2*/,
                     {0,0,0,0,0,0,0,0,0,0,0,1,0,4,6,0,3,5,3,2,0,3}/*3*/,
                     {0,0,0,0,0,0,0,0,0,4,3,9,8,0,4,6,5,1,1,1,0,4}/*4*/,
                     {0,0,0,0,0,0,0,4,7,6,8,3,7,1,5,8,2,0,3,1,2,5}/*5*/,
                     {0,0,0,0,0,2,1,9,3,6,9,5,0,6,4,0,3,7,7,8,5,6}/*6*/,
                     {0,0,0,0,5,5,8,5,4,5,8,6,4,0,8,3,2,8,4,0,0,7}/*7*/,
                     {0,0,0,9,2,2,3,3,7,2,0,3,6,8,5,4,7,7,5,8,0,8}/*8*/,
                     {0,1,0,9,4,1,8,9,8,9,1,3,1,5,1,2,3,5,9,2,0,9}/*9*/,
};

int Int22Add(int22 *lh, int22 *rh, int22 *sum)
{
     int i, c = 0;

    for(i = 21; i >= 0; i--)
    {
        (*sum).d[i] = (*lh).d[i] + (*rh).d[i] + c;
        c = (*sum).d[i] >= 10;
        if(c) (*sum).d[i] -= 10;
    }
    return c;
}

int Int22Sub(int22 *lh, int22 *rh, int22 *diff)
{
     int i, c = 0, k;

    for(i = 21; i >= 0; i--)
    {
        k = (*lh).d[i] < (*rh).d[i] + c ? 10 : 0;
        (*diff).d[i] = k + (*lh).d[i] - (*rh).d[i] - c;
        c = k == 10;
    }
    return c;
}

void Init1()
{
   int i, j;

   for(i = 1; i < 10; i++)
        for(j = 0; j < 21; j++)
            Int22Add(&f10[i][0], &f10[i][j - 1], &f10[i][j]);
}

int AreEqual1(int22 *lh, int22 *rh)
{
    int i;
    for(i = 0; i < 22; i++)
        if((*lh).d[i] != (*rh).d[i]) return 0;
    return 1;
}

int IsBiggerThanMax21(int22 *n)
{
    return (*n).d[0] != 0;
}

int IsSmallerThanMin21(int22 *n)
{
    return (*n).d[0] == 0 && (*n).d[1] == 0;
}

int Check(int d[], int22 *sum)
{
    int i, nums[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for(i = 1; i < 22; i++)
        nums[9 - (*sum).d[i]]++;
    for(i = 0; i < 10; i++)
        if(d[i] != nums[i]) return 0;
    return 1;
}

void Writeln(int22 *sum)
{
    int i;
    for(i = 1; i < 22; i++)
        printf("%d", (*sum).d[i]);
    printf("\n");
}

void Test()
{
    uint96 f2_20 = {0, 0, 0x2800000};
    uint96 f3_20 = {0, 0x30, 0xB5B675FC};
    uint96 f4_20 = {0, 0x5000, 0};
    uint96 f5_20 = {0, 0x21E19E, 0x0C9BA930};
    uint96 f6_20 = {0, 0x616B6CE, 0xBF800000};
    uint96 f7_20 = {0, 0x9B071214, 0xE4F4830C};
    uint96 f8_20 = {0xA,0,0};
    uint96 f9_20 = {0x76, 0xA1DEC9C4, 0xEA6F3734};

    if(AreEqual(f2_20, f21s[2][19]))
        printf("f2_20 Pass\n");
    if(AreEqual(f3_20, f21s[3][19]))
        printf("f3_20 Pass\n");
    if(AreEqual(f4_20, f21s[4][19]))
        printf("f4_20 Pass\n");
    if(AreEqual(f5_20, f21s[5][19]))
        printf("f5_20 Pass\n");
    if(AreEqual(f6_20, f21s[6][19]))
        printf("f6_20 Pass\n");
    if(AreEqual(f7_20, f21s[7][19]))
        printf("f7_20 Pass\n");
    if(AreEqual(f8_20, f21s[8][19]))
        printf("f8_20 Pass\n");
    if(AreEqual(f9_20, f21s[9][19]))
        printf("f9_20 Pass\n");
}

void Test1()
{
    int22 f2_20 = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,1,9,4,3,0,4,0}};
    int22 f3_20 = {{0,0,0,0,0,0,0,0,0,0,2,0,9,2,0,7,0,6,4,0,6,0}};
    int22 f4_20 = {{0,0,0,0,0,0,0,0,8,7,9,6,0,9,3,0,2,2,2,0,8,0}};
    int22 f5_20 = {{0,0,0,0,0,0,9,5,3,6,7,4,3,1,6,4,0,6,2,5,0,0}};
    int22 f6_20 = {{0,0,0,0,4,3,8,7,3,9,0,1,2,8,0,7,5,5,7,1,2,0}};
    int22 f7_20 = {{0,0,1,1,1,7,0,9,1,7,2,8,1,6,6,5,6,8,0,1,4,0}};
    int22 f8_20 = {{0,1,8,4,4,6,7,4,4,0,7,3,7,0,9,5,5,1,6,1,6,0}};
    int22 f9_20 = {{2,1,8,8,3,7,9,7,8,2,6,3,0,2,4,7,1,8,4,1,8,0}};
    int22 diff;
    int22 dr =    {{2,0,0,3,9,1,2,3,4,1,8,9,3,1,5,1,6,6,8,0,2,0}};
    int22 f8_201 = {{1,1,8,4,4,6,7,4,4,0,7,3,7,0,9,5,5,1,6,1,6,0}};
    int22 f9_201 = {{2,0,8,8,3,7,9,7,8,2,6,3,0,2,4,7,1,8,4,1,8,0}};
    int22 dr1 =    {{0,9,0,3,9,1,2,3,4,1,8,9,3,1,5,1,6,6,8,0,2,0}};

    if(AreEqual1(&f2_20, &f10[2][19]))
        printf("f2_20 Pass\n");
    if(AreEqual1(&f3_20, &f10[3][19]))
        printf("f3_20 Pass\n");
    if(AreEqual1(&f4_20, &f10[4][19]))
        printf("f4_20 Pass\n");
    if(AreEqual1(&f5_20, &f10[5][19]))
        printf("f5_20 Pass\n");
    if(AreEqual1(&f6_20, &f10[6][19]))
        printf("f6_20 Pass\n");
    if(AreEqual1(&f7_20, &f10[7][19]))
        printf("f7_20 Pass\n");
    if(AreEqual1(&f8_20, &f10[8][19]))
        printf("f8_20 Pass\n");
    if(AreEqual1(&f9_20, &f10[9][19]))
        printf("f9_20 Pass\n");

    Int22Sub(&f9_20, &f8_20, &diff);
    if(AreEqual1(&dr, &diff))
        printf("sub Pass\n");
    Int22Sub(&f9_201, &f8_201, &diff);
    if(AreEqual1(&dr1, &diff))
        printf("sub1 Pass\n");
}

int main()
{
    /*
    uint96 max21 = {0x36, 0x35C9ADC5, 0xDE9FFFFF};
    uint96 min21 = {0x5, 0x6BC75E2D ,0x63100000};
    uint96 sum;
    */

    int22 sum = {{0}};
    //int22 s1 = {{0,1,2,8,4,6,8,6,4,3,0,4,3,7,3,1,3,9,1,2,5,2}};
    int digits, pointer, nums[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int count = 0, count1 = 0;
    Init1();
    //Test1();

    digits = 9;
    pointer = 0;
    nums[0] = 9;
    sum = f10[9][8];

    while(pointer >= 0)
    {
       if(pointer < 9 && digits < 21)
       {
           pointer++;
           nums[pointer] = 21 - digits;
           digits = 21;
           count1++;
           Int22Add(&f10[9 - pointer][nums[pointer] - 1], &sum, &sum);
           if(IsSmallerThanMin21(&sum)) break;     //小于最小的21位数，结束
           if(!IsBiggerThanMax21(&sum))            //是一个21位数
           {
               count++;
               if(Check(nums, &sum)) Writeln(&sum);
                //if(AreEqual1(&s1, &sum))  Writeln(&sum);
           }
       }
       //while(nums[pointer] == 0)
       //    if(--pointer < 0) break;

       while(pointer >= 0)
       {
           if(nums[pointer] > 0)
           {
               nums[pointer]--;
               digits--;
               Int22Sub(&sum, &f10[9 - pointer][0], &sum);
               count1++;
               if(!IsBiggerThanMax21(&sum)) break;
           }
           else
           {
               pointer--;
           }
       }
    }
    printf("\nrun%.2fseconds\n",(double)clock()/CLOCKS_PER_SEC);
    printf("check:%d\tcalc:%d", count, count + count1);

    return 0;
}
