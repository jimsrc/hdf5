#include "funcs.cc"

const H5std_string FILE_NAME( "Group.h5" );
const int	   RANK = 2;

// Operator function
extern "C" herr_t file_info(hid_t loc_id, const char *name, const H5L_info_t *linfo, void *opdata);


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef float dtype;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++


int main(void){
    int nx=10, ny=3;
    h5mgr hm;
    float p[10], *pp;
    pp = p;

    hm.build("salida.h5", nx, ny);

    dtype **dataf;
    dataf = AllocMat(nx, ny);

    for(int i=0; i<nx; i++)
        for(int j=0; j<ny; j++){
            dataf[i][j] = 1.1*i + j;
            printf("(%d,%d): %g\n", i, j, dataf[i][j]);
        }
    //dataf[0][0] = 9.99;
    //dataf[1][0] = 9.99;
    printf("%g\n", dataf[1][0]);
    printf("%g\n", dataf[1][3]);
    printf("%f\n", dataf[2][2]);
    printf("%f\n", dataf[2][0]);
    printf("(%d,%d): %g\n", nx-1, ny-1, dataf[nx-1][ny-1]);

    char path[50], vname[50];
    sprintf(path, "/Data");
    sprintf(vname, "VarNameeee");
    hm.run(dataf, vname, path);

    return 0;
}

/*
 * Operator function.
 */
herr_t
file_info(hid_t loc_id, const char *name, const H5L_info_t *linfo, void *opdata){
    hid_t group;
    /*
     * Open the group using its name.
     */
    group = H5Gopen2(loc_id, name, H5P_DEFAULT);
    /*
     * Display group name.
     */
    cout << "Name : " << name << endl;
    H5Gclose(group);
    return 0;
}

