#ifndef MAT_MATRIX_H
#define MAT_MATRIX_H

namespace mat {
  enum class MatrixOrdering {
    RowMajor,
    ColMajor,
  };

  template<typename Type, int RowCount, int ColCount, MatrixOrdering order = MatrixOrdering::RowMajor>
  class Matrix {
  public:
    // Rows count
    static constexpr int Rows = RowCount;

    // Columns count
    static constexpr int Cols = ColCount;

    // Elements count
    static constexpr int Size = RowCount * ColCount;

    // Matrix order
    static constexpr MatrixOrdering Order = order;

    constexpr static int chooseRow() {
          if constexpr (order == MatrixOrdering::RowMajor) {
              return RowCount;
          } else {
              return ColCount;
          }
      }

      constexpr static int chooseCol() {
          if constexpr (order == MatrixOrdering::RowMajor) {
              return ColCount;
          } else {
              return RowCount;
          }
      }

      std::array<std::array<Type, ColCount>, RowCount> Elements;

    // Default constructor
    constexpr Matrix() : Elements{} {
      if (Order == MatrixOrdering::RowMajor) {
        for (int i = 0; i < Rows; i++) {
          for (int j = 0; j < Cols; j++) {
            Elements[i][j] = 0;
          }
        }
      } else {
        for (int i = 0; i < Rows; i++) {
          for (int j = 0; j < Cols; j++) {
            Elements[j][i] = 0;
          }
        }
      }
    }

    // Initialisation constructor
    template<int DataLength>
    constexpr explicit Matrix(const Type(&data)[DataLength]): Elements{} {
      int index = 0;
      if (Order == MatrixOrdering::RowMajor) {
        for (int i = 0; i < Rows; i++) {
          for (int j = 0; j < Cols; j++) {
            Elements[i][j] = data[index++];
          }
        }
      } else {
          for(int i = 0; i < Cols; i++) {
              for(int j = 0; j < Rows; j++) {
                  Elements[j][i] = data[index++];
              }
          }
      }
    }

     // Conversion constructor
     template<MatrixOrdering otherOrder>
     constexpr explicit Matrix(const Matrix<Type, Rows, Cols, otherOrder>& other): Elements{} {
         if (order != otherOrder) {
             auto it = other.begin();
             if(order == MatrixOrdering::RowMajor) {
                 for(int i = 0; i < Rows; i++) {
                     for(int j = 0; j < Cols; j++) {
                         Elements[i][j] = *it++;
                     }
                 }
             } else {
                 for(int i = 0; i < Cols; i++) {
                     for(int j = 0; j < Rows; j++) {
                         Elements[j][i] = *it++;
                     }
                 }
             }
         } else {
             for (int i = 0; i < Rows; i++) {
                 for (int j = 0; j < Cols; j++) {
                     Elements[i][j] = other.Elements[i][j];
                 }
             }
         }
     }

    // Affectation from a matrix with different ordering
    template<MatrixOrdering otherOrder>
    constexpr auto& operator=(const Matrix<Type, Rows, Cols, otherOrder>& other) {
      if (order != otherOrder) {
          auto it = other.begin();
          if(order == MatrixOrdering::RowMajor) {
              for(int i = 0; i < Rows; i++) {
                  for(int j = 0; j < Cols; j++) {
                      Elements[i][j] = *it++;
                  }
              }
          } else {
              for(int i = 0; i < Cols; i++) {
                  for(int j = 0; j < Rows; j++) {
                      Elements[j][i] = *it++;
                  }
              }
          }
      } else {
        for (int i = 0; i < Rows; i++) {
          for (int j = 0; j < Cols; j++) {
            Elements[i][j] = other.Elements[i][j];
          }
        }
      }
      return *this;
    }

     // Retrun the transposed matrix
     constexpr Matrix<Type, Rows, Cols, Order> transpose() {
         Matrix<Type, Cols, Rows, Order> result;
         if (Order == MatrixOrdering::RowMajor) {
             for (int i = 0; i < Rows; i++) {
                 for (int j = 0; j < Cols; j++) {
                     result.Elements[i][j] = Elements[j][i];
                 }
             }
         } else {
             for (int i = 0; i < Rows; i++) {
                 for (int j = 0; j < Cols; j++) {
                     result.Elements[j][i] = Elements[i][j];

                 }
             }
         }

         return result;
     }

     constexpr void print() {
         for (int i = 0; i < Rows; i++) {
             for (int j = 0; j < Cols; j++) {
                 std::cout << Elements[i][j] << " ";
             }
             std::cout << std::endl;
         }
     }


    // Get the value at specified row and col
    constexpr const Type& operator() (int row, int col) const {
        return Elements[row][col];
    }

