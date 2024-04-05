template<typennem T>
class quatornion {
    T w, x, y, z;

    quatornion(T w, T x, T y, T z) : w(w), x(x), y(y), z(z) {}
    quatornion(const quatornion& src) : w(src.w), x(src.x), y(src.y), z(src.z) {}
  

}