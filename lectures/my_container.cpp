#include<iostream>
#include<iterator>

using namespace std;

template <class T, int n>
class my_container{
    public:
        // Constructors
        my_container(){
            // Empty construction
            data = new T[n];
        }

        // Copy data from b into containter.
        explicit my_container(T *b):my_container(){
            for(int idx = 0; idx < n; ++idx){
                data[idx] = b[idx];
            }
        }

        // Copy constructor
        my_container(const my_container &b):my_container(){
            for(int idx = 0; idx < n; ++idx){
                data[idx] = b.data[idx];
            }
        }

        // Move constructor
        my_container(my_container &&b)noexcept{
            // Take reference to data from other objects.
            data = b.data;

            // Remove that reference from the other object.
            b.data = nullptr;
        }

        // operator[]
        T operator[](int index){
            return this->data[index];
        }

        void set(int idx, T data){
            this->data[idx] = data;
        }

        // Associated assignement
        my_container& operator=(my_container &&b)noexcept{
            data = b.data;
            b.data = nullptr;
            return *this;
        }

        iterator begin() noexcept{
            return &this->data[0];
        }

        iterator end() noexcept{
            return &this->data[n]
        }

        // Destructor.
        ~my_container(){
            delete[] data;
        }

    private:
        T* data;
};

int main(){
    my_container<int, 5> data;

    for(int idx=0; idx<5; ++idx){
        data.set(idx, idx);
    }

    // print out results
    cout << "data: ";
    for(int idx=0; idx<5; ++idx){
        cout << data[idx] << " ";
    }
    cout << endl;
}