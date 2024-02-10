/* Universidade Federal do Rio de Janeiro
 * Escola Politécnica
 * Departamento de Eletrônica e Computação
 * Prof. Fernando Silva
 * EEL 670 - Linguagem de Programação
 *
 * Authors: Daniel Dahis     (dahisdaniel@poli.ufrj.br)
 *          Leonan França    (leonancfr@poli.ufrj.br)
 *          Gustavo Silva    (diguser@gmail.com)
 *          Michael Douglas  (michaeldouglas@poli.ufrj.br)
 */
#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_ 1

#include <vector>
#ifdef DEBUG
  #include<iostream>
#endif

#define DATA_OUT_OF_RANGE           -1
#define ACCESS_INVALID_LINE         -2
#define ACCESS_INVALID_COLUM        -3
#define ACCESS_INVALID_OUT_OF_RANGE -4
#define INVALID_ORDER               -5
#define INVALID_MATRIX_SIZE         -6

//! Estrutura que possui os dois índices de uma matriz
struct MatrixPosition {
  int i,j;
};

//! Classe que implementa uma matriz usando o std::vector
/**
Note que o acesso dos elementos é da forma:
i = 0 até lines-1
j = 0 até columns-1

Essa classe foi inicialmente criada para manipular apenas números, muito cuidado ao usar com ponteiros
*/
template<typename T>
class Matrix{
  private:
    std::vector<T> matrix;
    unsigned lines,columns;
  public:
    //! Instancia a matriz com 0 linhas e 0 colunas
    Matrix();
    
    //! Instancia a matriz com linhas e colunas definidas
    /**
    \param lines: Número de linhas
    \param columns: Número de colunas
    */
    Matrix(unsigned const lines,unsigned const columns);
    
    //! Instancia a matriz com linhas e colunas definidas e um valor padrão
    /**
    \param lines: Número de linhas
    \param columns: Número de colunas
    \param value: Valor de cada elemento da matriz
    */
    Matrix(unsigned const lines,unsigned const columns,T value);
    
    ~Matrix();
    
    //! Redimensiona a matriz
    /**
    \param lines: Número de linhas
    \param columns: Número de colunas
    */
    void resize(unsigned lines,unsigned columns);
    
    //! Obtém o elemento dados os índices
    /**
    \param i: Acessa o elemento da linha i
    \param j: Acessa o elemento da coluna j
    */
    typename std::vector<T>::reference at(unsigned const i,unsigned const j);
    
    //! Clona uma matriz
    /**
    \param other: Matriz a ser clonada
    */
    Matrix<T>& operator=(Matrix<T>& other);
    
    //! Soma outra matriz à matriz atual
    /**
    \param other: Matriz que será usada na soma
    \return Uma das matrizes com os valores calculados
    */
    Matrix<T>& operator+=(Matrix<T>& other);
    
    //! Multiplica a matriz atual por outra matriz
    /**
    Não usar com ponteiro
    \param other: Matriz que será usada na multiplicação
    \return Uma terceira matriz com os valores calculados
    */
    Matrix<T>& operator*(Matrix<T>& other);
    
    //! Multiplica a matriz atual por um valor
    /**
    Não usar com ponteiro
    \param value: Valor a ser multiplicado
    \return Uma segunda matriz com os valores calculados
    */
    Matrix<T>& operator*(T& value);
    
    //! Subtrai duas matrizes duas matrizes
    /**
    A-B == this - other
    
    Não usar com ponteiro
    \param other: Matriz que será usada na subtração
    \return Uma terceira matriz com os valores calculados
    */
    Matrix<T>& operator-(Matrix<T>& other);
    
    //! Subtrai duas matrizes
    /**
    Não usar com ponteiro
    \param other: Matriz que será usada na soma
    \return Uma terceira matriz com os valores calculados
    */
    Matrix<T>& operator+(Matrix<T>& other);
    
    //! Divide a matriz atual por um valor
    /**
    Não usar com ponteiro
    \param value: Valor a ser dividido
    \return Uma segunda matriz com os valores calculados
    */
    Matrix<T>& operator/(T&);
    
    //! Obtém uma subdivisão da matriz
    /**
    \param start_i: Índice i onde será o elemento (0,0) da nova matriz
    \param start_j: Índice j onde será o elemento (0,0) da nova matriz
    \param final_i: Índice i onde será o elemento (n,m) da nova matriz
    \param final_j: Índice j onde será o elemento (n,m) da nova matriz
    \return Uma nova matriz com dimensão (final_i-start_i)x(final_j-start_j)
    */
    Matrix<T>& subMatrix(unsigned const start_i,unsigned const start_j,unsigned const final_i,unsigned const final_j);
    
