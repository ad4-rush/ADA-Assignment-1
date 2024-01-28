import time
import random

def count_smaller_or_equal(arr, target):
    # print("Using smaller_or_equal")
    # Count the number of elements in arr that are less than or equal to target
    count = 0
    left, right = 0, len(arr) - 1

    while left <= right:
        mid = (left + right) // 2
        if arr[mid] <= target:
            count = mid + 1
            left = mid + 1
        else:
            right = mid - 1

    return count


def count_greater_or_equal(arr, target):
    # print("Using g_or_equal")
    # Count the number of elements in arr that are greater than or equal to target
    count = 0
    left, right = 0, len(arr) - 1

    while left <= right:
        mid = (left + right) // 2
        if arr[mid] >= target:
            count += right - mid + 1  # Update the count correctly
            right = mid - 1
        else:
            left = mid + 1

    return count
def brute_force_kth_smallest_element(a, b, c, k):
    print("Using Brute Force")
    a_pointer = b_pointer = c_pointer = 0
    while True:
        if a[a_pointer] <= b[b_pointer] and a[a_pointer] <= c[c_pointer]:
            a_pointer += 1
            if a_pointer + b_pointer + c_pointer >= k:
                return A[a_pointer - 1]
        elif a[a_pointer] >= b[b_pointer] and b[b_pointer] <= c[c_pointer]:
            b_pointer += 1
            if a_pointer + b_pointer + c_pointer >= k:
                return B[b_pointer - 1]
        elif a[a_pointer] >= c[c_pointer] and b[b_pointer] >= c[c_pointer]:
            c_pointer += 1
            if a_pointer + b_pointer + c_pointer >= k:
                return C[c_pointer - 1]


def kth_smallest_element(A, B, C, k):
    last = -1
    if len(A)*3<k:
        print("K is greater than 3*n")
        return None
    if (len(A)>k):
        last = k    
    if k<len(A)/10 and len(A)<100:
        return brute_force_kth_smallest_element(A, B, C, k)
    # Define the search range based on the minimum and maximum values in the three arrays
    low, high = min(A[0], B[0], C[0]), max(A[last], B[last], C[last])

    while low < high:
        mid = (low + high) // 2

        # Check if k is greater than 1.5 times the total number of elements
        if k > 1.5 * (len(A)):
            # Count the number of elements greater than or equal to mid in A, B, and C
            count_a = count_greater_or_equal(A, mid)
            count_b = count_greater_or_equal(B, mid)
            count_c = count_greater_or_equal(C, mid)

            total_count = len(A)*3-(count_a + count_b + count_c)+1
        else:
            # Count the number of elements less than or equal to mid in A, B, and C
            count_a = count_smaller_or_equal(A, mid)
            count_b = count_smaller_or_equal(B, mid)
            count_c = count_smaller_or_equal(C, mid)

            total_count = count_a + count_b + count_c

        # Adjust the search range based on the count
        if total_count < k:
            low = mid + 1
        else:
            high = mid
    print(low)
    return low

# Sample O(n) operation for comparison
def linear_operation(arr):
    total = 0
    for element in arr:
        total += element
    return total

# Function to generate random sorted arrays of size n
def generate_sorted_arrays(n):
    A = [3 * i + 1 for i in range(n)]
    B = [elem + 1 for elem in A]
    C = [elem + 1 for elem in B]
    return A, B, C

# Function to measure execution time of a function
def measure_time(func, *args):
    start_time = time.time()
    func(*args)
    end_time = time.time()
    return end_time - start_time

# Main comparison function
def compare_time_complexity(n, k):
    A, B, C = generate_sorted_arrays(n)
    print("ALL ARRAY CREATED ")
    # Measure time for the given algorithm
    algorithm_time = measure_time(kth_smallest_element, A, B, C, k)

    # Measure time for a sample O(n) operation
    print(f"Given Algorithm Time: {algorithm_time:.6f} seconds")
    sample_operation_time = measure_time(linear_operation, A)

    print(f"Sample O(n) Operation Time: {sample_operation_time:.6f} seconds")

# Example usage with n = 1000 and k = 500
compare_time_complexity(10000000, 500000)
