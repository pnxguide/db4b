all:
	mkdir -p bin;
	g++ -std=c++20 \
		-o bin/db4b.out \
		src/main.cpp;

clean:
	rm -rf bin/*.*