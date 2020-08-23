#include <iostream>
using namespace std;

// Define a single linked list

// Define the individual element class
template <class linked_element_type>
class list_element{
    public:
        // Constructor
        list_element(linked_element_type data, list_element* ptr = nullptr):data(data), next(ptr){}

        linked_element_type get_data() const{
            return this->data;
        }
        
        void set_data(linked_element_type data){
            this->data = data;
        }

        list_element* get_next() const{
            return this->next;
        }

        void set_next(list_element* ptr){
            this->next = ptr;
        }

    private:
        linked_element_type data;
        list_element* next;
};

// Define the class
template <class linked_element_type>
class single_linked_list{
    public:

        // Constructors
        // Create empty list
        single_linked_list():head(nullptr), cursor(nullptr){}

        //Make a hard copy of a list
        single_linked_list(const single_linked_list<linked_element_type>& list){
            if (list.get_head() == nullptr){
                this->head=nullptr;
                this->cursor=nullptr;
            } else {
                list_element<linked_element_type>* buffer = nullptr;
                list_element<linked_element_type>* list_ptr = nullptr;
                // Make a deep copy of all the elements within the list.
                // Create new element with data from first element of list
                list_ptr = list.get_head();
                buffer = new list_element<linked_element_type>(list_ptr->get_data());

                // put the cursor on it
                this->cursor = buffer;

                // Go to the next node in the original list.
                list_ptr = list_ptr->get_next();

                // put the head on the first node.
                this->head = this->cursor;
                while(list_ptr != nullptr){
                    buffer = new list_element<linked_element_type>(list_ptr->get_data());                   

                    this->cursor->set_next(buffer);
                    this->cursor = this->cursor->get_next();
                    list_ptr = list_ptr->get_next(); 
                }
                this->cursor = this->head;
            }
        }

        // Destructor
        ~single_linked_list(){ 
            list_element<linked_element_type>* local_cursor = this->head;
            list_element<linked_element_type>* delete_cursor =  nullptr;
            while(local_cursor != nullptr){
                delete_cursor = local_cursor;
                local_cursor = local_cursor->get_next();
                delete delete_cursor;
            }
        }

        // Getter and Setter for private variables.
        list_element<linked_element_type>* get_head() const {
            return this->head;
        }

        list_element<linked_element_type>* get_element() const {
            return this->cursor;
        }

        // Functions to use the list
        void prepend(linked_element_type data){
            // Append a new element in the beginning.
            if (this->head == nullptr){
                this->cursor = this->head = new list_element<linked_element_type>(data);
            } else {
                this->head = new list_element<linked_element_type>(data, head);
            }
        }

        void advance(){
            if (this->cursor != nullptr){
                this->cursor = this->cursor->next;
            } else {
                // Start again in the begining
                this->cursor = this->head;
            }
        }

        void print() const{
            list_element<linked_element_type>* local_cursor = this->head;
            if (local_cursor != nullptr){
                while(local_cursor != nullptr){
                    cout << local_cursor->get_data();
                    local_cursor = local_cursor->get_next();
                    if (local_cursor != nullptr){
                        cout << "->";
                    }
                }
                cout << endl;
            }
        }

    private:
        list_element<linked_element_type>* head;
        list_element<linked_element_type>* cursor;
};

/*
// overload << operator for list.
template <class linked_element_type>
iostream& operator<< (iostream& out, single_linked_list<linked_element_type> list){
    list_element<linked_element_type>* local_cursor = list->get_head();
    while(local_cursor != nullptr){
        out << local_cursor->get_data();
        local_cursor = local_cursor->get_next();
        if (local_cursor != nullptr){
            out << "->";
        }
    }
    return out;
}
I did not get overloading << work with a template class.
*/

int main(){
    single_linked_list<double> test_list = single_linked_list<double>();

    for(int i = 0; i < 15; i++){
        test_list.prepend(2.7 * (i * i));
    }
    test_list.print();

    single_linked_list<double> test_list_2 = single_linked_list<double>(test_list);
    test_list_2.print();

    return 0;
}
