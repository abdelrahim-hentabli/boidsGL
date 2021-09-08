#ifndef VEC_H
#define VEC_H

#include <iostream>
#include <stdarg.h>
#include <assert.h>
#include <math.h>

const double FLT_EPS = 1e-5;

bool double_equality(const double& lhs, const double& rhs){
    return std::abs(lhs - rhs)<=FLT_EPS;
}

template<class T, int n> struct vec;
template<class T, int n> T dot(const vec<T,n>& v, const vec<T,n>& u);

template<class T, int n>
struct vec
{
  T x[n];

  vec(){
    fill(0);
  }
 
  vec(T a){
    assert(n == 1); x[0] = a;
  }
  
  vec(T a, T b){
    assert(n == 2); x[0] = a; x[1] = b;
  }

  vec(T a, T b, T c){
    assert(n == 3); x[0] = a; x[1] = b; x[2] = c;
  }

  void fill(T value){
    for(int i = 0; i < n; i++){x[i] = value;}
  }
  
  friend std::ostream& operator<<(std::ostream& out, const vec& v){
    out<<'<';
    for(int i = 0; i < n-1; i++){out<<v.x[i]<<", ";}
    if(n>0) {out<<v.x[n-1]<<'>';}
    return out;
  }

  T& operator [](const uint& index){
    assert(n>index); return x[index];
  }

  bool operator ==(const vec<T,n>& rhs) const{
    for(int i = 0; i < n; i++){if(std::abs(x[i] - rhs.x[i])>FLT_EPS) return false;}
    return true;
  }

  bool operator !=(const vec<T,n>& rhs) const{
    for(int i = 0; i < n; i++){if(std::abs(x[i] - rhs.x[i])>FLT_EPS) return true;}
    return false;
  }

  vec<T, n> operator +(const vec<T,n>& rhs){
    vec<T, n> output;
    for(int i = 0; i < n; i++){output.x[i] = x[i] + rhs.x[i];}
    return output;
  }
  
  vec<T, n> operator -(const vec<T,n>& rhs){
    vec<T, n> output;
    for(int i = 0; i < n; i++){output.x[i] = x[i] - rhs.x[i];}
    return output;
  }

  vec<T, n> operator *(const T& rhs){
    vec<T, n> output;
    for(int i = 0; i < n; i++){output.x[i] = x[i] * rhs;}
    return output;
  }

  friend vec<T, n> operator *(const T& lhs, const vec<T,n>& rhs){
    vec<T, n> output;
    for(int i = 0; i < n; i++){output.x[i] = lhs * rhs.x[i];}
    return output;
  }

  vec<T, n> operator /(const T& rhs){
    vec<T, n> output;
    for(int i = 0; i < n; i++){output.x[i] = x[i] / rhs;}
    return output;
  }

  friend vec<T, n> operator /(const T& lhs, const vec<T,n>& rhs){
    vec<T, n> output;
    for(int i = 0; i < n; i++){output.x[i] = lhs / rhs.x[i];}
    return output;
  }
  

  vec<T, 3> operator *(const vec<T,3>& rhs){
    vec<T,3> output;
    output.x[0] = x[1] * rhs.x[2] - (x[2] * rhs.x[1]);
    output.x[1] = x[2] * rhs.x[0] - (x[0] * rhs.x[2]);
    output.x[2] = x[0] * rhs.x[1] - (x[1] * rhs.x[0]);
    return output;
  }

  vec<T, 3> operator *(const vec<T,2>& rhs){
    assert (n == 2);
    vec<T,3> output;
    output.x[0] = 0;
    output.x[1] = 0;
    output.x[2] = x[0] * rhs.x[1] - (x[1] * rhs.x[0]);
    return output;
  }
  
  vec<T, n> operator +=(const vec<T,n>& rhs){
    for(int i = 0; i < n; i++){x[i] = x[i] + rhs.x[i];}
    return *this;
  }

  vec<T, n> operator -=(const vec<T,n>& rhs){
    for(int i = 0; i < n; i++){x[i] = x[i] - rhs.x[i];}
    return *this;
  }

  vec<T,n> operator /=(const T& rhs){
    for(int i = 0; i < n; i++){x[i] /= rhs;}
    return *this;
  }

  vec<T,n> operator *=(const T& rhs){
    for(int i = 0; i < n; i++){x[i] *= rhs;}
    return *this;
  }

  double magnitude(){
    double sum = 0;
    for(int i = 0; i < n; i++){
      sum += x[i] * x[i];
    }
    return sqrt(sum);
  }

  vec<T,n> normalize(){
    double mag = magnitude();
    for(int i = 0; i < n; i++){x[i] /= mag;}
    return *this;
  }

  
};

template<class T, int n> T dot(const vec<T,n>& v, const vec<T,n>& u){
  T sum = 0;
  for(int i = 0; i < n; i++){
    sum += v.x[i] * u.x[i];
  }
  return sum;
}

typedef vec<double, 2> vec2;
typedef vec<double, 3> vec3;
typedef vec<double, 4> vec4;

typedef vec<int, 2> ivec2;
typedef vec<int, 3> ivec3;
typedef vec<int, 4> ivec4;

#endif //VEC
