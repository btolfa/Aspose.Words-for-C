﻿#pragma once
// Copyright (c) 2001-2021 Aspose Pty Ltd. All Rights Reserved.
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////

#include <Aspose.Words.Cpp/License.h>
#include <system/details/dispose_guard.h>
#include <system/io/file.h>
#include <system/io/file_stream.h>
#include <system/io/path.h>
#include <system/io/stream.h>

#include "ApiExampleBase.h"

using System::ArrayPtr;
using System::MakeArray;
using System::MakeObject;
using System::SharedPtr;
using System::String;

using namespace Aspose::Words;

namespace ApiExamples {

class ExLicense : public ApiExampleBase
{
public:
    void LicenseFromFileNoPath()
    {
        //ExStart
        //ExFor:License
        //ExFor:License.#ctor
        //ExFor:License.SetLicense(String)
        //ExSummary:Shows how initialize a license for Aspose.Words using a license file in the local file system.
        // Set the license for our Aspose.Words product by passing the local file system filename of a valid license file.
        String licenseFileName = System::IO::Path::Combine(LicenseDir, u"Aspose.Words.Cpp.lic");

        auto license = MakeObject<License>();
        license->SetLicense(licenseFileName);

        // Create a copy of our license file in the binaries folder of our application.
        String licenseCopyFileName = System::IO::Path::Combine(AssemblyDir, u"Aspose.Words.Cpp.lic");
        System::IO::File::Copy(licenseFileName, licenseCopyFileName);

        // If we pass a file's name without a path,
        // the SetLicense will search several local file system locations for this file.
        // One of those locations will be the "bin" folder, which contains a copy of our license file.
        license->SetLicense(u"Aspose.Words.Cpp.lic");
        //ExEnd

        license->SetLicense(u"");
        System::IO::File::Delete(licenseCopyFileName);
    }

    void LicenseFromStream()
    {
        //ExStart
        //ExFor:License.SetLicense(Stream)
        //ExSummary:Shows how to initialize a license for Aspose.Words from a stream.
        // Set the license for our Aspose.Words product by passing a stream for a valid license file in our local file system.
        {
            SharedPtr<System::IO::Stream> myStream = System::IO::File::OpenRead(System::IO::Path::Combine(LicenseDir, u"Aspose.Words.Cpp.lic"));
            auto license = MakeObject<License>();
            license->SetLicense(myStream);
        }
        //ExEnd
    }
};

} // namespace ApiExamples