    //! Obtém uma subdivisão da matriz
    /**
    Similar a: subMatrix(i,j,n,m);
    Onde n é o número de linhas e m é o número de colunas
    \param start_i: Índice i onde será o elemento (0,0) da nova matriz
    \param start_j: Índice j onde será o elemento (0,0) da nova matriz
    \return Uma nova matriz com dimensão (n-start_i)x(m-start_j)
    */
    Matrix<T>& subMatrix(unsigned const start_i,unsigned const start_j);
    
    //! Obtém um vetor coluna da matriz
    /**
    \param j: Índice da coluna a ser obtida
    \return Uma nova matriz com dimensão (n,1)
    */
    Matrix<T>& getColumn(unsigned const j);
    
    //! Adiciona colunas à matriz
    /**
    \param m: Número de colunas a adicionar
    \return Se a operação ocorreu com sucesso
    */
    bool addColumns(unsigned const m);
    
    //! Adiciona linhas à matriz
    /**
    \param n: Número de linhas a adicionar
    \return Se a operação ocorreu com sucesso
    */
    bool addLines(unsigned const n);
    
    //! Remove uma linha da matriz
    /**
    \param i: Índice da linha a ser removida
    \return Se a operação ocorreu com sucesso
    */
    bool remLine(unsigned const i);
    
    //! Transfere(sem remoção) uma coluna (por completo) de uma matriz à linha da matriz atual
    /**
    \param other: Matriz donde se lerá a coluna
    \param column: Coluna da matriz other a ser transferida
    \param line: Linha de destino
    \param start: Offset da linha de destino
    \return Se a operação ocorreu com sucesso
    */
    bool appendColumnInLine(Matrix<T>& other,unsigned const column,unsigned const line,unsigned const start);
    
    //! Transfere(sem remoção) toda uma matriz para a matriz atual
    /**
    \param other: Matriz donde será obtido os valores
    \param line: Offset da linha de destino
    \param column: Offset da coluna de destino
    \return Se a operação ocorreu com sucesso
    */
    bool appendMatrix(Matrix<T>& other,unsigned const line,unsigned const column);
    
    //! Obtém o número de colunas da matriz
    unsigned getColumns();
    
    //! Obtém o número de linhas da matriz
    unsigned getLines();
    
    #ifdef DEBUG
    void debug();
    #endif
    
    //! Preenche toda a matriz com um valor
    /**
    \param value: Valor a preencher a matriz
    */
    void fill(T value);
    
    //! Obtém o único valor da matriz
    /**
    Essa função só funciona se a matriz for 1x1
    \return O único valor da matriz
    */
    T& toValue();
};

template<typename T>
Matrix<T>::Matrix(){this->lines=0;this->columns=0;}

template<typename T>
Matrix<T>::~Matrix(){}

template<typename T>
Matrix<T>::Matrix(const unsigned l, const unsigned c){
  if(c*l > matrix.max_size()){
    #ifdef DEBUG
      std::cout << "MATRIX ERROR: Unable to initialize matrix with "<<l<<" lines and "<<c<<" columns."<<std::endl<<"Limit is "<<matrix.max_size()<<" cells."<<std::endl;
    #endif
    throw DATA_OUT_OF_RANGE;
  }
  this->lines = l;
  this->columns = c;
  this->matrix.resize(l*c);
}

template<typename T>
Matrix<T>::Matrix(unsigned const l,unsigned const c,T def){
  if(c*l > matrix.max_size()){
    #ifdef DEBUG
      std::cout << "MATRIX ERROR: Unable to initialize matrix with "<<l<<" lines and "<<c<<" columns."<<std::endl<<"Limit is "<<matrix.max_size()<<" cells."<<std::endl;
    #endif
    throw DATA_OUT_OF_RANGE;
  }
  this->lines = l;
  this->columns = c;
  this->matrix.resize(l*c);
  for(unsigned i=0;i<l*c;i++)
    this->matrix.at(i) = def;
}

template<typename T>
void Matrix<T>::resize(unsigned const l, unsigned const c){
  if(c*l > matrix.max_size()){
    #ifdef DEBUG
      std::cout << "MATRIX ERROR: Unable to initialize matrix with "<<l<<" lines and "<<c<<" columns."<<std::endl<<"Limit is "<<matrix.max_size()<<" cells."<<std::endl;
    #endif
    throw DATA_OUT_OF_RANGE;
  }
  this->lines = l;
  this->columns = c;
  this->matrix.resize(l*c);
}

