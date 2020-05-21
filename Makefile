# simple_redis makefile

# -g 选项 支持gdb调试


# 编译全部
all: err.o log.o conf.o libread_line.so libcommon.a
	gcc err.o log.o conf.o server.c -g -o server -I ./lib -L ./lib -lread_line -ldl -lcommon

err.o:
	gcc -c err.c -o err.o

log.o:
	gcc -c log.c -o log.o

conf.o:
	gcc -c conf.c -o conf.o


# export LD_LIBRARY_PATH=$(PWD)/lib:LD_LIBRARY_PATH
libread_line.so:
	gcc -fPIC -shared ./lib/read_line.c -o ./lib/libread_line.so
	
libcommon.a: common.o
	ar -rc ./lib/libcommon.a ./lib/common.o

common.o: 
	gcc -c ./lib/common.c -o ./lib/common.o

# 清除
clean:
	rm -rf *.o
	rm -rf ./lib/*.so
	rm -rf ./lib/*.a
	rm -rf server

