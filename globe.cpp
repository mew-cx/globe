// globe.cpp
// http://mew.cx/ 2015-02-15

#include <stdio.h>
#include <vector>
#include <cmath>
#include <assert.h>

/////////////////////////////////////////////////////////////////////////////

class Vec3
{
public:
    typedef int Id;

    Vec3( float x, float y, float z ) : _id(_v.size())
    {
        _x = x;
        _y = y;
        _z = z;
        normalize();
        texCoord();
        _v.push_back( this );
    }

    Vec3( Id a, Id b ) : _id(_v.size())
    {
        _x = (_v[a]->_x + _v[b]->_x) / 2.0f;
        _y = (_v[a]->_y + _v[b]->_y) / 2.0f;
        _z = (_v[a]->_z + _v[b]->_z) / 2.0f;
        normalize();
        texCoord();
        _v.push_back( this );
    }

    Id id() const { return _id; }

    void texCoord()
    {
        const float PI = 3.1415927f;
        _s = std::atan2( -_y, _x ) / (2 * PI) + 0.5f;
        _t = std::acos( _z ) / PI;
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

            printf( "v  %f %f %f\n", v._x, v._y, v._z );
            printf( "vn %f %f %f\n", v._x, v._y, v._z );
            printf( "vt %f %f\n", v._s, v._t );
        }
    }

private:
    const Id _id;
    float _x, _y, _z;
    float _s, _t;

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

        Vec3* ab = new Vec3( a->id(), b->id() );
        Vec3* bc = new Vec3( b->id(), c->id() );
        Vec3* ca = new Vec3( c->id(), a->id() );

        subdivide3( level-1, a, ab, ca );
        subdivide3( level-1, b, bc, ab );
        subdivide3( level-1, c, ca, bc );
        subdivide3( level-1, ab, bc, ca );
    }

public:         // static
    static void print()
    {
        for( Array::iterator i = _t.begin(); i != _t.end(); ++i )
        {
            Tri* t( *i );
            Vec3::Id a = t->_a+1;
            Vec3::Id b = t->_b+1;
            Vec3::Id c = t->_c+1;
            printf( "f  %d/%d/%d %d/%d/%d %d/%d/%d\n", a, a, a, b, b, b, c, c, c );
        }
    }

private:
    const Id _id;
    Vec3::Id _a, _b, _c;

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
    Vec3* yp = new Vec3(  0,  0, -1 );     // north pole
    Vec3* yn = new Vec3(  0,  0,  1 );     // south poke

    Vec3* xp = new Vec3(  1,  0,  0 );     // +90 at equator
    Vec3* xn = new Vec3( -1,  0,  0 );     // -90

    Vec3* zp = new Vec3(  0,  1,  0 );     // 0 at equator
    Vec3* zn = new Vec3(  0, -1,  0 );     // 180 at equator

    const int levels = 4;

    Tri::subdivide3( levels, yp, xn, zp );      // A
    Tri::subdivide3( levels, yp, xp, zp );      // B
    Tri::subdivide3( levels, yp, xp, zn );      // C
    Tri::subdivide3( levels, yp, xn, zn );      // D
    Tri::subdivide3( levels, yn, xn, zp );      // E
    Tri::subdivide3( levels, yn, xp, zp );      // F
    Tri::subdivide3( levels, yn, xp, zn );      // G
    Tri::subdivide3( levels, yn, xn, zn );      // H

    printf( "mtllib globe.mtl\n" );
    printf( "usemtl mat1\n" );
    printf( "o 1\n" );
    Vec3::print();
    Tri::print();

    return EXIT_SUCCESS;
}


// vim: sw=4 ts=8 et ic ai nows ru:
