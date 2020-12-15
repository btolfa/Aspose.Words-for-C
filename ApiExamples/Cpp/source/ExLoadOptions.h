﻿#pragma once
// Copyright (c) 2001-2020 Aspose Pty Ltd. All Rights Reserved.
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <iostream>
#include <Aspose.Words.Cpp/Model/Document/Document.h>
#include <Aspose.Words.Cpp/Model/Document/EditingLanguage.h>
#include <Aspose.Words.Cpp/Model/Document/FileFormatInfo.h>
#include <Aspose.Words.Cpp/Model/Document/FileFormatUtil.h>
#include <Aspose.Words.Cpp/Model/Document/IWarningCallback.h>
#include <Aspose.Words.Cpp/Model/Document/LanguagePreferences.h>
#include <Aspose.Words.Cpp/Model/Document/LoadOptions.h>
#include <Aspose.Words.Cpp/Model/Document/SaveFormat.h>
#include <Aspose.Words.Cpp/Model/Document/WarningInfo.h>
#include <Aspose.Words.Cpp/Model/Document/WarningSource.h>
#include <Aspose.Words.Cpp/Model/Document/WarningType.h>
#include <Aspose.Words.Cpp/Model/Fonts/FontSettings.h>
#include <Aspose.Words.Cpp/Model/Fonts/FontSubstitutionSettings.h>
#include <Aspose.Words.Cpp/Model/Fonts/TableSubstitutionRule.h>
#include <Aspose.Words.Cpp/Model/Loading/IResourceLoadingCallback.h>
#include <Aspose.Words.Cpp/Model/Loading/ResourceLoadingAction.h>
#include <Aspose.Words.Cpp/Model/Loading/ResourceLoadingArgs.h>
#include <Aspose.Words.Cpp/Model/Loading/ResourceType.h>
#include <Aspose.Words.Cpp/Model/Nodes/NodeCollection.h>
#include <Aspose.Words.Cpp/Model/Nodes/NodeType.h>
#include <Aspose.Words.Cpp/Model/Saving/SaveOutputParameters.h>
#include <Aspose.Words.Cpp/Model/Settings/MsWordVersion.h>
#include <Aspose.Words.Cpp/Model/Styles/StyleCollection.h>
#include <Aspose.Words.Cpp/Model/Text/Font.h>
#include <Aspose.Words.Cpp/Model/Text/ParagraphFormat.h>
#include <drawing/image.h>
#include <drawing/image_converter.h>
#include <system/array.h>
#include <system/collections/list.h>
#include <system/enum.h>
#include <system/enum_helpers.h>
#include <system/exceptions.h>
#include <system/io/directory.h>
#include <system/object_ext.h>
#include <system/test_tools/compare.h>
#include <system/test_tools/method_argument_tuple.h>
#include <system/test_tools/test_tools.h>
#include <system/text/encoding.h>
#include <testing/test_predicates.h>

#include "ApiExampleBase.h"

using System::String;
using System::SharedPtr;
using System::ArrayPtr;
using System::MakeObject;
using System::MakeArray;

using namespace Aspose::Words;
using namespace Aspose::Words::Fonts;
using namespace Aspose::Words::Loading;
using namespace Aspose::Words::Settings;

