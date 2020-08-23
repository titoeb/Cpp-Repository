
int main(){
    // Two enumerators within the same scope would not be possible
    // within C or C++ before std  11.
    enum class Color: int{RED, BLUE, GREEN};
    enum class Stoplight: int{RED, BLUE, GREEN};
    enum class fuzzy: unsigned{TRUE = 2, FALSE=0, MAYBE=1};
}