// main.cpp
// 

#define TRUE 1
#define FALSE 0

#include <vcg/complex/complex.h>
//io
#include <wrap/io_trimesh/import.h>
#include <wrap/io_trimesh/export_ply.h>

#include <cstdlib>
#include <iostream>
#include <string>

class MyVertex;
class MyEdge;
class MyFace;

struct MyUsedTypes: public vcg::UsedTypes<vcg::Use<MyVertex>::AsVertexType,vcg::Use<MyEdge>::AsEdgeType,vcg::Use<MyFace>::AsFaceType>{};

class MyVertex  : public vcg::Vertex< MyUsedTypes,vcg::vertex::VFAdj,vcg::vertex::Coord3f,vcg::vertex::Normal3f,vcg::vertex::Mark,vcg::vertex::BitFlags  >
{
};

class MyEdge : public vcg::Edge< MyUsedTypes> {};

class MyFace    : public vcg::Face< MyUsedTypes,
    vcg::face::VFAdj,
    vcg::face::VertexRef,
    vcg::face::BitFlags > {};

// the main mesh class
class MyMesh    : public vcg::tri::TriMesh<std::vector<MyVertex>, std::vector<MyFace> > {};

static int print_verbose = 0;

static char *input_mesh_name = NULL;

void OpenMesh(MyMesh &m) {
    int err = vcg::tri::io::Importer<MyMesh>::Open(m, input_mesh_name);
    if(err) {
        fprintf(stderr, "Error in roading %s: '%s'\n", input_mesh_name, vcg::tri::io::Importer<MyMesh>::ErrorMsg(err));
        if(vcg::tri::io::Importer<MyMesh>::ErrorCritical(err)) exit(-1);
    }
    std::cout << "read mesh " << input_mesh_name << std::endl;
    //cleaning

}

int ParseArgs(int argc, char **argv) {
    // prg name
    argc--; argv++;
    while(argc>0) {
        if((*argv)[0] == '-') {
            //option
            if(!strcmp(*argv, "-v")) {print_verbose = TRUE;}
            else { fprintf(stderr, "Invalid program argument: %s\n", *argv); return 0;}
            argv++; argc--;
        }
        else {
            //mesh name
            if(!input_mesh_name) input_mesh_name = *argv;
            else std::cerr << "Invalid program argument: " << *argv <<std::endl;
            argv++; argc--;
        }

    }
    if(!input_mesh_name) {
        fprintf(stderr,
                "Usage: ./main <options> input_mesh \n\n");
        return FALSE;
    }
    return TRUE;
}

int main(int argc, char* argv[]) {
    std::cout << "I am doing something" << std::endl;
    //
    MyMesh              M;
    unsigned long       elapsed_time;

    int t0 = clock();
    
    std::cout << "start processing.. " << std::endl;
    if(!ParseArgs(argc, argv)) exit(-1);
    OpenMesh(M);
    
    

    if(print_verbose) {
        // print mesh info
        std::cout << "Mesh info: " << std::endl;
        fprintf(stdout, " Input: '%s'\n\tvertices   %7i\n\tfaces    %7i\n", input_mesh_name, M.vn, M.fn);
    }
    
    
    elapsed_time = clock() - t0;
    fprintf(stdout, "  Computation time  : %d ms\n" , (int)(1000.0*elapsed_time/CLOCKS_PER_SEC));

    return 0;
    
}