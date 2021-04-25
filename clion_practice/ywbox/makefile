gcc = arm-none-linux-gnueabi-gcc
target = main2
source1 = $(wildcard ./src/*.c)
source2 = $(wildcard ./*.c)
$(target):$(source)
	$(gcc) -lrt -o $(target) $(source1) $(source2)

.PHONY : clean
clean :
	-rm main2