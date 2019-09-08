#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>

// OpenMesh::TriMesh_ArrayKernelT is one of the base data structures that
// OpenMesh provides. Here we use the default configuration. You can customize
// it using traits and dynamic properties.
using Mesh = OpenMesh::TriMesh_ArrayKernelT<>;

int main()
{
    Mesh mesh;

    // OpenMesh can process several common mesh file formats.
    OpenMesh::IO::read_mesh(mesh, "./data/mesh/bunny.off");

    // Here we use a range-based for loop to iterate through all the vertices of
    // a mesh.
    for (auto v : mesh.vertices()) {
        int valence = 0;
        // Here we use a vertex-vertex circulator to iterate through the
        // one-ring neighbors of a vertex.
        for (auto vit = mesh.cvv_begin(v); vit != mesh.cvv_end(v); ++vit) {
            ++valence;
        }
    }

    // We can store the mesh into another file format.
    OpenMesh::IO::write_mesh(mesh, "bunny.ply");

    return 0;
}
