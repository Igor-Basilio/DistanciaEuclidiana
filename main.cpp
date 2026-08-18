
#include <iostream>
#include <random>
#include <chrono>
#include <windows.h>
#include <shellapi.h>
#include <string>

using namespace std;

using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

    int argc;
    LPWSTR *argv = CommandLineToArgvW(GetCommandLineW(), &argc);

    int T = 10;
    int N = 10;

    if (argc != 2)
    {
        MessageBoxW(NULL, L"Missing argument to the program (T), which defines the size of the vectors.\n "
                          "Usage : .\\main <T>",
                    L"Missing Argument (T)", MB_OK);
        exit(0);
    }
    else
    {
        // TODO check if stoi failed to convert string to number.
        T = stoi(argv[1]);
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dis(1, 100);

    vector<float> q;
    for (int i = 0; i < T; i++)
        q.push_back(dis(gen));

    vector<vector<float>> X;
    for (int i = 0; i < N; i++)
    {
        vector<float> curr;
        for (int j = 0; j < T; j++)
        {
            curr.push_back(dis(gen));
        }
        X.push_back(curr);
    }

    vector<float> res(N, 0);

    // Execution start
    auto start = high_resolution_clock::now();

    for (int j = 0; j < X.size(); j++)
    {
        float sum = 0;
        for (int k = 0; k < X[j].size(); k++)
        {
            sum += pow(q[k] - X[j][k], 2);
        }
        res[j] = sum;
        sum = 0;
    }

    auto end = high_resolution_clock::now();
    duration<double, std::milli> ms_double = end - start;
    std::cout << "Execution time: " << ms_double.count() << " ms\n";
    // Execution end

    return EXIT_SUCCESS;
}