namespace ApiExamples {

class ExLoadOptions : public ApiExampleBase
{
public:
    //ExStart
    //ExFor:LoadOptions.ResourceLoadingCallback
    //ExSummary:Shows how to handle external resources when loading Html documents.
    void LoadOptionsCallback()
    {
        auto loadOptions = MakeObject<LoadOptions>();
        loadOptions->set_ResourceLoadingCallback(MakeObject<ExLoadOptions::HtmlLinkedResourceLoadingCallback>());

        // When we load the document, our callback will handle linked resources such as CSS stylesheets and images.
        auto doc = MakeObject<Document>(MyDir + u"Images.html", loadOptions);
        doc->Save(ArtifactsDir + u"LoadOptions.LoadOptionsCallback.pdf");
    }

private:
    /// <summary>
    /// Prints the filenames of all external stylesheets, and substitutes all images of a loaded html document.
    /// </summary>
    class HtmlLinkedResourceLoadingCallback : public IResourceLoadingCallback
    {
    public:
        ResourceLoadingAction ResourceLoading(SharedPtr<ResourceLoadingArgs> args) override
        {
            switch (args->get_ResourceType())
            {
            case ResourceType::CssStyleSheet:
                std::cout << "External CSS Stylesheet found upon loading: " << args->get_OriginalUri() << std::endl;
                return ResourceLoadingAction::Default;

            case ResourceType::Image: {
                std::cout << "External Image found upon loading: " << args->get_OriginalUri() << std::endl;
                const String newImageFilename = u"Logo.jpg";
                std::cout << "\tImage will be substituted with: " << newImageFilename << std::endl;
                SharedPtr<System::Drawing::Image> newImage = System::Drawing::Image::FromFile(ImageDir + newImageFilename);
                auto converter = MakeObject<System::Drawing::ImageConverter>();
                ArrayPtr<uint8_t> imageBytes =
                    System::DynamicCast<System::Array<uint8_t>>(converter->ConvertTo(newImage, System::ObjectExt::GetType<System::Array<uint8_t>>()));
                args->SetData(imageBytes);
                return ResourceLoadingAction::UserProvided;
            }

            default:
                break;
            }

            return ResourceLoadingAction::Default;
        }
    };
    //ExEnd

public:
    void ConvertShapeToOfficeMath(bool isConvertShapeToOfficeMath)
    {
        //ExStart
        //ExFor:LoadOptions.ConvertShapeToOfficeMath
        //ExSummary:Shows how to convert EquationXML shapes to Office Math objects.
        auto loadOptions = MakeObject<LoadOptions>();

        // Use this flag to specify whether to convert the shapes with EquationXML attributes
        // to Office Math objects and then load the document.
        loadOptions->set_ConvertShapeToOfficeMath(isConvertShapeToOfficeMath);

        auto doc = MakeObject<Document>(MyDir + u"Math shapes.docx", loadOptions);

        if (isConvertShapeToOfficeMath)
        {
            ASSERT_EQ(16, doc->GetChildNodes(NodeType::Shape, true)->get_Count());
            ASSERT_EQ(34, doc->GetChildNodes(NodeType::OfficeMath, true)->get_Count());
        }
        else
        {
            ASSERT_EQ(24, doc->GetChildNodes(NodeType::Shape, true)->get_Count());
            ASSERT_EQ(0, doc->GetChildNodes(NodeType::OfficeMath, true)->get_Count());
        }
        //ExEnd
    }

    void SetEncoding()
    {
        //ExStart
        //ExFor:LoadOptions.Encoding
        //ExSummary:Shows how to set the encoding with which to open a document.
        // A FileFormatInfo object will detect this file as being encoded in something other than UTF-7.
        SharedPtr<FileFormatInfo> fileFormatInfo = FileFormatUtil::DetectFileFormat(MyDir + u"Encoded in UTF-7.txt");

        ASPOSE_ASSERT_NE(System::Text::Encoding::get_UTF7(), fileFormatInfo->get_Encoding());

        // If we load the document with no loading configurations, Aspose.Words will detect its encoding as UTF-8.
        auto doc = MakeObject<Document>(MyDir + u"Encoded in UTF-7.txt");

        // The contents, parsed in UTF-8, create a valid string.
        // However, knowing that the file is in UTF-7, we can see that the result is incorrect.
        ASSERT_EQ(u"Hello world+ACE-", doc->ToString(SaveFormat::Text).Trim());

        // In cases of ambiguous encoding such as this one, we can set a specific encoding variant
        // to parse the file within a LoadOptions object.
        auto loadOptions = MakeObject<LoadOptions>();
        loadOptions->set_Encoding(System::Text::Encoding::get_UTF7());

        // Load the document while passing the LoadOptions object, then verify the document's contents.
        doc = MakeObject<Document>(MyDir + u"Encoded in UTF-7.txt", loadOptions);

        ASSERT_EQ(u"Hello world!", doc->ToString(SaveFormat::Text).Trim());
        //ExEnd
    }

