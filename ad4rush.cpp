#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

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
        cout<<low<<high<<endl;//for testing
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

    cout << low << endl;
    return low;
}

int main() {
    vector<int> A = {0, 2, 5, 8, 15};
    vector<int> B = {1, 7, 9, 12, 20};
    vector<int> C = {0, 2, 4, 11, 18};
    int k = 1;

    int result = kth_smallest_element(A, B, C, k);
    cout << "The " << k << "-th smallest element is: " << result << endl;

    return 0;
}
