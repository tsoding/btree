btree.png: btree.dot
	dot -Tpng btree.dot -o btree.png

btree.dot: btree
	./btree > btree.dot

btree: main.cpp
	clang++ -Wall -std=c++17 -ggdb -o btree main.cpp
