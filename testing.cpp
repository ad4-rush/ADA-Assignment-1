#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace chrono;

int mini(const vector<int>& a, const vector<int>& b, const vector<int>& c) {
    return min(min(a[0], b[0]), c[0]);
}

int maxi(const vector<int>& a, const vector<int>& b, const vector<int>& c) {
    return max(max(a.back(), b.back()), c.back());
}

int count_smaller_or_equal(const vector<int>& arr, int target) {
    int count = 0;
    int left = 0, right = arr.size() - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] <= target) {
            count = mid + 1;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return count;
}

int count_greater_or_equal(const vector<int>& arr, int target) {
    int count = 0;
    int left = 0, right = arr.size() - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] > target) {
            count += right - mid + 1;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return count;
}

int kth_smallest_element(const vector<int>& A, const vector<int>& B, const vector<int>& C, int k) {
    int last = -1;

    if (A.size() * 3 + 1 < k) {
        cout << "K is greater than 3*n" << endl;
        return -1; // Return an appropriate value
    }

    if (A.size() > k) {
        last = k;
    }

    int low = mini(A, B, C);
    int high = maxi(A, B, C);

    while (low < high) {
        int mid = (low + high) / 2;

        int total_count;
        if (k > 1.5 * A.size()) {
            int count_a = count_greater_or_equal(A, mid);
            int count_b = count_greater_or_equal(B, mid);
            int count_c = count_greater_or_equal(C, mid);

            total_count = A.size() * 3 - (count_a + count_b + count_c) + 1;
        } else {
            int count_a = count_smaller_or_equal(A, mid);
            int count_b = count_smaller_or_equal(B, mid);
            int count_c = count_smaller_or_equal(C, mid);

            total_count = count_a + count_b + count_c;
        }

        if (total_count < k) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    return low;
}

// Linear-time implementation for comparison
int kth_smallest_element_linear(const vector<int>& A, const vector<int>& B, const vector<int>& C, int k) {
    vector<int> merged;
    merged.insert(merged.end(), A.begin(), A.end());
    merged.insert(merged.end(), B.begin(), B.end());
    merged.insert(merged.end(), C.begin(), C.end());

    sort(merged.begin(), merged.end());

    if (k <= merged.size()) {
        return merged[k - 1];
    } else {
        cout << "K is greater than the total number of elements" << endl;
        return -1; // Return an appropriate value
    }
}

// Function to generate a large array of random sorted integers
vector<int> generate_large_array(int size) {
    vector<int> array;
    srand(time(0));

    for (int i = 0; i < size; ++i) {
        array.push_back(rand() % 1000000); // Adjust the range as needed
    }

    sort(array.begin(), array.end());
    return array;
}

int main() {
    // Test with provided arrays
    vector<int> A = {0, 2, 5, 8, 15};
    vector<int> B = {1, 7, 9, 12, 20};
    vector<int> C = {0, 2, 4, 11, 18};
    int k = 1;

    auto start = high_resolution_clock::now();
    int result = kth_smallest_element(A, B, C, k);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "The " << k << "-th smallest element is: " << result << endl;
    cout << "Time taken by binary search: " << duration.count() << " microseconds" << endl;

    // Test with a large array
    int large_array_size = 1000000;
    vector<int> large_array = generate_large_array(large_array_size);
    k = 500000; // Adjust the value of k as needed

    start = high_resolution_clock::now();
    result = kth_smallest_element(large_array, large_array, large_array, k);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);

    cout << "The " << k << "-th smallest element (binary search) is: " << result << endl;
    cout << "Time taken by binary search: " << duration.count() << " microseconds" << endl;

    start = high_resolution_clock::now();
    result = kth_smallest_element_linear(large_array, large_array, large_array, k);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);

    cout << "The " << k << "-th smallest element (linear-time) is: " << result << endl;
    cout << "Time taken by linear-time search: " << duration.count() << " microseconds" << endl;

    return 0;
}
