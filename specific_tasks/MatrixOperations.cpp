#include <iostream>
#include <string>
using namespace std;

//MatrixIO
void cinMatrix(int **&, int, int, int);
void coutMatrix(int **&, int, int, int, int, bool);
void DeleteMatrix(int **&, int, int);
//Operations
void GetTransposedMatrix(int **&, int **&, int, int);
//miscellaneous
string StringToLen(string, int, char, bool);
string GetElement(int **&, int, int, int, int, int, bool);

int main(){
    int n;
    int **A, Aw, Ah;
    cin >> n >> Ah;
    Aw = n/Ah + bool(n % Ah);
    cinMatrix(A, Ah, Aw, n);
    int **B, Bh = Aw, Bw = Ah;
    GetTransposedMatrix(A, B, Ah, Aw);
    DeleteMatrix(A, Ah, Aw);
    coutMatrix(B, Bh , Bw, 4, n, false);
    DeleteMatrix(B, Bh, Bw);
}

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