    constexpr Type& operator() (int row, int col) {
      if(Order == MatrixOrdering::RowMajor) {
        return Elements[row][col];
      } else {
        return Elements[col][row];
      }
    }

     // Addition - in place
     template<typename OtherType, MatrixOrdering otherOrder>
     auto& operator+=(const Matrix<OtherType, Rows, Cols, otherOrder>& other) {
         *this = *this+other;
         return *this;
     }

     // Addition - classic
     template<typename OtherType, MatrixOrdering otherOrder>
     constexpr Matrix<std::common_type_t<Type, OtherType>, Rows, Cols, Order> operator+(const Matrix<OtherType, Rows, Cols, otherOrder>& other) const {

       Matrix<std::common_type_t<Type, OtherType>, Rows, Cols, Order> result;

         for (int i = 0; i < Rows; i++) {
             for (int j = 0; j < Cols; j++) {
                 result(i, j) = Elements[i][j] + other(i, j);
             }
         }
       return result;
     }

     // Substration - in place
     template<typename OtherType, MatrixOrdering otherOrder>
     auto& operator-=(const Matrix<OtherType, Rows, Cols, otherOrder>& other) {
        *this = *this-other;
        return *this;
     }

     // Substraction - classic
     template<typename OtherType, MatrixOrdering otherOrder>
     constexpr Matrix<std::common_type_t<Type, OtherType>, Rows, Cols, Order> operator-(const Matrix<OtherType, Rows, Cols, otherOrder>& other) const {
        Matrix<std::common_type_t<Type, OtherType>, Rows, Cols, Order> result;
         for (int i = 0; i < Rows; i++) {
             for (int j = 0; j < Cols; j++) {
                 result(i, j) = Elements[i][j] - other(i, j);
             }
         }
       return result;
     }

     // Product - in place
     template<typename OtherType, MatrixOrdering otherOrder>
     constexpr auto& operator*=(const Matrix<OtherType, Rows, Cols, otherOrder>& other) {
        *this = *this * other;
        return *this;
     }

     // Product - classic
     template<typename OtherType, int OtherCols, MatrixOrdering otherOrder>
     constexpr Matrix<std::common_type_t<Type, OtherType>, Rows, OtherCols, Order> operator*(const Matrix<OtherType, Cols, OtherCols, otherOrder>& other) const {

        if(order == MatrixOrdering::RowMajor) {
          Matrix<std::common_type_t<Type, OtherType>, Rows, other.Cols> result;

          for(int i = 0; i < Rows; i++) {
            for(int j = 0; j < OtherCols; j++) {
              Type sum = 0;
              for(int k = 0; k < other.Rows; k++) {
                sum += Elements[i][k] * other(k, j);
              }
              result(i, j) = sum;
            }
          }
          return result;
        }

     }

     // Equality
     template<typename OtherType, int OtherRows, int OtherCols, MatrixOrdering otherOrder>
     constexpr bool operator==(const Matrix<OtherType, OtherRows, OtherCols, otherOrder>& other) const {
       if (Rows != OtherRows || Cols != OtherCols) {
         return false;
       }
       std::cout << Rows << " " << Cols << std::endl;
       for (int i = 0; i < Rows; i++) {
         for (int j = 0; j < Cols; j++) {
             std::cout << Elements[i][j] << " " << other(i, j) << std::endl;
           if (Elements[i][j] != other(i, j)) {
             return false;
           }
         }
       }
       return true;
     }

    // // Difference
     template<typename OtherType, int OtherRows, int OtherCols, MatrixOrdering otherOrder>
     constexpr bool operator!=(const Matrix<OtherType, OtherRows, OtherCols, otherOrder>& other) const {
       return !(*this == other);
     }

  public:
    /**
     * Define here the iterator classe
     * iterator must be allow to modify the values
     * const_iterator must be point to constant value
     */
    struct iterator
    {
      using value_type = Type;

      using difference_type = std::ptrdiff_t;

      using pointer = Type*;

      using reference = Type&;

      using iterator_category = std::random_access_iterator_tag;

      using type = Matrix<Type, RowCount, ColCount, order>;

      constexpr iterator(Matrix<Type, RowCount, ColCount, order>& matrix, int row, int col) : m_matrix(matrix), m_row(row), m_col(col) {}

      constexpr iterator(const iterator& other) : m_matrix(other.m_matrix), m_row(other.m_row), m_col(other.m_col) {}

      constexpr iterator& operator=(const iterator& other) {
        m_matrix = other.m_matrix;
        m_row = other.m_row;
        m_col = other.m_col;
        return *this;
      }

