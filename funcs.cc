/*
 */
#include "funcs.h"


void h5mgr::build(char* fname, int nxx, int nyy){
    sprintf(fname_out, "%s", fname);
    nx = nxx;
    ny = nyy;
    rank = 2;
}


int h5mgr::run(float** dataff, char* varname, char* path_to_var){
    char pathname[100];
    sprintf(pathname, "%s/%s", path_to_var, varname); // "/Data/Float_Data"
    hsize_t  dims[rank];
    // Try block to detect exceptions raised by any of the calls inside it
    try{
        Exception::dontPrint();
        H5File *file = new H5File( fname_out, H5F_ACC_TRUNC );
        Group* group = new Group( file->createGroup( path_to_var ));

        dims[0]     = nx; //10; //1000;
        dims[1]     = ny; //3; //20;

        DataSpace* dataspace = new DataSpace(rank, dims); // create second dspace
        DataSet* dataset     = new DataSet(file->createDataSet(pathname, PredType::NATIVE_FLOAT, *dataspace));

        float dataf[nx][ny];
        dataf[0][0] = 33.334;
        dataf[0][2] = 33.334;
        dataset->write(&dataff[0][0], PredType::NATIVE_FLOAT);
        //dataset->write(&dataf[0][0], PredType::NATIVE_FLOAT);

        delete dataset;
        delete dataspace;
        delete group;
        delete file;
        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    }  // end of try block
    // catch failure caused by the H5File operations
    catch( FileIException error ){
        error.printError();
        return -1;
    }
    // catch failure caused by the DataSet operations
    catch( DataSetIException error ){
        error.printError();
        return -1;
    }
    // catch failure caused by the DataSpace operations
    catch( DataSpaceIException error ){
        error.printError();
        return -1;
    }
    // catch failure caused by the Attribute operations
    catch( AttributeIException error ){
        error.printError();
        return -1;
    }
    return 0;
}
