#include "RefCounter.h"

template<typename T>
class MySmartPointer{
public:
    MySmartPointer() {
        counterPointer = nullptr;
        objectPointer = nullptr;
    }

    MySmartPointer(T* objectPointer) {
        this->objectPointer = objectPointer;
        counterPointer = new RefCounter();
        counterPointer->add();
    }

    MySmartPointer(const MySmartPointer<T>& other) {
        objectPointer = other.objectPointer;
        counterPointer = other.counterPointer;
        if (counterPointer) counterPointer->add();
    }

    MySmartPointer(MySmartPointer<T>&& other) {
        objectPointer = other.objectPointer;
        counterPointer = other.counterPointer;
        other.objectPointer = nullptr;
        other.counterPointer = nullptr;
    }

    ~MySmartPointer() {
        release();
    }

    MySmartPointer<T>& operator=(const MySmartPointer<T>& other) {
        if (this == &other) return (*this);

        release();

        counterPointer = other.counterPointer;
        objectPointer = other.objectPointer;

        if (counterPointer) counterPointer->add();

        return (*this);
    }

    MySmartPointer<T>& operator=(MySmartPointer<T>&& other) {
        if (this == &other) return (*this);

        release();

        counterPointer = other.counterPointer;
        objectPointer = other.objectPointer;
        other.objectPointer = nullptr;
        other.counterPointer = nullptr;

        return (*this);
    }

    T& operator*() const {
        return(*objectPointer);
    }

    T* operator->() const {
        return(objectPointer);
    }

    T* getObjectPointer() const {
        return(objectPointer);
    }

    int getRefCount() const {
        return(counterPointer ? counterPointer->get() : 0);
    }


private:
    RefCounter* counterPointer;
    T* objectPointer;

    void release() {
        if (counterPointer) {
            counterPointer->dec();
            if (counterPointer->get() == 0) {
                delete objectPointer;
                delete counterPointer;
            }
        }
        counterPointer = nullptr;
        objectPointer = nullptr;
    }
};




