# practical-geometry-processing

This repo contains a list of tutorials on practical geometry processing.

1. [How to use OpenMesh in your code](https://github.com/unclejimbo/practical-geometry-processing/tree/master/use_openmesh).
2. [How to use CGAL in your code](https://github.com/unclejimbo/practical-geometry-processing/tree/master/use_cgal).

## Build instructions

Use cmake to generate build scripts on both Windows and Linux:

```
mkdir build
cd build
cmake ..
```

If you are using MSVC(>=2017), the prebuilt third-party dependencies will be downloaded automatically on the first run of cmake configuration. Otherwise, you'll need to configure the dependencies in cmake by yourself. If you want to disable prebuilt libraries, set the `USE_PREBUILT_LIBS` variable to `FALSE` in cmake:

```
cmake -DUSE_PREBUILT_LIBS=FALSE ..
```
