#include <stdio.h>
#include <stdlib.h> 

struct date_and_time 
{
    int day;
    int month;
    int year;
    int hour;
    int minute;
    int second;
};

struct data 
{
    int product_ID;
    int issue_code;
    struct date_and_time DAT;
};

void task(struct data[], int);

void merge_sort(struct data[], int, int, int);

void merge(struct data[], int, int, int, int, int);

void search_issue_code(struct data[], int, int);

void duplicates(struct data logs[], int size);


int main() 
{
    struct data task1[5]; // Set 1
    struct data task2[5]; // Set 2
    struct data task3[5]; // Set 3

    printf("\nTASK 1\n\n");

    task(task1, 1);

    task(task2, 2);

    task(task3, 3);

    // Combine all logs into a single array
    struct data all_logs[15];
    for (int i = 0; i < 5; i++) 
    {
        all_logs[i] = task1[i];
        all_logs[i + 5] = task2[i];
        all_logs[i + 10] = task3[i];
    }

    // Sort all logs by product ID
    merge_sort(all_logs, 0, 14, 2);

    printf("\nTASK 2\n\n");
    printf("\nAll Logs sorted by Product ID\n\n");
    for (int i = 0; i < 15; i++) 
    {
        printf("Product ID: %d     ", all_logs[i].product_ID);
        printf("Issue Code: %d     ", all_logs[i].issue_code);
        printf("Date and Time: %d/%d/%d %d:%d:%d\n", all_logs[i].DAT.day, all_logs[i].DAT.month, all_logs[i].DAT.year, all_logs[i].DAT.hour, all_logs[i].DAT.minute, all_logs[i].DAT.second);
    }
    printf("--------------------------------------------------------------------------------\n");

    // Search for earliest occurrence of an issue code for a given product ID
    int search_product_id;

    printf("\nTASK 3\n\n");
    printf("Enter Product ID to search for earliest occurrence of issue code: ");

    scanf("%d", &search_product_id);

    // Call search issue code function
    search_issue_code(all_logs, 15, search_product_id);

    // Call duplicates function
    duplicates(all_logs, 8); 

    return 0;
}

// Compare two struct data objects based on the desired factor
int compare(struct data a, struct data b, int factor) 
{
    switch(factor) 
    {
        case 1: // Sort by Date & Time 
            if (a.DAT.year != b.DAT.year)
                return a.DAT.year - b.DAT.year;
            if (a.DAT.month != b.DAT.month)
                return a.DAT.month - b.DAT.month;
            if (a.DAT.day != b.DAT.day)
                return a.DAT.day - b.DAT.day;
            if (a.DAT.hour != b.DAT.hour)
                return a.DAT.hour - b.DAT.hour;
            if (a.DAT.minute != b.DAT.minute)
                return a.DAT.minute - b.DAT.minute;
            return a.DAT.second - b.DAT.second;

        case 2: // Sort by Product ID
            return a.product_ID - b.product_ID;

        case 3: // Sort by Issue Code 
            return a.issue_code - b.issue_code;

        default:
            return 0;
    }
}

// Merge sort implementation to sort the array of struct data objects
void merge_sort(struct data arr[], int left, int right, int factor) 
{
    if (left < right) 
    {
        int mid = (left + right) / 2;
        merge_sort(arr, left, mid, factor);
        merge_sort(arr, mid + 1, right, factor);
        merge(arr, left, mid, mid + 1, right, factor);
    }
}

// Merge function to merge two sorted subarrays
void merge(struct data arr[], int left_start, int left_end, int right_start, int right_end, int factor) 
{
    int left_size = left_end - left_start + 1;
    int right_size = right_end - right_start + 1;
    struct data *left_arr = (struct data *)malloc(left_size * sizeof(struct data));
    struct data *right_arr = (struct data *)malloc(right_size * sizeof(struct data));

    for (int i = 0; i < left_size; i++) 
    {
        left_arr[i] = arr[left_start + i];
    }
    for (int j = 0; j < right_size; j++) 
    {
        right_arr[j] = arr[right_start + j];
    }

    int left_index = 0, right_index = 0, merged_index = left_start;

    while (left_index < left_size && right_index < right_size) 
    {
        if (compare(left_arr[left_index], right_arr[right_index], factor) <= 0) 
        {
            arr[merged_index++] = left_arr[left_index++];
        } 
        else 
        {
            arr[merged_index++] = right_arr[right_index++];
        }
    }
    while (left_index < left_size) 
    {
        arr[merged_index++] = left_arr[left_index++];
    }

    while (right_index < right_size) 
    {
        arr[merged_index++] = right_arr[right_index++];
    }

    free(left_arr);
    free(right_arr);
}

