#include <stdio.h>
#include <stdlib.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

typedef struct node
{
    short data;
    short idx;
    struct node *next;
} node;

int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{

    node *idxs[0x10000];
    int flags[0x10000];

    int *res = malloc(2 * sizeof(int));
    *returnSize = 2;

    for (int i = 0; i < numsSize; i++)
    {
        int num = nums[i];
        int obj = target - num;
        int hash = obj & 0xffff;

        if (flags[hash] == 0xdeadbeef)
        {
            for (node *cur = idxs[hash]; cur != NULL; cur = cur->next)
            {
                if (cur->data == (obj >> 16))
                {
                    res[0] = i;
                    res[1] = cur->idx;
                    return res;
                }
            }
        }

        hash = num & 0xffff;

        node *p = malloc(sizeof(node));
        p->data = num >> 16;
        p->idx = i;
        p->next = idxs[hash];
        idxs[hash] = p;
        flags[hash] = 0xdeadbeef;
    }

    return res;
}

main()
{
    int nums[] = {3, 3};
    int numSize = 2;
    int target = 6;
    int returnSize;
    int *res = twoSum(nums, numSize, target, &returnSize);
    for (int i = 0; i < returnSize; i++)
    {
        printf("%d\n", res[i]);
    }
}
