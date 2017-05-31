default:
	# agregar "-show" para ver el comando q ejecuta en realidad (no ejecuta el comando)
	h5cc -shlib -DHAVE_CONFIG_H  '-D H5_USE_16_API'   -g -O2 -MT h5ex_t_cpxcmpd.o -MD -MP -c -o h5ex_t_cpxcmpd.o h5ex_t_cpxcmpd.c
	h5cc -shlib  -g -O2   -o h5ex_t_cpxcmpd h5ex_t_cpxcmpd.o
	./h5ex_t_cpxcmpd 
	h5dump h5ex_t_cpxcmpd.h5
