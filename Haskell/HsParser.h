/******************************************************************************
 * CoHsright (c) 2014-2016 Leandro T. C. Melo (ltcmelo@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a coHs of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 * USA
 *****************************************************************************/

/*--------------------------*/
/*--- The UaiSo! Project ---*/
/*--------------------------*/

#ifndef UAISO_HSPARSER_H__
#define UAISO_HSPARSER_H__

#include "Ast/AstFwd.h"
#include "Ast/AstList.h"
#include "Common/Test.h"
#include "Parsing/ParserLLk.h"
#include <cstddef>
#include <vector>

namespace uaiso {

class Lexer;
class ParsingContext;

class UAISO_API HsParser final : public ParserLLk
{
public:
    HsParser();

    bool parse(Lexer* lexer, ParsingContext* context) override;

private:
    DECL_CLASS_TEST(HsParser)

    using NestedName = std::unique_ptr<NestedNameAst>;

    //--- Expressions ---//

    Expr parseExpr();
    Expr parseAExpr();
    Expr parseIntLit();
    Expr parseFloatLit();
    Expr parseStrLit();
    Expr parseCharLit();
    Expr parseBoolLit();
    Expr parseWildcard();
    Expr parsePlainRhs();
    Expr parseGuardRhs();

    //--- Declarations ---//

    Decl parseModule();
    Decl parseExport();
    Decl parseImport();
    DeclList parseSelection(bool allowModid);
    DeclList parseBody();
    DeclList parseTopDecls();
    Decl parseDecl();
    Decl parsePatBindOrAnyFuncOrTypeSig();
    Decl parsePatBindOrInfFuncOrChainFunc();
    Decl parsePatBindOrChainFunc(std::vector<SourceLoc>&& parens);
    Decl parsePatBind();
    Decl parseInfFunc();
    Decl parseFunc();
    Decl parsePat();
    Decl parseAPat();
    Decl parseLPat();
    Decl parseFuncRhs(Decl func);
    Decl parsePatBindRhs(Decl pat, Expr (HsParser::*parse)());
    DeclList parsePatList();
    DeclList parsePatDList();
    DeclList parseAPatList();
    DeclList parseAPatDList();
    Decl finishAsPat(Name var, bool extendMatch);
    Decl finishInfixCtor(Decl pat, Name qConOp);
    Decl finishLabeledPat(Name qConId);
    Decl finishListConOrListPat();
    Decl finishUnitOrWrapOrTupConOrTupPat();
    Decl finishPatBindOrInfixFunc(Decl pat);

    //--- Specifiers ---//

    Spec parseContextType();
    Spec parseType();
    Spec parseBType();
    Spec parseAType();

    //--- Names ---//

    Name parseModid();
    Name parseVarOrCon();
    Name parseQVar();
    Name parseQVarId();
    Name parseQVarSymWrap();
    Name parseQCon();
    Name parseQConId();
    Name parseQConIdTick();
    Name parseQConSym();
    Name parseQConSymWrap();
    Name parseVar();
    Name parseVarId();
    Name parseVarIdTick();
    Name parseVarSym();
    Name parseVarSymWrap();
    Name parseCon();
    Name parseConId();
    Name parseConSym();
    Name parseConSymWrap();
    Name maybeParseQConOp();
    Name maybeParseVar();

    bool isVarSym(const Token tk) const;
    bool isConSym(const Token tk) const;
    bool isAPatFIRST(const Token tk) const;

    // Helpers

    Name parseName(Token tk);
    Name parseQName(Token qualTk, Name (HsParser::*parseFunc)());
    Name parseSymWrapOrId(Name (HsParser::*parseSymWrap)(), Name (HsParser::*parseId)());
};


// Auxiliary lookhead functions.

inline bool HsParser::isVarSym(const Token tk) const
{
    switch (tk) {
    case TK_EXCLAM:
    case TK_POUND:
    case TK_DOLLAR:
    case TK_PERCENT:
    case TK_AMPER:
    case TK_ASTERISK:
    case TK_PLUS:
    case TK_MINUS:
    case TK_DOT:
    case TK_SLASH:
    case TK_LS:
    case TK_GR:
    case TK_QUESTION:
    case TK_CARET:
    case TK_PUNC_IDENT:
        return true;
    default:
        return false;
    }
}

inline bool HsParser::isConSym(const Token tk) const
{
    switch (tk) {
    case TK_COLON:
    case TK_SPECIAL_IDENT:
        return true;
    default:
        return false;
    }
}

inline bool HsParser::isAPatFIRST(const Token tk) const
{
    switch (tk) {
    case TK_IDENT:
    case TK_PROPER_IDENT:
    case TK_PROPER_IDENT_QUAL:
    case TK_LPAREN:
    case TK_LBRACKET:
    case TK_TILDE:
    case TK_INT_LIT:
    case TK_FLOAT_LIT:
    case TK_TRUE_VALUE:
    case TK_FALSE_VALUE:
    case TK_CHAR_LIT:
    case TK_STR_LIT:
    case TK_UNDERSCORE:
        return true;
    default:
        return false;
    }
}

} // namespace uaiso

#endif
