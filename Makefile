ifeq ($(OS),Windows_NT)
		FLAGS = -DCMAKE_SH="CMAKE_SH-NOTFOUND" -G "MinGW Makefiles"
else
		FLAGS = ""
endif

all: clean run

mem:
	valgrind --leak-check=full --leak-resolution=med make run

memcheck:
	valgrind --leak-check=full --leak-resolution=med make

run: reload build exec

mkdir_build:
		[ -d ./cmake-build-debug ] | mkdir -p cmake-build-debug

build:
		cd cmake-build-debug;cmake --build . --parallel 16 --target ECS
exec:
		./cmake-build-debug/ECS

clean:
		rm -rf cmake-build-debug

reload: mkdir_build
		cd cmake-build-debug;cmake $(FLAGS) ..