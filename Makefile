all: parallel serial 

parallel:

	g++ multiMatriz.cpp -o parallel -fopenmp

serial:

	g++ multiMatrizSerial.cpp -o serial

clean:

	rm -rf parallel serial       

run_parallel: 

	./parallel

run_serial: 

	./serial

# all: parallel serial 

# parallel:

# 	g++ madhava.cpp -o parallel -fopenmp

# serial:

# 	g++ serialMadhava.cpp -o serial

# clean:

# 	rm -rf parallel serial       

# run_parallel: 

# 	./parallel

# run_serial: 

# 	./serial