/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright held by original author
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Typedef
    Foam::label

Description
    A label is an int/long/long long depending on the range wanted.
    A readLabel function is defined so that label can be constructed from
    Istream.

\*---------------------------------------------------------------------------*/

#ifndef label_H
#define label_H

#include <climits>
#include <cstdlib>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


#if FOAM_LABEL64
#    define WANTEDRANGE 9000000000000000000
#else
#    define WANTEDRANGE 2000000000
#endif


#if INT_MAX > WANTEDRANGE

// Define label as an int

#include "int.H"

namespace Foam
{
    typedef int label;

    static const label labelMax = INT_MAX;
    static const label labelMin = INT_MIN;

    inline label readLabel(Istream& is)
    {
        return readInt(is);
    }

} // End namespace Foam


#elif LONG_MAX > WANTEDRANGE

// Define label as a long

#include "int.H"
#include "long.H"

namespace Foam
{
    typedef long label;

    static const label labelMax = LONG_MAX;
    static const label labelMin = LONG_MIN;

    inline label readLabel(Istream& is)
    {
        return readLong(is);
    }

} // End namespace Foam


#elif LLONG_MAX > WANTEDRANGE

// Define label as a long long

#include "int.H"
#include "long.H"
#include "longLong.H"

namespace Foam
{
    typedef long long label;

    static const label labelMax = LLONG_MAX;
    static const label labelMin = LLONG_MIN;

    inline label readLabel(Istream& is)
    {
        return readLongLong(is);
    }

} // End namespace Foam

#endif


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "pTraits.H"
#include "direction.H"

namespace Foam
{

// template specialisation for pTraits<label>
template<>
class pTraits<label>
{
    label p_;

public:

    //- Component type
    typedef label cmptType;

    // Member constants

        enum
        {
            dim = 3,         // Dimensionality of space
            rank = 0,        // Rank od label is 0
            nComponents = 1  // Number of components in label is 1
        };

    // Static data members

        static const char* const typeName;
        static const char* componentNames[];
        static const label zero;
        static const label one;

    // Constructors

        //- Construct from Istream
        pTraits(Istream& is);

    // Member Functions

        operator label() const
        {
            return p_;
        }
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//- Raise one label to the power of another
label pow(label a, label b);

//- Evaluate n! : n <= 12
label factorial(label n);


#define MAXMIN(retType, type1, type2)              \
                                                   \
inline retType max(const type1 s1, const type2 s2) \
{                                                  \
    return (s1 > s2)? s1: s2;                      \
}                                                  \
                                                   \
inline retType min(const type1 s1, const type2 s2) \
{                                                  \
    return (s1 < s2)? s1: s2;                      \
}


MAXMIN(char, char, char)
MAXMIN(short, short, short)
MAXMIN(int, int, int)
MAXMIN(long, long, long)
MAXMIN(long long, long long, long long)

MAXMIN(unsigned char, unsigned char, unsigned char)
MAXMIN(unsigned short, unsigned short, unsigned short)
MAXMIN(unsigned int, unsigned int, unsigned int)
MAXMIN(unsigned long, unsigned long, unsigned long)
MAXMIN(unsigned long long, unsigned long long, unsigned long long)

MAXMIN(long, int, long)
MAXMIN(long long, int, long long)
MAXMIN(long long, long long, int)

inline label& setComponent(label& l, const direction)
{
    return l;
}

inline label component(const label l, const direction)
{
    return l;
}

inline label mag(const label l)
{
    return ::abs(l);
}

inline label sign(const label s)
{
    return (s >= 0)? 1: -1;
}

inline label pos(const label s)
{
    return (s >= 0)? 1: 0;
}

inline label neg(const label s)
{
    return (s < 0)? 1: 0;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
