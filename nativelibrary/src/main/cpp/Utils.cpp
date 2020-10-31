//
// Created by 张世东 on 2020/10/31.
//
#include "string"
#include <stdio.h>
void quickSort(int s[], int l, int r);
int quickSortPartition(int s[], int l, int r);

void quickSort(int s[], int l, int r){
    //数组左界<右界才有意义，否则说明都已排好，直接返回即可
    if (l>=r){
        return;
    }

    // 划分，返回基准点位置
    int i = quickSortPartition(s, l, r);

    // 递归处理左右两部分，i处为分界点，不用管i了
    quickSort(s, l, i - 1);
    quickSort(s, i + 1, r);
}

int quickSortPartition(int s[], int l, int r){
    //Swap(s[l], s[(l + r) / 2]); //若以中间数为基准，则先将中间的这个数和第一个数交换即可
    int i = l, j = r, x = s[l]; //将最左元素记录到x中
    while (i < j)
    {
        // 从右向左找第一个<x的数
        // 无需考虑下标越界
        while(i < j && s[j] >= x)
            j--;
        if(i < j)
            s[i++] = s[j]; //直接替换掉最左元素（已在x中存有备份）

        // 从左向右找第一个>x的数
        while(i < j && s[i] <= x)
            i++;
        if(i < j)
            //替换掉最右元素(已在最左元素中有备份）
            //最左元素一定被覆盖过，若没有，则表明右侧所有元素都>x，那么算法将终止
            s[j--] = s[i];
    }
    s[i] = x;  //i的位置放了x，所以其左侧都小于x，右侧y都大于x
    return i;
}

std::string getStringFromC(){
    std::string str =  "你好，我是 c++ 层创建的字符串";
    return str;
}

