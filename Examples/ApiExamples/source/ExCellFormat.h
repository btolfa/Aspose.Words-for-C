﻿#pragma once
// Copyright (c) 2001-2021 Aspose Pty Ltd. All Rights Reserved.
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <Aspose.Words.Cpp/Body.h>
#include <Aspose.Words.Cpp/Document.h>
#include <Aspose.Words.Cpp/DocumentBuilder.h>
#include <Aspose.Words.Cpp/Saving/SaveOutputParameters.h>
#include <Aspose.Words.Cpp/Section.h>
#include <Aspose.Words.Cpp/Tables/Cell.h>
#include <Aspose.Words.Cpp/Tables/CellCollection.h>
#include <Aspose.Words.Cpp/Tables/CellFormat.h>
#include <Aspose.Words.Cpp/Tables/CellMerge.h>
#include <Aspose.Words.Cpp/Tables/Row.h>
#include <Aspose.Words.Cpp/Tables/RowCollection.h>
#include <Aspose.Words.Cpp/Tables/Table.h>
#include <Aspose.Words.Cpp/Tables/TableCollection.h>
#include <system/test_tools/compare.h>
#include <system/test_tools/test_tools.h>
#include <testing/test_predicates.h>

#include "ApiExampleBase.h"

using System::ArrayPtr;
using System::MakeArray;
using System::MakeObject;
using System::SharedPtr;
using System::String;

using namespace Aspose::Words;
using namespace Aspose::Words::Tables;

namespace ApiExamples {

class ExCellFormat : public ApiExampleBase
{
public:
    void VerticalMerge()
    {
        //ExStart
        //ExFor:DocumentBuilder.EndRow
        //ExFor:CellMerge
        //ExFor:CellFormat.VerticalMerge
        //ExSummary:Shows how to merge table cells vertically.
        auto doc = MakeObject<Document>();
        auto builder = MakeObject<DocumentBuilder>(doc);

        // Insert a cell into the first column of the first row.
        // This cell will be the first in a range of vertically merged cells.
        builder->InsertCell();
        builder->get_CellFormat()->set_VerticalMerge(CellMerge::First);
        builder->Write(u"Text in merged cells.");

        // Insert a cell into the second column of the first row, then end the row.
        // Also, configure the builder to disable vertical merging in created cells.
        builder->InsertCell();
        builder->get_CellFormat()->set_VerticalMerge(CellMerge::None);
        builder->Write(u"Text in unmerged cell.");
        builder->EndRow();

        // Insert a cell into the first column of the second row.
        // Instead of adding text contents, we will merge this cell with the first cell that we added directly above.
        builder->InsertCell();
        builder->get_CellFormat()->set_VerticalMerge(CellMerge::Previous);

        // Insert another independent cell in the second column of the second row.
        builder->InsertCell();
        builder->get_CellFormat()->set_VerticalMerge(CellMerge::None);
        builder->Write(u"Text in unmerged cell.");
        builder->EndRow();
        builder->EndTable();

        doc->Save(ArtifactsDir + u"CellFormat.VerticalMerge.docx");
        //ExEnd

        doc = MakeObject<Document>(ArtifactsDir + u"CellFormat.VerticalMerge.docx");
        SharedPtr<Table> table = doc->get_FirstSection()->get_Body()->get_Tables()->idx_get(0);

        ASSERT_EQ(CellMerge::First, table->get_Rows()->idx_get(0)->get_Cells()->idx_get(0)->get_CellFormat()->get_VerticalMerge());
        ASSERT_EQ(CellMerge::Previous, table->get_Rows()->idx_get(1)->get_Cells()->idx_get(0)->get_CellFormat()->get_VerticalMerge());
        ASSERT_EQ(u"Text in merged cells.", table->get_Rows()->idx_get(0)->get_Cells()->idx_get(0)->GetText().Trim(u'\a'));
        ASSERT_NE(table->get_Rows()->idx_get(0)->get_Cells()->idx_get(0)->GetText(), table->get_Rows()->idx_get(1)->get_Cells()->idx_get(0)->GetText());
    }

    void HorizontalMerge()
    {
        //ExStart
        //ExFor:CellMerge
        //ExFor:CellFormat.HorizontalMerge
        //ExSummary:Shows how to merge table cells horizontally.
        auto doc = MakeObject<Document>();
        auto builder = MakeObject<DocumentBuilder>(doc);

        // Insert a cell into the first column of the first row.
        // This cell will be the first in a range of horizontally merged cells.
        builder->InsertCell();
        builder->get_CellFormat()->set_HorizontalMerge(CellMerge::First);
        builder->Write(u"Text in merged cells.");

        // Insert a cell into the second column of the first row. Instead of adding text contents,
        // we will merge this cell with the first cell that we added directly to the left.
        builder->InsertCell();
        builder->get_CellFormat()->set_HorizontalMerge(CellMerge::Previous);
        builder->EndRow();

        // Insert two more unmerged cells to the second row.
        builder->get_CellFormat()->set_HorizontalMerge(CellMerge::None);
        builder->InsertCell();
        builder->Write(u"Text in unmerged cell.");
        builder->InsertCell();
        builder->Write(u"Text in unmerged cell.");
        builder->EndRow();
        builder->EndTable();

        doc->Save(ArtifactsDir + u"CellFormat.HorizontalMerge.docx");
        //ExEnd

        doc = MakeObject<Document>(ArtifactsDir + u"CellFormat.HorizontalMerge.docx");
        SharedPtr<Table> table = doc->get_FirstSection()->get_Body()->get_Tables()->idx_get(0);

        ASSERT_EQ(1, table->get_Rows()->idx_get(0)->get_Cells()->get_Count());
        ASSERT_EQ(CellMerge::None, table->get_Rows()->idx_get(0)->get_Cells()->idx_get(0)->get_CellFormat()->get_HorizontalMerge());
        ASSERT_EQ(u"Text in merged cells.", table->get_Rows()->idx_get(0)->get_Cells()->idx_get(0)->GetText().Trim(u'\a'));
    }

    void Padding()
    {
        //ExStart
        //ExFor:CellFormat.SetPaddings
        //ExSummary:Shows how to pad the contents of a cell with whitespace.
        auto doc = MakeObject<Document>();
        auto builder = MakeObject<DocumentBuilder>(doc);

        // Set a padding distance (in points) between the border and the text contents
        // of each table cell we create with the document builder.
        builder->get_CellFormat()->SetPaddings(5, 10, 40, 50);

        // Create a table with one cell whose contents will have whitespace padding.
        builder->StartTable();
        builder->InsertCell();
        builder->Write(String(u"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. ") +
                       u"Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.");

        doc->Save(ArtifactsDir + u"CellFormat.Padding.docx");
        //ExEnd

        doc = MakeObject<Document>(ArtifactsDir + u"CellFormat.Padding.docx");

        SharedPtr<Table> table = doc->get_FirstSection()->get_Body()->get_Tables()->idx_get(0);
        SharedPtr<Cell> cell = table->get_Rows()->idx_get(0)->get_Cells()->idx_get(0);

        ASPOSE_ASSERT_EQ(5, cell->get_CellFormat()->get_LeftPadding());
        ASPOSE_ASSERT_EQ(10, cell->get_CellFormat()->get_TopPadding());
        ASPOSE_ASSERT_EQ(40, cell->get_CellFormat()->get_RightPadding());
        ASPOSE_ASSERT_EQ(50, cell->get_CellFormat()->get_BottomPadding());
    }
};

} // namespace ApiExamples
