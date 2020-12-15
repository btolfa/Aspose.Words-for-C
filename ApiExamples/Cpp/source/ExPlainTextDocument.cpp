﻿// Copyright (c) 2001-2020 Aspose Pty Ltd. All Rights Reserved.
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
#include "ExPlainTextDocument.h"

namespace ApiExamples { namespace gtest_test {

class ExPlainTextDocument : public ::testing::Test
{
protected:
    static System::SharedPtr<::ApiExamples::ExPlainTextDocument> s_instance;

    void SetUp() override
    {
        s_instance->SetUp();
    };

    static void SetUpTestCase()
    {
        s_instance = System::MakeObject<::ApiExamples::ExPlainTextDocument>();
        s_instance->OneTimeSetUp();
    };

    static void TearDownTestCase()
    {
        s_instance->OneTimeTearDown();
        s_instance = nullptr;
    };
};

System::SharedPtr<::ApiExamples::ExPlainTextDocument> ExPlainTextDocument::s_instance;

TEST_F(ExPlainTextDocument, Load)
{
    s_instance->Load();
}

TEST_F(ExPlainTextDocument, LoadWithOptions)
{
    s_instance->LoadWithOptions();
}

TEST_F(ExPlainTextDocument, LoadFromStream)
{
    s_instance->LoadFromStream();
}

TEST_F(ExPlainTextDocument, LoadFromStreamWithOptions)
{
    s_instance->LoadFromStreamWithOptions();
}

TEST_F(ExPlainTextDocument, BuiltInProperties)
{
    s_instance->BuiltInProperties();
}

TEST_F(ExPlainTextDocument, CustomDocumentProperties)
{
    s_instance->CustomDocumentProperties_();
}

}} // namespace ApiExamples::gtest_test
