gcc = arm-none-linux-gnueabi-gcc
target = hlw
source1 = util.c
source2 = hlw8032.c
$(target):$(source)
	$(gcc) -lrt -o $(target) $(source1) $(source2)
.PHONY : clean
clean :
	-rm hlw