template<typename T>
typename std::vector<T>::reference Matrix<T>::at(unsigned l, unsigned c){
  if(l >= this->lines){
    #ifdef DEBUG
      std::cout<<"MATRIX ERROR: Access line #"<<l<<" but limit is "<<this->lines<<" lines, including line zero"<<std::endl;
    #endif
    throw ACCESS_INVALID_LINE;
  }
  if(c >= this->columns){
    #ifdef DEBUG
      std::cout<<"MATRIX ERROR: Access column #"<<c<<" but limit is "<<this->columns<<" columns, including column zero"<<std::endl;
    #endif
    throw ACCESS_INVALID_COLUM;
  }
  std::size_t pos=c+l*this->columns;
  if(pos >= this->matrix.size()){
    #ifdef DEBUG
      std::cout<<"MATRIX ERROR: Accessing element out of Matrix range: line #"<<l<<" column #"<<c<<std::endl;
    #endif
    throw ACCESS_INVALID_OUT_OF_RANGE;
  }
  return matrix[pos];
}

#ifdef DEBUG
template<typename T>
void Matrix<T>::debug(){
  std::cout<<std::endl<<" === Debugging Matrix ==="<<std::endl;
  if(this->matrix.size() == 0){
    std::cout << "  Matrix is empty"<<std::endl;
    return;
  }
  std::cout<<"{";
  for(std::size_t i=0;i<this->lines;i++){
    std::cout<<"["<<this->at(i,0);
    for(std::size_t j=1;j<this->columns;j++){
      std::cout<<","<<this->at(i,j);
    }
    std::cout<<"]";
    if(i != (this->lines-1))
      std::cout<<"\n";
  }
  std::cout<<"}"<<std::endl;
}
#endif

template<typename T>
bool Matrix<T>::addLines(unsigned const lines){
  if((this->lines+lines)*this->columns >= this->matrix.max_size())
    return false;
  this->lines += lines;
  this->matrix.resize(this->columns*this->lines);
  return true;
}

template<typename T>
bool Matrix<T>::addColumns(unsigned const columns){
  if((this->columns+columns)*this->lines >= this->matrix.max_size())
    return false;
  this->matrix.resize((this->columns+columns)*this->lines);
  unsigned jump = (this->lines-1)*(columns);
  for(unsigned i=(this->columns*this->lines)-1;i>=this->columns;i--){
    this->matrix.at(i+jump) = this->matrix.at(i);
    this->matrix.at(i) = T();
    if(i%this->columns == 0)
      jump -= columns;
  }
  this->columns += columns;
  return true;
}

template<typename T>
bool Matrix<T>::remLine(unsigned const line){
  if(line >= this->lines)
    return false;
  for(std::size_t i = line*this->columns; i<(this->matrix.size()-this->columns);i++){
    this->matrix[i] = this->matrix[i+this->columns];
  }
  this->lines--;
  this->matrix.resize(this->lines*this->columns);
  return true;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>& mx){
  this->resize(mx.lines,mx.columns);
  for(std::size_t i =0;i<mx.matrix.size();i++){
    this->matrix[i] = mx.matrix[i];
  }
  return *this;
}

template<typename T>
bool Matrix<T>::appendColumnInLine(Matrix<T>& mx,unsigned const column,unsigned const line,unsigned const start){
  if(this->columns < start+mx.lines)
    return false;
  for(unsigned i=0;i<mx.lines;i++){
    *(this->at(line,start+i)) = *(mx.at(i,column));
  }
  return true;
}

