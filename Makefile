.PHONY: test

bin/fae: src/*.cc src/**/*.cc
	clang++ \
		-O2 \
		-std=c++20 \
		-pedantic \
		-Wall \
		-Werror \
		-Wextra \
		-Wno-c99-extensions \
		-Wno-switch \
		-fno-signed-char \
		-fno-finite-loops \
		-fno-math-errno \
		-fno-strict-aliasing \
		-fno-strict-overflow \
		-fno-trapping-math \
		-fno-vectorize \
		-o bin/fae \
		src/fae.cc

test: bin/fae
	./bin/fae test/example.fae
