gcc = arm-none-linux-gnueabi-gcc
target = volta
source1 = util.c
source2 = voltameter.c
$(target):$(source)
	$(gcc) -lrt -o $(target) $(source1) $(source2)
.PHONY : clean
clean :
	-rm volta