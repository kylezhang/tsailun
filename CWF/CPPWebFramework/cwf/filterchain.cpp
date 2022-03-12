/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "filterchain.h"
#include "configuration.h"
#include "constants.h"

CWF_BEGIN_NAMESPACE

FilterChain::FilterChain(Controller *controller, const Configuration &configuration) :  controller(controller), configuration(configuration)
{
}

void FilterChain::doFilter(CWF::Request &request, CWF::Response &response)
{
    if(controller != nullptr)
    {
        const HttpParser &parser = request.getHttpParser();
        if(parser.getMethod()      == HTTP::METHOD::GET)
            controller->doGet(request, response);
        else if(parser.getMethod() == HTTP::METHOD::POST)
            controller->doPost(request, response);
        else if(parser.getMethod() == HTTP::METHOD::PUT)
            controller->doPut(request, response);
        else if(parser.getMethod() == HTTP::METHOD::DELETE)
            controller->doDelete(request, response);
        else if(parser.getMethod() == HTTP::METHOD::OPTIONS)
            controller->doOptions(request, response);
        else if(parser.getMethod() == HTTP::METHOD::TRACE)
            controller->doTrace(request, response);
    }
    else
    {
        QString url  = request.getRequestURL();
        QString path = request.getPath();
        const QString &extention = CWF::FileManager::fileExtention(url);

        if(url == FILE_EXTENTION::BAR)
        {
            request.getRequestDispatcher(configuration.getIndexPage()).forward(request, response);
        }
        else if(extention == FILE_EXTENTION::HTML || extention == FILE_EXTENTION::HTM)
        {
			response.write_file(request, path + url, HTTP::TEXT_HTML_UTF8);
        }
        else if(extention == FILE_EXTENTION::CSS || extention == FILE_EXTENTION::TXT || extention == FILE_EXTENTION::PHP)
        {
			response.write_file(request, path + url, ("text/" + extention.toLatin1() + "; charset=UTF-8"));
        }
        else if(extention == FILE_EXTENTION::ICO)
        {
			response.write_file(request, path + url, HTTP::IMAGE_MICROSOFT_ICO);
        }
        else if(extention == FILE_EXTENTION::PNG || extention == FILE_EXTENTION::GIF || extention == FILE_EXTENTION::BMP)
        {
			response.write_file(request, path + url, ("image/" + extention.toLatin1()));
        }
        else if(extention == FILE_EXTENTION::JPE || extention == FILE_EXTENTION::JPG)
        {
			response.write_file(request, path + url, HTTP::IMAGE_JPEG);
        }
        else if(extention == FILE_EXTENTION::TIFF || extention == FILE_EXTENTION::TIF)
        {
			response.write_file(request, path + url, HTTP::IMAGE_TIFF);
        }
        else if(extention == FILE_EXTENTION::SVG || extention == FILE_EXTENTION::SVGZ)
        {
			response.write_file(request, path + url, HTTP::IMAGE_SVG_XML);
        }
        else if(extention == FILE_EXTENTION::PDF  || extention == FILE_EXTENTION::XML ||
                extention == FILE_EXTENTION::JSON || extention == FILE_EXTENTION::ZIP)
        {
			response.write_file(request, path + url, ("application/" + extention.toLatin1()));
        }
        else if(extention == FILE_EXTENTION::MP3)
        {
			response.write_file(request, path + url, HTTP::AUDIO_MP3);
        }
        else if(extention == FILE_EXTENTION::MP4)
        {
			response.write_file(request, path + url, HTTP::AUDIO_MP4);
        }
        else if(extention == FILE_EXTENTION::FLV)
        {
			response.write_file(request, path + url, HTTP::VIDEO_FLV);
        }
        else if(extention == FILE_EXTENTION::DOC)
        {
			response.write_file(request, path + url, HTTP::APPLICATION_MSWORD);
        }
        else if(extention == FILE_EXTENTION::RTF)
        {
			response.write_file(request, path + url, HTTP::APPLICATION_RTF);
        }
        else if(extention == FILE_EXTENTION::XLS)
        {
			response.write_file(request, path + url, HTTP::APPLICATION_EXCEL);
        }
        else if(extention == FILE_EXTENTION::PPT)
        {
			response.write_file(request, path + url, HTTP::APPLICATION_POWER_POINT);
        }
        else if(extention == FILE_EXTENTION::JS)
        {
			response.write_file(request, path + url, HTTP::APPLICATION_JAVASCRIPT);
        }
        else if(extention == FILE_EXTENTION::ODT)
        {
			response.write_file(request, path + url, HTTP::APPLICATION_OPEN_DOCUMENT_TEXT);
        }
        else if(extention == FILE_EXTENTION::ODS)
        {
			response.write_file(request, path + url, HTTP::APPLICATION_OPEN_DOCUMENT_SPREADSHEET);
        }
        else if(extention == FILE_EXTENTION::SWF)
        {
			response.write_file(request, path + url, HTTP::APPLICATION_SHOCKWAVE_FLASH);
        }
        else if(extention == FILE_EXTENTION::RAR)
        {
			response.write_file(request, path + url, HTTP::APPLICATION_RAR_COMPRESSED);
        }
        else if(extention == FILE_EXTENTION::EXE || extention == FILE_EXTENTION::MSI)
        {
			response.write_file(request, path + url, HTTP::APPLICATION_MS_DOWNLOAD);
        }
        else if(extention == FILE_EXTENTION::CAB)
        {
			response.write_file(request, path + url, HTTP::APPLICATION_CAB_COMPRESSED);
        }
        else if(extention == FILE_EXTENTION::PSD)
        {
			response.write_file(request, path + url, HTTP::APPLICATION_PHOTOSHOP);
        }
        else if(extention == FILE_EXTENTION::AI || extention == FILE_EXTENTION::EPS ||
                extention == FILE_EXTENTION::PS)
        {
			response.write_file(request, path + url, HTTP::APPLICATION_POSTSCRIPT);
        }
        else if (extention == FILE_EXTENTION::WOFF || extention == FILE_EXTENTION::WOFF2)
        {
			response.write_file(request, path + url, HTTP::APPLICATION_FONT_WOFF);
        }
        else if (extention == FILE_EXTENTION::EOT || extention == FILE_EXTENTION::TTF)
        {
			response.write_file(request, path + url, HTTP::APPLICATION_FONT_TTF);
        }
    //    else if(extention == FILE_EXTENTION::INI)
    //    {
    //        QString file(CWF::FileManager::fileName(url));
    //        if(file != CONFIGURATION::CPP_WEB_INI)
				//response.write_file(request, path + url, ("text/" + extention.toLatin1() + "; charset=UTF-8"));
    //        else if(configuration.getAccessServerPages())
				//response.write_file(request, path + url, ("text/" + extention.toLatin1() + "; charset=UTF-8"));
    //        else
    //            request.getRequestDispatcher(STATUS::STATUS_401).forward(request, response);
    //    }
        else
        {
			//write_NoType(response, path, url);
			response.write_file(request, path + url);
			/*
            response.setStatus(Response::SC_NOT_FOUND, STATUS::NOT_FOUND);
            response.addHeader("Content-Type; charset=UTF-8", "text/html");
            request.getRequestDispatcher(STATUS::STATUS_404).forward(request, response);
			*/
        }
    }
}

/*
void FilterChain::write(Response &response, const QString &path, const QString &url, const QByteArray &name, const QByteArray &value) const
{
    QFile file(path + url);
    if(file.open(QIODevice::ReadOnly))
    {
        response.addHeader(name, value);
        response.write(file.readAll());
    }
    else
    {
        response.sendError(0, file.errorString().toLatin1());
    }
}

void FilterChain::write_NoType(Response &response, const QString &path, const QString &url) const
{
	QFile file(path + url);
	if (file.open(QIODevice::ReadOnly))
	{
		//response.addHeader(name, value);
		response.write(file.readAll());
	}
	else
	{
		response.sendError(0, file.errorString().toLatin1());
	}
}
*/

CWF_END_NAMESPACE
