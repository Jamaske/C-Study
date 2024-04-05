

template<typename T>
class Vector {
    T x, y, z;
    Vector(const T x, T y, T z) : x(x), y(y), z(z) {}
    Vector(const Vector& src) : x(src.x), y(src.y), z(src.z) {}

    Vector& operator+= (const Vector& other) const {
        this.x += other.x; this.y += other.y; this.z += other.z;
        return this;
    }

    Vector& operator-= (const Vector& other) const {
        this.x -= other.x; this.y -= other.y; this.z -= other.z;
        return this;
    }

    Vector& operator- (const Vector& other) const {
        return Vector(this.x - other.x, this.y - other.y, this.z - other.z);
    }

    Vector& operator- ()const {
        return Vector(-this.x, -this.y, -this.z);
    }

    Vector& operator^(const Vector& other)const {
        return Vector(
            this.y * other.z - this.z * other.y,
            this.z * other.x - this.x * other.z,
            this.x * other.y - this.y * other.x
        );
    }

    T operator*(const Vector& other) {
        return this.x * other.x + this.y * other.y + this.z * other.z;
    }
};





template<typename T>
Vector<T> operator+(const Vector<T>& lhs, const Vector<T>& rhs) {
    return Vector<T>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}
template<typename T>
Vector<T> operator+(Vector<T>&& lhs, const Vector<T>& rhs){
    return lhs += rhs;
}
template<typename T>
Vector<T> operator+(const Vector<T>&, Vector<T>&&);
template<typename T>
Vector<T> operator+(Vector<T>&&, Vector<T>&&);


int main() {
    return 0;
}