#include <iostream>
#include <vector>

using namespace std;

vector<vector<long long>> get_minor(int jump_col, vector<vector<long long>> &m)
{
    vector<vector<long long>> m_out(m.size() - 1, vector<long long>(m.size() - 1, 0));
    for (int row = 0; row < m_out.size(); row++)
    {
        for (int col = 0; col < m_out.size(); col++)
        {
            if (col < jump_col)
            {
                m_out[row][col] = m[row + 1][col];
            }
            else
            {
                m_out[row][col] = m[row + 1][col + 1];
            }
        }
    }
    return m_out;
}

void print_vec(vector<vector<long long>> m)
{
    for (auto row : m)
    {
        for (auto col : row)
            cout << col << " ";
        cout << endl;
    }
    cout << endl;
}

long long determinant(vector<vector<long long>> m)
{
    if (m.size() == 1)
    {
        return m[0][0];
    }
    // TODO: Return the determinant of the square matrix passed in
    if (m.size() == 2)
    {
        return m[0][0] * m[1][1] - m[0][1] * m[1][0];
    }

    long long det = 0;
    vector<vector<long long>> minor;
    for (int col = 0; col < m.size(); col++)
    {
        minor = get_minor(col, m);
        //print_vec(minor);
        if (col % 2 == 1)
        {
            det = det - m[0][col] * determinant(minor);
        }
        else
        {
            det = det + m[0][col] * determinant(minor);
        }
    }
    return det;
}

int main()
{
    // cout << determinant({{1}}) << endl;
    // cout << determinant({{1, 3}, {2, 5}}) << endl;
    cout << determinant({{2, 5, 3}, {1, -2, -1}, {1, 3, 4}}) << endl;
}