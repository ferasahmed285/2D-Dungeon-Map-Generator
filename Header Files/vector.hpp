#ifndef VECTOR_HPP
#define VECTOR_HPP

template <typename T>
class Vector {
public:
    Vector();
    Vector(size_t count, const T& value);
    ~Vector();

    Vector(const Vector& other);
    Vector& operator=(const Vector& other);

    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    void push_back(const T& value);
    void pop_back();
    size_t getSize() const;
    bool empty() const;

private:
    void reallocate(size_t newCap);
    T* data;
    size_t size;
    size_t capacity;
};

template <typename T>
Vector<T>::Vector() : data(nullptr), size(0), capacity(0) {}

template <typename T>
Vector<T>::Vector(size_t count, const T& value)
    : size(count), capacity(count) {
    data = new T[capacity];
    for (size_t i = 0; i < size; ++i)
        data[i] = value;
}

template <typename T>
Vector<T>::~Vector() {
    delete[] data;
}

template <typename T>
Vector<T>::Vector(const Vector& other)
    : size(other.size), capacity(other.capacity) {
    data = new T[capacity];
    for (size_t i = 0; i < size; ++i)
        data[i] = other.data[i];
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) {
        delete[] data;
        size = other.size;
        capacity = other.capacity;
        data = new T[capacity];
        for (size_t i = 0; i < size; ++i)
            data[i] = other.data[i];
    }
    return *this;
}

template <typename T>
T& Vector<T>::operator[](size_t index) {
    return data[index];
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const {
    return data[index];
}

template <typename T>
void Vector<T>::push_back(const T& value) {
    if (size == capacity)
        reallocate(capacity == 0 ? 1 : capacity * 2);
    data[size++] = value;
}

template <typename T>
void Vector<T>::pop_back() {
    if (size > 0)
        --size;
}

template <typename T>
size_t Vector<T>::getSize() const {
    return size;
}

template <typename T>
bool Vector<T>::empty() const {
    return size == 0;
}

template <typename T>
void Vector<T>::reallocate(size_t newCap) {
    T* newData = new T[newCap];
    for (size_t i = 0; i < size; ++i)
        newData[i] = data[i];
    delete[] data;
    data = newData;
    capacity = newCap;
}

#endif // VECTOR_HPP
