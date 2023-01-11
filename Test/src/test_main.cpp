#include <cassert>

void max_test(){
    int a = 10;
    int b = 15;
    assert((a>b ? a : b), max(a,b));
}
