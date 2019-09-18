# Use libigl

[libigl](https://libigl.github.io/) is another geometry processing library you should be familiar with. The major difference between CGAL/OpenMesh and this library is the mesh data structure. In the previous tutorials, we've seen that both OpenMesh and CGAL use the halfedge data structure to represent a surface mesh. However, igl uses matrices to encode the geometry. The vertex positions are encoded in a Nx3 matrix `V`, and the triangle connectivities are encoded in another Nx3 matrix `F`. There is no explicit representation for edges or halfedges. This data structure is more compact compared to the halfedge data structure. And it also comes in handy when the algorithm involves solving linear systems, which is very common in geometry processing.

[Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page) is the underlying matrix representation used in igl, so you should at least have some basic understanding of its matrix types.

In this tutorial, you will learn how to read a mesh into the Eigen matrix using libigl. And then, you will compute the [geodesic distance](https://en.wikipedia.org/wiki/Geodesic). Simply put, geodesic distance is the shortest distance on the curved surface. Finally, you will map the distances to vertex colors and write the result out to see the distances.

Keep in mind that igl does not only provides geometry algorithms, but also many utility functions you could use to build your own algorithm. Generally, every function or algorithm lives in its own header. And there are plenty of headers in libigl. So you might want to search in their repo to find what you are looking for.

## Build notes

Both Eigen and libigl are header-only libraries, which means you could include them directly in your project. However, here we choose to configure them using CMake first and then they could be easily integrated into the cmake target, without worrying about the include paths etc..
