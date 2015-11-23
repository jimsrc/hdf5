H5CC=/usr/local/hdf5/bin/h5c++
exe:
	${H5CC} h5group.cpp -o exe

clean:
	rm exe *.o
