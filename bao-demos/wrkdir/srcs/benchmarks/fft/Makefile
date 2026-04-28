all: fft

# fft implementation  
fft: driver.c fft.c 
	gcc driver.c fft.c -o fft -lm 

clean: 
	rm -f *.o fft 

run: