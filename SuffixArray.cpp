#include <iostream>
using namespace std;

//------------------------------ Suffix -------------------------------//
class SuffixArray
{
private:
    char *str;         // Input string
    int *suffix_array; // Resultant suffix array
    int *rank;         // Rank array
    int *temp;         // Temporary rank array
    int n;             // Length of the string

public:
    SuffixArray(const char *input)
    {
        n = 0;
        while (input[n] != '\0')
        {
            n++;
        }

        str = new char[n];
        suffix_array = new int[n];
        rank = new int[n];
        temp = new int[n];

        for (int i = 0; i < n; ++i)
        {
            str[i] = input[i];
            suffix_array[i] = i;
            if (str[i] == '$')
            {
                rank[i] = 0;
            }
            rank[i] = (str[i] - 'A') + 1;
        }
    }

    ~SuffixArray()
    {
        delete[] str;
        delete[] suffix_array;
        delete[] rank;
        delete[] temp;
    }

    void ConstructUsingPrefixDoubling()
    {
        int k = 1;
        int *temp_sa = new int[n];
        while (k < n)
        {
            MergeSort(k, temp_sa);

            temp[suffix_array[0]] = 0;
            for (int i = 1; i < n; ++i)
            {
                temp[suffix_array[i]] = temp[suffix_array[i - 1]] + (Compare(k, suffix_array[i - 1], suffix_array[i]) ? 1 : 0);
            }

            for (int i = 0; i < n; ++i)
            {
                rank[i] = temp[i];
            }

            k *= 2;
        }
        delete[] temp_sa;
    }

    void Print()
    {
        for (int i = 0; i < n; ++i)
        {
            cout << suffix_array[i] << " ";
        }
        cout << endl;
    }

private:
    bool Compare(int k, int i, int j)
    {
        if (rank[i] != rank[j])
        {
            return rank[i] < rank[j];
        }
        int ri = (i + k < n) ? rank[i + k] : -1;
        int rj = (j + k < n) ? rank[j + k] : -1;
        return ri < rj;
    }

    void MergeSort(int k, int *temp_sa)
    {
        merge(0, n - 1, k, temp_sa);
    }

    void merge(int left, int right, int k, int *temp_sa)
    {
        if (left >= right)
        {
            return;
        }

        int mid = left + (right - left) / 2;

        merge(left, mid, k, temp_sa);
        merge(mid + 1, right, k, temp_sa);

        int i = left, j = mid + 1, idx = left;

        while (i <= mid && j <= right)
        {
            if (Compare(k, suffix_array[i], suffix_array[j]))
            {
                temp_sa[idx++] = suffix_array[i++];
            }
            else
            {
                temp_sa[idx++] = suffix_array[j++];
            }
        }

        while (i <= mid)
        {
            temp_sa[idx++] = suffix_array[i++];
        }

        while (j <= right)
        {
            temp_sa[idx++] = suffix_array[j++];
        }

        for (int i = left; i <= right; ++i)
        {
            suffix_array[i] = temp_sa[i];
        }
    }
};
//------------------------------- MAIN -------------------------------//
int main()
{
    SuffixArray t("ACGACTACGATAAC$");
    t.ConstructUsingPrefixDoubling();
    t.Print(); // Prints:  14 11 12  0  6  3  9 13  1  7  4  2  8 10  5
    return 0;
}