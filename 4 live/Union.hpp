#ifndef UNION_HPP
#define UNION_HPP

#include <cstddef>

template<typename T1, typename T2>
class Union {
    private:
        T1* p1;
        T2* p2;
        bool isFirstFlag;

    public:
        Union() = delete;
        Union(const T1& v);
        Union(const T2& v);
        Union(const Union<T1, T2>& other);
        ~Union();

        Union<T1, T2>& operator=(const Union<T1, T2>& other);
        Union<T1, T2>& operator=(const T1& v);
        Union<T1, T2>& operator=(const T2& v);

        bool isFirst() const;
        bool isSecond() const;

        T1 getFirst() const;
        T2 getSecond() const;
};

// Partial specialization: T1 jest typem wskaźnikowym (U*), T2 nie
template<typename U, typename T2>
class Union<U*, T2> {
    private:
        U* p1;
        T2* p2;
        bool isFirstFlag;

    public:
        Union() = delete;
        Union(U* const& ptr);
        Union(const T2& v);
        Union(const Union<U*, T2>& other);
        ~Union();

        Union<U*, T2>& operator=(const Union<U*, T2>& other);
        Union<U*, T2>& operator=(U* const& ptr);
        Union<U*, T2>& operator=(const T2& v);

        bool isFirst() const;
        bool isSecond() const;

        U* getFirst() const;
        T2 getSecond() const;
};

// Partial specialization: T1 nie jest wskaznikiem, T2 jest
template<typename T1, typename V>
class Union<T1, V*> {
    private:
        T1* p1;
        V* p2;
        bool isFirstFlag;

    public:
        Union() = delete;
        Union(const T1& v);
        Union(V* const& ptr);
        Union(const Union<T1, V*>& other);
        ~Union();

        Union<T1, V*>& operator=(const Union<T1, V*>& other);
        Union<T1, V*>& operator=(const T1& v);
        Union<T1, V*>& operator=(V* const& ptr);

        bool isFirst() const;
        bool isSecond() const;

        T1 getFirst() const;
        V* getSecond() const;
};

// Partial specialization: oba typy są wskaźnikami
template<typename U, typename V>
class Union<U*, V*> {
    private:
        U* p1;
        V* p2;
        bool isFirstFlag;

    public:
        Union() = delete;
        Union(U* const& ptr1);
        Union(V* const& ptr2);
        Union(const Union<U*, V*>& other);
        ~Union();

        Union<U*, V*>& operator=(const Union<U*, V*>& other);
        Union<U*, V*>& operator=(U* const& ptr);
        Union<U*, V*>& operator=(V* const& ptr);

        bool isFirst() const;
        bool isSecond() const;

        U* getFirst() const;
        V* getSecond() const;
};

template<typename T1, typename T2>
Union<T1, T2>::Union(const T1& v): p1(new T1(v)), p2(NULL), isFirstFlag(true) {}

template<typename T1, typename T2>
Union<T1, T2>::Union(const T2& v): p1(NULL), p2(new T2(v)), isFirstFlag(false) {}

template<typename T1, typename T2>
Union<T1, T2>::Union(const Union<T1, T2>& other): p1(NULL), p2(NULL), isFirstFlag(other.isFirstFlag) {
    if (other.isFirstFlag) {
        if (other.p1) p1 = new T1(*other.p1);
    } else {
        if (other.p2) p2 = new T2(*other.p2);
    }
}

template<typename T1, typename T2>
Union<T1, T2>::~Union() {
    if (p1) {
        delete p1;
        p1 = NULL;
    }
    if (p2) {
        delete p2;
        p2 = NULL;
    }
}

template<typename T1, typename T2>
Union<T1, T2>& Union<T1, T2>::operator=(const Union<T1, T2>& other) {
    if (this == &other) return *this;

    if (p1) {
        delete p1;
        p1 = NULL;
    }
    if (p2) {
        delete p2;
        p2 = NULL;
    }

    isFirstFlag = other.isFirstFlag;
    if (other.isFirstFlag) {
        if (other.p1) p1 = new T1(*other.p1);
    } else {
        if (other.p2) p2 = new T2(*other.p2);
    }
    return *this;
}

