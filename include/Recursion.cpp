#include "Recursion.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <random> // 包含隨機數生成的標頭文件
#include <ctime>  // 包含時間相關函式的標頭文件

double power(double n, int p)
{
    /*
    宣告 double power(double n, int p); ，然後使用下面的方式來做遞迴:
    (0) 先檢查 p 是否等於 0，是的話就傳回答案 1; 若 p 不等於 0 則先算出 ans = power(n, p/2);
    (1) 如果 p 是偶數，則 return ans*ans;
    (2) 如果 p 是奇數，則 return n*ans*ans;
    這裡有使用到整數除法無條件捨去的特性。
    */
    if (p == 0)
        return 1;
    else
    {
        double ans = power(n, p / 2);
        if (p % 2 == 0)
            return ans * ans;
        else
            return n * ans * ans;
    }
}

int show_parenthesis(int n)
{
    /*
    用 recursive 方式，產生下面的輸出
    Input: 10
    Output: ((((1+2)*3+4)*5+6)*7+8)*9+10=4555
    Input: 11
    Output: (((((1+2)*3+4)*5+6)*7+8)*9+10)*11=50105
    */
    if (n == 1)
        return 1;

    if (n % 2 == 0)
        return (show_parenthesis(n - 1) + n);
    else
        return (show_parenthesis(n - 1) * n);
}

void hanoi(char from, char to, char buffer, int n_disks)
{
    // Tower of Honoi//
    if (n_disks == 2)
    {
        printf("move the top disk from tower %c to %c \n", from, buffer);
        printf("move the top disk from tower %c to %c \n", from, to);
        printf("move the top disk from tower %c to %c \n", buffer, to);
    }
    else
    {
        hanoi(from, buffer, to, n_disks - 1);
        printf("move the top disk from tower %c to %c \n", from, to);
        hanoi(buffer, to, from, n_disks - 1);
    }
}

namespace castle
{
    /*
     *三座城堡問題： 在 3x3 的棋盤上擺三個城堡。 城堡只能走水平或垂直方向，
     *可以吃掉在同一條水平或垂直線上的其他棋子。所以每個 row 只能擺一個城堡。
     *修改底下的程式碼，使得最後只輸出滿足互不衝突、互不吃掉對方的擺法。
     */

    /*想法
    1.每一個row一定會有一個castle
    2.固定在第一個row放置1城堡，再從第二個row擺放，依序由上往下

    place fun
    if col <3
        放置成功後結束往下一col 放置
    if col == row
        放置成功後結束，回傳結果
    */
    int board[5][5] = {0};
    bool check_safe(int col, int table_size)
    {
        for (int i = 0; i < table_size; i++)
        {
            if (board[i][col] == 1)
                return false;
        }
        return true;
    }

    void place(int row, int table_size)
    {
        if (row == table_size)
            show_board(table_size);
        else
        {
            for (int col = 0; col < table_size; col++)
            {
                if (check_safe(col, table_size))
                {
                    board[row][col] = 1;
                    place(row + 1, table_size);
                    board[row][col] = 0;
                }
            }
        }
    }

