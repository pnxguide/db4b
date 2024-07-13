all:
	mkdir -p bin;
	g++ -std=c++20 \
		-o bin/ljdb.out \
		src/main.cpp;