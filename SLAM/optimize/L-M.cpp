#include <bits/stdc++.h>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Eigen>

using namespace std;

// LM算法 $(H + \lembda D^TD)\Delta x = -J*f(x)$
// H = JJ^T
// D一般取JJ^T的对角线元素的平方根
// \lembda 越大越接近梯度下降法，说明二阶近似效果不好
int main()
{
    // 雅可比矩阵的维度，也就是待优化变量的维度
    int jac_leng = 3;

    Eigen::MatrixXd D(jac_leng, jac_leng);
    D.setIdentity();
    Eigen::MatrixXd Hess(jac_leng, jac_leng);
    Eigen::MatrixXd HessuD(jac_leng, jac_leng);

    Eigen::VectorXd JacT(jac_leng); // J*f(x)
    Eigen::VectorXd dxi(jac_leng);
    Eigen::VectorXd new_dxi(jac_leng);

    Hess = 4 * Eigen::Matrix3d::Identity();

    D.diagonal() = Hess.diagonal(); // H = H + λ D^T D //?取的hessian矩阵的对角线，因为D一般取J^TJ的对角线元素的平方根

    // 计算Hessian矩阵 H 和雅可比矩阵 J

    // 将H矩阵转换为稀疏化的表示形式
    Eigen::SparseMatrix<double> A1_sparse(jac_leng, jac_leng); // 这种形式的矩阵与原来的矩阵H存储一样的数据，但是内存效率更高
    std::vector<Eigen::Triplet<double>> tripletlist;
    for (int a = 0; a < jac_leng; a++)
        for (int b = 0; b < jac_leng; b++)
            if (HessuD(a, b) != 0)
            {
                tripletlist.push_back(Eigen::Triplet<double>(a, b, HessuD(a, b)));

                // 直接插入速度慢
                // A1_sparse.insert(a, b) = A(a, b);
            }

    A1_sparse.setFromTriplets(tripletlist.begin(), tripletlist.end()); // 从Triplet中生成稀疏矩阵A1_sparse
    A1_sparse.makeCompressed();                                        // 压缩优化矩阵

    // 使用矩阵的求解器求解dx
    Eigen::SimplicialLDLT<Eigen::SparseMatrix<double>> Solver_sparse; // 定义矩阵求解器
    Solver_sparse.compute(A1_sparse);

    if (Solver_sparse.info() != Eigen::Success)
    {
        // 分解失败
    }
    dxi = Solver_sparse.solve(-JacT); // 求解dx
    if (Solver_sparse.info() != Eigen::Success)
    {
        // 求解识别
    }

    //更新状态量

    // 计算误差是否下降
    // 误差不下降，则JJ^T + \lembda D^TD近似不准，则应该增大\lembda使得求解更接近梯度下降法，重新求解以保证算法是下降算法
    // 下降则进行下一次迭代
}
