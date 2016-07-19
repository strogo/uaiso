/******************************************************************************
 * Copyright (c) 2014-2016 Leandro T. C. Melo (ltcmelo@gmail.com)
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
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 * USA
 *****************************************************************************/

/*--------------------------*/
/*--- The UaiSo! Project ---*/
/*--------------------------*/

#include "Haskell/HsParser.h"
#include "Haskell/HsLexer.h"
#include "Ast/Ast.h"
#include "Common/Assert.h"
#include "Common/Trace__.h"
#include "Parsing/ParsingContext.h"

#define TRACE_NAME "HsParser"

using namespace uaiso;

namespace uaiso {

extern std::unordered_map<std::uint16_t, const char*> tokenName;

}

HsParser::HsParser()
{}

void HsParser::matchOrSkipTo(Token tk, const char *rule)
{
    if (!match(tk)) {
        DEBUG_TRACE("%s, skip to %s\n", rule, tokenName[tk]);
        skipTo(tk);
    }
}

bool HsParser::parse(Lexer* lexer, ParsingContext* context)
{
    UAISO_ASSERT(lexer, return false);
    UAISO_ASSERT(context && context->fileName(), return false);

    lexer_ = lexer;
    context_ = context;

    consumeToken();
    if (ahead_ == TK_EOP)
        return false;

    auto prog = std::unique_ptr<ProgramAst>(newAst<ProgramAst>());
    if (ahead_ == TK_MODULE)
        prog->setModule(parseModuleDecl().release());
    prog->setDecls(parseBody().release());
    context->takeAst(std::unique_ptr<Ast>(prog.release()));

    return true;
}

Parser::Decl HsParser::parseModuleDecl()
{
    UAISO_ASSERT(ahead_ == TK_MODULE, return Decl());

    match(TK_MODULE);
    auto module = ModuleDeclAst::create();
    module->setKeyLoc(lastLoc_);
    module->setName(parseModidName().release());

    // Exports
    if (maybeConsume(TK_LPAREN)) {
        do {
            if (maybeConsume(TK_RPAREN))
                goto ExportsDone;

            parseExportDecl();
        } while (maybeConsume(TK_COMMA));
        matchOrSkipTo(TK_RPAREN, "parseModuleDecl");
    }

ExportsDone:
    match(TK_WHERE);
    module->setTerminLoc(lastLoc_);

    return std::move(module);
}

Parser::Decl HsParser::parseExportDecl()
{
    switch (ahead_) {
    case TK_MODULE:
        consumeToken();
        parseModidName();
        break;

    case TK_LPAREN:
        parseQVarSymName();
        break;

    case TK_IDENT: {
        parseVarIdName();
        break;
    }

    default:
        auto qname = parseConIdList();
        if (maybeConsume(TK_IDENT)) {
            addToList(qname, parseVarIdName().release());
        } else if (maybeConsume(TK_LPAREN)) {
            if (maybeConsume(TK_DOT_DOT)) {
                // TODO: mark export all
            } else {
                do {
                    parseQVarOrQConName();
                } while (maybeConsume(TK_COMMA));
            }
            matchOrSkipTo(TK_RPAREN, "parseExportDecl");
        }
        // TODO: add names to export decl
        break;
    }

    return Decl();
}

Parser::DeclList HsParser::parseBody()
{
    return DeclList();
}

Parser::Expr HsParser::parseExpr()
{
    return parseAExpr();
}

Parser::Expr HsParser::parseAExpr()
{
    switch (ahead_) {
    case TK_INT_LIT:
        consumeToken();
        return Expr(newAst<NumLitExprAst>()->setLitLoc(lastLoc_)
                    ->setVariety(NumLitVariety::IntFormat));

    case TK_FLOAT_LIT:
        consumeToken();
        return Expr(newAst<NumLitExprAst>()->setLitLoc(lastLoc_)
                    ->setVariety(NumLitVariety::FloatFormat));

    case TK_TRUE_VALUE:
    case TK_FALSE_VALUE:
        consumeToken();
        return Expr(newAst<BoolLitExprAst>()->setLitLoc(lastLoc_));

    default:
        failMatch(true);
        return Expr();
    }
}

