/*--------------------------------------------------------------------------
@COPYRIGHT  :
              Copyright 1996, Alex P. Zijdenbos, 
              McConnell Brain Imaging Centre,
              Montreal Neurological Institute, McGill University.
              Permission to use, copy, modify, and distribute this
              software and its documentation for any purpose and without
              fee is hereby granted, provided that the above copyright
              notice appear in all copies.  The author and McGill University
              make no representations about the suitability of this
              software for any purpose.  It is provided "as is" without
              express or implied warranty.
---------------------------------------------------------------------------- 
$RCSfile: fcomplex.cc,v $
$Revision: 1.2 $
$Author: jason $
$Date: 2002-03-20 21:42:46 $
$State: Exp $
--------------------------------------------------------------------------*/
#include "fcomplex.h"

// A few functions that define (bogus) math ops for complex

static int _errorCount_fcomplex = 100;

int operator < (const fcomplex&, const fcomplex&) {
  if (_errorCount_fcomplex) {
    cerr << "Comparison of fcomplex numbers undefined" << endl;
    _errorCount_fcomplex--;
  }
  return 0;
}

int operator <= (const fcomplex&, const fcomplex&) {
  if (_errorCount_fcomplex) {
    cerr << "Comparison of fcomplex numbers undefined" << endl;
    _errorCount_fcomplex--;
  }
  return 0;
}

int operator > (const fcomplex&, const fcomplex&) {
  if (_errorCount_fcomplex) {
    cerr << "Comparison of fcomplex numbers undefined" << endl;
    _errorCount_fcomplex--;
  }
  return 0;
}

int operator >= (const fcomplex&, const fcomplex&) {
  if (_errorCount_fcomplex) {
    cerr << "Comparison of fcomplex numbers undefined" << endl;
    _errorCount_fcomplex--;
  }
  return 0;
}


ostream& 
operator << (ostream& os, fcomplex value) {
  os << "( " << real(value) << ", " << imag(value) << ")";
  return os;
}

istream& 
operator >> (istream& is, fcomplex&) {
  cerr << "operator >> not implemented for fcomplex" << endl;
  return is;
}

//end of fcomplex;

