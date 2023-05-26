

//Vector implementation
template<typename T>
Vector<T>::Vector(T x, T y, T z):
        x(x), y(y), z(z){

}

template<typename T>
Vector<T>::Vector():
    Vector(0,0,0){

}

template<typename T>
Vector<T>::~Vector()= default;

template<typename T>
Vector<T>::Vector(const Vector<T> &src):
    x(src.x), y(src.y), z(src.z){

}

template<typename T>
Vector<T>& Vector<T>::operator= (const Vector<T> &src) {
    x = src.x;
    y = src.y;
    z = src.z;
    return *this;
}
/*
template<typename T>
T Vector<T>::operator[](unsigned char which){
    switch (which) {
        case 0:
        case 'x':
            return x;
        case 1:
        case 'y':
            return y;
        case 2:
        case 'z':
            return z;
        default:
            return;
    }
}
*/
template<typename T>
T Vector<T>::Len2() {
    return x*x + y*y + z*z;
}

template<typename T>
Vector<T> Vector<T>::operator+(const Vector<T>& other) {
    return Vector(x+other.x, y+other.y, z+other.z);
}

template<typename T>
Vector<T> Vector<T>::operator-(const Vector<T>& other) {
    return Vector(x-other.x, y-other.y, z-other.z);
}

template<typename T>
T Vector<T>::operator*(const Vector<T> &other) {//dot product
    return x*other.x + y*other.y + z*other.z;
}


template<typename T>
Vector<T> Vector<T>::operator^(const Vector<T> &other) {//cross product
    return Vector(y*other.z - z*other.y,  x * other.z - z * other.x,  x * other.y - y * other.x);
}

template<typename T>
Vector<T> Vector<T>::operator*(T t) {
    return Vector(t*x, t*y, t*z);
}


template<typename T>
void Vector<T>::PrintVector(std::ostream out) {
    out << '(' << x << "; " << Vector::y<<"; "<< Vector::z<<' ' <<')'<< std::endl;
}

template<typename T>
T triple_prod(const Vector<T>& a, const Vector<T>& b, const Vector<T>& c){
    return (a^b)*c;
}


//Segment implementation
template<typename T>
Segment<T>::Segment(Vector<T> point0,Vector<T> point1):
    p0(point0), p1(point1){

}

template<typename T>
Segment<T>::Segment():Segment(Vector<T>(), Vector<T>()){

}

template<typename T>
Segment<T>::~Segment() = default;


template<typename T>
Segment<T>::Segment(Segment<T> &src):
    p0(src.p0), p1(src.p1){

}

template<typename T>
Segment<T>& Segment<T>::operator=(const Segment<T> &src){
    p0 = src.p0;
    p1 = src.p1;
    return *this;
}

template<typename T>
Vector<T> Segment<T>::Get_Dir_Vec() {
    return p1 - p0;
}

template<typename T>
T Segment<T>::Len2(){
    return Get_Dir_Vec().Len2();
}

template<typename T>
bool Segment<T>::IsBelong(const Vector<T>& point) {
    Vector a = point - p0;
    Vector b = p1 - point;
    return (a ^ b).Len2() == 0;
}

/*
 * template<typename T>
bool Segment<T>::IsIntersects(Segment<T> other_segment) {
    return triple_prod(this->Get_Dir_Vec(), other_segment.Get_Dir_Vec(), p0 - other_segment.p0) == 0;
}

template<typename T>
T Segment<T>::crossing_dist(Segment<T> other_segment) {
    Vector<T> norm = this->Get_Dir_Vec() ^ other_segment.Get_Dir_Vec();
    norm = norm * (1 / sqrt(norm.Len2()));//use any other normalization method you need
    return norm * (p0 - other_segment.p0);
}

template<typename T>
Vector<T> Segment<T>::Intersection(Segment<T> other_segment) {
    return Vector<T>();
}
 */

template<typename T>
void Segment<T>::PrintSegment() {
    std::cout << "point0: ";
    p0.PrintVector();
    std::cout << "point1: ";
    p1.PrintVector();
}

//Plane implementation
template<typename T>
Plane<T>::Plane(Vector<T> normal, T offset):
    norm(normal), offset(offset) {

}

template<typename T>
Plane<T>::Plane(Vector<T> normal, Vector<T> any_point):
    Plane(normal, (normal * any_point) * -1){

}

template<typename T>
Plane<T>::Plane(Vector<T> A, Vector<T> B, Vector<T> C):
    Plane( (B-A)^(C-A), A) {

}

template<typename T>
Plane<T>::~Plane() = default;

template<typename T>
Plane<T>::Plane(const Plane<T> &src):
    norm(src.norm), offset(src.offset){

}

template<typename T>
Plane<T>& Plane<T>::operator=(const Plane<T> &src) {
    norm = src.norm;
    offset = src.offset;
    return *this;
}

template<typename T>
bool Plane<T>::IsBelong(const Vector<T> &some_point) {
    return norm * some_point + offset == 0;
}

template<typename T>
bool Plane<T>::Dist_to_Point(const Vector<T> &some_point, T &dist) {
    dist = (norm * some_point + offset) / sqrt(norm.Len2());
    return !dist;
}

template<typename T>
bool Plane<T>::IsParallel(const Plane<T> &other_plane) {
    return (norm ^ other_plane.norm).Len2() == 0;
}

template<typename T>
bool Plane<T>::Intersection(const Plane<T> &other_plane, Vector<T> &intersection, T& dist) {
    intersection = norm ^ other_plane.norm;
    if(intersection.Len2() == 0){
        dist = offset / sqrt(norm.Len2()) - other_plane.offset / sqrt(other_plane.norm.Len2());
    }
    return !dist;
}