    void show_board(int table_size)
    {
        for (int i = 0; i < table_size; i++)
        {
            for (int j = 0; j < table_size; j++)
            {
                printf(" %d", board[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

namespace queen
{
    /* q[i] 記錄的是在第 i 列 (row) 出現的皇后，要擺在第幾行 (column) */
    /* 譬如，q[] 的內容如果是 {2, 0, 3, 1}，表示四個皇后分別放在棋盤的 (0,2), (1,0), (2,3), (3,1) 四個位置 */
    int abs(int x) { return (x < 0 ? x : -x); }
    int Q_position[8][8] = {0};

    bool vaild(int cur_row, int cur_col)
    {
        for (int pre_qn_row = 0; pre_qn_row < 8; pre_qn_row++)
        {
            for (int pre_qn_col = 0; pre_qn_col < 8; pre_qn_col++)
            {
                if (Q_position[pre_qn_row][pre_qn_col])
                {
                    int dx = abs(cur_row - pre_qn_row);
                    int dy = abs(cur_col - pre_qn_col);
                    if (dx == 0 | dy == 0 | dy == dx)
                        return false;
                }
            }
        }
        return true;
    }
    void show_board(int table_size = 8)
    {
        for (int i = 0; i < table_size; i++)
        {
            for (int j = 0; j < table_size; j++)
            {
                printf(" %d", Q_position[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }

    void place(int cur_row)
    {
        if (cur_row == 8)
            show_board();
        else
        {
            for (int cur_col = 0; cur_col < 8; cur_col++)
            {
                if (vaild(cur_row, cur_col))
                {
                    Q_position[cur_row][cur_col] = 1;
                    place(cur_row + 1);
                    Q_position[cur_row][cur_col] = 0;
                }
            }
        }
    }

}

namespace MakeChange
{
    /*
    輸入不同面值的銅板，然後輸入一個金額，將全部可能的找零方式列出。
    譬如有 1 元、5元、10元銅板， 要湊出 17 元，如果將可能的組合表示成 "(1元個數,5元個數,10元個數)"，總共會有下列幾種方法：
    (2,1,1)
    (2,3,0)
    (7,0,1)
    (7,2,0)
    (12,1,0)
    (17,0,0)
    */
    int coin_list[10] = {1, 5, 10};
    int coin_num[10] = {0};
    void show_change(int coin_type)
    {
        int i;
        printf("(%d", coin_num[0]);
        for (i = 1; i < coin_type; i++)
        {
            printf(",%d", coin_num[i]);
        }
        printf(")\n");
    }

    void exchange(int amount, int smallest, int coin_type)
    {
        if (smallest < coin_type)
        {
            if (amount == 0)
                show_change(coin_type);
            else if (amount > 0)
            {
                // 換一個coin type
                exchange(amount, smallest + 1, coin_type);
                // amount 換一個coin
                coin_num[smallest]++;
                exchange(amount - coin_list[smallest], smallest, coin_type);
                coin_num[smallest]--;
            }
        }
    };

}
void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}
namespace Merge_sort
{
    void merge(int *arr, int num)
    {
        int R_count(0), L_count(0);
        int *sorted_arr = new int[num];

        for (int i = 0; i < num; i++)
        {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
        for (int i = 0; i < num; i++)
        {

            if (L_count == num / 2)
            {
                sorted_arr[i] = arr[R_count + num / 2];
                ++R_count;
            }
            else if (R_count == num / 2)
            {
                sorted_arr[i] = arr[L_count];
                ++L_count;
            }
            else if (arr[R_count + num / 2] < arr[L_count])
            {
                sorted_arr[i] = arr[R_count + num / 2];
                ++R_count;
            }
            else
            {
                sorted_arr[i] = arr[L_count];
                ++L_count;
            }
        }

        for (int i = 0; i < num; i++)
        {
            arr[i] = sorted_arr[i];
            std::cout << sorted_arr[i] << " ";
        }
        std::cout << std::endl;
        delete[] sorted_arr;
        sorted_arr = NULL;
    }

    void merge_sort(int *arr, int num)
    {
        if (num > 2)
        {
            merge_sort(arr, num / 2);
            merge_sort(arr + num / 2, num / 2);
            merge(arr, num);
        }

        else if ((arr[0] > arr[1]) & num == 2)
        {
            swap(arr[0], arr[1]);
        }
    }

}

namespace merge2
{
    void merge(int *arr, int left_index, int left_len, int right_index, int right_len)
    {
        int buffer[20] = {0};
        int left_count(0), right_count(0), buf_index(0);
        while (left_count < left_len & right_count < right_len)
        {
            if (arr[left_index + left_count] > arr[right_index + right_count])
                buffer[buf_index++] = arr[right_index + right_count++];
            else
                buffer[buf_index++] = arr[left_index + left_count++];
        }

        while (right_count < right_len)
        {
            buffer[buf_index++] = arr[right_index + right_count++];
        }

        while (left_count < left_len)
        {
            buffer[buf_index++] = arr[left_index + left_count++];
        }

        for (int i = 0; i < (right_len + left_len); i++)
            arr[left_index + i] = buffer[i];
        return;
    }

    void merge_sort(int *arr, int left_index, int right_index)
    {
        if (left_index >= right_index)
            return;
        int mid = left_index + (right_index - left_index) / 2;
        merge_sort(arr, left_index, mid);
        merge_sort(arr, mid + 1, right_index);
        printf("%d, %d, %d, %d\n", left_index, mid - left_index + 1, mid + 1, right_index - mid);
        merge(arr, left_index, mid - left_index + 1, mid + 1, right_index - mid);
        for (int i = 0; i < 16; i++)
            printf("%d, ", arr[i]);
        printf("\n");
        return;
    }

}