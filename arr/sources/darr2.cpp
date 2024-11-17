// double arrays (m x n) - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

#include "arr.hpp"
#include "mth.hpp"
#include "trg.hpp"

namespace arr {

bool darr2::showOutput = false;
const double tol = 1.e-14;

//
darr2::darr2(const uiarr2& A) : double_arr2(A.size(0), A.size(1))
{
    for (size_t i = 0; i < m_nRows; i++)
        for (size_t j = 0; j < m_nCols; j++)
            at(i, j) = A(i, j);
}

//
darr2 darr2::operator+() const { return *this; }

//
darr2 darr2::operator-() const
{
    darr2 res(*this);
    for (size_t i = 0; i < m_nRows; i++)
        for (size_t j = 0; j < m_nCols; j++)
            res(i, j) *= -1;
    return res;
}

//
darr2 darr2::operator+(const darr2& A) const
{
    darr2 res(*this);
    size_t i, j;
    for (i = 0; i < size(0); ++i)
        for (j = 0; j < size(1); ++j)
            res(i, j) += A(i, j);
    return res;
}

//
darr2 darr2::operator-(const darr2& A) const
{
    darr2 res(*this);
    size_t i, j;
    for (i = 0; i < size(0); ++i)
        for (j = 0; j < size(1); ++j)
            res(i, j) -= A(i, j);
    return res;
}

//
darr2 darr2::operator+=(const darr2& A) { return *this = *this + A; }

darr2 darr2::operator-=(const darr2& A) { return *this = *this - A; }

darr2 darr2::operator/(double x) const { return (1. / x) * (*this); }

darr2 darr2::operator*=(double x) { return *this = x * (*this); }

darr2 darr2::operator/=(double x) { return *this = (*this) / x; }

//
darr1 darr2::operator*(const darr1& A) const
{
    size_t i, j;
    darr1 res(size(0));
    for (i = 0; i < size(0); ++i) {
        double x = 0.;
        for (j = 0; j < size(1); ++j)
            x += (*this)(i, j) * A(j);
        res(i) = x;
    }
    return res;
}

//
darr2 darr2::operator*(const darr2& A) const
{
    size_t i, j, k;
    darr2 res(size(0), A.size(1));
    for (i = 0; i < res.size(0); ++i)
        for (j = 0; j < res.size(1); ++j) {
            double x = 0.;
            for (k = 0; k < size(1); ++k)
                x += (*this)(i, k) * A(k, j);
            res(i, j) = x;
        }
    return res;
}

//
darr2 darr2::inv() const
{
    size_t m = size(0), n = size(1);
    darr2 res = ident(m, n);
    if (!isSquare()) {
        err = -1;
        return res;
    }
    double d = det();
    if (d == 0.) {
        err = -1;
        return res;
    }
    darr2 P, L, U;
    if (!PLU(P, L, U)) {
        err = -1;
        return res;
    }

    darr2 Y(m, m);
    for (size_t i = 0; i < m; i++) {
        darr1 b(P.row(i));
        darr1 y(m);
        for (size_t ip = 0; ip < m; ip++) {
            double sum = b(ip);
            for (size_t j = 0; j < ip; j++)
                sum -= L(ip, j) * y(j);
            y(ip) = sum / L(ip, ip);
        }
        Y.col(i) = y;
    }

    darr2 X(m, m);
    for (size_t i = 0; i < m; i++) {
        darr1 x(m);
        darr1 y = Y.col(i);
        // for(int ip=m-1;ip>=0;ip--)
        for (size_t ip = m; ip > 0; ip--) {
            size_t ipp = ip - 1;
            double sum = y(ipp);
            for (size_t j = ip; j < m; j++)
                sum -= U(ipp, j) * x(j);
            x(ipp) = sum / U(ipp, ipp);
        }
        X.col(i) = x;
    }
    res = X;
    return res;
}

//
darr1 darr2::diag() const
{
    std::size_t m = size(0), n = size(1);
    std::size_t f = m;
    if (f < n)
        f = n;
    darr1 res(f);

    std::size_t i;
    for (i = 0; i < f; ++i)
        res(i) = (*this)(i, i);
    return res;
}

//
darr2 darr1::diag() const
{
    std::size_t m = size();
    std::size_t i;
    darr2 res(m, m);
    res = (double)0;
    for (i = 0; i < m; ++i)
        res(i, i) = at(i);
    return res;
}

//
double darr2::trace() const
{
    if (!isSquare())
        return 0;
    std::size_t i;
    double res = 0;
    for (i = 0; i < size(0); ++i)
        res += at(i, i);
    return res;
}

//
double darr2::diagProd() const
{
    if (!isSquare())
        return 0;
    std::size_t i;
    double res = 1;
    for (i = 0; i < size(0); ++i)
        res *= at(i, i);
    return res;
}

//
darr2 darr2::pseudoInvLeft() const
{
    darr2 AT = T();
    darr2 res = (AT * (*this)).inv() * AT;
    return res;
}

//
darr2 darr2::pseudoInvRight() const
{
    darr2 AT = T();
    darr2 AAT = (*this) * AT;
    darr2 AATi = AAT.inv();
    darr2 res = AT * AATi;
    return res;
}

//
darr2 darr2::dampedPseudoInvLeft(double lambda) const
{
    darr2 AT = T();
    darr2 ATA = AT * (*this);
    darr2 G = ATA + lambda * (ATA.diag()).diag();
    darr2 Gi = G.inv();
    darr2 res = Gi * AT;
    return res;
}

//
darr2 darr2::cofactor() const
{
    darr2 res(size(0), size(0));
    size_t i, j;
    for (i = 0; i < size(0); ++i)
        for (j = 0; j < size(0); ++j)
            res(i, j) = cos((i + j) * trg::Pi) * minor(i, j).det();
    return res;
}

//
darr2 darr2::adjugate() const { return cofactor().T(); }

//
darr2 darr2::makePivotable(bool& isSingular) const
{
    darr2 A(*this);
    std::size_t m = size(0);
    std::size_t i = 0, j;
    isSingular = false;
    while ((i < m) && (!isSingular)) {
        for (j = i + 1; j < m; ++j)
            if (fabs(A(i, i)) < fabs(A(j, j))) {
                A.swapRows(i, j);
                A.row(j) *= -1.;
            }

        if (A(i, i) == 0) {
            j = 0;
            while ((j < m - 1) && (A(j, i) == 0)) {
                j++;
                if (A(j, i) != 0) {
                    A.swapRows(i, j);
                    A.row(j) *= -1.;
                }
                else
                    isSingular = true;
            }
        }
        i++;
    }
    return A;
}

//
darr2 darr2::upper(bool& isSingular) const
{
    isSingular = false;
    darr2 A(*this); //=makePivotable(isSingular);
    // if(!isSquare()){arr_err=1;return A;}
    std::size_t m = size(0), n = size(1);
    std::size_t i = 0, j, jRow;

    std::size_t mn = m;
    if (n < mn)
        mn = n;
    while ((i < mn) && (!isSingular)) {
        double Amax = fabs(A(i, i));
        jRow = i;
        bool needSwap = false;
        for (j = i + 1; j < m; ++j)
            if (fabs(A(j, i)) > Amax) {
                jRow = j;
                Amax = fabs(A(j, i));
                needSwap = true;
            }

        if (needSwap) {
            A.swapRows(i, jRow);
            A.row(jRow) *= -1.;
        }

        if (Amax != 0.)
            for (j = i + 1; j < m; ++j) {
                double ratio = A(j, i) / A(i, i);
                A.row(j) -= ratio * A.row(i);
                A(j, i) = 0.;
            }
        else {
            // std::cout<<A<<"\n";
            isSingular = true;
        }
        i++;
    }
    return A;
}

// Lower-Upper-Permutation Factorization
// Factors matrix A such that PA=LU
bool darr2::PLU(darr2& P, darr2& L, darr2& U) const
{
    std::size_t m = size(0), n = size(1);
    std::size_t p = std::min(m, n);
    P = darr2::ident(m, m);
    L = darr2::ident(m, p);
    U = darr2::zero(p, n);

    darr2 A(*this);
    darr1 V(m);
    std::size_t i, j, k;
    double big, sum, val;
    // Find largest value in each row
    for (i = 0; i < m; ++i) {
        big = 0.;
        for (j = 0; j < n; ++j)
            if ((val = fabs(A(i, j))) > big)
                big = val;
        if (big == 0.)
            return false;
        V(i) = big;
    }

    for (j = 0; j < n; ++j) {
        // Get Uij (i<j)
        for (i = 0; i < j; ++i) {
            sum = A(i, j);
            for (k = 0; k < i; ++k)
                sum -= A(i, k) * A(k, j);
            A(i, j) = sum;
        }

        // Find largest term in column
        big = 0.;
        std::size_t iMax = j;
        for (i = j; i < m; ++i) {
            sum = A(i, j);
            for (k = 0; k < j; ++k)
                sum -= A(i, k) * A(k, j);
            A(i, j) = sum;
            if ((val = V(i) * fabs(sum)) >= big) {
                big = val;
                iMax = i;
            }
        }

        // Swap rows, if necessary
        if (iMax != j) {
            A.swapRows(iMax, j);
            P.swapRows(iMax, j);
            A.row(iMax) *= -1;
            P.row(iMax) *= -1;
            V(iMax) = V(j);
        }

        if (A(j, j) == 0.)
            return false;

        if (j < n)
            for (i = j + 1; i < m; ++i)
                A(i, j) /= A(j, j);
    }

    // Find L(i,j)
    for (i = 0; i < m; ++i)
        for (j = 0; j < i; ++j)
            L(i, j) = A(i, j);

    // Find U(i,j)
    for (i = 0; i < n; ++i)
        for (j = i; j < n; ++j)
            U(i, j) = A(i, j);

    P = P.T();
    return true;
}

//
double darr2::det() const
{
    if (!isSquare()) {
        err = 1;
        return 0;
    }
    bool isSingular = false;
    darr2 A = upper(isSingular);
    if (isSingular) {
        return 0;
    }
    return A.diagProd();
}

//
darr2 operator*(const double x, const darr2& A)
{
    darr2 res(A);
    size_t i, j;
    for (i = 0; i < A.size(0); ++i)
        for (j = 0; j < A.size(1); ++j)
            res(i, j) = x * A(i, j);
    return res;
}

//
bool darr2::isSquareSymm() const
{
    if (!isSquare())
        return false;
    size_t n = size(0);

    for (size_t i = 0; i < n; i++)
        for (size_t j = i + 1; j < n; j++)
            if ((*this)(i, j) != at(j, i))
                return false;
    return true;
}

//
double darr2::findAngle(const size_t i, const size_t j, double& ang) const
{
    double s, c;
    double Apq = at(i, j);
    if (Apq != 0.) {
        double App = at(i, j);
        double Aqq = at(i, j);
        double tau = (Aqq - App) / (2. * Apq);
        double t, c1;

        if (tau >= 0.)
            t = 1. / (tau + ::sqrt(1. + mth::sqr(tau)));
        else
            t = -1. / (-tau + ::sqrt(1. + mth::sqr(tau)));

        c1 = 1. / ::sqrt(1. + mth::sqr(t));
        c = c1;
        s = t * c1;
    }
    else {
        c = 1.;
        s = 0.;
    }

    ang = trg::asincos(s, c);
    return fabs(Apq); // reduction in off(A) is 2*(A_pq)^2
}

//
double darr2::sum() const
{
    double tot = 0.;
    for (size_t i = 0; i < m_nRows; i++)
        for (size_t j = 0; j < m_nCols; j++)
            tot += at(i, j);
    return tot;
}

//
double darr2::sumSqr() const
{
    double tot = 0.;
    for (size_t i = 0; i < m_nRows; i++)
        for (size_t j = 0; j < m_nCols; j++)
            tot += mth::sqr(at(i, j));
    return tot;
}

//
double darr2::sumOffDiag() const
{
    double tot = 0.;
    for (size_t i = 0; i < m_nRows; i++)
        for (size_t j = i + 1; j < m_nCols; j++)
            tot += at(i, j);
    return 2. * tot;
}

// Generate Householder matrix for column i
darr2 darr2::Householder(const size_t i) const
{
    size_t m = size(0);
    darr2 H = darr2::ident(m, m);
    darr1 en = darr1::zero(m - i);
    en(0) = 1.;
    darr1 xn(m - i);
    for (size_t j = 0; j < m - i; j++)
        xn(j) = at(i + j, i);
    double rho = -mth::sgn(xn(0));
    if (rho == 0.)
        rho = 1.;
    double xmag = xn.mag();
    darr1 u = xn;
    u(0) -= rho * xmag;
    if (u.mag() > 0.) {
        darr1 v = u.norm();
        darr2 vvT = v * v.T();
        darr2sub(H(i, i, m - i, m - i)) -= 2. * vvT;
    }
    return H;
}

//
darr2 darr2::Householder(const size_t iRow, const size_t jCol) const
{
    size_t m = size(0);
    darr2 H = darr2::ident(m, m);
    darr1 en = darr1::zero(m - iRow);
    en(0) = 1.;
    darr1 xn(m - iRow);
    for (size_t j = 0; j < m - iRow; j++)
        xn(j) = at(iRow + j, jCol);
    double rho = -mth::sgn(xn(0));
    if (rho == 0.)
        rho = 1.;
    double xmag = xn.mag();
    darr1 u = xn;
    u(0) -= rho * xmag;
    if (u.mag() > 0.) {
        darr1 v = u.norm();
        darr2 vvT = v * v.T();
        H(iRow, iRow, m - iRow, m - iRow) -= 2. * vvT;
    }
    return H;
}

// Return upper-bidiagonal form B of matrix A=*this, such that
// A=U*B*V.T()
darr2 darr2::upperBidiag(darr2& U, darr2& V) const
{
    darr2 A(*this);
    U = darr2::ident(m_nRows, m_nRows);
    V = darr2::ident(m_nCols, m_nCols);
    size_t n = std::max(m_nRows, m_nCols);
    for (size_t i = 0; i < n; i++) {
        if (i < m_nRows) {
            darr2 Ui = A.Householder(i);
            A = Ui * A;
            U = U * Ui;
            A(i + 1, i, m_nRows - i - 1, 1) = 0;
        }
        if (i < m_nCols - 1) {
            darr2 Vi = A.T().Householder(i + 1, i);
            A = A * Vi.T();
            V = V * Vi;
            A(i, i + 2, 1, m_nCols - i - 2) = 0.;
        }
    }
    return A;
}

// Return Hessenberg (tridiagonal) form of symmetric matrix using unitary
// transformation P *this=P.T()*H*P
darr2 darr2::tridiag(darr2& P) const
{
    if (!isSquare())
        return *this;
    P = darr2::ident(m_nRows, m_nRows);
    darr2 A(*this);
    for (size_t i = 0; i < m_nRows - 1; i++) {
        darr2 Pp = A.Householder(i + 1, i);
        A = Pp * A * Pp.T();
        P = Pp * P;
        A(i + 2, i, m_nRows - i - 2, 1) = 0;
        A(i, i + 2, 1, m_nRows - i - 2) = 0.;
    }
    return A;
}

// Return upper triangular form of matrix using unitary transformation P
// R=P*(*this)
darr2 darr2::upperTriang(darr2& P) const
{
    darr2 A(*this);
    double nRows = m_nRows - 1;
    if (m_nRows > m_nCols)
        nRows = m_nCols;
    P = darr2::ident(m_nRows, m_nRows);
    darr2 R = A;
    for (size_t i = 0; i < nRows; i++) {
        darr2 Pi = R.Householder(i);
        R = Pi * R; //*Pi.T();
        R(i + 1, i, m_nCols - i - 1, 1) = 0.;
        P = Pi * P;
    }
    return R;
}

//
darr2 darr2::QR(darr2& Q) const
{
    darr2 QT;
    darr2 R = upperTriang(QT);
    Q = QT.T();
    return R;
}

//
bool darr2::diagSymm(darr2& s, darr2& V) const
{
    if (!isSquareSymm())
        return false;

    bool res = false;
    darr2 A(*this);
    std::size_t nRot = 0;
    V = darr2::ident(m_nRows, m_nRows);

    long niter = 200 * m_nRows * (m_nRows + 1) / 2;
    bool found = false;
    for (long iter = 0; iter < niter; iter++) {
        double aMax = 0.;
        size_t k = 0, l = 0;
        found = false;
        for (size_t ip = 0; ip < m_nRows; ip++)
            for (size_t iq = ip + 1; iq < m_nRows; iq++)
                if (fabs(A(ip, iq)) > aMax) {
                    aMax = fabs(A(ip, iq));
                    k = ip;
                    l = iq;
                    found = true;
                }

        if (found) {
            double g = A(l, l), h = A(k, k);
            double x = (g - h) / 2., y = A(k, l);
            if (::sqrt(x * x + y * y) > tol) {
                double ang = -atan2(y, x) / 2.;

                // Way faster!!
                A.rotR(k, l, ang);
                A.rotL(k, l, ang);
                V.rotR(k, l, ang);
                A(k, l) = A(l, k) = 0.;
            }
        }
        else {
            res = true;
            break;
        }
        nRot++;
    }

    darr1 sv = A.diag();
    for (size_t ip = 0; ip < m_nRows; ++ip)
        for (size_t iq = 0; iq < ip; iq++)
            if (sv(ip) > sv(iq)) // sort eigenvalues
            {
                sv.swap(ip, iq);
                A.swapCols(ip, iq);
            }
    if (!res)
        err = 1;
    s = sv.diag();
    return res;
}

//
darr2 darr2::diagSymm(darr2& v) const
{
    darr2 s;
    bool res = diagSymm(s, v);
    if (!res) {
        err = -1;
        s = *this;
    }
    return s;
}

// Singular-value decomposition
// New method: First make matrix upper bidiagonal.
// Then alternately zero elements on upper and lower diagonals.
// Iterate
bool darr2::SVD(darr2& U, darr2& S, darr2& V) const
{
    bool res = false;
    darr2 A(*this);
    upperBidiag(U, V); // Don't need B

    long nIter = 100 * std::max(m_nRows, m_nCols);
    for (long iIter = 0; iIter < nIter; iIter++) {
        for (size_t j = 0; j < m_nCols - 1; j++) {
            darr2 Sp = U.T() * A * V;
            double x = Sp(j, j);
            double y = Sp(j, j + 1);
            if (::sqrt(x * x + y * y) > tol) {
                double ang = atan2(y, x);
                V.rotR(j, j + 1, ang);
            }
        }
        for (size_t i = 0; i < m_nRows - 1; i++) {
            darr2 Sp = U.T() * A * V;
            double x = Sp(i, i);
            double y = Sp(i + 1, i);
            if (::sqrt(x * x + y * y) > tol) {
                double ang = -atan2(y, x);
                U.rotR(i + 1, i, ang);
            }
        }
    }

    S = U.T() * A * V;
    darr1 z = S.diag();
    size_t mp = z.size();
    for (size_t i = 0; i < mp; i++)
        if (z(i) < 0.)
            V.col(i) *= -1;

    S = U.T() * A * V;
    z = S.diag();
    for (size_t i = 0; i < mp; i++)
        for (size_t j = i + 1; j < mp; j++)
            if (z(i) < z(j)) {
                V.swapCols(i, j);
                U.swapCols(i, j);
            }

    S = U.T() * A * V;
    for (size_t i = 0; i < m_nRows; i++)
        for (size_t j = 0; j < m_nCols; j++)
            if (i != j) {
                if (fabs(S(i, j)) < tol)
                    S(i, j) = 0.;
            }

    if (!res)
        err = 1;
    return res;
}

//
bool darr2::SVDred(darr2& U, darr2& S, darr2& V, double fac) const
{
    bool res = SVD(U, S, V);
    size_t n = std::min(m_nRows, m_nCols);

    double sMax = S(0, 0);
    size_t nRed = 1;
    for (size_t i = 1; i < n; i++) // remove small factors
        if (S(i, i) > sMax / fac)
            nRed++;
        else
            break;

    U = U(0, 0, m_nRows, nRed);
    S = S(0, 0, nRed, nRed);
    V = V(0, 0, m_nCols, nRed);
    return res;
}

//
darr2 darr2::pseudoInv(double fac) const
{
    darr2 U, S, V;
    if (SVDred(U, S, V, fac))
        return V * S.inv() * U.T();
    return *this;
}

//
darr2 darr1::T() const { return darr2(*this).T(); }

//
darr2 darr2::zero(const size_t m, const size_t n)
{
    darr2 res(m, n);
    res = 0.;
    return res;
}

// static
darr2 darr2::ident(const size_t nRows, const size_t nCols)
{
    darr2 A(nRows, nCols);
    for (size_t i = 0; i < nRows; i++)
        for (size_t j = 0; j < nCols; j++)
            A(i, j) = (i == j) ? 1. : 0.;
    return A;
}

//
darr2 darr2::rot(const size_t iRow, const size_t jCol, double ang, size_t n)
{
    darr2 A = ident(n, n);
    double c = cos(ang), s = sin(ang);
    A(iRow, jCol) = s;
    A(jCol, iRow) = -s;
    A(iRow, iRow) = A(jCol, jCol) = c;
    return A;
}

// Multiplies *this by rotation matrix from right affecting cols iCol and
// jCol
void darr2::rotR(const size_t iCol, const size_t jCol, double ang)
{
    double c = cos(ang), s = sin(ang);
    for (size_t k = 0; k < m_nRows; k++) {
        double Aki = at(k, iCol);
        double Akj = at(k, jCol);
        at(k, iCol) = c * Aki + s * Akj;
        at(k, jCol) = -s * Aki + c * Akj;
    }
}

// Multiplies *this by rotation matrix from left affecting rows iRow and
// jRow
void darr2::rotL(const size_t iRow, const size_t jRow, double ang)
{
    // cout<<"init:\n"<<*this<<"\n";
    double c = cos(ang), s = sin(ang);
    for (size_t k = 0; k < m_nCols; k++) {
        double Aik = at(iRow, k);
        double Ajk = at(jRow, k);
        at(iRow, k) = c * Aik + s * Ajk;
        at(jRow, k) = -s * Aik + c * Ajk;
    }
}

//
darr2 darr1::operator*(const darr2& A) const
{
    std::size_t nRows = m_n, nCols = A.size(1);
    darr2 res(nRows, nCols);
    if (A.size(0) != 1)
        return res;
    for (size_t i = 0; i < nRows; i++)
        for (size_t j = 0; j < nCols; j++)
            res(i, j) = at(i) * A(0, j);
    return res;
}

//
darr2 darr2::pwr(const double x) const
{
    darr2 A(m_nRows, m_nCols);
    for (size_t i = 0; i < m_nRows; i++)
        for (size_t j = 0; j < m_nCols; j++)
            A(i, j) = pow(at(i, j), x);
    return A;
}

//
darr2 darr2::rowEschelon() const
{
    darr2 A(*this);
    for (size_t i = 0; i < m_nRows; i++) {
        // Find row with valid pivot
        size_t k = i;
        bool found = false;
        while ((k < m_nRows) && (!found)) {
            if (A(k, i) == 0.)
                k++;
            else
                found = true;
        }
        if (!found)
            continue;
        if (k != i)
            A.swapRows(i, k);

        double pivot = A(i, i);
        if (pivot != 0.) {
            A.row(i) /= pivot;

            for (size_t k = 0; k < m_nRows; k++) {
                if (k != i) {
                    double fac = A(k, i);
                    A.row(k) -= fac * A.row(i);
                    A(k, i) = 0.;
                }
            }
        }
    }
    return A;
}

// Generate square matrix with cols representing basis vector
darr2 darr2::span() const
{
    darr2 A = rowEschelon().T();
    size_t nRows = A.size(0), nCols = A.size(1);
    darr2 B = ident(nRows, nRows);

    // Find row with valid pivot
    for (size_t i = 0; (i < nRows) && (i < nCols); i++) {
        size_t k = i;
        bool found = false;
        while ((k < nRows) && (!found)) {
            if (A(k, i) == 0.)
                k++;
            else
                found = true;
        }
        if (!found)
            continue;
        if (k != i) {
            A.swapRows(i, k);
            B.swapRows(i, k);
        }

        double pivot = A(i, i);
        if (pivot != 0) {
            A.row(i) /= pivot;

            for (size_t k = 0; k < nRows; k++) {
                if (k != i) {
                    double fac = A(k, i);
                    A.row(k) -= fac * A.row(i);
                    B.row(k) -= fac * B.row(i);
                }
            }
        }
    }
    return B.T();
}

// Generate matrix with cols representing nullspace basis vector
// ((*this)*B.T() = 0*B.T());
darr2 darr2::nullspace() const
{
    darr2 A = rowEschelon().T();
    size_t nRows = A.size(0), nCols = A.size(1);
    darr2 B = ident(nRows, nRows);

    // Find row with valid pivot
    for (size_t i = 0; (i < nRows) && (i < nCols); i++) {
        size_t k = i;
        bool found = false;
        while ((k < nRows) && (!found)) {
            if (A(k, i) == 0.)
                k++;
            else
                found = true;
        }
        if (!found)
            continue;
        if (k != i) {
            A.swapRows(i, k);
            B.swapRows(i, k);
        }

        double pivot = A(i, i);
        if (pivot != 0.) {
            A.row(i) /= pivot;
            for (size_t k = 0; k < nRows; k++) {
                if (k != i) {
                    double fac = A(k, i);
                    A.row(k) -= fac * A.row(i);
                    B.row(k) -= fac * B.row(i);
                }
            }
        }
    }

    std::vector<size_t> null_rows;
    for (size_t i = 0; i < nRows; i++) {
        if (i < nCols) {
            if (A(i, i) == 0.)
                null_rows.push_back(i);
        }
        else
            null_rows.push_back(i);
    }

    size_t n_null = null_rows.size();
    darr2 C(n_null, nRows);
    for (size_t i = 0; i < n_null; i++) {
        C.row(i) = B.row(null_rows[i]);
    }
    return C.T();
}

//
darr2 darr2::sqr() const { return pwr(2.); }

darr2 darr2::sqrt() const { return pwr(0.5); }
} // namespace arr
