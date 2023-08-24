#include <bits/stdc++.h>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>

using namespace std;

double fun(Eigen::Vector3d Status, double x)
{
    return exp(Status[0] * x * x + Status[1] * x + Status[2]);
}

double get_Error(Eigen::Vector3d Status, double x, double y)
{
    return y - fun(Status, x);
}

Eigen::Vector3d get_Jacobian(Eigen::Vector3d Status, double x, double y)
{
    Eigen::Vector3d J;
    double f = fun(Status, x);
    J[0] = -x * x * f;
    J[1] = -x * f;
    J[2] = -f;
    return J;
}

int main()
{
    Eigen::Vector3d Status_ture;
    Status_ture[0] = 1.0;
    Status_ture[1] = 2.0;
    Status_ture[2] = 1.0;

    Eigen::Vector3d Status;
    Status[0] = 2.0;
    Status[1] = -1.0;
    Status[2] = 5.0;

    vector<double> x_data, y_data;

    // 数据数量
    int N = 100;
    for (int i = 0; i < N; i++)
    {
        double x = i / 100.0;
        x_data.push_back(x);
        double random = (double)rand() / RAND_MAX;
        random = random * 2 - 1; //-1~1之间的随机数字
        y_data.push_back(fun(Status_ture, x) + random);
    }

    // 求解
    int iterations = 100;
    double error = 0, last_error = 0;

    for (int i = 0; i < iterations; i++)
    {

        // H*dx = J*J^T
        // g = -J error
        error = 0;
        Eigen::Matrix3d H = Eigen::Matrix3d::Zero();
        Eigen::Vector3d g = Eigen::Vector3d::Zero();

        // 使用数据凑H*dx = J*J^T
        for (int j = 0; j < N; j++)
        {
            Eigen::Vector3d J = get_Jacobian(Status, x_data[j], y_data[j]);
            double e = get_Error(Status, x_data[j], y_data[j]);
            
            H += J * J.transpose();
            g += -e * J;
            error += e * e;
        }

        Eigen::Vector3d dx = H.ldlt().solve(g);

        if (isnan(dx[0]))
        {
            cout << i << "求解出 nan" << endl;
            break;
        }

        Status += dx;
        if (i % 10 == 0)
            cout << "Status:" << Status.transpose() << " error:" << error << endl;
    }

    // 对比求解结果
    cout << "Status_ture:" << Status_ture.transpose() << endl;
    cout << "Status:" << Status.transpose() << endl;
}