Parser::Name HsParser::parseModidName()
{
    auto modid = NestedNameAst::create();
    do {
        modid->addName(parseName(TK_PROPER_IDENT).release());
    } while (maybeConsume(TK_JOKER));

    return std::move(modid);
}

Parser::Name HsParser::parseQVarOrQConName()
{
    if (ahead_ == TK_LPAREN) {
        consumeToken();
        auto qname = parseConIdList();
        switch (ahead_) {
        case TK_COLON:
        //case TK_CUSTOM_COLON:
            addToList(qname, parseConSymName().release());
            break;

        default:
            addToList(qname, parseVarSymName().release());
            break;
        }
        matchOrSkipTo(TK_RPAREN, "parseQVarOrQConName");
        return Name();
    }

    auto qname = parseConIdList();
    if (ahead_ == TK_IDENT) {
        addToList(qname, parseVarIdName().release());
        return Name();
    }

    return Name();
}

Parser::Name HsParser::parseQConName()
{
    if (ahead_ == TK_LPAREN)
        return parseQConSymName();
    return parseQConIdName();
}

Parser::Name HsParser::parseQVarName()
{
    if (ahead_ == TK_LPAREN)
        return parseQVarSymName();
    return parseQVarIdName();
}

Parser::Name HsParser::parseConName()
{
    if (ahead_ == TK_LPAREN)
        return parseConSymName();
    return parseConIdName();
}

Parser::Name HsParser::parseVarName()
{
    if (ahead_ == TK_LPAREN)
        return parseVarSymName();
    return parseVarIdName();
}

Parser::Name HsParser::parseQConIdName()
{
    return parseQName(&HsParser::parseConIdName);
}

Parser::Name HsParser::parseQVarIdName()
{
    return parseQName(&HsParser::parseVarIdName);
}

Parser::Name HsParser::parseQConSymName()
{
    UAISO_ASSERT(ahead_ == TK_LPAREN, return Name());
    consumeToken();
    auto name = parseQName(&HsParser::parseConSymName);
    matchOrSkipTo(TK_RPAREN, "parseQConSymName");

    return std::move(name);
}

Parser::Name HsParser::parseQVarSymName()
{
    UAISO_ASSERT(ahead_ == TK_LPAREN, return Name());
    consumeToken();
    auto name = parseQName(&HsParser::parseVarSymName);
    matchOrSkipTo(TK_RPAREN, "parseQVarSymName");

    return std::move(name);
}

Parser::Name HsParser::parseConSymName()
{
    switch (ahead_) {
    case TK_COLON:
    case TK_CUSTOM_OPRTR: // TODO: Custom that begins with `:`.
        consumeToken();
        return SimpleNameAst::create(lastLoc_);

    default:
        failMatch(true);
        return ErrorNameAst::create();
    }
}

Parser::Name HsParser::parseVarSymName()
{
    switch (ahead_) {
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
    case TK_CUSTOM_OPRTR: {
        consumeToken();
        return SimpleNameAst::create(lastLoc_);
    }

    default:
        failMatch(true);
        return ErrorNameAst::create();
    }
}

Parser::Name HsParser::parseConIdName()
{
    return parseName(TK_PROPER_IDENT);
}

Parser::Name HsParser::parseVarIdName()
{
    return parseName(TK_IDENT);
}

Parser::NameList HsParser::parseConIdList()
{
    NameList names;
    do {
        addToList(names, parseConIdName().release());
    } while (maybeConsume(TK_JOKER));

    return names;
}

Parser::Name HsParser::parseQName(Name (HsParser::*parseFunc)())
{
    auto qname = NestedNameAst::create();
    while (maybeConsume(TK_PROPER_IDENT)) {
        addToList(qname->names_, SimpleNameAst::create(lastLoc_).release());
        match(TK_JOKER);
    }
    addToList(qname->names_, ((this->*(parseFunc))()).release());

    return std::move(qname);
}

HsParser::Name HsParser::parseName(Token tk)
{
    /*
     * We cannot fail a NameAst match. This would mean an identifier without a
     * corresponding location in the lexeme map, which is not allowed in our
     * design. Therefore, an ErrorNameAst must be constructed in such case.
     */
    if (match(tk))
        return SimpleNameAst::create(lastLoc_);

//    consumeToken();
    auto name = ErrorNameAst::create();
    name->setErrorLoc(lastLoc_);
    return std::move(name);
}
