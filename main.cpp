#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <iostream>

// Whitepaper: https://infolab.usc.edu/csci585/Spring2010/den_ar/indexing.pdf

template <typename Key, size_t K>
struct Page
{
    size_t count;               // l in the whitepaper
    Page<Key, K> *p[2 * K + 1];
    Key x[2 * K + 1];

    bool contains(Key key)
    {
        size_t begin = 1;
        size_t end = count;

        while (begin < end) {
            size_t middle = (begin + end) >> 1;

            if (key < x[middle]) {
                end = middle - 1;
            } else if (x[middle] < key) {
                begin = middle + 1;
            } else {
                return true;
            }
        }

        if (key < x[begin]) {
            return p[begin - 1] && p[begin - 1]->contains(key);
        } else if (x[begin] < key) {
            return p[begin] && p[begin]->contains(key);
        } else {
            return true;
        }
    }

    void print_dot()
    {
        for (size_t i = 0; i <= count; ++i) {
            if (p[i] != nullptr) {
                p[i]->print_dot();
            }
        }
        std::cout << "struct" << this << "[label=\"";
        std::cout << "<p0> &#183;";
        for (size_t i = 1; i <= count; ++i) {
            std::cout << "|<x" << i << "> " << x[i]
                      << "|<p" << i << "> &#183;";
        }
        std::cout << "\"];" << std::endl;

        for (size_t i = 0; i <= count; ++i) {
            if (p[i] != nullptr) {
                std::cout << "struct" << this << ":" << "p" << i << " -> "
                          << "struct" << p[i] << ";" << std::endl;
            }
        }
    }
};

template <typename Key, size_t K>
struct BTree
{
    Page<Key, K> *root;

    bool contains(Key key)
    {
        return root->contains(key);
    }

    void print_dot()
    {
        std::cout << "digraph {" << std::endl;
        std::cout << "node [shape=record]" << std::endl;
        root->print_dot();
        std::cout << "}" << std::endl;
    }
};

BTree<int, 3> tao23 = {
    .root = new Page<int, 3> {
        .count = 1,
        .p = {
            new Page<int, 3> {
                .count = 2,
                .p = {
                    new Page<int, 3> {
                        .count = 4,
                        .p = {},
                        .x = {{}, 1, 2, 3, 4},
                    },
                    new Page<int, 3> {
                        .count = 2,
                        .x = {{}, 6, 7}
                    },
                    new Page<int, 3> {
                        .count = 2,
                        .x = {{}, 9, 10}
                    }
                },
                .x = {{}, 5, 8},
            },
            new Page<int, 3> {
                .count = 2,
                .p = {
                    new Page<int, 3> {
                        .count = 4,
                        .x = {{}, 12, 13, 14, 15},
                    },
                    new Page<int, 3> {
                        .count = 4,
                        .x = {{}, 17, 18, 19, 20},
                    },
                    new Page<int, 3> {
                        .count = 4,
                        .x = {{}, 22, 23, 24, 25},
                    },
                },
                .x = {{}, 16, 21},
            },
        },
        .x = {{}, 11},
    },
};

int main(int argc, char *argv[])
{
    tao23.print_dot();

    return 0;
}
