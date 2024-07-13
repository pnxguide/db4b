all:
	mkdir -p bin;
	g++ -std=c++20 -O3 \
		-o bin/db4b.out \
		src/catalog/*.cpp \
		src/storage/*.cpp \
		src/operator/*.cpp \
		src/planner/*.cpp \
		src/util/*.cpp \
		src/main.cpp;

clean:
	rm -rf bin/*.*

run:
	./bin/db4b.out