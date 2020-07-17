/*

   ____                               ____      ___ ____       ____  ____      ___
  6MMMMb                              `MM(      )M' `MM'      6MMMMb\`MM(      )M'
 8P    Y8                              `MM.     d'   MM      6M'    ` `MM.     d'
6M      Mb __ ____     ____  ___  __    `MM.   d'    MM      MM        `MM.   d'
MM      MM `M6MMMMb   6MMMMb `MM 6MMb    `MM. d'     MM      YM.        `MM. d'
MM      MM  MM'  `Mb 6M'  `Mb MMM9 `Mb    `MMd       MM       YMMMMb     `MMd
MM      MM  MM    MM MM    MM MM'   MM     dMM.      MM           `Mb     dMM.
MM      MM  MM    MM MMMMMMMM MM    MM    d'`MM.     MM            MM    d'`MM.
YM      M9  MM    MM MM       MM    MM   d'  `MM.    MM            MM   d'  `MM.
 8b    d8   MM.  ,M9 YM    d9 MM    MM  d'    `MM.   MM    / L    ,M9  d'    `MM.
  YMMMM9    MMYMMM9   YMMMM9 _MM_  _MM_M(_    _)MM_ _MMMMMMM MYMMMM9 _M(_    _)MM_
            MM
            MM
           _MM_

  Copyright (c) 2018, Kenneth Troldal Balslev

  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
  - Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
  - Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
  - Neither the name of the author nor the
    names of any contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */

#ifndef OPENXLSX_IMPL_XLABSTRACTXMLFILE_H
#define OPENXLSX_IMPL_XLABSTRACTXMLFILE_H

// ===== Standard Library Includes ===== //
#include <iostream>
#include <map>
#include <memory>
#include <string>

// ===== OpenXLSX Includes ===== //
#include "XLXmlData.hpp"
#include "XLXmlParser.hpp"

namespace OpenXLSX::Impl
{
    class XLDocument;

    /**
     * @brief The XLAbstractXMLFile is an pure abstract class, which provides an interface
     * for derived classes to use. It functions as an ancestor to all classes which are represented by an .xml
     * file in an .xlsx package
     */
    class XLAbstractXMLFile
    {
    public:    // ===== PUBLIC MEMBER FUNCTIONS
        /**
         * @brief Constructor. Creates an object using the parent XLDocument object, the relative file path
         * and a data object as input.
         * @param parent
         * @param filePath The path of the XML file, relative to the root.
         * @param xmlData An std::string object with the XML data to be represented by the object.
         */
        explicit XLAbstractXMLFile(XLXmlData* xmlData);

        /**
         * @brief Copy constructor. Default (shallow) implementation used.
         */
        XLAbstractXMLFile(const XLAbstractXMLFile&) = default;

        /**
         * @brief
         * @param other
         */
        XLAbstractXMLFile(XLAbstractXMLFile&& other) noexcept = default;

        /**
         * @brief Destructor. Default implementation used.
         */
        virtual ~XLAbstractXMLFile() = default;

        /**
         * @brief The assignment operator. The default implementation has been used.
         * @return A reference to the new object.
         */
        XLAbstractXMLFile& operator=(const XLAbstractXMLFile&) = default;

        /**
         * @brief
         * @param other
         * @return
         */
        XLAbstractXMLFile& operator=(XLAbstractXMLFile&& other) noexcept = default;

        /**
         * @brief
         * @return
         */
        virtual explicit operator bool() const;

        /**
         * @brief Provide the XML data represented by the object.
         * @param xmlData A std::string with the XML data.
         */
        void SetXmlData(const std::string& xmlData);

        /**
         * @brief Method for getting the XML data represented by the object.
         * @return A std::string with the XML data.
         */
        virtual std::string GetXmlData() const;

        /**
         * @brief Delete the XML file from the zipped .xlsx package.
         */
        virtual void DeleteXMLData();

        /**
         * @brief Get the path of the current file.
         * @return A string with the path of the file.
         * @note This method is final, i.e. it cannot be overridden.
         */
        virtual std::string FilePath() const final;

        /**
         * @brief
         * @return
         */
        virtual const XLDocument& ParentDoc() const final
        {
            return *m_xmlData->getParentDoc();
        }

        /**
         * @brief
         * @return
         */
        virtual XLDocument& ParentDoc() final
        {
            return *m_xmlData->getParentDoc();
        }

        /**
         * @brief
         * @return
         */
        virtual std::string getRID() const final
        {
            return m_xmlData->getXmlID();
        }

    protected:    // ===== PROTECTED MEMBER FUNCTIONS
        /**
         * @brief This method returns the underlying XMLDocument object.
         * @return A pointer to the XMLDocument object.
         * @note This method is final, i.e. it cannot be overridden.
         */
        virtual XMLDocument& XmlDocument() final;

        /**
         * @brief This method returns the underlying XMLDocument object.
         * @return A pointer to the const XMLDocument object.
         * @note This method is final, i.e. it cannot be overridden.
         */
        virtual const XMLDocument& XmlDocument() const final;

        /**
         * @brief The parseXMLData method is used to map or copy the XML data to the internal data structures.
         * @return true on success; otherwise false.
         * @note This is a pure virtual function, meaning that this must be implemented in derived classes.
         */
        virtual bool ParseXMLData() = 0;

    private:    // ===== PRIVATE MEMBER VARIABLES
        XLXmlData* m_xmlData;
    };
}    // namespace OpenXLSX::Impl

#endif    // OPENXLSX_IMPL_XLABSTRACTXMLFILE_H
