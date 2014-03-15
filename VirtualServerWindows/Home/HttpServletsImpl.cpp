#include "HttpServletsImpl.h"
#include "../interfaces/ILogger.h"

void RedirectToHomeServlet::doMethod(IHttpServletRequest& request, IHttpServletResponse& response){
	response.setStatus(302);
	response.addHeader("Location", "/home/");
	// PENDING In HTTP documents:
	// "Unless the request method was HEAD, the entity of the response SHOULD contain a short hypertext note with a hyperlink to the new URI(s)."
}

void MenuListServlet::doMethod(IHttpServletRequest& request, IHttpServletResponse& response){
	// TODO design
	LOG(INFO) << "Module can log!";
	response.getOutputStream()
		<< "{"
		<< "  \"menu\":"
		<< "    ["
		<< "      { \"name\": \"Home\", \"url\": \"/home/#\" }, "
		<< "      { \"name\": \"Clone\", \"url\": \"/installer/#\", \"title\": \"Create a local server in your machine.\" }, "
		<< "      { \"name\": \"About\", \"url\": \"/home/#about\" } "
		<< "    ]"
		<< "}";
}