template<typename T1, typename T2>
Union<T1, T2>& Union<T1, T2>::operator=(const T1& v) {
    if (p1) {
        delete p1;
        p1 = NULL;
    }
    if (p2) {
        delete p2;
        p2 = NULL;
    }
    p1 = new T1(v);
    isFirstFlag = true;
    return *this;
}

template<typename T1, typename T2>
Union<T1, T2>& Union<T1, T2>::operator=(const T2& v) {
    if (p1) {
        delete p1;
        p1 = NULL;
    }
    if (p2) {
        delete p2;
        p2 = NULL;
    }
    p2 = new T2(v);
    isFirstFlag = false;
    return *this;
}

template<typename T1, typename T2>
bool Union<T1, T2>::isFirst() const {
    return isFirstFlag;
}

template<typename T1, typename T2>
bool Union<T1, T2>::isSecond() const {
    return !isFirstFlag;
}

template<typename T1, typename T2>
T1 Union<T1, T2>::getFirst() const {
    if (isFirstFlag && p1) return *p1;
    return T1();
}

template<typename T1, typename T2>
T2 Union<T1, T2>::getSecond() const {
    if (!isFirstFlag && p2) return *p2;
    return T2();
}


//Specjalizacja 1
template<typename U, typename T2>
Union<U*, T2>::Union(U* const& ptr): p1(ptr), p2(NULL), isFirstFlag(true) {}

template<typename U, typename T2>
Union<U*, T2>::Union(const T2& v): p1(NULL), p2(new T2(v)), isFirstFlag(false) {}

template<typename U, typename T2>
Union<U*, T2>::Union(const Union<U*, T2>& other): p1(other.p1), p2(NULL), isFirstFlag(other.isFirstFlag) {
    if (!other.isFirstFlag) {
        if (other.p2) p2 = new T2(*other.p2);
    }
}

template<typename U, typename T2>
Union<U*, T2>::~Union() {
    // nie usuwamy p1
    if (p2) {
        delete p2;
        p2 = NULL;
    }
}

template<typename U, typename T2>
Union<U*, T2>& Union<U*, T2>::operator=(const Union<U*, T2>& other) {
    if (this == &other) return *this;

    if (p2) {
        delete p2;
        p2 = NULL;
    }

    isFirstFlag = other.isFirstFlag;
    p1 = other.p1;
    if (!other.isFirstFlag) {
        if (other.p2) p2 = new T2(*other.p2);
    }
    return *this;
}

template<typename U, typename T2>
Union<U*, T2>& Union<U*, T2>::operator=(U* const& ptr) {
    if (p2) {
        delete p2;
        p2 = NULL;
    }
    p1 = ptr;
    isFirstFlag = true;
    return *this;
}

template<typename U, typename T2>
Union<U*, T2>& Union<U*, T2>::operator=(const T2& v) {
    if (p2) {
        delete p2;
        p2 = NULL;
    }
    p2 = new T2(v);
    isFirstFlag = false;
    return *this;
}

template<typename U, typename T2>
bool Union<U*, T2>::isFirst() const {
    return isFirstFlag;
}

template<typename U, typename T2>
bool Union<U*, T2>::isSecond() const {
    return !isFirstFlag;
}

template<typename U, typename T2>
U* Union<U*, T2>::getFirst() const {
    if (isFirstFlag) return p1;
    return NULL;
}

template<typename U, typename T2>
T2 Union<U*, T2>::getSecond() const {
    if (!isFirstFlag && p2) return *p2;
    return T2();
}

//Specjalizacja 2
template<typename T1, typename V>
Union<T1, V*>::Union(const T1& v): p1(new T1(v)), p2(NULL), isFirstFlag(true) {}

