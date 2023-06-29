#include<stdio.h>
#include<stdlib.h>

// int* set(int *A, int *N)
char* set(char *A, int *N)
{
    char *Set_Array;
    Set_Array = (char*)malloc((*N)*sizeof(char));

    int j = 0;

    for(int i=0;i < *N;i++)
    {
        int exist = 0;

        for(int k=0;k < j;k++)
        {
            if(Set_Array[k] == A[i])
            {
                exist = 1;
            }
        }

        if(exist == 0)
        {
            Set_Array[j] = A[i];
            j++;
        }
    }
    
    *N  = j;

    return Set_Array;
}
//---------------------------------------------------------
char* set_intersection(char *A1, int *N1, char *A2, int *N2)
{
    char *Set_A1, *Set_A2, *Intersect_Set;
    int greatest = 0;
    int k = 0;

    Set_A1 = (char*)malloc((*N1)*sizeof(char));
    Set_A2 = (char*)malloc((*N2)*sizeof(char));

    Set_A1 = set(A1, N1);
    Set_A2 = set(A2, N2);

    if(*N1 > *N2)
        greatest = *N1;

    else
        greatest = *N2;

    Intersect_Set = (char*)malloc((greatest)*sizeof(char));
    
    for(int m=0;m < *N1;m++)
    {
        for(int n=0;n < *N2;n++)
        {
            if(Set_A1[m] == Set_A2[n])
            {
                Intersect_Set[k] = Set_A1[m];
                k++;
            }
        }
    }

    *N1 = k;
    return Intersect_Set;

}
//--------------------------------------------------------
char* set_union(char *A3, int *N3, char *A4, int *N4)
{
    char *Set_A3, *Set_A4, *Union_Set;
    int sum = 0;
    int leng = 0;

    Set_A3 = (char*)malloc((*N3)*sizeof(char));
    Set_A4 = (char*)malloc((*N4)*sizeof(char));

    Set_A3 = set(A3, N3);
    Set_A4 = set(A4, N4);
    sum = *N3 + *N4;
    Union_Set = (char*)malloc((sum)*sizeof(char));

    if(*N3 >= *N4)
    {
        for(int r=0;r < *N3;r++)
        {
            Union_Set[r] = Set_A3[r];
        }

        leng = *N3;

        for(int o=0;o < *N4;o++)
        {
            int exist = 0;
            for(int p=0;p < *N3;p++)
            {
                if(Set_A4[o] == Set_A3[p])
                {
                    exist = 1;
                }
            }

            if(exist == 0)
            {
                Union_Set[leng] = Set_A4[o];
                leng++;
            }
        }

        *N3 = leng;

        return Union_Set;
    }

    else
    {
        for(int r=0;r < *N4;r++)
        {
            Union_Set[r] = Set_A4[r];
        }

        leng = *N4;

        for(int o=0;o < *N3;o++)
        {
            int exist = 0;
            for(int p=0;p < *N4;p++)
            {
                if(Set_A3[o] == Set_A4[p])
                {
                    exist = 1;
                }
            }

            if(exist == 0)
            {
                Union_Set[leng] = Set_A3[o];
                leng++;
            }
        }

        *N3 = leng;

        return Union_Set;
    }

}
//---------------------------------------------------------
char* set_difference(char *A5, int *N5, char *A6, int *N6)
{
    char *Set_A5, *Set_A6, *Diff_Set;
    int leng = 0;
    int i, j;
    int k = 0;

    Set_A5 = (char*)malloc((*N5)*sizeof(char));
    Set_A6 = (char*)malloc((*N6)*sizeof(char));

    Set_A5 = set(A5, N5);
    Set_A6 = set(A6, N6);
    Diff_Set = (char*)malloc((*N5)*sizeof(char));

    for(i=0;i < *N5;i++)
    {
        for(j=0;j < *N6;j++)
        {
            if(Set_A5[i] == Set_A6[j])
                break;
        }

        if(j == *N6)
        {
            Diff_Set[k] = Set_A5[i];
            k++;
        }
    }

    *N5 = k;

    return Diff_Set;
}
//----------------------------------------------------------
char *set_sort(char *A7, int *N7, int choice)
{
    if(choice == 1)
    {
        for(int z=0;z < *N7-1;z++)
        {
            int swap_count = 0;
            for(int x=0;x < *N7-z-1;x++)
            {
                if(A7[x] > A7[x+1])
                {
                    char temp = 0;
                    temp = A7[x];
                    A7[x] = A7[x+1];
                    A7[x+1] = temp;
                    swap_count = 1;
                }
            }
            if(swap_count == 0)
                return A7;
        }
    }

    if(choice == 0)
    {
        for(int z=0;z < *N7-1;z++)
        {
            int swap_count = 0;
            for(int x=0;x < *N7-z-1;x++)
            {
                if(A7[x] < A7[x+1])
                {
                    char temp = 0;
                    temp = A7[x];
                    A7[x] = A7[x+1];
                    A7[x+1] = temp;
                    swap_count = 1;
                }
            }
            if(swap_count == 0)
                return A7;
        }
    }

    return A7;
}
//----------------------------------------------------------
char maxof(char *A8, int *N8)
{
    char max_elem = A8[0];

    for(int d=0;d < *N8;d++)
    {
        if(A8[d] > max_elem)
        {
            max_elem = A8[d];
        }
    }

    return max_elem;
}
//----------------------------------------------------------
char minof(char *A9, int *N9)
{
    char min_elem = A9[0];

    for(int d=0;d < *N9;d++)
    {
        if(A9[d] < min_elem)
        {
            min_elem = A9[d];
        }
    }

    return min_elem;
}
//-----------------------------------------------------------
char sumall(char *A9, int *N9)
{
    char adding = 0;

    for(int y=0;y < *N9;y++)
    {
        adding += A9[y];
    }

    return adding;
}