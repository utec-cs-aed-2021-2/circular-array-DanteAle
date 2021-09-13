#include <iostream>
using namespace std;

template <class T>
class CircularArray
{
private:
    T *array;
    int capacity;
    int back, front;

public:
    CircularArray();
    CircularArray(int _capacity);
    virtual ~CircularArray();
    void push_front(T data);
    void push_back(T data);
    void insert(T data, int pos);
    T pop_front();
    T pop_back();
    bool is_full();
    bool is_empty();
    int size();
    void display();
    void clear();
    T &operator[](int);
    void sort();
    bool is_sorted();
    CircularArray *reverse();
    string to_string();

private:
    int next(int);
    int prev(int);
};


template <class T>
string CircularArray<T>::to_string()
{
    string result ="";
    for (int i = 0; i < size(); i++)
        result += std::to_string((*this)[i]) + " ";
    return result;
}


template <class T>
CircularArray<T>::CircularArray()
{
    CircularArray(0);
}

template <class T>
CircularArray<T>::CircularArray(int _capacity)
{
    this->capacity = _capacity;
    this->front = this->back = -1;
    this->array = new T[_capacity];
}

template <class T>
CircularArray<T>::~CircularArray()
{
    delete[] array;
}

template <class T>
T &CircularArray<T>::operator[](int index){
    if (index>=capacity){
        exit(0);
    }
    return *(this->array + index); 
}

template <class T>
int CircularArray<T>::prev(int index)
{
    return (index == 0) ? capacity - 1 : index - 1;
}

template <class T>
int CircularArray<T>::next(int index)
{
    return (index + 1) % capacity;
}

template <class T>
int CircularArray<T>::size(){
    if(is_empty()){
        return true;
    }
    if(back>=front){
        return back - front + 1;
    }
    else{
        return capacity - front + back + 1;
    }
}

template <class T>
bool CircularArray<T>::is_empty()
{
    return front == -1;
}

template <class T>
bool CircularArray<T>::is_full()
{
    return front == next(back) && !is_empty();
}

template <class T>
void CircularArray<T>::display()
{
    for (int i = 0; i < size(); i++)
        cout << (*this)[i] << ",";
    cout << endl;
}

template <class T>
void CircularArray<T>::push_front(T data){
    if(is_full()){
        cout<<"Array full"<<endl;
        return;
    }
    else if(is_empty()){
        this->front = this->back = 0;
        *(this->array + this->back) = data;
    }
    else{
        int temp = back;
        back = next(back);
        while(temp!=prev(front)){
            *(this->array + this->next(temp)) = *(this->array + temp);
            temp = prev(temp);
        }
        *(this->array+this->front) =  data;
    }

    if ((*this)[0] > (*this)[1])
    {
        int zzz = (*this)[0];
        for (int i = 0; i < size()-1; i++){
            (*this)[i] = (*this)[i+1];
        }
        (*this)[size()-1] = zzz;

    }

}

template <class T>
void CircularArray<T>::push_back(T data)
{
    if(is_full()){
        cout<<"Array is fully"<<endl;
        return;
    }
    else if(is_empty()){
        this->front = this->back = 0;
        *(this->array + this->back) = data;
    }
    else{
        *(this->array + this->next(back)) = data;
        back = next(back);
    } 
}

template <class T>
T CircularArray<T>::pop_front(){
    if(is_empty()){
        cout<<"Queue is empty"<<endl;
        return 0;
    }
    int temp = *(this -> array + this -> front);
    *(this -> array + this -> front) = -1;
    if(front == back){
        front = back= -1;
    }
    else{
        front = next(front);
    }
    return temp;
}

template <class T>
T CircularArray<T>::pop_back(){
    if(is_empty()){
        cout<<"Queue is empty"<<endl;
        return 0;
    }
    int temp = *(this -> array + this -> back);
    *(this -> array + this->back) = -1;
    if (front == back){
        front = back = -1;
    }
    else{
        back = prev(back);
    }
    return temp;    
}
template <class T>
void CircularArray<T>::clear(){
    while(size()!=0){
        pop_back();
    }
}
template<class T> 
CircularArray<T> *CircularArray<T>::reverse(){
    if (size()%2 == 0)
    {
        for (int i = 0; i < size()/2; ++i)
        {
            swap((*this)[i], (*this)[size()-1-i]);
        }
    }
    else
    {
        for (int i = 0; i < (size()-1)/2; ++i)
        {
            swap((*this)[i], (*this)[size()-1-i]);
        }
    }
}
template<class T> 
void CircularArray<T>::sort(){
    int actual = front;
    if (is_empty()){
        return;
    }
    else{
        do{
            int pivote = next(actual);
            while (pivote != next(back)){
                if (*(this->array + actual) > *(this->array + pivote)){
                    int temp = *(this->array + actual);
                    *(this->array + actual) = *(this->array + pivote);
                    *(this->array + pivote) = temp;
                }
                pivote = next(pivote);
            }
        actual = next(actual);
        }while(next(actual) != next(back));
        
        if ((*this)[0] > (*this)[1])
        {
            int zzz = (*this)[0];
            for (int i = 0; i < size()-1; i++){
                (*this)[i] = (*this)[i+1];
            }
            (*this)[size()-1] = zzz;

        }
    }
}
template<class T> 
bool CircularArray<T>::is_sorted(){
    int first = front;
    int last = back;
    if (first == last){
        return true;
    }
    int pivote = first;
    while (++pivote != last){
        if (*(this -> array + pivote)<*(this->array + first)){
            return false;
        }
        ++first;
    }
    return true;
}

template<class T>
void CircularArray<T>::insert(T data, int pos){
    int n = size();
    if(pos < 0 || pos > n){
        throw "Index no valid";
    }
    if(n == capacity){
        throw "Array is full";
    }
    if(pos == 0){
        push_front(data);
    }
    else{
        for (int i = n - 1; i >= pos; i--){
            (*this)[i+1] = (*this)[i];
        }    
        (*this)[pos] = data;
        back = next(back);
    }
}