    void FontSettings_()
    {
        //ExStart
        //ExFor:LoadOptions.FontSettings
        //ExSummary:Shows how to apply font substitution settings while loading a document.
        // Create a FontSettings object that will substitute the "Times New Roman" font
        // with the font "Arvo" from our "MyFonts" folder.
        auto fontSettings = MakeObject<FontSettings>();
        fontSettings->SetFontsFolder(FontsDir, false);
        fontSettings->get_SubstitutionSettings()->get_TableSubstitution()->AddSubstitutes(u"Times New Roman", MakeArray<String>({u"Arvo"}));

        // Set that FontSettings object as a member of a newly created LoadOptions object.
        auto loadOptions = MakeObject<LoadOptions>();
        loadOptions->set_FontSettings(fontSettings);

        // Load the document, then render it as a PDF with the font substitution.
        auto doc = MakeObject<Document>(MyDir + u"Document.docx", loadOptions);

        doc->Save(ArtifactsDir + u"LoadOptions.FontSettings.pdf");
        //ExEnd
    }

    void LoadOptionsMswVersion()
    {
        //ExStart
        //ExFor:LoadOptions.MswVersion
        //ExSummary:Shows how to emulate the loading procedure of a specific Microsoft Word version during document loading.
        // By default, Aspose.Words loads documents according to Microsoft Word 2019 specification.
        auto loadOptions = MakeObject<LoadOptions>();

        ASSERT_EQ(MsWordVersion::Word2019, loadOptions->get_MswVersion());

        // This document is missing the default paragraph formatting style.
        // This default style will be regenerated when we load the document either with Microsoft Word or Aspose.Words.
        loadOptions->set_MswVersion(MsWordVersion::Word2007);
        auto doc = MakeObject<Document>(MyDir + u"Document.docx", loadOptions);

        // The style's line spacing will have this value when loaded by Microsoft Word 2007 specification.
        ASSERT_NEAR(12.95, doc->get_Styles()->get_DefaultParagraphFormat()->get_LineSpacing(), 0.01);
        //ExEnd
    }

    //ExStart
    //ExFor:LoadOptions.WarningCallback
    //ExSummary:Shows how to print and store warnings that occur during document loading.
    void LoadOptionsWarningCallback()
    {
        // Create a new LoadOptions object and set its WarningCallback attribute
        // as an instance of our IWarningCallback implementation.
        auto loadOptions = MakeObject<LoadOptions>();
        loadOptions->set_WarningCallback(MakeObject<ExLoadOptions::DocumentLoadingWarningCallback>());

        // Warnings that occur during the loading of the document will now be printed and stored.
        auto doc = MakeObject<Document>(MyDir + u"Document.docx", loadOptions);

        SharedPtr<System::Collections::Generic::List<SharedPtr<WarningInfo>>> warnings =
            (System::StaticCast<ApiExamples::ExLoadOptions::DocumentLoadingWarningCallback>(loadOptions->get_WarningCallback()))->GetWarnings();
        ASSERT_EQ(3, warnings->get_Count());
        TestLoadOptionsWarningCallback(warnings);
        //ExSkip
    }

private:
    /// <summary>
    /// IWarningCallback that prints warnings and their details as they arise during document loading.
    /// </summary>
    class DocumentLoadingWarningCallback : public IWarningCallback
    {
    public:
        void Warning(SharedPtr<WarningInfo> info) override
        {
            std::cout << String::Format(u"Warning: {0}", info->get_WarningType()) << std::endl;
            std::cout << String::Format(u"\tSource: {0}", info->get_Source()) << std::endl;
            std::cout << "\tDescription: " << info->get_Description() << std::endl;
            mWarnings->Add(info);
        }

        SharedPtr<System::Collections::Generic::List<SharedPtr<WarningInfo>>> GetWarnings()
        {
            return mWarnings;
        }

        DocumentLoadingWarningCallback() : mWarnings(MakeObject<System::Collections::Generic::List<SharedPtr<WarningInfo>>>())
        {
        }

