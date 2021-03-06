#include<stdio.h>
#include"Matrix.h"

//行列の初期化
Matrix::Matrix(int row, int column){
	Init(row,column);
}
//行列を開放
Matrix::~Matrix(){

	delete[] mat;

	return;
}
//初期化(行列の行と列のサイズを指定する)
int Matrix::Init(int row, int column){

	this->row = row;
	this->column = column;
	this->size = row*column;
	mat = new double[row*column];
	//�G���[������Ă���
	if (mat == NULL){
		return 1;
	}
	return 0;
}
//行と列の番号と配列の要素番号の対応を調べる
int Matrix::getAdres(int row, int column){
	return this->column*row + column;
}
//指定要素に数値を入れる
void Matrix::set(double data, int row, int column){

	this->mat[getAdres(row, column)] = data;

	return;
}
//指定要素から数値を取り出す
double Matrix::get(int row, int column){
	return this->mat[getAdres(row, column)];
}
//行列をLU分解する
int  Matrix::LU(Matrix &matL, Matrix &matU){

	int i,j,k;
	double temp,temp2;
	int n = this->row;
	//�s��̏�����
	//matL.Init(this->row,this->column);
	//matU.Init(this->row, this->column);
	
	//�s���R�s�[����B
	
	for (i = 0; i < matL.row; i++){
		for (j = 0; j < matL.column; j++){
			matU.set(get(i,j), i, j);//����Ώۂ̍s���U�s��ɃR�s�[����B
			matL.set(i == j, i, j);//L�s��͒P�ʍs��ɂ���B
		}
	}
	//LU�����s���B
	for (j = 0; j < n; j++){//��
		for (i = j + 1; i < n; i++)//�s
		{
			//�Ίp�s��0�ɂȂ����ꍇ���s����
			//if (matU.get(i, j) == 0){
				//return 1;
			//}
			temp = matU.get(i, j) / matU.get(j, j);
			for (k = j; k < n; k++){//��𑀍�
				temp2 = matU.get(i, k) - temp*matU.get(j, k);
				matU.set(temp2, i, k);
			}
			matL.set(temp, i, j);
		}
	}
	return 0;

}
//行列式を求める
double Matrix::det(){

	int i;
	double det = 0;

	Matrix matL(this->row, this->column);
	Matrix matU(this->row, this->column);

	this->LU(matL, matU);
	//
	for (i = 0; i<this->row; i++){
		det += matU.get(i, i);
	}
	return 0;
}
//正方行列がどうか調べる
int Matrix::checkSquare(){
	
	return (this->row==this->column);

}
int Matrix::checkDiag(){
	int i;

	for (i = 0; i < column;i++){
		if (0==get(i,i)){
			return 1;
		}
	}
	return 0;
}
//行列の行を入れ替える
int Matrix::swapRow(int row0, int row1){

	int i;
	double temp;

	if (this->row < row0 || this->row < row1){
		return 1;
	}
	for (i = 0; i < this->column; i++){
		temp = this->get(row0, i);
		this->set(this->get(row1, i), row0, i);//�Е��̍s�̗v�f������B
		this->set(temp, row1, i);
	}
	return 0;
}
//行列の列を入れ替える
int Matrix::swapColu(int colu0, int colu1){

	int i;
	double temp;

	if (this->row < colu0 || this->row < colu1){
		return 1;
	}
	for (i = 0; i < this->column; i++){
		temp = this->get(i, colu0);
		this->set(this->get(i, colu1), i, colu0);//�Е��̍s�̗v�f������B
		this->set(temp, i, colu1);
	}
	return 0;
}
//工事中
Matrix &Matrix::operator =(const Matrix &mat){


	int i;
	this->row = mat.row;
	this->column = mat.column;
	this->size = mat.size;
	for (i = 0; i < mat.size; i++){
		this->mat[i] = mat.mat[i];
	}
	return *this;
}
Matrix &Matrix::operator +(const Matrix &mat){

	int i;
	Matrix *matOut = new Matrix(mat.row, mat.column);
	matOut->size = mat.size;
	for (i = 0; i < mat.size; i++){
		matOut->mat[i] = this->mat[i] + mat.mat[i];
	}
	return *matOut;
}
Matrix &Matrix::operator +=(const Matrix &mat){

	int i;
	Matrix *matOut = new Matrix(mat.row, mat.column);//�v�Z���ʎ��[�p
	matOut->size = mat.size;
	for (i = 0; i < mat.size; i++){
		this->mat[i] += mat.mat[i];
	}
	return *this;
}

Matrix &Matrix::operator -(const Matrix &mat){

	int i;
	Matrix *matOut = new Matrix(mat.row, mat.column);
	for (i = 0; i < mat.size; i++){
		(*matOut).mat[i] = this->mat[i] -mat.mat[i];
	}
	return *matOut;
}
Matrix &Matrix::operator -=(const Matrix &mat){

	int i;
	Matrix *matOut = new Matrix(mat.row, mat.column);
	for (i = 0; i < mat.size; i++){
		this->mat[i] -= mat.mat[i];
	}
	return *this;
}
Matrix &Matrix::operator *(const Matrix &mat){

	int i, j, k;
	Matrix *matOut = new Matrix(mat.row, mat.column);
	
	double temp;

	for (i = 0; i<(this->row); i++){
		for (j = 0; j<(mat.column); j++){
			temp = 0;
			for (k = 0; k<(this->column); k++){
				temp += this->get(i, k)* mat.mat[getAdres(k, j)];
			}
			matOut->set(temp, i, j);
		}
	}
	return *matOut;
}
Matrix &Matrix::operator *=(const Matrix &mat){

	int i, j, k;
	Matrix *matOut = new Matrix(mat.row, mat.column);

	double temp;
	
	for (i = 0; i<(this->row); i++){
		for (j = 0; j<(mat.column); j++){
			temp = 0;
			for (k = 0; k<(this->column); k++){
				temp += this->get(i, k)* mat.mat[getAdres(k, j)];
			}
			matOut->set(temp, i, j);
		}
	}

	return *this;
}
Matrix &Matrix::operator /(const Matrix &mat){

	int i, j, k;
	double temp;
	Matrix tempM(mat.row, mat.column);
	Matrix *matOut = new Matrix(mat.row, mat.column);
	for (i = 0; i < size; i++){
		tempM.mat[i] = (1/mat.mat[i]);
	}
	for (i = 0; i<(this->row); i++){
		for (j = 0; j<(mat.column); j++){
			temp = 0;
			for (k = 0; k<(this->column); k++){
				temp += this->get(i, k)* tempM.get(k, j);
			}
			matOut->set(temp, i, j);
		}
	}
	return *matOut;
}
Matrix &Matrix::operator /=(const Matrix &mat){

	int i, j, k;
	double temp;
	Matrix tempM(mat.row, mat.column);
	Matrix *matOut = new Matrix(mat.row, mat.column);
	for (i = 0; i < size; i++){
		tempM.mat[i] = (1 / mat.mat[i]);
	}
	for (i = 0; i<(this->row); i++){
		for (j = 0; j<(mat.column); j++){
			temp = 0;
			for (k = 0; k<(this->column); k++){
				temp += this->get(i, k)* tempM.get(k, j);
			}
			matOut->set(temp, i, j);
		}
	}
	return *this;
}