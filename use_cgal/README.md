# Use CGAL

[CGAL](https://www.cgal.org/) contains a full range of data structures and algorithms in computational geometry. They are grouped by topics, and each package provides its own documentation and code examples. It might be a little bit overwhelming at first glance, but it'll be mucher easier to explore this library when you are familiar with a few packages.

This tutorial will introduce you to the basic halfedge data structure used in CGAL, the [Surface Mesh](https://doc.cgal.org/latest/Surface_mesh/index.html#Chapter_3D_Surface_mesh) package. It is very similar to the halfedge data structure in OpenMesh, so you could learn how to navigate on the on this mesh by reading through its api documentation. Here I'll show you how to do a common mesh processing task, specifically mesh simplification, on this data structure with the algorithm provided in the [Triangulated Surface Mesh Simplification](https://doc.cgal.org/latest/Surface_mesh_simplification/index.html#Chapter_Triangulated_Surface_Mesh_Simplification) package.

You'll find that many mesh processing algorithms in CGAL could operate on the Surface Mesh data structure, which proves to be very handy. In fact, these algorithms can also work with OpenMesh, thanks to some template tricks. But I'll leave it to a later tutorial.
