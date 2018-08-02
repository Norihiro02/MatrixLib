#include <math.h>
class Matrix{
private:
	double *mat;//�s��̒��g
	int row;
	int column;
	int size;
	int getAdres(int row, int column);
public:
	int Init(int row, int column);
	Matrix();
	Matrix(int row, int column);//�����T�C�Y��w��
	~Matrix();
	void set(double data, int row, int column);//�v�f�Ƀf�[�^����B
	double get(int row, int column);//�v�f����f�[�^����o���B
	int LU(Matrix &matL,Matrix &matU);
	int checkDiag();
	int checkSquare();
	double det();//�s�񎮂�Z�o
	int swapRow(int row0, int row1);
	int swapColu(int colu0, int colu1);

	//�s��v�Z�p�̉��Z�q
	Matrix& operator =(const Matrix &mat);
	Matrix& operator +(const Matrix &mat);
	Matrix& operator +=(const Matrix &mat);
	Matrix& operator -(const Matrix &mat);
	Matrix& operator -=(const Matrix &mat);
	Matrix& operator *(const Matrix &mat);
	Matrix& operator *=(const Matrix &mat);
	Matrix& operator /(const Matrix &mat);
	Matrix& operator /=(const Matrix &mat);
};
