#include<iostream>

using namespace std;
int valtab[127];

class Tree;
// Abstract base class of the node.
class Node{
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

    private:
        friend class Tree;
        friend ostream& operator<<(ostream&, const Tree&);
        int reference_count;
};

class Tree{
   
    public:
        Tree(int value);
        Tree(char id);
        Tree(const char op, Tree tree);
        Tree(const char op, Tree left, Tree right);
        // Copy constructor
        Tree(const Tree& t){
            p = t.p;
            ++p->reference_count;
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
        
    private:
        friend class Node;
        friend ostream& operator<<(ostream&, const Tree&);

        // Polymorphic pointer: Pointer to a abstract class.
        Node *p;
};

void Tree::operator=(const Tree& tree){
    ++tree.p->reference_count;
    if(this->p - 1 == 0){
        delete this->p;
    }

    p = tree.p;
}

// Polymorphic print routine.
ostream& operator<<(ostream& o, const Tree& tree){
    // Polymorphic call on the appropriate print method.
    tree.p->print(o);
    return(o);
}

// Leaf Note: First implementation of Node
class LeafNode: public Node{
    friend class Tree;
    void print(ostream& o)=0;
    virtual int eval()=0;
};

class IntNode: public LeafNode{
    friend class Tree;
    int value;

    void print(ostream& o){
        o << value;
    }

    // Constructor
    IntNode(int k):value(k){}

    public:
    int eval(){
        return value;
    }
};

class IdNode: public LeafNode{

    public:
        int eval(){
            return valtab[name];
        }

    private:
        friend class Tree;
        const char name;
        void print(ostream& o){
            o << name;
        }

        IdNode(const char id):name(id){}
};

class UnaryNode: public Node{

    public:
        int eval(){
            switch(op){
                case '-': return(-opnd.eval());
                case '+': return(+opnd.eval());
                default: cerr << "no operand\n" << endl;
                return 0;
            }
        }

    private:
        friend class Tree;
        const char op;
        Tree opnd;
        UnaryNode(const char a, Tree b): op(a), opnd(b){}
        void print(ostream& o){
            o << "(" << op << opnd << ")";
        }
};

class BinaryNode: public Node{
    public:
        int eval(){
            switch(op){
                case '-': return(left.eval() - right.eval());
                case '+': return(left.eval() + right.eval());
                case '*': return(left.eval() * right.eval());
                default: {
                    cerr << "no operand\n" << endl;
                    return 0;
                }
            }
        }
    private:
        friend class Tree;
        const char op;
        Tree left;
        Tree right;
        BinaryNode(const char a, Tree b, Tree c):op(a), left(b), right(c){}
        void print(ostream& o){
            o << "(" << left << op << right << ")";
        }
};

Tree::Tree(int value){
    p = new IntNode(value);
}

Tree::Tree(char id){
    p = new IdNode(id);
}

Tree::Tree(const char op, Tree tree){
    p = new UnaryNode(op, tree);
}

Tree::Tree(const char op, Tree left, Tree right){
    p = new BinaryNode(op, left, right);
}


int main(){
    valtab['A'] = 3;
    valtab['B'] = 4;

    cout << "A = 3, B = 4" << endl;

    Tree t1 = Tree('*', Tree('-', 5), Tree('+', 'A', 4));
    Tree t2 = Tree('+', Tree('-', 'A', 1), Tree('+', t1, 'B'));

    cout << "t1 = " << t1 << " ; t2 = " << t2 << endl;
    cout << "t1: " << t1.eval() << "t2:" << t2.eval() << endl;
    return 0;
}