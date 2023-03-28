#include <iostream>
#include <cmath>
using namespace std;

//сортировки
template <typename elType>
void BubbleSort(elType* arr, int n, bool (*comparator)(elType, elType) = NULL){
    /*
     * BubbleSort простая сортировка для небольших массивов ~1000
     * сложность:
     *   худшая  O(n^2)
     *   средняя O(n^2)
     *   лучшая  O(n^2)
     * память O(1)
    */
    if (comparator == NULL) {
        elType temp;
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - 1; ++j) {
                if (arr[j] > arr[j + 1]) {
                    temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
    else{
        elType temp;
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - 1; ++j) {
                if ( comparator( arr[j], arr[j + 1]) ) {
                    temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
}

template <typename elType>
void QuickSort(elType *arr, int end, int start = 0){
    /*
     * recursive QuickSort хорошая и простая в написании сортировка
     * сложность:
     *   худшая  O(n^2)
     *   средняя O(n*log(n))
     *   лучшая  O(n*log(n))
     * память O(1)
     */
    if (start>=end){
        return;
    }
    elType pivot= arr[end];
    int SepPointer = start;
    elType temp;
    for(int i = start; i < end; i++){
        if (arr[i] < pivot){
            temp = arr[i];
            arr[i] = arr[SepPointer];
            arr[SepPointer] = temp;
            SepPointer++;
        }
    }
    temp = arr[end];
    arr[end] = arr[SepPointer];
    arr[SepPointer] = temp;
    Quicksort(arr, SepPointer-1, start);
    Quicksort(arr, end, SepPointer+1);
}

template <typename elType>
void Merge_sort(elType* &arr, unsigned int len) {
    /*
     *не рекурсивная MergeSort
     * сложность:
     *   худшая  O(n*log(n))
     *   средняя O(n*log(n))
     *   лучшая  O(n*log(n))
     * память O(n)
     */
    unsigned int block_size = 1, block_start, block_sep, block_end;
    elType *arr2 = new elType[len];
    unsigned int i, j, k;

    while (true) {
        if (block_size >= len) {
            //delete[] arr2;
            break;
        }

        block_end = 0;
        //сортируем все блоки из arr в arr2
        do {
            //сортируем конкретные два блока
            block_start = block_end;
            block_sep = min(block_start + block_size, len);
            block_end = min(block_sep + block_size, len);
            for (i = block_start, j = block_sep, k = block_start; i < block_sep && j < block_end;) {
                if (arr[i] < arr[j]) arr2[k++] = arr[i++];
                else arr2[k++] = arr[j++];
            }
            if (i < block_sep) memcpy(arr2 + k, arr + i, (block_sep - i) * sizeof(elType));
            else if (j < block_end) memcpy(arr2 + k, arr + j, (block_end - j) * sizeof(elType));

        } while (block_end != len);
        block_size *= 2;

        if (block_size >= len) {
            //delete[] arr;
            arr = arr2;
            break;
        }

        block_end = 0;
        //сортируем все блоки из arr2 в arr
        do {
            //сортируем конкретные два блока
            block_start = block_end;
            block_sep = min(block_start + block_size, len);
            block_end = min(block_sep + block_size, len);
            for (i = block_start, j = block_sep, k = block_start; i < block_sep && j < block_end;) {
                if (arr2[i] < arr2[j]) arr[k++] = arr2[i++];
                else arr[k++] = arr2[j++];
            }
            if (i < block_sep) memcpy(arr + k, arr2 + i, (block_sep - i) * sizeof(elType));
            else if (j < block_end) memcpy(arr + k, arr2 + j, (block_end - j) * sizeof(elType));

        } while (block_end != len);
        block_size *= 2;
    }
}


//матрицы !!нужно переписать на структуры
string stl(string s, int ToLen, char fill = ' ', bool beak = false){
    int Len = s.length();
    if (Len < ToLen){
        if (beak){
            s.append(string(ToLen - Len, fill));

            return s;
        }
        else {
            s.insert(0, string(ToLen - Len, fill));
            return s;
        }
    }
    else if (Len > ToLen) {
        if (beak) return s.substr(0, ToLen);
        else return s.substr(Len - ToLen, ToLen);
    }
    else return s;
}
string GetElement(int **&matrix, int i, int j, int h, int w, int el_num, bool RowCountPrior = true){
    if ((RowCountPrior && i * w + j < el_num) || (!RowCountPrior && j * h +i < el_num)) return to_string(matrix[i][j]);
    else return "";
}
void cinMatrix(int **&matrix, int h, int w, int el_num){
    matrix = new int* [h];
    int i, j, k = 0;
    int temp;
    for(i = 0; i < h; i++){
        matrix[i] = new int[w];
        for(j = 0; j < w; j++){
            if (k++ < el_num) {
                cin>>temp;
                matrix[i][j] = temp;
            }
            else matrix[i][j] = -1;
        }
    }
}
void coutMatrix(int **&matrix, int h, int w, int cell_size,int el_num, bool RowCountPrior = true){
    /* sep chars map
    ctttttttttttttttc
    l   h   h   h   r
    lvvvxvvvxvvvxvvvr
    l   h   h   h   r
    lvvvxvvvxvvvxvvvr
    l   h   h   h   r
    cbbbbbbbbbbbbbbbc
    use lower case x to print nothing*/
    const char L = '{';
    const char H = '|';
    const char R = '}';

    const char T = '_';
    const char V = '-';
    const char B = '=';

    //removed with other lines
    const char X = '+';
    const char C = '*';

    //шапка
    if (T!='x') {
        if (L!='x') cout << C;
        cout<< string((cell_size+1)*w - 1, T);
        if (R!='x')cout << C;
        cout << endl;
    }

    //первоя строка
    if(h > 0) {
        if (L!='x') cout << L ;
        if (w > 0) cout << stl(GetElement(matrix, 0, 0, h,  w, el_num, RowCountPrior), cell_size);
        for (int j = 1; j < w; j++) {
            if (H!='x')cout << H;
            cout << stl(GetElement(matrix, 0, j, h, w, el_num, RowCountPrior), cell_size);
        }
        if (R!='x') cout << R;
        cout << endl;
    }

    //[2;h] строки
    for (int i = 1; i < h; ++i) {
        //разделители строк
        if (V!='x') {
            if (L != 'x') cout << L;
            cout << string(cell_size, V);
            for (int j = 1; j < w; j++){
                if (H!='h') cout << X;
                cout << string(cell_size, V);
            }
            if (R!='x') cout << R;
            cout << endl;
        }

        if (L!='x') cout << L;
        if (w > 0) cout << stl(GetElement(matrix, i, 0, h, w, el_num, RowCountPrior), cell_size);
        for (int j = 1; j < w; ++j) {
            if (H!='x')cout << H;
            cout << stl(GetElement(matrix, i, j, h, w, el_num,RowCountPrior), cell_size);
        }
        if (R!='x') cout << R;
        cout << endl;
    }

    //низ
    if (B!='x') {
        if (L!='x') cout << C;
        cout << string((cell_size + 1) * w - 1, B);
        if (R!='x') cout << C;
        cout << endl;
    }
}
void DeleteMatrix(int **&matrix, int h, int w){
    for (int i = 0; i < h; i++){
        delete matrix[i];
    }
    delete matrix;
}
void GetTransposedMatrix(int **&matrix, int **&matrixT, int h, int w){
    matrixT = new int* [w];
    for (int i = 0; i < w; ++i) {
        matrixT[i] = new int[h];
        for (int j = 0; j < h; ++j) {
            matrixT[i][j] = matrix[j][i];
        }
    }
}



//List
template<typename elType>
struct list{//lists aka dynamic arrays
            elType *storage;//real array
            unsigned int buffer;//size of storage
            elType *elements;//part of storage filled with real elements, which located somewhere in center
            unsigned int size;//size of filled elements

            unsigned int LfS ;//Left free Space - free space for adding elements to the beginning without reallocating array in heap each time
            unsigned  int RfS;//Right free Space - same for left

            float LfR;//Left free Ratio - ratio between size and LfS
            float RfR;//Right free Ratio - ratio between size and RfS
            //LfS = size * Lf_ratio; RfS = size * Rf_ratio; note put ZERO to disable buffering spare space at this side

            unsigned short elsize = sizeof(elType);//размер элементов

            explicit list (float Left_free_Space_Ratio = 0.25, float Right_free_Space_Ratio = 0.5){
                //ОСТОРОЖНО - КОСТЫЛЬИ
                //для инициализации нужен пробный элемент для определения типа данных
                elsize = sizeof(elType);
                buffer = 1;
                storage = new elType[buffer];//НЕ ВЫКАЛИ ГЛАЗА

                LfR = Left_free_Space_Ratio;
                RfR = Right_free_Space_Ratio;
                LfS = 0;
                RfS = 1;
                size = 0;
                elements = storage;

            }

            void Normalize(){
                //пересоздаёт массив по размеру заполненных данных
                elType *temp = new elType[size];
                memcpy(temp, elements, elsize * size);
                delete[] storage;
                LfS = 0; RfS = 0; buffer = size;
                storage = temp; elements = temp;
            }
            void Buffering(int reserve = 0){
                //добавляет reserve ячеек в список
                //положительные значения reserve используются для доп памяти справа, отрицательные для доп памяти слева

                if(reserve > 0){
                    LfS = LfR * (size + reserve);
                    RfS = RfR * (size + reserve) + reserve;
                }
                else{
                    LfS = LfR * (size + (-reserve) ) + (-reserve);
                    RfS = RfR * (size + (-reserve));
                }

                buffer = LfS + size + RfS;

                elType *temp = new elType[buffer];
                memcpy(temp + LfS, elements, elsize * size);
                delete[] storage;
                storage = temp;
                elements = storage + LfS;
            }

            void Info(){
                cout << "====INFO====\n";
                cout << "buffer: " << buffer << endl;
                cout << "size: " << size << endl;
                cout << "Left free Space: " << LfS << endl;
                cout << "Right free Space: " << RfS << endl;
                cout << "Storage location: " << &storage << endl;
                cout << "elements location: " << &elements << endl;
                cout << "=============\n";
            }
            void Delete(){
                //хз чё ещё должно быть
                delete[] storage;
            }
            void Print(){
                for(int i = 0; i < size; i++){
                    cout << elements[i] << ' ';
                }
                cout << endl;
            }

            elType getel(unsigned int index, elType deflt = NULL){
                if(index >= size) return deflt;
                return elements[index];
            }
            elType* getsubarr(unsigned int start, unsigned int len){
                if (start + len > size) return nullptr;
                elType* temp = new elType[len];
                memcpy(temp, elements + start, elsize * len);
                return temp;
            }

            //add <element/array/list> to the end of the list
            void append(elType element){
                if(!RfS) Buffering(1);
                RfS--;
                elements[size] = element;
                size++;
            }
            void append(elType *arr, unsigned int len){
                if(RfS < len) Buffering(len);
                RfS -= len;
                memcpy(elements + size, arr, elsize * len);
                size += len;
            }
            void append(list arr){
                if(RfS < arr.size) Buffering(arr.size);
                RfS -= arr.size;
                memcpy(elements + size, arr.elements, elsize * arr.size);
                size += arr.size;
            }

            //add <element/array/list> to the beginning of the list
            void appbeg(elType element){
                if(!LfS) Buffering(-1);
                LfS--;
                elements--;
                size++;
                elements[0] = element;

            }
            void appbeg(elType *arr, unsigned int len){
                if(LfS < len) Buffering(-len);
                LfS -= len;
                elements -= len;
                size += len;
                memcpy(elements, arr, elsize * len);

            }
            void appbeg(list arr){
                if(LfS < arr.size) Buffering(-arr.size);
                RfS -= arr.size;
                elements -= arr.size;
                size += arr.size;
                memcpy(elements, arr.elements, elsize * arr.size);
            }

            //remove <element/fragment> from the end of the list
            //return fragment in form of array or another list
            elType popend(){
                RfS++;
                return elements[size--];
            }
            elType* popend(unsigned int len){
                if(len > size) return nullptr;
                elType *temp = new elType[len];
                RfS += len;
                size -=len;
                memcpy(temp, elements + size, elsize * len);
                return temp;
            }
            list popend_list(unsigned int len){
                if(len > size) return nullptr;
                list temp = list<elType>(LfR, RfR);
                RfS += len;
                size -=len;
                temp.append(elements + size, len);
                return temp;
            }


            elType popbeg(){
                size--;
                elements++;
                LfS++;
                return elements[-1];
            }
            elType* popbeg(unsigned int len){
                if(len > size) return nullptr;
                elType *temp = new elType[len];
                memcpy(temp, elements, elsize * len);
                size -=len;
                elements += len;
                RfS += len;
                return temp;
            }
            list popbeg_list(unsigned int len){
                if(len > size) cout << "popbeg_list function invalid len error"<< endl;
                else {
                    list temp = list<elType>(LfR, RfR);
                    temp.append(elements, len);
                    size -= len;
                    elements += len;
                    RfS += len;
                    return temp;
                }
            }
};
void Dynamic_Array_showcase(){
    list arr = list<char>(0.25,1.0);
    arr.Buffering(-5);

    arr.Info();

    arr.append("abr",3);
    arr.append('a');
    arr.append("ca", 2);
    arr.append("da",2);
    arr.append("bra",3);

    arr.appbeg("!!", 2);
    arr.append("_cool!", 6);

    cout << "after all appending" << endl;
    arr.Info();

    cout<< "1)"; arr.Print();

    cout << endl << "2)"; list temp1 = arr.popbeg_list(8); temp1.Print();

    cout << endl << "3)";cout << arr.popbeg() << endl;

    cout << endl << "4)"; arr.Print();

    cout << endl << "5)" << endl;
    char *temp2 = arr.getsubarr(4, 5);
    for(int i = 0; i < 5; i++){
        cout << temp2[i]<<endl;
    }
    cout<< endl;

    arr.Info();
}

//Data storage types
struct stack{

    struct node{
        int a;
        node* next;
    };

    node* top = nullptr;
    void push(int n){
        node* temp = new node;
        temp->a = n;
        temp->next = top;
        top = temp;
    }
    int pop(){
        int temp1 = top->a;
        node* temp2 = top->next;
        delete top;
        top = temp2;
        return temp1;
    }
    int get(int n){
        //возвращает n-ый элемент списка начиная с вершины
        node* pos = top;
        for(int i = 0; i < n; i++){
            pos = pos->next;
        }
        return pos->a;
    }
    bool is_empty(){
        return (top == nullptr);
    }
};

//3D Linear algebra
#define dttp double
struct Vector {
    dttp x;
    dttp y;
    dttp z;

    Vector() {
        x = 0;
        y = 0;
        z = 0;
    }

    Vector(dttp a, dttp b, dttp c) {
        x = a;
        y = b;
        z = c;
    }

    void read() {
        cin >> x >> y >> z;
    }

    void print() {
        cout << x << ' ' << y << ' ' << z << endl;
    }

    Vector operator+(const Vector &V) {//сумма
        return Vector(x + V.x, y + V.y, z + V.z);
    }

    Vector operator-(const Vector &V) {//разность
        return Vector(x - V.x, y - V.y, z - V.z);
    }

    Vector operator-() {//обратный вектор
        return Vector(-x, -y, -z);
    }

    dttp operator*(const Vector &V) {//скалярное произведение
        return (x * V.x + y * V.y + z * V.z);
    };

    Vector operator&(const Vector &V) {//векторное произведение
        return Vector(y * V.z - V.y * z, x * V.z - V.x * z, x * V.y - V.x * y);
    }

    bool isZero() {//равенство
        return (x == 0) && (y == 0) && (z == 0);
    }
    //как прописывая метод структуры обращаться к этой же структуре, а не её свойствам

    bool operator||(Vector &V) {//коллинеарность
        dttp temp;
        return (V.x * y * z == (temp = x * V.y * z)) && (temp == x * y * V.z);
    }

    dttp len2() {
        return (x * x + y * y + z * z);
    }

    double len1() {
        return sqrt(len2());
    }

    Vector scale(double t) {
        return Vector(x * t, y * t, z * t);
    }

    Vector normalize() {//dttp должен быть дробным
        double coef = 1 / sqrt(len2());
        return scale(coef);
    }
};
struct Line {
    Vector Base;
    Vector Dir;
    bool dirIsNormalised;

    Line(dttp pointX, dttp pointY, dttp pointZ, dttp diractionX, dttp diractionY, dttp diractionZ) {
        Base.x = pointX;
        Base.y = pointY;
        Base.z = pointZ;
        Dir.x = diractionX;
        Dir.y = diractionY;
        Dir.z = diractionZ;
        dirIsNormalised = (Dir * Dir == 1);
    }

    Line() {
        Base = Vector();
        Dir = Vector();
    }

    Line(Vector Point, Vector Direction) {
        Base = Point;
        Dir = Direction;
    }

    void read() {
        cin >> Base.x >> Base.y >> Base.z >> Dir.x >> Dir.y >> Dir.z;
        dirIsNormalised = (Dir * Dir == 1);
    }

    void print() {
        cout << "Base: " << Base.x << ' ' << Base.y << ' ' << Base.z << "  Direction: " << Dir.x << ' ' << Dir.y
             << ' ' << Dir.z << endl;
    }

    void NoramlizeDirectionVector() {
        if (!dirIsNormalised) Dir.normalize();
        dirIsNormalised = true;
    }

    bool isParallel(Line &L) {
        return (Dir & L.Dir).isZero();
    }

    double dist1(Vector &V) {//расстояние от прямой до точки
        Vector RotationAxis = (V - Base) & Dir;
        double dist;
        if (RotationAxis.x == 0 && RotationAxis.y == 0) dist = RotationAxis.z;
        else dist = RotationAxis.len1();

        if (!dirIsNormalised) dist /= Dir.len1();
        return dist;
    }

    double dist1(Line &L) {//расстояние от прямой до прямой
        return (Base - L.Base) * (Dir & L.Dir).normalize();
    }

};
struct Plane {
    Vector Base;
    Vector Normal;
    bool normalIsNormalized;

    Plane(dttp pointX, dttp pointY, dttp pointZ, dttp normalX, dttp normalY, dttp normalZ) {
        Base.x = pointX;
        Base.y = pointY;
        Base.z = pointZ;
        Normal.x = normalX;
        Normal.y = normalY;
        Normal.z = normalZ;
    }

    Plane() {
        Base = Vector();
        Normal = Vector();
    }

    Plane(Vector Point, Vector normalVector) {
        Base = Point;
        Normal = normalVector;
    }

    void read() {
        cin >> Base.x >> Base.y >> Base.z >> Normal.x >> Normal.y >> Normal.z;
    }

    void print() {
        cout << "Base: " << Base.x << ' ' << Base.y << ' ' << Base.z << "  Normal: " << Normal.x << ' ' << Normal.y
             << ' ' << Normal.z << endl;
    }

    void NormalizeNormalVector() {
        if (!normalIsNormalized) Normal = Normal.normalize();
        normalIsNormalized = true;
    }

    bool isParallel(Line &L) {
        return (Normal * L.Dir) == 0;
    }

    bool isParallel(Plane &P) {
        return (Normal & P.Normal).isZero();
    }

    double dist1(Vector &V) {//расстояние от плоскости до прямой
        double dist = (V - Base) * Normal;
        if (!normalIsNormalized) dist /= Normal.len1();

        return dist;
    }

    double dist1(Line &L) {
        if (!isParallel(L)) return 0;
        return dist1(L.Base);
    }

    double dist1(Plane &P) {
        if (!isParallel(P)) return 0;
        return dist1(P.Base);
    }

    Vector intersection(Line &L) {
        if (isParallel(L)) return Vector(0, 0, 0);//я хз как обрабатывать этот случай
        double t = ((Base - L.Base) * Normal) / (L.Dir * Normal);
        return L.Base + L.Dir.scale(t);
    }

/*
Line intersection(Plane &P){
    return Line(, Normal & P.Normal)
}
*/


};


//разное

void prefixfuc(char *str, int *pi, int len) {
    pi[0] = 0;
    int i = 0, j = 0;
    //для любого i ограничено сверху числом len
    while (++i < len) {
        //отображение str само на себя сюрьективно, так как из не равенства аргументов
        // (i огр сверху, а j стремиться к 0) следует не равенство значений функции str в них
        //выберем в качестве произвольного j число значение j-ого знака числа pi
        while (str[i] != str[j] && j-->0) j = pi[j];
        //получим что для любого i < len, i-ный символ числа pi равен приделу числа j справа
        pi[i] = ++j;
    }
}

double precise_sum(double &a,const double &b){
    //принимает a, b: a+b<inf
    //возвращает погрешность суммы, и заменяет первый аргумент суммой
    double s = a + b, r = s - b;
    r = (a - r) + (b - (s - r));
    a = s;
    return r;
}

double precise_sum(const double &a,const double &b, double &s){
    //принимает a, b: a+b<inf
    //возвращает погрешность суммы, и записывает суммы в 3 аргумент
    s = a + b;
    double r = s - b;
    return r = (a - r) + (b - (s - r));
}

double precise_sum_ordered(const double &a,const double &b, double &s){
    //принимает a, b: a+b<inf, a > b
    //возвращает погрешность суммы, и записывает суммы в 3 аргумент
    s = a + b;
    return b - (s - a);
}


int main(){
    Plane P1(Vector(1, 1, 1), Vector(1 , 0 ,1 ));
    Plane P2(Vector(1, 0, 0), Vector(1 , 0 ,1 ));
    Plane temp;
    temp = P1;
    P1 = P2;
    P2 = temp;
    P1.print();
    P2.print();

    }