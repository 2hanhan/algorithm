#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>

#include <iostream>

using namespace std;

int main()
{
    Eigen::Matrix3d A;
    A << 1, 1, 1,
        0, 5, 0,
        0, 0, 1;
    cout << "A.norm():" << A.norm(); // 矩阵的模，各个元素平方和开根号
    return 0;
}