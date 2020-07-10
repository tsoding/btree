#include <iostream>
#include <cstdio>
#include <cstdlib>

// Whitepaper: https://infolab.usc.edu/csci585/Spring2010/den_ar/indexing.pdf

template <typename Key, typename Value, size_t K>
struct Page
{
    size_t count;               // l in the whitepaper
    Page<Key, Value, K> *p[2 * K + 1];
    Key x[2 * K + 1];
    Value a[2 * K + 1];

    void print()
    {
        std::cout << "node" << this << "[label=\"";
        for (size_t i = 1; i <= count; ++i) {
            std::cout << x[i] << ' ';
        }
        std::cout << "\",shape=record];" << std::endl;

        for (size_t i = 0; i <= count; ++i) {
            if (p[i] != nullptr) {
                std::cout << "node" << this
                          << " -> "
                          << "node" << p[i] << ";" << std::endl;
                p[i]->print();
            }
        }
    }
};

template <typename Key, typename Value, size_t K>
struct BTree
{
    Page<Key, Value, K> *root;

    Value &get(Key key)
    {
    }

    void print()
    {
        std::cout << "digraph {" << std::endl;
        root->print();
        std::cout << "}" << std::endl;
    }
};

BTree<int, int, 3> tao23 = {
    .root = new Page<int, int, 3> {
        .count = 1,
        .p = {
            new Page<int, int, 3> {
                .count = 2,
                .p = {},
                .x = {{}, 5, 8},
                .a = {{}, 5, 8},
            },
            new Page<int, int, 3> {
                .count = 2,
                .p = {},
                .x = {{}, 16, 21},
                .a = {{}, 16, 21},
            },
        },
        .x = {{}, 11},
        .a = {{}, 11},
    },
};

int main(int argc, char *argv[])
{
    tao23.print();
    return 0;
}