template<typename T1, typename V>
Union<T1, V*>::Union(V* const& ptr): p1(NULL), p2(ptr), isFirstFlag(false) {}

template<typename T1, typename V>
Union<T1, V*>::Union(const Union<T1, V*>& other): p1(NULL), p2(other.p2), isFirstFlag(other.isFirstFlag) {
    if (other.isFirstFlag) {
        if (other.p1) p1 = new T1(*other.p1);
    }
}

template<typename T1, typename V>
Union<T1, V*>::~Union() {
    // nie usuwamy p2_
    if (p1) {
        delete p1;
        p1 = NULL;
    }
}

template<typename T1, typename V>
Union<T1, V*>& Union<T1, V*>::operator=(const Union<T1, V*>& other) {
    if (this == &other) return *this;

    if (p1) {
        delete p1;
        p1 = NULL;
    }

    isFirstFlag = other.isFirstFlag;
    p2 = other.p2;
    if (other.isFirstFlag) {
        if (other.p1) p1 = new T1(*other.p1);
    }
    return *this;
}

template<typename T1, typename V>
Union<T1, V*>& Union<T1, V*>::operator=(const T1& v) {
    if (p1) {
        delete p1;
        p1 = NULL;
    }
    p1 = new T1(v);
    isFirstFlag = true;
    return *this;
}

template<typename T1, typename V>
Union<T1, V*>& Union<T1, V*>::operator=(V* const& ptr) {
    if (p1) {
        delete p1;
        p1 = NULL;
    }
    p2 = ptr;
    isFirstFlag = false;
    return *this;
}

template<typename T1, typename V>
bool Union<T1, V*>::isFirst() const {
    return isFirstFlag;
}

template<typename T1, typename V>
bool Union<T1, V*>::isSecond() const {
    return !isFirstFlag;
}

template<typename T1, typename V>
T1 Union<T1, V*>::getFirst() const {
    if (isFirstFlag && p1) return *p1;
    return T1();
}

template<typename T1, typename V>
V* Union<T1, V*>::getSecond() const {
    if (!isFirstFlag) return p2;
    return NULL;
}

//Specjalizacja 3
template<typename U, typename V>
Union<U*, V*>::Union(U* const& ptr1): p1(ptr1), p2(NULL), isFirstFlag(true) {}

template<typename U, typename V>
Union<U*, V*>::Union(V* const& ptr2): p1(NULL), p2(ptr2), isFirstFlag(false) {}

template<typename U, typename V>
Union<U*, V*>::Union(const Union<U*, V*>& other): p1(other.p1), p2(other.p2), isFirstFlag(other.isFirstFlag) {}

template<typename U, typename V>
Union<U*, V*>::~Union() {
    // nie usuwamy żadnego wskaźnika
}

template<typename U, typename V>
Union<U*, V*>& Union<U*, V*>::operator=(const Union<U*, V*>& other) {
    if (this == &other) return *this;

    p1 = other.p1;
    p2 = other.p2;
    isFirstFlag = other.isFirstFlag;
    return *this;
}

template<typename U, typename V>
Union<U*, V*>& Union<U*, V*>::operator=(U* const& ptr) {
    p1 = ptr;
    p2 = NULL;
    isFirstFlag = true;
    return *this;
}

template<typename U, typename V>
Union<U*, V*>& Union<U*, V*>::operator=(V* const& ptr) {
    p1 = NULL;
    p2 = ptr;
    isFirstFlag = false;
    return *this;
}

template<typename U, typename V>
bool Union<U*, V*>::isFirst() const {
    return isFirstFlag;
}

template<typename U, typename V>
bool Union<U*, V*>::isSecond() const {
    return !isFirstFlag;
}

template<typename U, typename V>
U* Union<U*, V*>::getFirst() const {
    if (isFirstFlag) return p1;
    return NULL;
}

template<typename U, typename V>
V* Union<U*, V*>::getSecond() const {
    if (!isFirstFlag) return p2;
    return NULL;
}

#endif // UNION_HPP