      constexpr iterator& operator++() {
        if (Order == MatrixOrdering::RowMajor) {
          if (m_col < Cols - 1) {
            ++m_col;
          } else {
            m_col = 0;
            ++m_row;
          }
        } else {
          if (m_row < Rows - 1) {
            ++m_row;
          } else {
            m_row = 0;
            ++m_col;
          }
        }
        return *this;
      }

      constexpr iterator operator++(int) {
        iterator tmp(*this);
        ++(*this);
        return tmp;
      }

      constexpr iterator& operator--() {
        if (Order == MatrixOrdering::RowMajor) {
          if (m_col > 0) {
            --m_col;
          } else {
            m_col = Cols - 1;
            --m_row;
          }
        } else {
          if (m_row > 0) {
            --m_row;
          } else {
            m_row = Rows - 1;
            --m_col;
          }
        }
        return *this;
      }

      constexpr iterator operator--(int) {
        iterator tmp(*this);
        --(*this);
        return tmp;
      }

      constexpr iterator& operator+=(difference_type n) {
        if (Order == MatrixOrdering::RowMajor) {
          m_col += n;
          if (m_col >= Cols) {
            m_col -= Cols;
            ++m_row;
          }
        } else {
          m_row += n;
          if (m_row >= Rows) {
            m_row -= Rows;
            ++m_col;
          }
        }
        return *this;
      }

      constexpr iterator operator+(difference_type n) const {
        iterator tmp(*this);
        tmp += n;
        return tmp;
      }

      constexpr iterator& operator-=(difference_type n) {
        if (Order == MatrixOrdering::RowMajor) {
          m_col -= n;
          if (m_col < 0) {
            m_col += Cols;
            --m_row;
          }
        } else {
          m_row -= n;
          if (m_row < 0) {
            m_row += Rows;
            --m_col;
          }
        }
        return *this;
      }

      constexpr iterator operator-(difference_type n) const {
        iterator tmp(*this);
        tmp -= n;
        return tmp;
      }

      constexpr difference_type operator-(const iterator& other) const {
        if (Order == MatrixOrdering::RowMajor) {
          return m_col - other.m_col + (m_row - other.m_row) * Cols;
        } else {
          return m_row - other.m_row + (m_col - other.m_col) * Rows;
        }
      }

      constexpr reference operator*() const {
        return m_matrix(m_row, m_col);
      }

      constexpr pointer operator->() const {
        return &m_matrix(m_row, m_col);
      }

      constexpr bool operator==(const iterator& other) const {
        return m_matrix == other.m_matrix && m_row == other.m_row && m_col == other.m_col;
      }

      constexpr bool operator!=(const iterator& other) const {
        return !(*this == other);
      }

      constexpr bool operator<(const iterator& other) const {
        if (Order == MatrixOrdering::RowMajor) {
          return m_row < other.m_row || (m_row == other.m_row && m_col < other.m_col);
        } else {
          return m_col < other.m_col || (m_col == other.m_col && m_row < other.m_row);
        }
      }

      constexpr bool operator>(const iterator& other) const {
        return other < *this;
      }

      constexpr bool operator<=(const iterator& other) const {
        return !(other < *this);
      }

      constexpr bool operator>=(const iterator& other) const {
        return !(*this < other);
      }

      constexpr reference operator[](difference_type n) const {
        return *(*this + n);
      }

      ~iterator() {
//        m_matrix = nullptr;
      }

      Matrix<Type, RowCount, ColCount, order>& m_matrix;

      int m_row;

      int m_col;

      friend class Matrix;
    };


    constexpr iterator begin() {
      return iterator(*this, 0, 0);
    }

    constexpr iterator end() {
      return iterator(*this, Rows, 0);
    }

    struct const_iterator {
        using value_type = const Type;

        using difference_type = std::ptrdiff_t;

        using pointer = const Type*;

        using reference = const Type&;

        using iterator_category = std::random_access_iterator_tag;

        using type = const Matrix<Type, RowCount, ColCount, order>;

        constexpr const_iterator(type& matrix, int row, int col) : m_matrix(matrix), m_row(row), m_col(col) {}

        constexpr const_iterator(const const_iterator& other) : m_matrix(other.m_matrix), m_row(other.m_row), m_col(other.m_col) {}

        constexpr const_iterator& operator=(const const_iterator& other) {
          m_matrix = other.m_matrix;
          m_row = other.m_row;
          m_col = other.m_col;
          return *this;
        }

        constexpr const_iterator& operator++() {
          if (Order == MatrixOrdering::RowMajor) {
            ++m_col;
            if (m_col >= Cols) {
              m_col -= Cols;
              ++m_row;
            }
          } else {
            ++m_row;
            if (m_row >= Rows) {
              m_row -= Rows;
              ++m_col;
            }
          }
          return *this;
        }

