#include "funcs.cc"

const H5std_string FILE_NAME( "Group.h5" );
const int	   RANK = 2;

// Operator function
extern "C" herr_t file_info(hid_t loc_id, const char *name, const H5L_info_t *linfo, void *opdata);


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef float dtype;


void LiberaMat(dtype **Mat,int i){ 
        for(int k=0; k<=i; k++)
                free(Mat[i]);
        free(Mat);
}


dtype **AllocMat(int nRows, int nCols){
    dtype **Mat;
    // dsps probar con calloc!
    if((Mat = (dtype **) calloc(nRows,sizeof(dtype *))) == NULL)//porq "double *"? 
        return NULL;

    //--- alocamos el punto de origen
    if((Mat[0] = (dtype *) calloc( nCols*nRows,sizeof( dtype ) ))==NULL){
        LiberaMat(Mat,0);
        return NULL;
    }

    //--- alojamos los demas elementos
    for(int i=1; i<nRows; i++)
        Mat[i] = Mat[0] + i*nCols; //(dtype *) malloc(nCols*sizeof(dtype));
    return Mat;
}


dtype **AllocMat_(int nFilas, int nColumnas){
    dtype **Mat;

    if((Mat = (dtype**) calloc(nFilas, sizeof(dtype *))) == NULL)//porq "double *"? 
        return NULL;

    for(int i=0; i<nFilas; i++)
        if((Mat[i] = (dtype *) calloc(nColumnas, sizeof(dtype)))==NULL) {
            LiberaMat(Mat,i);
            return NULL;
        }   
    return Mat;
}
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

