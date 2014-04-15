package com.newton449.virtualserverclient.testserver;

import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 *
 * @author Steven
 */
public class UploadTreeViewServlet extends HttpServlet {

    /**
     * Processes requests for both HTTP <code>GET</code> and <code>POST</code>
     * methods.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        try (PrintWriter out = response.getWriter()) {
            out.println("{\n"
                    + "    \"Data\": {\n"
                    + "        \"CodeRepository\": {\n"
                    + "            \"Sender\": {\n"
                    + "                \"version_1\": [\n"
                    + "                    \"file1.c\",\n"
                    + "                    \"file1.cpp\"\n"
                    + "                ],\n"
                    + "                \"version_2\": [\n"
                    + "                    \"file1.c\",\n"
                    + "                    \"file1.cpp\"\n"
                    + "                ],\n"
                    + "                \"version_3\": [\n"
                    + "                    \"file1.c\",\n"
                    + "                    \"file1.cpp\",\n"
                    + "                    \"file2.c\",\n"
                    + "                    \"file2.cpp\"\n"
                    + "                ]\n"
                    + "            },\n"
                    + "            \"Receiver\": {},\n"
                    + "            \"Channel\": {}\n"
                    + "        },\n"
                    + "        \"VirtualServer\": {\n"
                    + "            \"DataRepository\": {},\n"
                    + "            \"HttpServer\": {}\n"
                    + "        },\n"
                    + "        \"Test\": {\n"
                    + "            \"Sender\": {\n"
                    + "                \"version_1\": [],\n"
                    + "                \"version_2\": [],\n"
                    + "                \"version_3\": [],\n"
                    + "                \"version_4\": []\n"
                    + "            }\n"
                    + "        }\n"
                    + "    }\n"
                    + "}");
        }
    }

    // <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
    /**
     * Handles the HTTP <code>GET</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Handles the HTTP <code>POST</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Returns a short description of the servlet.
     *
     * @return a String containing servlet description
     */
    @Override
    public String getServletInfo() {
        return "Short description";
    }// </editor-fold>

}
/*
{
    "Data": {
        "CodeRepository": {
            "Sender": {
                "version_1": [
                    "file1.c",
                    "file1.cpp"
                ],
                "version_2": [
                    "file1.c",
                    "file1.cpp"
                ],
                "version_3": [
                    "file1.c",
                    "file1.cpp",
                    "file2.c",
                    "file2.cpp"
                ]
            },
            "Receiver": {},
            "Channel": {}
        },
        "VirtualServer": {
            "DataRepository": {},
            "HttpServer": {}
        },
        "Test": {
            "Sender": {
                "version_1": [],
                "version_2": [],
                "version_3": [],
                "version_4": []
            }
        }
    }
}
*/