template<typename T>
Matrix<T>& Matrix<T>::operator+=(Matrix<T>& mx){
  if((mx.lines != this->lines)||(mx.columns != this->columns))
    throw INVALID_MATRIX_SIZE;
  for(std::size_t i=0;i<this->matrix.size();i++){
    this->matrix[i] += mx.matrix[i];
  }
  return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::subMatrix(unsigned const sl,unsigned const sc,unsigned const el,unsigned const ec){
  if((sl >= this->lines)||(el > this->lines)||(sc >= this->columns)||(ec > this->columns)){
    #ifdef DEBUG
      std::cout<<"MATRIX ERROR: Accessing element out of matrix range."<<std::endl;
    #endif
    throw ACCESS_INVALID_OUT_OF_RANGE;
  }
  if((el <= sl)||(ec <= sc)){
    #ifdef DEBUG
      std::cout<<"MATRIX ERROR: Order to split matrix is invalid."<<std::endl;
    #endif
    throw INVALID_ORDER;
  }
  Matrix<T> *tmp;
  tmp = new Matrix<T>(el-sl,ec-sc);
  for(unsigned i=sl;i<el;i++){
    for(unsigned j=sc;j<ec;j++){
      tmp->at(i-sl,j-sc) = this->at(i,j);
    }
  }
  return *tmp;
}

template<typename T>
Matrix<T>& Matrix<T>::subMatrix(unsigned const sl,unsigned const sc){
  return this->subMatrix(sl,sc,this->lines,this->columns);
}

template<typename T>
Matrix<T>& Matrix<T>::getColumn(unsigned const column){
  if(column >= this->columns)
    throw ACCESS_INVALID_OUT_OF_RANGE;
  Matrix<T> *tmp;
  tmp = new Matrix<T>(this->lines,1);
  for(unsigned i=0;i<this->lines;i++)
    tmp->at(i,0) = this->at(i,column);
  return *tmp;
}

template<typename T>
bool Matrix<T>::appendMatrix(Matrix<T>& mx,unsigned const line,unsigned const column){
  if((mx.lines+line > this->lines)||(mx.columns+column > this->columns))
    return false;
  for(unsigned i=0;i<mx.lines;i++){
    for(unsigned j=0;j<mx.columns;j++)
      this->at(line+i,column+j) = mx.at(i,j);
  }
  return true;
}

template<typename T>
Matrix<T>& Matrix<T>::operator*(Matrix<T>& mx){
  if(this->columns != mx.lines){
    #ifdef DEBUG
      std::cout<<"MATRIX ERROR: Multiply matrix A[mxn] and B[cxd] where n = "<<this->columns<<" and c = "<<mx.lines<<std::endl;
    #endif
    throw INVALID_MATRIX_SIZE;
  }
  Matrix<T> *tmp;
  tmp = new Matrix<T>(this->lines,mx.columns);
  for(unsigned i=0;i<this->lines;i++){
    for(unsigned j=0;j<mx.columns;j++){
      for(unsigned k=0;k<this->columns;k++){
        tmp->at(i,j) += (this->at(i,k))*(mx.at(k,j));
      }
    }
  }
  return *tmp;
}

template<typename T>
Matrix<T>& Matrix<T>::operator*(T& val){
  Matrix<T> *tmp;
  tmp = new Matrix<T>();
  *tmp = *this;
  for(unsigned i=0;i<tmp->lines;i++){
    for(unsigned j=0;j<tmp->columns;j++){
      tmp->at(i,j) *= val;
    }
  }
  return *tmp;
}

template<typename T>
Matrix<T>& Matrix<T>::operator-(Matrix<T>& mx){
  if((this->lines != mx.lines)||(this->columns!=mx.columns)){
    #ifdef DEBUG
      std::cout<<"MATRIX ERROR: Subtraction only occur with matrix with same dimensions."<<std::endl;
    #endif
    throw INVALID_MATRIX_SIZE;
  }
  Matrix<T> *tmp;
  tmp = new Matrix<T>(mx.lines,mx.columns);
  for(unsigned i=0;i<mx.lines;i++){
    for(unsigned j=0;j<mx.columns;j++){
      tmp->at(i,j) = this->at(i,j) - mx.at(i,j);
    }
  }
  return *tmp;
}

template<typename T>
Matrix<T>& Matrix<T>::operator+(Matrix<T>& mx){
  if((this->lines != mx.lines)||(this->columns!=mx.columns)){
    #ifdef DEBUG
      std::cout<<"MATRIX ERROR: Subtraction only occur with matrix with same dimensions."<<std::endl;
    #endif
    throw INVALID_MATRIX_SIZE;
  }
  Matrix<T> *tmp;
  tmp = new Matrix<T>(mx.lines,mx.columns);
  for(unsigned i=0;i<mx.lines;i++){
    for(unsigned j=0;j<mx.columns;j++){
      tmp->at(i,j) = this->at(i,j) + mx.at(i,j);
    }
  }
  return *tmp;
}

template<typename T>
Matrix<T>& Matrix<T>::operator/(T& val){
  Matrix<T> *tmp;
  tmp = new Matrix<T>(this->lines,this->columns);
  for(unsigned i=0;i<this->lines;i++){
    for(unsigned j=0;j<this->columns;j++){
      tmp->at(i,j) = this->at(i,j) /val;
    }
  }
  return *tmp;
}

template<typename T>
T& Matrix<T>::toValue(){
  if((this->lines != 1)||(this->columns != 1)){
    #ifdef DEBUG
      std::cout<<"MATRIX ERROR: Unable to convert to value the matrix with more than 1 line or 1 column."<<std::endl;
    #endif
    this->debug();
    throw INVALID_MATRIX_SIZE;
  }
  return this->matrix.at(0,0);
}

template<typename T>
void Matrix<T>::fill(T v){
  for(unsigned j=0;j<this->columns;j++){
    for(unsigned i=0;i<this->lines;i++){
      this->at(i,j) = v;
    }
  }
}
template<typename T>
unsigned Matrix<T>::getColumns(){
  return columns;
}

template<typename T>
unsigned Matrix<T>::getLines(){
  return lines;
}
#endif
