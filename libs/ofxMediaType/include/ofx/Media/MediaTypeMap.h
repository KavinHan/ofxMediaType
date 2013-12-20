// =============================================================================
//
// Copyright (c) 2009-2013 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#pragma once


#include <sstream>
#include <string>
#include <map>
#include "Poco/File.h"
#include "Poco/Mutex.h"
#include "Poco/Path.h"
#include "Poco/StringTokenizer.h"
#include "Poco/Net/MediaType.h"
#include "ofx/Media/BaseMediaTypeProvider.h"


namespace ofx {
namespace Media {


class MediaTypeMap: public BaseMediaTypeProvider
    // MediaTypeMap is a class that attempts to return MIME Type information for
    // a given file using the file's suffix.  The default functionality loads
    // an Apache mime.types file to create the database.  Database entries can
    // also be added and removed manually.
{
public:
    typedef std::shared_ptr<MediaTypeMap> SharedPtr;
        ///< A shared pointer typedef.

    typedef std::map<std::string,Poco::Net::MediaType> FileSuffixToMediaTypeMap;
        ///< A map of file suffix keys and their MIME type values.

    typedef FileSuffixToMediaTypeMap::const_iterator ConstIterator;
        ///< A const iterator for the FileSuffixToMediaTypeMap type.

    MediaTypeMap();
        ///< Create a default MediaType map.
    MediaTypeMap(const std::string& mimeTypesFile);
        ///< Create a default MediaType map with the given
        ///< Apache mime.types file location.

    MediaTypeMap(const std::string& mimeTypesFile,
                 const std::string& defaultMediaType);
        ///< Create a default MediaType map with the given
        ///< Apache mime.types file location and the default media
        ///< type to be used for unrecognized files.

    virtual ~MediaTypeMap();
        ///< Destroy the MediaTypeMap.

    Poco::Net::MediaType getMediaTypeForPath(const Poco::Path& path) const;
        ///< Returns the MediaType for the given path.

    std::string getMediaDescription(const Poco::Path& path, bool bExamineCompressed) const;
        ///< Returns the MediaType for the given path.

    void add(const std::string& suffix, const Poco::Net::MediaType& mediaType);
        ///< Add an entry to the media type database where `suffix` is the
        ///< key and `mediaType` is the associated MediaType.

    void load(std::istream& inputStream);
        ///< Load an Apache mime.types file from the given input stream.

    void clear();
        ///< Remove all entries from the loaded mime types map database.

    Poco::Net::MediaType getDefaultMediaType() const;
        ///< Returns the default media type.  Usually `application/octet-stream`

    void setDefaultMediaType(const Poco::Net::MediaType& defaultMediaType);
        ///< Sets the default media type used for unmatched file suffixes.

    static SharedPtr getDefault()
        ///< Get a the default instance of the MediaTypeMap.
    {
        static SharedPtr ptr = SharedPtr(new MediaTypeMap());
        return ptr;
    }

    static FileSuffixToMediaTypeMap parse(std::istream& inputStream);
        ///< Parse Apache mime.types files and return the corresponding
        ///< FileSuffixToMediaTypeMap.

    static const std::string DEFAULT_MEDIA_TYPE;
        ///< The default MIME type used for unmatched files.

    static const std::string DEFAULT_APACHE_MIME_TYPES_PATH;
        ///< The default path location for the Apache mime types file.

private:
    FileSuffixToMediaTypeMap _map;
    Poco::Net::MediaType _defaultMediaType;

};


} } // namespace ofx::Media
