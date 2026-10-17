#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* 排序函数类型；true 表示成功。 */
typedef bool (*SortFunction)(int *, size_t);

/* 交换两个整数。 */
static void swap(int *a, int *b)
{
    /* 暂存一个值，避免交换时覆盖。 */
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* 冒泡排序：逐轮将最大值移到末尾。 */
static bool bubble_sort(int *array, size_t length)
{
    /* end 是未排序区间的右边界。 */
    for (size_t end = length; end > 1; --end) {
        /* 标记本轮是否发生交换。 */
        bool swapped = false;
        /* 比较相邻元素并将较大值右移。 */
        for (size_t i = 1; i < end; ++i) {
            if (array[i - 1] > array[i]) {
                swap(&array[i - 1], &array[i]);
                swapped = true;
            }
        }
        /* 未交换表示数组已有序。 */
        if (!swapped) {
            break;
        }
    }
    return true;
}

/* 选择排序：每轮将未排序部分的最小值放到开头。 */
static bool selection_sort(int *array, size_t length)
{
    /* i 是未排序区间的起点。 */
    for (size_t i = 0; i < length; ++i) {
        /* 记录当前最小值下标。 */
        size_t min_index = i;
        /* 扫描剩余元素，寻找最小值。 */
        for (size_t j = i + 1; j < length; ++j) {
            if (array[j] < array[min_index]) {
                min_index = j;
            }
        }
        /* 将最小值放到未排序区间开头。 */
        if (min_index != i) {
            swap(&array[i], &array[min_index]);
        }
    }
    return true;
}

/* 插入排序：将当前元素插入前方有序区间。 */
static bool insertion_sort(int *array, size_t length)
{
    /* 从第二个元素开始逐个插入。 */
    for (size_t i = 1; i < length; ++i) {
        /* 暂存待插入值。 */
        int value = array[i];
        /* j 从待插入位置向左扫描。 */
        size_t j = i;
        /* 将较大元素右移，为 value 腾出位置。 */
        while (j > 0 && array[j - 1] > value) {
            array[j] = array[j - 1];
            --j;
        }
        /* 放入待插入值。 */
        array[j] = value;
    }
    return true;
}

/* 希尔排序：缩小间隔，对分组元素进行插入排序。 */
static bool shell_sort(int *array, size_t length)
{
    /* 间隔从一半逐次减半，最终为 1。 */
    for (size_t gap = length / 2; gap > 0; gap /= 2) {
        /* 对间隔为 gap 的元素执行插入排序。 */
        for (size_t i = gap; i < length; ++i) {
            /* 暂存当前待插入值。 */
            int value = array[i];
            /* j 从当前位置向前移动。 */
            size_t j = i;
            while (j >= gap && array[j - gap] > value) {
                array[j] = array[j - gap];
                j -= gap;
            }
            /* 放入正确位置。 */
            array[j] = value;
        }
    }
    return true;
}

/* 合并两个相邻有序区间。 */
static void merge_ranges(int *array, int *buffer, size_t left,
                         size_t middle, size_t right)
{
    /* i、j 遍历左右区间，out 指向缓冲区写入位置。 */
    size_t i = left;
    size_t j = middle;
    size_t out = left;

    /* 依次写入两区间中较小的元素。 */
    while (i < middle && j < right) {
        if (array[i] <= array[j]) {
            buffer[out++] = array[i++];
        } else {
            buffer[out++] = array[j++];
        }
    }
    /* 复制左区间剩余元素。 */
    while (i < middle) {
        buffer[out++] = array[i++];
    }
    /* 复制右区间剩余元素。 */
    while (j < right) {
        buffer[out++] = array[j++];
    }
    /* 将合并结果写回原数组。 */
    for (i = left; i < right; ++i) {
        array[i] = buffer[i];
    }
}

/* 递归排序区间并合并两半。 */
static void merge_sort_range(int *array, int *buffer, size_t left, size_t right)
{
    /* 长度小于 2 时递归结束。 */
    if (right - left < 2) {
        return;
    }
    /* 计算区间中点。 */
    size_t middle = left + (right - left) / 2;
    /* 分别排序左右区间。 */
    merge_sort_range(array, buffer, left, middle);
    merge_sort_range(array, buffer, middle, right);
    /* 合并有序区间。 */
    merge_ranges(array, buffer, left, middle, right);
}

/* 归并排序入口：分配缓冲区并启动递归。 */
static bool merge_sort(int *array, size_t length)
{
    /* 少于两个元素无需排序。 */
    if (length < 2) {
        return true;
    }
    /* 检查分配大小是否溢出。 */
    if (length > (size_t)-1 / sizeof(*array)) {
        return false;
    }
    /* 分配临时缓冲区。 */
    int *buffer = malloc(length * sizeof(*buffer));
    if (buffer == NULL) {
        return false;
    }
    /* 排序整个数组。 */
    merge_sort_range(array, buffer, 0, length);
    /* 释放缓冲区。 */
    free(buffer);
    return true;
}

/* 快速排序递归：按基准值划分区间。 */
static void quick_sort_range(int *array, size_t low, size_t high)
{
    /* 单元素区间无需处理。 */
    if (low >= high) {
        return;
    }

    /* i、j 分别从两端扫描。 */
    size_t i = low;
    size_t j = high;
    /* 取区间中间值为基准。 */
    int pivot = array[low + (high - low) / 2];

    /* 双向扫描并交换位置不当的元素。 */
    while (i <= j) {
        /* 跳过小于基准值的元素。 */
        while (array[i] < pivot) {
            ++i;
        }
        /* 跳过大于基准值的元素。 */
        while (array[j] > pivot) {
            --j;
        }
        /* 交换两侧位置不当的元素。 */
        if (i <= j) {
            swap(&array[i], &array[j]);
            ++i;
            /* 防止无符号下标下溢。 */
            if (j == 0) {
                break;
            }
            --j;
        }
    }

    /* 递归排序基准值两侧区间。 */
    if (low < j) {
        quick_sort_range(array, low, j);
    }
    if (i < high) {
        quick_sort_range(array, i, high);
    }
}

/* 快速排序入口。 */
static bool quick_sort(int *array, size_t length)
{
    /* 长度大于 1 时递归排序整个数组。 */
    if (length > 1) {
        quick_sort_range(array, 0, length - 1);
    }
    return true;
}

/* 向下调整节点，使子树满足最大堆性质。 */
static void sift_down(int *array, size_t root, size_t length)
{
    /* root 位于非叶子节点范围内时继续调整。 */
    while (root < length / 2) {
        /* 选择较大的孩子。 */
        size_t child = root * 2 + 1;
        if (child + 1 < length && array[child] < array[child + 1]) {
            ++child;
        }
        /* 父节点已不小于孩子，调整结束。 */
        if (array[root] >= array[child]) {
            return;
        }
        /* 交换父子节点并继续向下调整。 */
        swap(&array[root], &array[child]);
        root = child;
    }
}

/* 堆排序：构建最大堆并依次取出堆顶。 */
static bool heap_sort(int *array, size_t length)
{
    /* 自底向上构建最大堆。 */
    for (size_t i = length / 2; i > 0; --i) {
        sift_down(array, i - 1, length);
    }
    /* 将堆顶最大值移到末尾并缩小堆范围。 */
    for (size_t end = length; end > 1; --end) {
        swap(&array[0], &array[end - 1]);
        /* 恢复剩余区间的最大堆性质。 */
        sift_down(array, 0, end - 1);
    }
    return true;
}

/* 计数排序：统计各整数出现次数，适合数值范围较小的数据。 */
static bool counting_sort(int *array, size_t length)
{
    /* 少于两个元素无需排序。 */
    if (length < 2) {
        return true;
    }

    /* 查找数据的最小值和最大值。 */
    int min_value = array[0];
    int max_value = array[0];
    for (size_t i = 1; i < length; ++i) {
        if (array[i] < min_value) {
            min_value = array[i];
        }
        if (array[i] > max_value) {
            max_value = array[i];
        }
    }

    /* 计算计数范围，使用 long long 避免 int 减法溢出。 */
    size_t range = (size_t)((long long)max_value - (long long)min_value + 1);
    /* 检查分配大小是否溢出。 */
    if (range > (size_t)-1 / sizeof(size_t)) {
        return false;
    }
    /* 分配并清零计数数组。 */
    size_t *counts = calloc(range, sizeof(*counts));
    if (counts == NULL) {
        return false;
    }

    /* 统计每个数值的出现次数。 */
    for (size_t i = 0; i < length; ++i) {
        /* index 是当前数值对应的计数下标。 */
        size_t index = (size_t)((long long)array[i] - (long long)min_value);
        ++counts[index];
    }

    /* 按数值顺序将统计结果写回数组。 */
    size_t output = 0;
    for (size_t i = 0; i < range; ++i) {
        while (counts[i] > 0) {
            array[output++] = (int)((long long)min_value + (long long)i);
            --counts[i];
        }
    }

    /* 释放计数数组。 */
    free(counts);
    return true;
}

/* 基数排序：从低位到高位稳定地处理整数各位。 */
static bool radix_sort(int *array, size_t length)
{
    /* 少于两个元素无需排序。 */
    if (length < 2) {
        return true;
    }
    /* 检查缓冲区分配大小是否溢出。 */
    if (length > (size_t)-1 / sizeof(*array)) {
        return false;
    }

    /* 分配排序所需的辅助缓冲区。 */
    int *buffer = malloc(length * sizeof(*buffer));
    if (buffer == NULL) {
        return false;
    }

    /* 翻转符号位，使无符号排序顺序符合有符号整数顺序。 */
    const unsigned int sign_bit = UINT_MAX / 2u + 1u;
    /* source 和 destination 分别是本轮读、写数组。 */
    int *source = array;
    int *destination = buffer;

    /* 逐位进行稳定分组。 */
    for (size_t bit = 0; bit < sizeof(unsigned int) * CHAR_BIT; ++bit) {
        /* 统计当前位为 0 的元素个数。 */
        size_t zero_count = 0;

        /* 确定当前位为 1 的区间起点。 */
        for (size_t i = 0; i < length; ++i) {
            /* key 将有符号数映射为可排序的无符号键值。 */
            unsigned int key = (unsigned int)source[i] ^ sign_bit;
            if (((key >> bit) & 1u) == 0) {
                ++zero_count;
            }
        }

        /* 分别记录 0 和 1 的写入位置。 */
        size_t zero_index = 0;
        size_t one_index = zero_count;
        /* 按原顺序写入两组，保持稳定性。 */
        for (size_t i = 0; i < length; ++i) {
            unsigned int key = (unsigned int)source[i] ^ sign_bit;
            if (((key >> bit) & 1u) == 0) {
                destination[zero_index++] = source[i];
            } else {
                destination[one_index++] = source[i];
            }
        }

        /* 交换读写数组，处理下一位。 */
        int *temp = source;
        source = destination;
        destination = temp;
    }

    /* 结果在缓冲区时复制回原数组。 */
    if (source != array) {
        for (size_t i = 0; i < length; ++i) {
            array[i] = source[i];
        }
    }
    /* 释放缓冲区。 */
    free(buffer);
    return true;
}

/* qsort 比较函数：按整数升序比较。 */
static int compare_ints(const void *left, const void *right)
{
    /* 将通用指针转换为整数指针并读取值。 */
    int a = *(const int *)left;
    int b = *(const int *)right;
    /* 避免直接相减导致溢出。 */
    return (a > b) - (a < b);
}

/* 使用标准库 qsort 排序。 */
static bool standard_qsort(int *array, size_t length)
{
    qsort(array, length, sizeof(*array), compare_ints);
    return true;
}

/* 检查数组是否升序排列。 */
static bool is_sorted(const int *array, size_t length)
{
    /* 检查相邻元素是否逆序。 */
    for (size_t i = 1; i < length; ++i) {
        if (array[i - 1] > array[i]) {
            return false;
        }
    }
    return true;
}

/* 依次运行并验证所有排序算法。 */
int main(void)
{
    /* 测试数据包含负数和重复值。 */
    const int input[] = {29, -10, 0, 45, 7, -3, 7, 100, -50, 42};
    /* 输入元素个数。 */
    const size_t length = sizeof(input) / sizeof(input[0]);
    /* 每种算法使用独立的工作数组。 */
    int work[sizeof(input) / sizeof(input[0])];
    /* 算法名称及对应函数。 */
    const struct {
        const char *name;
        SortFunction sort;
    } sorts[] = {
        {"Bubble sort", bubble_sort},
        {"Selection sort", selection_sort},
        {"Insertion sort", insertion_sort},
        {"Shell sort", shell_sort},
        {"Merge sort", merge_sort},
        {"Quick sort", quick_sort},
        {"Heap sort", heap_sort},
        {"Counting sort", counting_sort},
        {"Radix sort (signed integers)", radix_sort},
        {"C library qsort", standard_qsort}
    };

    /* 依次测试各算法。 */
    for (size_t i = 0; i < sizeof(sorts) / sizeof(sorts[0]); ++i) {
        /* 重置工作数组。 */
        for (size_t j = 0; j < length; ++j) {
            work[j] = input[j];
        }
        /* 执行当前排序。 */
        if (!sorts[i].sort(work, length)) {
            fprintf(stderr, "%s failed: unable to allocate memory or range too large\n",
                    sorts[i].name);
            return EXIT_FAILURE;
        }
        /* 验证排序结果。 */
        if (!is_sorted(work, length)) {
            fprintf(stderr, "%s failed validation\n", sorts[i].name);
            return EXIT_FAILURE;
        }

        /* 打印算法名称和排序结果。 */
        printf("%-28s", sorts[i].name);
        for (size_t j = 0; j < length; ++j) {
            printf("%s%d", j == 0 ? "" : " ", work[j]);
        }
        putchar('\n');
    }

    /* 所有算法均执行成功。 */
    return EXIT_SUCCESS;
}