        constexpr const_iterator operator++(int) {
          const_iterator tmp(*this);
          ++*this;
          return tmp;
        }

        constexpr const_iterator& operator--() {
          if (Order == MatrixOrdering::RowMajor) {
            --m_col;
            if (m_col < 0) {
              m_col += Cols;
              --m_row;
            }
          } else {
            --m_row;
            if (m_row < 0) {
              m_row += Rows;
              --m_col;
            }
          }
          return *this;
        }

        constexpr const_iterator operator--(int) {
          const_iterator tmp(*this);
          --*this;
          return tmp;
        }

        constexpr const_iterator& operator+=(difference_type n) {
          if (Order == MatrixOrdering::RowMajor) {
            m_col += n;
            if (m_col >= Cols) {
              m_col -= Cols;
              m_row += m_col / Cols;
              m_col %= Cols;
            }
          } else {
            m_row += n;
            if (m_row >= Rows) {
              m_row -= Rows;
              m_col += m_row / Rows;
              m_row %= Rows;
            }
          }
          return *this;
        }

        constexpr const_iterator operator+(difference_type n) const {
          const_iterator tmp(*this);
          tmp += n;
          return tmp;
        }

        constexpr const_iterator& operator-=(difference_type n) {
          return *this += -n;
        }

        constexpr const_iterator operator-(difference_type n) const {
          const_iterator tmp(*this);
          tmp -= n;
          return tmp;
        }

        constexpr difference_type operator-(const const_iterator& other) const {
          if (Order == MatrixOrdering::RowMajor) {
            return (m_row - other.m_row) * Cols + (m_col - other.m_col);
          } else {
            return (m_col - other.m_col) * Rows + (m_row - other.m_row);
          }
        }

        constexpr reference operator*() const {
          return m_matrix(m_row, m_col);
        }

        constexpr pointer operator->() const {
          return &m_matrix(m_row, m_col);
        }

        constexpr bool operator==(const const_iterator& other) const {
          return m_row == other.m_row && m_col == other.m_col;
        }

        constexpr bool operator!=(const const_iterator& other) const {
          return !(*this == other);
        }

        constexpr bool operator<(const const_iterator& other) const {
          if (Order == MatrixOrdering::RowMajor) {
            return m_row < other.m_row || (m_row == other.m_row && m_col < other.m_col);
          } else {
            return m_col < other.m_col || (m_col == other.m_col && m_row < other.m_row);
          }
        }

        constexpr bool operator>(const const_iterator& other) const {
          return other < *this;
        }

        constexpr bool operator<=(const const_iterator& other) const {
          return !(other < *this);
        }

        constexpr bool operator>=(const const_iterator& other) const {
          return !(*this < other);
        }

        constexpr reference operator[](difference_type n) const {
          return *(*this + n);
        }

        const type& m_matrix;

        int m_row;

        int m_col;

        friend class Matrix;


    };

     constexpr const_iterator begin() const {
       return const_iterator(*this, 0, 0);
     }

     constexpr const_iterator end() const {
       return const_iterator(*this, Rows, 0);
     }
  };


   /**
    * Define here the VecR and VecC classes
    */

    template<typename Type, int Cols>
    using VecR = Matrix<Type, 1, Cols>;

    template<typename Type, int Rows>
    using VecC = Matrix<Type, Rows, 1>;




   template<typename Type, int Cols>
   constexpr VecR<Type, Cols> vecRow(const Type(&data)[Cols]) {
     return VecR<Type, Cols>(data);
   }

   template<typename Type, int Rows>
   constexpr VecC<Type, Rows> vecCol(const Type(&data)[Rows]) {
     return VecC<Type, Rows>(data);
   }

   // Convert the matrix to the opposite ordering
   template<typename Type, int Rows, int Cols, MatrixOrdering Order>
   constexpr auto convert(const Matrix<Type, Rows, Cols, Order>& mat) {
     if(Order == MatrixOrdering::RowMajor) {
       return Matrix<Type, Cols, Rows, MatrixOrdering::ColMajor>(mat);
     } else {
       return Matrix<Type, Rows, Cols, MatrixOrdering::RowMajor>(mat);
     }
   }

  // Retrun the identity matrix
  template<typename Type, int Size>
  constexpr Matrix<Type, Size, Size> identity() {
    Matrix<Type, Size, Size> mat;
    for (int i = 0; i < Size; ++i) {
      mat(i, i) = 1;
    }
    return mat;
  }
}

#endif // MAT_MATRIX_H
