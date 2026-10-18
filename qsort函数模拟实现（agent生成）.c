#include <stdio.h>
#include <stddef.h>

void bubble_sort(void *base, size_t count, size_t size,
                 int (*compar)(const void *, const void *))
{
    if (base == NULL || compar == NULL || size == 0 || count < 2)
    {
        return;
    }

    unsigned char *bytes = base;
    for (size_t i = 0; i < count - 1; i++)
    {
        int swapped = 0;
        for (size_t j = 0; j < count - 1 - i; j++)
        {
            unsigned char *left = bytes + j * size;
            unsigned char *right = left + size;
            if (compar(left, right) > 0)
            {
                for (size_t k = 0; k < size; k++)
                {
                    unsigned char temp = left[k];
                    left[k] = right[k];
                    right[k] = temp;
                }
                swapped = 1;
            }
        }

        if (!swapped)
        {
            break;
        }
    }
}

int compare_int(const void *left, const void *right)
{
    int a = *(const int *)left;
    int b = *(const int *)right;
    return (a > b) - (a < b);
}

struct Student
{
    const char *name;
    int age;
};

int compare_student_by_age(const void *left, const void *right)
{
    const struct Student *a = left;
    const struct Student *b = right;
    return (a->age > b->age) - (a->age < b->age);
}

int main(void)
{
    int numbers[] = {9, 3, 7, 1, 5};
    size_t number_count = sizeof(numbers) / sizeof(numbers[0]);
    bubble_sort(numbers, number_count, sizeof(numbers[0]), compare_int);

    printf("Sorted integers: ");
    for (size_t i = 0; i < number_count; i++)
    {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    struct Student students[] = {
        {"Alice", 20},
        {"Bob", 18},
        {"Carol", 22}
    };
    size_t student_count = sizeof(students) / sizeof(students[0]);
    bubble_sort(students, student_count, sizeof(students[0]),
                compare_student_by_age);

    printf("Students sorted by age:\n");
    for (size_t i = 0; i < student_count; i++)
    {
        printf("%s: %d\n", students[i].name, students[i].age);
    }

    return 0;
}
