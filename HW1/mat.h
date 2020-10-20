#ifndef __mat__
#define __mat__

#include <cmath>
#include <iostream>
#include "vec.h"

template<class T, int m, int n> struct mat;
template<class T, int m, int n> T dot(const mat<T,m,n>& u,const mat<T,m,n>& v);

template<class T, int m, int n>
struct mat
{
    T x[m][n];

    mat()
    {make_zero();}

    void make_zero()
    {for(int i = 0; i < m; i++) for(int j = 0; j < n; j++) x[i][j] = 0;}

    void make_id()
    {assert(m==n);make_zero();for(int i = 0; i < m; i++) x[i][i] = 1;}

    static mat id()
    {
        mat r;
        r.make_id();
        return r;
    }
    
    mat& operator += (const mat& v)
    {for(int i = 0; i < m; i++) for(int j = 0; j < n; j++) x[i][j] += v.x[i][j]; return *this;}

    mat& operator -= (const mat& v)
    {for(int i = 0; i < m; i++) for(int j = 0; j < n; j++) x[i][j] -= v.x[i][j]; return *this;}

    // *this += c*id();
    mat& operator += (const T& c)
    {assert(m==n);for(int i = 0; i < m; i++) x[i][i] += c; return *this;}

    // *this -= c*id();
    mat& operator -= (const T& c)
    {assert(m==n);for(int i = 0; i < m; i++) x[i][i] -= c; return *this;}

    mat& operator *= (const T& c)
    {for(int i = 0; i < m; i++) for(int j = 0; j < n; j++) x[i][j] *= c; return *this;}

    mat& operator /= (const T& c)
    {for(int i = 0; i < m; i++) for(int j = 0; j < n; j++) x[i][j] /= c; return *this;}

    mat operator + () const
    {return *this;}

    mat operator - () const
    {mat r; for(int i = 0; i < m; i++) for(int j = 0; j < n; j++) r[i] = -x[i][j]; return r;}

    mat operator + (const mat& v) const
    {return mat(*this)+=v;}

    mat operator - (const mat& v) const
    {return mat(*this)-=v;}

    mat operator * (const T& c) const
    {return mat(*this)*=c;}

    mat operator / (const T& c) const
    {return mat(*this)/=c;}

    // *this + c*id();
    mat operator + (const T& c) const
    {return mat(*this)+=c;}

    // *this - c*id();
    mat operator - (const T& c) const
    {return mat(*this)-=c;}

    vec<T,m> operator * (const vec<T,n>& u) const
    {
        vec<T,m> r;
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
                r.x[i] += x[i][j] * u.x[j];
        return r;
    }

    template<int p>
    mat<T,m,p> operator * (const mat<T,n,p>& M) const
    {
        mat<T,m,p> r;
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
                for(int k = 0; k < p; k++)
                    r.x[i][k] += x[i][j] * M.x[j][k];
        return r;
    }

    mat<T,n,m> transposed() const
    {
        mat<T,n,m> r;
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
                r.x[j][i]=x[i][j];
        return r;
    }

    const T& operator() (int i, int j) const
    {return x[i][j];}

    T& operator() (int i, int j)
    {return x[i][j];}
};

template <class T>
mat<T,3,3> cross_product_matrix(const vec<T,3>& u)
{
    mat<T,3,3> m;
    m.x[0][0]=0;
    m.x[0][1]=-u[2];
    m.x[0][2]=u[1];
    m.x[1][0]=u[2];
    m.x[1][1]=0;
    m.x[1][2]=-u[0];
    m.x[2][0]=-u[1];
    m.x[2][1]=u[0];
    m.x[2][2]=0;
    return m;
}

template <class T, int m, int n>
mat<T,m,n> operator * (const T& c, const mat<T,m,n>& v)
{return v*c;}

template <class T, int m, int n>
std::ostream& operator << (std::ostream& out, const mat<T,m,n> & M)
{
    for(int i = 0; i < m; i++)
    {
        if(i) out << " ; ";
        for(int j = 0; j < n; j++)
        {
            if(j) out << ' ';
            out << M.x[i][j];
        }
    }
    return out;
}

typedef mat<double,3,3> mat3;

#endif
