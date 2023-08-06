/*
 * lefl_datastruct.c
 */
#include "lefl.h"


lefl_array_elm_t lefl_loop_array_get(lefl_loop_array_t *arr,int16_t j)
{
    if(j>=0&&j<arr->len)
    {
        return arr->data[arr->index-j>=0?arr->index-j:arr->index-j+arr->len];
    }
    else
    {
        return 0;
    }
}

void lefl_loop_array_push_back(lefl_loop_array_t *arr,lefl_array_elm_t t)
{
    arr->index++;
    if(arr->index>=arr->len)
    {
        arr->index=0;
    }
    arr->data[arr->index]=t;
}

lefl_array_elm_t lefl_loop_array_max(lefl_loop_array_t *arr)
{
    lefl_array_elm_t max = 0;
    for(uint8_t i=0;i<arr->len;i++)
    {
        if(arr->data[i]>max)
            max=arr->data[i];
    }
    return max;
}

void lefl_bit_array_set(lefl_bit_array_t* arr, int16_t n,bool b)
{
    if(n>=0&&n<arr->len)
    {
        arr->data[n/LEFL_BIT_ARRAY_UNIT_WIDTH]&=
            (~(1<<(n%LEFL_BIT_ARRAY_UNIT_WIDTH)));
        arr->data[n/LEFL_BIT_ARRAY_UNIT_WIDTH]|=
            (b<<(n%LEFL_BIT_ARRAY_UNIT_WIDTH));
    }
}

bool lefl_bit_array_get(lefl_bit_array_t* arr, int16_t n)
{
    if(n>=0&&n<arr->len)
        return 1&
            (arr->data[n/LEFL_BIT_ARRAY_UNIT_WIDTH]>>(n%LEFL_BIT_ARRAY_UNIT_WIDTH));
    else
        return false;
}

void lefl_bit_array_shift(lefl_bit_array_t* arr, int16_t n)
{
    if(n>0)
    {
        for(int16_t i=(arr->len-1)/LEFL_BIT_ARRAY_UNIT_WIDTH;i>0;i--)
        {
            arr->data[i]<<=n;
            arr->data[i]|=(arr->data[i-1]>>(LEFL_BIT_ARRAY_UNIT_WIDTH-n));
        }
        arr->data[0]<<=n;
    }
    if(n<0)
    {
        for(int16_t i=0;i<(arr->len-1)/LEFL_BIT_ARRAY_UNIT_WIDTH;i++)
        {
            arr->data[i]>>=(-n);
            arr->data[i]|=arr->data[i+1]<<(LEFL_BIT_ARRAY_UNIT_WIDTH-(-n));
        }
        arr->data[(arr->len-1)/LEFL_BIT_ARRAY_UNIT_WIDTH]>>=(-n);
    }
}