    private:
        SharedPtr<System::Collections::Generic::List<SharedPtr<WarningInfo>>> mWarnings;
    };
    //ExEnd

protected:
    static void TestLoadOptionsWarningCallback(SharedPtr<System::Collections::Generic::List<SharedPtr<WarningInfo>>> warnings)
    {
        ASSERT_EQ(WarningType::UnexpectedContent, warnings->idx_get(0)->get_WarningType());
        ASSERT_EQ(WarningSource::Docx, warnings->idx_get(0)->get_Source());
        ASSERT_EQ(u"3F01", warnings->idx_get(0)->get_Description());

        ASSERT_EQ(WarningType::MinorFormattingLoss, warnings->idx_get(1)->get_WarningType());
        ASSERT_EQ(WarningSource::Docx, warnings->idx_get(1)->get_Source());
        ASSERT_EQ(u"Import of element 'shapedefaults' is not supported in Docx format by Aspose.Words.", warnings->idx_get(1)->get_Description());

        ASSERT_EQ(WarningType::MinorFormattingLoss, warnings->idx_get(2)->get_WarningType());
        ASSERT_EQ(WarningSource::Docx, warnings->idx_get(2)->get_Source());
        ASSERT_EQ(u"Import of element 'extraClrSchemeLst' is not supported in Docx format by Aspose.Words.", warnings->idx_get(2)->get_Description());
    }

public:
    void TempFolder()
    {
        //ExStart
        //ExFor:LoadOptions.TempFolder
        //ExSummary:Shows how to use the hard drive instead of memory when loading a document.
        // When we load a document, various elements are temporarily stored in memory as the save operation is taking place.
        // We can use this option to use a temporary folder in the local file system instead,
        // which will reduce our application's memory overhead.
        auto options = MakeObject<LoadOptions>();
        options->set_TempFolder(ArtifactsDir + u"TempFiles");

        // The specified temporary folder must exist in the local file system before the load operation.
        System::IO::Directory::CreateDirectory_(options->get_TempFolder());

        auto doc = MakeObject<Document>(MyDir + u"Document.docx", options);

        // The folder will persist with no residual contents from the load operation.
        ASSERT_EQ(0, System::IO::Directory::GetFiles(options->get_TempFolder())->get_Length());
        //ExEnd
    }

    void AddEditingLanguage()
    {
        //ExStart
        //ExFor:LanguagePreferences
        //ExFor:LanguagePreferences.AddEditingLanguage(EditingLanguage)
        //ExFor:LoadOptions.LanguagePreferences
        //ExFor:EditingLanguage
        //ExSummary:Shows how to apply language preferences when loading a document.
        auto loadOptions = MakeObject<LoadOptions>();
        loadOptions->get_LanguagePreferences()->AddEditingLanguage(EditingLanguage::Japanese);

        auto doc = MakeObject<Document>(MyDir + u"No default editing language.docx", loadOptions);

        int localeIdFarEast = doc->get_Styles()->get_DefaultFont()->get_LocaleIdFarEast();
        std::cout << (localeIdFarEast == (int)EditingLanguage::Japanese
                          ? String(u"The document either has no any FarEast language set in defaults or it was set to Japanese originally.")
                          : String(
                                u"The document default FarEast language was set to another than Japanese language originally, so it is not overridden."))
                  << std::endl;
        //ExEnd

        ASSERT_EQ((int)EditingLanguage::Japanese, doc->get_Styles()->get_DefaultFont()->get_LocaleIdFarEast());

        doc = MakeObject<Document>(MyDir + u"No default editing language.docx");

        ASSERT_EQ((int)EditingLanguage::EnglishUS, doc->get_Styles()->get_DefaultFont()->get_LocaleIdFarEast());
    }

    void SetEditingLanguageAsDefault()
    {
        //ExStart
        //ExFor:LanguagePreferences.DefaultEditingLanguage
        //ExSummary:Shows how set a default language when loading a document.
        auto loadOptions = MakeObject<LoadOptions>();
        loadOptions->get_LanguagePreferences()->set_DefaultEditingLanguage(EditingLanguage::Russian);

        auto doc = MakeObject<Document>(MyDir + u"No default editing language.docx", loadOptions);

        int localeId = doc->get_Styles()->get_DefaultFont()->get_LocaleId();
        std::cout << (localeId == (int)EditingLanguage::Russian
                          ? String(u"The document either has no any language set in defaults or it was set to Russian originally.")
                          : String(u"The document default language was set to another than Russian language originally, so it is not overridden."))
                  << std::endl;
        //ExEnd

        ASSERT_EQ((int)EditingLanguage::Russian, doc->get_Styles()->get_DefaultFont()->get_LocaleId());

        doc = MakeObject<Document>(MyDir + u"No default editing language.docx");

        ASSERT_EQ((int)EditingLanguage::EnglishUS, doc->get_Styles()->get_DefaultFont()->get_LocaleId());
    }
};

} // namespace ApiExamples
