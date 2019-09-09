#include <fstream>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/Surface_mesh_simplification/edge_collapse.h>
#include <CGAL/Surface_mesh_simplification/Policies/Edge_collapse/Count_ratio_stop_predicate.h>

// Kernel is the trait class underlying CGAL's data structures, you can learn
// more about it in the 2D and 3D Linear Geometry Kernel package. Here it
// suffices to use a builtin kernel called Simple_cartesian.
using Kernel = CGAL::Simple_cartesian<double>;
// Here use the kernel to specialize the Surface_mesh template.
using Mesh = CGAL::Surface_mesh<Kernel::Point_3>;

int main()
{
    Mesh mesh;

    // Currently the Surface_mesh package only supports the off format.
    std::ifstream ifs("./data/mesh/bunny.off");
    CGAL::read_off(ifs, mesh);

    // A stop policy is needed to indicate the edge_collapse algorithm to
    // terminate. Here we stop the simplification process when the vertex count
    // ratio drops below 20%.
    CGAL::Surface_mesh_simplification::Count_ratio_stop_predicate<Mesh> stop(
        0.2);
    // And do the actual simplification.
    CGAL::Surface_mesh_simplification::edge_collapse(mesh, stop);

    std::ofstream ofs("bunny_simplified.off");
    CGAL::write_off(ofs, mesh);

    return 0;
}
