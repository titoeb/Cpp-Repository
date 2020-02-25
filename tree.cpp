#include<iostream>

using namespace std;

// Abstract base class of the node.
class Node{
    friend class Tree;
    friend ostream& operator<<(ostream&, const Tree&);
    int reference_count;

    protected:
        // Constructor, initiallize reference count to one.
        Node(){
            this->reference_count = 1;
        }

        // This are purely abstract classes with these methods in 0-notation.
        virtual void print(ostream&) = 0;
        virtual int eval() = 0;

        // Virtual Destructor.
        virtual ~Node(){}
};

// 
class Tree{
        friend class Node;
        friend ostream& operator<<(ostream&, const Tree&);

        // Polymorphic pointer: Pointer to a abstract class.
        Node *p;
    public:
        Tree(int);
        Tree(char);
        Tree(char*, Tree);
        Tree(char*, Tree, Tree);

        // Copy constructor
        Tree(const Tree& t){
            this->p = t.p;

            // Referential counting
            ++this->p->reference_count;
        }

        // Destructor, reduce the referential count.
        ~Tree(){
            --this->p->reference_count;
            if(this->p->reference_count <= 0){
                delete this->p;
            }
        }

        void operator=(const Tree& t);
        int eval(){

            // Polymorphic call of the val method
            return this->p->eval();
        }
};

// Polymorphic print routine.
ostream& operator<<(ostream& o, const Tree& tree){
    // Polymorphic call on the appropriate print method.
    tree->p->print(o);
    return(o
}

int main(){


    return 0;
}