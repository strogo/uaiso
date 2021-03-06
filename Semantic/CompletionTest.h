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

#ifndef UAISO_COMPLETIONTEST_H__
#define UAISO_COMPLETIONTEST_H__

#include "Common/LineCol.h"
#include "Semantic/CompletionProposer.h"

namespace uaiso {

class Factory;
class Unit;

class CompletionProposer::CompletionProposerTest : public Test
{
public:
    TEST_RUN(CompletionProposerTest
             // D
             , &CompletionProposerTest::DTestCase1
             , &CompletionProposerTest::DTestCase2
             , &CompletionProposerTest::DTestCase3
             , &CompletionProposerTest::DTestCase4
             , &CompletionProposerTest::DTestCase5
             , &CompletionProposerTest::DTestCase6
             , &CompletionProposerTest::DTestCase7
             , &CompletionProposerTest::DTestCase8
             , &CompletionProposerTest::DTestCase9
             , &CompletionProposerTest::DTestCase10
             , &CompletionProposerTest::DTestCase11
             , &CompletionProposerTest::DTestCase12
             , &CompletionProposerTest::DTestCase13
             , &CompletionProposerTest::DTestCase14
             , &CompletionProposerTest::DTestCase15
             , &CompletionProposerTest::DTestCase16
             , &CompletionProposerTest::DTestCase17
             , &CompletionProposerTest::DTestCase18
             , &CompletionProposerTest::DTestCase19
             // Go
             , &CompletionProposerTest::GoTestCase1
             , &CompletionProposerTest::GoTestCase2
             , &CompletionProposerTest::GoTestCase3
             , &CompletionProposerTest::GoTestCase4
             , &CompletionProposerTest::GoTestCase5
             , &CompletionProposerTest::GoTestCase6
             , &CompletionProposerTest::GoTestCase7
             , &CompletionProposerTest::GoTestCase8
             , &CompletionProposerTest::GoTestCase9
             , &CompletionProposerTest::GoTestCase10
             , &CompletionProposerTest::GoTestCase11
             , &CompletionProposerTest::GoTestCase12
             , &CompletionProposerTest::GoTestCase13
             , &CompletionProposerTest::GoTestCase14
             , &CompletionProposerTest::GoTestCase15
             , &CompletionProposerTest::GoTestCase16
             , &CompletionProposerTest::GoTestCase17
             // Python
             , &CompletionProposerTest::PyTestCase1
             , &CompletionProposerTest::PyTestCase2
             , &CompletionProposerTest::PyTestCase3
             , &CompletionProposerTest::PyTestCase4
             , &CompletionProposerTest::PyTestCase5
             , &CompletionProposerTest::PyTestCase6
             , &CompletionProposerTest::PyTestCase7
             , &CompletionProposerTest::PyTestCase8
             , &CompletionProposerTest::PyTestCase9
             , &CompletionProposerTest::PyTestCase10
             , &CompletionProposerTest::PyTestCase11
             , &CompletionProposerTest::PyTestCase12
             , &CompletionProposerTest::PyTestCase13
             , &CompletionProposerTest::PyTestCase14
             , &CompletionProposerTest::PyTestCase15
             , &CompletionProposerTest::PyTestCase16
             , &CompletionProposerTest::PyTestCase17
             , &CompletionProposerTest::PyTestCase18
             , &CompletionProposerTest::PyTestCase19
             , &CompletionProposerTest::PyTestCase20
             , &CompletionProposerTest::PyTestCase21
             , &CompletionProposerTest::PyTestCase22
             , &CompletionProposerTest::PyTestCase23
             , &CompletionProposerTest::PyTestCase24
             , &CompletionProposerTest::PyTestCase25
             , &CompletionProposerTest::PyTestCase26
             , &CompletionProposerTest::PyTestCase27
             , &CompletionProposerTest::PyTestCase28
             , &CompletionProposerTest::PyTestCase29
             , &CompletionProposerTest::PyTestCase30
             , &CompletionProposerTest::PyTestCase31
             , &CompletionProposerTest::PyTestCase32
             , &CompletionProposerTest::PyTestCase33
             , &CompletionProposerTest::PyTestCase34
             , &CompletionProposerTest::PyTestCase35
             , &CompletionProposerTest::PyTestCase36
             , &CompletionProposerTest::PyTestCase37
             , &CompletionProposerTest::PyTestCase38
             , &CompletionProposerTest::PyTestCase39
             , &CompletionProposerTest::PyTestCase40
             , &CompletionProposerTest::PyTestCase41
             , &CompletionProposerTest::PyTestCase42
             , &CompletionProposerTest::PyTestCase43
             , &CompletionProposerTest::PyTestCase44
             , &CompletionProposerTest::PyTestCase45
             , &CompletionProposerTest::PyTestCase46
             , &CompletionProposerTest::PyTestCase47
             , &CompletionProposerTest::PyTestCase48
             , &CompletionProposerTest::PyTestCase49
             )

