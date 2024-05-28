#pragma once

#include <c/ast/CToken.hpp>


struct COperator {
    static const COperator SCOPE; // _::_
    static const COperator INC; // _++
    static const COperator DEC; // _--
    static const COperator CALL; // _(_)
    static const COperator SUBSCRIPT; // _[_]
    static const COperator DOT; // _._
    static const COperator PTR; // _->_
    static const COperator PRE_INC; // ++_
    static const COperator PRE_DEC; // --_
    static const COperator INV; // ~_
    static const COperator NOT; // !_
    static const COperator POS; // +_
    static const COperator NEG; // -_
    static const COperator REF; // &_
    static const COperator DEREF; // *_
    static const COperator CAST; // (_)_
    static const COperator MUL; // _*_
    static const COperator DIV; // _/_
    static const COperator MOD; // _%_
    static const COperator ADD; // _+_
    static const COperator SUB; // _-_
    static const COperator LSL; // _<<_
    static const COperator ASR; // _>>_
    static const COperator LSR; // _>>>_
    static const COperator LES; // _<_
    static const COperator GTR; // _>_
    static const COperator LEQ; // _<=_
    static const COperator GEQ; // _>=_
    static const COperator EQU; // _==_
    static const COperator NEQ; // _!=_
    static const COperator AND; // _&_
    static const COperator XOR; // _^_
    static const COperator OR; // _|_
    static const COperator LAND; // _&&_
    static const COperator LXOR; // _^^_
    static const COperator LOR; // _||_
    static const COperator SET; // _=_
    static const COperator MUL_SET; // _*=_
    static const COperator DIV_SET; // _/=_
    static const COperator MOD_SET; // _%=_
    static const COperator ADD_SET; // _+=_
    static const COperator SUB_SET; // _-=_
    static const COperator LSL_SET; // _>>=_
    static const COperator ASR_SET; // _<<=_
    static const COperator LSR_SET; // _>>>=_
    static const COperator AND_SET; // _&=_
    static const COperator XOR_SET; // _^=_
    static const COperator OR_SET; // _|=_
    static const COperator TERNARY; // _?_:_
    static const COperator COMMA; // _,_

    const CToken &name; // The operator name
    const u32 lbp;       // The left hand operand binding power
    const u32 rbp;       // The right hand operand binding power


    COperator(
        const CToken &name,
        u32 lbp,
        u32 rbp
    ) :
        name(name),
        lbp(lbp),
        rbp(rbp)
    {}
};
