#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

class SelectionSortAlgorithm
{
public:
    SelectionSortAlgorithm() {}

    // Selection sort function
    void selectionSort(string** Data, int rows, int cols)
    {
        for (int i = 0; i < rows - 1; i++)
        {
            int minIndex = i;
            for (int j = i + 1; j < rows; j++)
            {
                if (Data[j][0] < Data[minIndex][0])
                {
                    minIndex = j;
                }
            }

            // Swap the rows
            for (int k = 0; k < cols; k++)
            {
                swap(Data[i][k], Data[minIndex][k]);
            }
        }
    }
};

int main()
{
    int Maxrows = 10000;
    int rows;

    cout << "Enter Input size: ";
    cin >> rows;

    int cols = 6;

    SelectionSortAlgorithm S;

    string** Data = new string * [Maxrows];
    for (int i = 0; i < Maxrows; i++)
    {
        Data[i] = new string[cols];
    }

    //ifstream inputFile("student_data.csv");
    //Relative Path
    ifstream inputFile("D:/#####Uni Fifth Sem/Algorithms/A2/Kashif/student_data.csv");
    if (!inputFile.is_open())
    {
        cerr << "Error opening student_data.csv file." << endl;
        return 1;
    }

    int row = 0;
    string line;
    while (getline(inputFile, line) && row < rows)
    {
        stringstream ss(line);
        int col = 0;
        string cell;

        while (getline(ss, cell, ',') && col < cols)
        {
            Data[row][col] = cell;
            col++;
        }

        row++;
    }

    inputFile.close();

    auto start = high_resolution_clock::now();

    S.selectionSort(Data, rows, cols);

    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start);

    cout << "Elapsed time: " << duration.count() << " milliseconds" << endl;

    ofstream OutputFile("Sorted_Data_SelectionSort.csv");
    if (!OutputFile.is_open())
    {
        cerr << "Error opening Sorted_Data_SelectionSort.csv file." << endl;
        return 1;
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            OutputFile << Data[i][j];
            if (j < cols - 1)
            {
                OutputFile << ",";
            }
        }
        OutputFile << endl;
    }

    OutputFile.close();

    cout << "Sorted data has been written to Sorted_Data_SelectionSort.csv." << endl;

    for (int i = 0; i < rows; i++)
    {
        delete[] Data[i];
    }
    delete[] Data;

    ofstream TimeComplexityFile("Selection_Running_Time.csv", ios::app);
    if (!TimeComplexityFile.is_open())
    {
        cerr << "Error opening Selection_Running_Time.csv file." << endl;
        return 1;
    }

    TimeComplexityFile << rows << "," << duration.count() << endl;

    TimeComplexityFile.close();

    cout << "Running Time and Input size has been appended to Selection_Running_Time.csv." << endl;

    return 0;
}