    //--- D ---//

    void DTestCase1();
    void DTestCase2();
    void DTestCase3();
    void DTestCase4();
    void DTestCase5();
    void DTestCase6();
    void DTestCase7();
    void DTestCase8();
    void DTestCase9();
    void DTestCase10();
    void DTestCase11();
    void DTestCase12();
    void DTestCase13();
    void DTestCase14();
    void DTestCase15();
    void DTestCase16();
    void DTestCase17();
    void DTestCase18();
    void DTestCase19();

    //--- Go ---//

    void GoTestCase1();
    void GoTestCase2();
    void GoTestCase3();
    void GoTestCase4();
    void GoTestCase5();
    void GoTestCase6();
    void GoTestCase7();
    void GoTestCase8();
    void GoTestCase9();
    void GoTestCase10();
    void GoTestCase11();
    void GoTestCase12();
    void GoTestCase13();
    void GoTestCase14();
    void GoTestCase15();
    void GoTestCase16();
    void GoTestCase17();

    //--- Python ---//

    void PyTestCase1();
    void PyTestCase2();
    void PyTestCase3();
    void PyTestCase4();
    void PyTestCase5();
    void PyTestCase6();
    void PyTestCase7();
    void PyTestCase8();
    void PyTestCase9();
    void PyTestCase10();
    void PyTestCase11();
    void PyTestCase12();
    void PyTestCase13();
    void PyTestCase14();
    void PyTestCase15();
    void PyTestCase16();
    void PyTestCase17();
    void PyTestCase18();
    void PyTestCase19();
    void PyTestCase20();
    void PyTestCase21();
    void PyTestCase22();
    void PyTestCase23();
    void PyTestCase24();
    void PyTestCase25();
    void PyTestCase26();
    void PyTestCase27();
    void PyTestCase28();
    void PyTestCase29();
    void PyTestCase30();
    void PyTestCase31();
    void PyTestCase32();
    void PyTestCase33();
    void PyTestCase34();
    void PyTestCase35();
    void PyTestCase36();
    void PyTestCase37();
    void PyTestCase38();
    void PyTestCase39();
    void PyTestCase40();
    void PyTestCase41();
    void PyTestCase42();
    void PyTestCase43();
    void PyTestCase44();
    void PyTestCase45();
    void PyTestCase46();
    void PyTestCase47();
    void PyTestCase48();
    void PyTestCase49();

    std::unique_ptr<Unit> runCore(std::unique_ptr<Factory> factory,
                                  const std::string& code,
                                  const std::string& fullFileName,
                                  const std::vector<const char*>& expected);

    void reset() override
    {
        lineCol_ = { -1, -1 };
        disableBuiltins_ = true;
        disableAutoModules_ = true;
        dumpAst_ = false;
        dumpCompletions_ = false;
    }

    LineCol lineCol_;
    bool disableBuiltins_ { true };
    bool disableAutoModules_ { true };
    bool dumpAst_ { false };
    bool dumpCompletions_ { false };
};

} // namespace uaiso

#endif