void task(struct data task[], int set_number) 
{
    switch(set_number)
    {
        case 1: // Generate random data and sort set one by Product ID
            for (int i = 0; i < 5; i++) 
            {
                
                task[i].product_ID = set_number * 100 + i + 1;
                task[i].issue_code = set_number * 1000 + i + 1;
                task[i].DAT.day = rand() % 30 + 1; // Random day between 1 and 30
                task[i].DAT.month = rand() % 12 + 1; // Random month between 1 and 12
                task[i].DAT.year = rand() % 10 + 2015; // Random year between 2015 and 2024
                task[i].DAT.hour = rand() % 24; // Random hour between 0 and 23
                task[i].DAT.minute = rand() % 60; // Random minute between 0 and 59
                task[i].DAT.second = rand() % 60; // Random second between 0 and 59

            }

            merge_sort(task, 0, 4, 2); // Sort by Product ID
            printf("Set 1 sorted by Product ID:\n");
            break;

        case 2: // Generate random data and sort set two by Issue Code
            for (int i = 0; i < 5; i++) 
            {
                
                task[i].product_ID = set_number * 100 + i + 1;
                task[i].issue_code = set_number * 1000 + i + 1;
                task[i].DAT.day = rand() % 30 + 1; // Random day between 1 and 30
                task[i].DAT.month = rand() % 12 + 1; // Random month between 1 and 12
                task[i].DAT.year = rand() % 10 + 2015; // Random year between 2015 and 2024
                task[i].DAT.hour = rand() % 24; // Random hour between 0 and 23
                task[i].DAT.minute = rand() % 60; // Random minute between 0 and 59
                task[i].DAT.second = rand() % 60; // Random second between 0 and 59
                
            }

            merge_sort(task, 0, 4, 3); // Sort by Issue Code
            printf("Set 2 sorted by Issue Code:\n");
            break;

        case 3: // Generate random data and sort set three by Date & Time
            for (int i = 0; i < 5; i++) 
            {

                // Generate fixed product ID and issue code
                task[i].product_ID = set_number * 100 + i + 1;
                task[i].issue_code = set_number * 1000 + i + 1;
                task[i].DAT.day = rand() % 30 + 1; // Random day between 1 and 30
                task[i].DAT.month = rand() % 12 + 1; // Random month between 1 and 12
                task[i].DAT.year = rand() % 10 + 2015; // Random year between 2015 and 2024
                task[i].DAT.hour = rand() % 24; // Random hour between 0 and 23
                task[i].DAT.minute = rand() % 60; // Random minute between 0 and 59
                task[i].DAT.second = rand() % 60; // Random second between 0 and 59

            }

            merge_sort(task, 0, 4, 1); // Sort by Date & Time
            printf("Set 3 sorted by Date & Time\n");
            break;

        default:
            printf("Invalid set number.\n");
            return;
    }
    
    // Print the sorted set
    for (int i = 0; i < 5; i++) 
    {
        printf("Product ID: %d     ", task[i].product_ID);
        printf("Issue Code: %d     ", task[i].issue_code);
        printf("Date and Time: %d/%d/%d %d:%d:%d\n", task[i].DAT.day, task[i].DAT.month, task[i].DAT.year, task[i].DAT.hour, task[i].DAT.minute, task[i].DAT.second);
    }

    printf("--------------------------------------------------------------------------------\n");
}

void search_issue_code(struct data arr[], int size, int search_product_id) 
{
    int earliest_index = -1;
    for (int i = 0; i < size; i++) 
    {
        if (arr[i].product_ID == search_product_id) 
        {
            earliest_index = i;
            break;
        }
    }

    if (earliest_index != -1) 
    {
        printf("Earliest occurrence of Issue Code for Product ID %d:\n", search_product_id);
        printf("Product ID: %d     ", arr[earliest_index].product_ID);
        printf("Issue Code: %d     ", arr[earliest_index].issue_code);
        printf("Date and Time: %d/%d/%d %d:%d:%d\n", arr[earliest_index].DAT.day, arr[earliest_index].DAT.month, arr[earliest_index].DAT.year, arr[earliest_index].DAT.hour, arr[earliest_index].DAT.minute, arr[earliest_index].DAT.second);
    } 
    else 
    {
        printf("Product ID %d not found.\n", search_product_id);
    }

    printf("--------------------------------------------------------------------------------\n");
}


void duplicates(struct data logs[], int size) 
{
    printf("\nTASK 4\n\n");
    printf("Sets being checked:\n\n");

    // Hardcoded data with duplicates
    struct data hardcoded_logs[10] = 
    {

        {101, 1001, {18, 3, 2024, 10, 30, 45}},
        {102, 1002, {22, 4, 2024, 15, 32, 54}},
        {103, 1003, {17, 3, 2024, 12, 15, 20}},
        {101, 1001, {18, 3, 2024, 10, 30, 45}},
        {101, 1001, {18, 3, 2024, 10, 30, 45}},
        {102, 1002, {22, 4, 2024, 15, 32, 54}},
        {107, 1004, {21, 3, 2024, 16, 25, 55}},
        {101, 1001, {18, 3, 2024, 10, 30, 45}},
        
    };

    // Print logs with duplicates
    for (int i = 0; i < size; i++) 
    {
        printf("Set %d - Product ID: %d     ", i + 1, hardcoded_logs[i].product_ID);
        printf("Issue Code: %d     ", hardcoded_logs[i].issue_code);
        printf("Date and Time: %d/%d/%d  %d:%d:%d\n", hardcoded_logs[i].DAT.day, hardcoded_logs[i].DAT.month, hardcoded_logs[i].DAT.year, hardcoded_logs[i].DAT.hour, hardcoded_logs[i].DAT.minute, hardcoded_logs[i].DAT.second);
    }
    
    printf("--------------------------------------------------------------------------------\n");

    // Count occurrences of each product ID
    int count_product_ID = 0;
    for (int i = 0; i < size; i++) 
    {
        if (hardcoded_logs[i].product_ID > count_product_ID) 
        {
            count_product_ID = hardcoded_logs[i].product_ID;
        }
    }

    int *count = (int *)calloc(count_product_ID, sizeof(int)); // Initialize an array to store counts, initially set to 0

    for (int i = 0; i < size; i++) 
    {
        count[hardcoded_logs[i].product_ID - 1]++; // Increment count for the corresponding product ID
    }

    // Print product IDs with their counts if they have duplicates
    printf("\nProduct IDs with Duplicates:\n\n");

    for (int i = 0; i < count_product_ID; i++) 
    {
        if (count[i] > 1) 
        {
            printf("Product ID: %d     ", i + 1); // Print product ID 
            printf("Issues Reported: %d\n", count[i]);
        }
    }

    free(count); // Free dynamically allocated memory
}