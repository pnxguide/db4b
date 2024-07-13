all:
	mkdir -p bin;
	g++ -std=c++20 \
		-o bin/db4b.out \
		src/planner/*.cpp \
		src/catalog/*.cpp \
		src/operator/*.cpp \
		src/storage/*.cpp \
		src/util/*.cpp \
		src/main.cpp;

clean:
	rm -rf bin/*.*

run:
	./bin/db4b.out