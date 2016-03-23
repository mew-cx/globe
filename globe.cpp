// globe.cpp
// http://mew.cx/ 2015-02-15 2016-03-22

#include <stdio.h>
#include <vector>
#include <cmath>
#include <assert.h>

/////////////////////////////////////////////////////////////////////////////

class Vec3
{
public:
    typedef size_t Id;

    Vec3( float x, float y, float z, bool roundUp ) : _id(_v.size())
    {
        _x = x;
        _y = y;
        _z = z;
        _roundUp = roundUp;
        normalize();
        texCoord();
        _v.push_back( this );
    }

    Vec3( Vec3* a, Vec3* b ) : _id(_v.size())
    {
        _x = (a->_x + b->_x) / 2.0f;
        _y = (a->_y + b->_y) / 2.0f;
        _z = (a->_z + b->_z) / 2.0f;
        _roundUp = ( a->_roundUp && b->_roundUp );
        normalize();
        texCoord();
        _v.push_back( this );
    }

    Id id() const { return _id; }

    void texCoord()
    {
        const float PI = 3.1415927f;
        _s = std::atan2( _y, _x ) / (2.0f * PI) + 0.5f;
        _t = std::acos( -_z ) / PI;

        const float tol0(0.01f);
        const float tol1(1.0f - tol0);
        if( (_s < tol0) && _roundUp )   _s = 1.0f;
        if( (_s > tol1) && !_roundUp )  _s = 0.0f;
    }

    void normalize()
    {
        const float len = std::sqrt( _x*_x + _y*_y + _z*_z );
        _x /= len;
        _y /= len;
        _z /= len;
    }

public:         // static
    static void print()
    {
        for( Array::iterator i = _v.begin(); i != _v.end(); ++i )
        {
            const Vec3& v( **i );
            const float s = 1.0f;       // geometry scale

            printf( "v  %f %f %f\n", s*v._x, s*v._y, s*v._z );
            printf( "vn %f %f %f\n", v._x, v._y, v._z );
            printf( "vt %f %f\n", v._s, v._t );
        }
    }

private:
    const Id _id;
    float _x, _y, _z;
    float _s, _t;
    bool _roundUp;

private:
    typedef std::vector<Vec3*> Array;
    static Array _v;

private:        // disallowed
    Vec3();
};

Vec3::Array Vec3::_v;

/////////////////////////////////////////////////////////////////////////////

class Tri
{
public:
    typedef int Id;

    Tri( Vec3& a, Vec3& b, Vec3& c ) :
            _id(_t.size()), _a(a.id()), _b(b.id()), _c(c.id())
    {
        _t.push_back( this );
    }

    static void subdivide3( int level, Vec3* a, Vec3* b, Vec3* c )
    {
        if( level == 0 )
        {
            new Tri( *a, *b, *c );
            return;
        }

        Vec3* ab( new Vec3( a, b ) );
        Vec3* bc( new Vec3( b, c ) );
        Vec3* ca( new Vec3( c, a ) );

        subdivide3( level-1, a,  ab, ca );
        subdivide3( level-1, b,  bc, ab );
        subdivide3( level-1, c,  ca, bc );
        subdivide3( level-1, ab, bc, ca );
    }

public:         // static
    static void print()
    {
        for( Array::iterator i = _t.begin(); i != _t.end(); ++i )
        {
            Tri& t( **i );
            Vec3::Id a( t._a );
            Vec3::Id b( t._b );
            Vec3::Id c( t._c );
            printf( "f  %d/%d/%d %d/%d/%d %d/%d/%d\n",
                    a+1, a+1, a+1,
                    b+1, b+1, b+1,
                    c+1, c+1, c+1 );
        }
    }

private:
    const Id _id;
    const Vec3::Id _a, _b, _c;

private:
    typedef std::vector<Tri*> Array;
    static Array _t;

private:        // disallowed
    Tri();
};

Tri::Array Tri::_t;

/////////////////////////////////////////////////////////////////////////////

int main( int argc, char* argv[] )
{
    // ECEF : earth-centered, earth-fixed
    Vec3* xp = new Vec3(  1,  0,  0, true );    // 0 at equator (prime meridian)
    Vec3* xe = new Vec3( -1,  0,  0, true );    // 180 at equator from east
    Vec3* xw = new Vec3( -1,  0,  0, false );   // 180 at equator from west

    Vec3* yp = new Vec3(  0,  1,  0, true );    // +90 at equator
    Vec3* yn = new Vec3(  0, -1,  0, true );    // -90 at equator

    Vec3* zp = new Vec3(  0,  0,  1, true );    // north pole
    Vec3* zn = new Vec3(  0,  0, -1, true );    // south pole

    const int levels = 4;

    Tri::subdivide3( levels, xw, yn, zp );      // A
    Tri::subdivide3( levels, xp, yn, zp );      // B
    Tri::subdivide3( levels, xp, yp, zp );      // C
    Tri::subdivide3( levels, xe, yp, zp );      // D

    Tri::subdivide3( levels, xw, yn, zn );      // E
    Tri::subdivide3( levels, xp, yn, zn );      // F
    Tri::subdivide3( levels, xp, yp, zn );      // G
    Tri::subdivide3( levels, xe, yp, zn );      // H

    printf( "mtllib globe.mtl\n" );
    printf( "usemtl mat1\n" );
    printf( "o 1\n" );
    Vec3::print();
    Tri::print();

    return 0;
}


// vim: sw=4 ts=8 et ic ai nows ru:
