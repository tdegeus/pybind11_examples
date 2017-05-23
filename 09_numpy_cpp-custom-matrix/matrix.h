
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cstdlib>
#include <vector>

template <class T>
class Matrix
{

  private:

    std::vector<T>      _data;     // data array
    std::vector<size_t> _shape;    // number of entries in each dimensions
    std::vector<size_t> _strides;  // stride length for each index

  public:

    // default constructor
    // -------------------

    Matrix<T>(){};

    // constructor
    // -----------

    Matrix<T>( std::vector<size_t> shape, const T *data=NULL )
    {
      if ( shape.size()<1 || shape.size()>3 )
        throw std::runtime_error("Input should be 1-D, 2-D, or 3-D");

      // store '_strides' and '_shape' always in 3-D,
      // use unit-length for "extra" dimensions (> 'shape.size()')
      while ( _shape  .size()<3 ) { _shape  .push_back(1); }
      while ( _strides.size()<3 ) { _strides.push_back(1); }

      for ( int i=0 ; i<shape.size() ; i++ )
        _shape[i] = shape[i];

      _strides[0] = _shape[2]*_shape[1];
      _strides[1] = _shape[2];
      _strides[2] = 1;

      int size = _shape[0]*_shape[1]*_shape[2];

      for ( int i=0 ; i<_data.size() ; i++ )
        _data[i] = (T)0;

      while ( _data.size()<size )
        _data.push_back((T)0);

      if ( data!=NULL )
        for ( int i=0 ; i<size ; i++ )
          _data[i] = data[i];
    };

    // copy constructor
    // ----------------

    Matrix               (const Matrix<T> &) = default;
    Matrix<T>& operator= (const Matrix<T> &) = default;

    // index operators
    // ---------------

    T& operator[] ( size_t i )
    { return _data[i]; };

    T& operator() ( size_t h, size_t i=0, size_t j=0 )
    { return _data[h*_strides[0]+i*_strides[1]+j*_strides[2]]; };

    // iterators
    // ---------

    auto begin()
    { return _data.begin(); }

    auto end ()
    { return _data.end  (); }

    // return pointer to data
    // ----------------------

    const T* data ( void ) const
    { return _data.data(); };

    // return shape array [ndim]
    // -------------------------

    std::vector<size_t> shape ( int ndim=0 ) const
    {
      if ( ndim==0 )
        ndim = this->ndim();

      std::vector<size_t> ret(ndim);

      for ( int i=0 ; i<ndim ; i++ )
        ret[i] = _shape[i];

      return ret;
    };

    // return strides array [ndim]
    // ---------------------------

    std::vector<size_t> strides ( bool bytes=false ) const
    {
      int ndim = this->ndim();
      std::vector<size_t> ret(ndim);

      for ( int i=0 ; i<ndim ; i++ )
        ret[i] = _strides[i];

      if ( bytes )
        for ( int i=0 ; i<ndim ; i++ )
          ret[i] *= sizeof(T);

      return ret;
    };

    // return size
    // -----------

    size_t size ( void ) const
    { return _data.size(); };

    // return number of dimensions
    // ---------------------------

    size_t ndim ( void ) const
    {
      size_t i;

      for ( i=2 ; i>0 ; i-- )
        if ( _shape[i]!=1 )
          break;

      return i+1;
    };

}; // class Matrix

#endif
