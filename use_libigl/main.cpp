#include <Eigen/Dense>
#include <igl/readOFF.h>
#include <igl/writeOFF.h>
#include <igl/exact_geodesic.h>
#include <igl/colormap.h>

int main()
{
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;
    igl::readOFF("./data/mesh/bunny.off", V, F);

    // Compute geodesic distances from all vertices to the source vertex 0.
    Eigen::VectorXi VS, FS, VT, FT;
    VS.resize(1);
    VS << 0;
    VT.setLinSpaced(V.rows(), 0, V.rows() - 1);
    Eigen::VectorXd D;
    igl::exact_geodesic(V, F, VS, FS, VT, FT, D);

    // Visualize the geodesics as colors using a colormap.
    Eigen::MatrixXd C;
    igl::colormap(igl::COLOR_MAP_TYPE_JET, D, true, C);
    igl::writeOFF("./bunny_heat_geodesics.off", V, F, C);
}
